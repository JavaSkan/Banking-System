function AddEmpl(){
    let ID=document.getElementById("IDInput").value;
    let name=document.getElementById("nameInput").value;
    let last=document.getElementById("lastnameInput").value;
    let address=document.getElementById("adressInput").value;
    let salary=document.getElementById("salaryInput").value;

    info=ID+"*"+name+"*"+last+"*"+address+"*"+salary;
    sendRegEmplInfo(info).then((answer)=>{
        console.log(answer);
    })
}
function getLoggedEmployee(){
    let space_id=document.getElementById("EmpID");
    let space_name=document.getElementById("EmpName");
    getLoggedEmployeeInfoCPP().then((reply) =>{
        const [id,name]=reply.data.split('*')
        space_id.innerText=id;
        space_name.innerText=name;
    })
}

function EmplLogin(){
    let ID=document.getElementById("employee_ID").value;
    let password=document.getElementById("password").value;
    EmplLoginCPP(ID+"*"+password).then((answer)=>{
        if(answer=="false"){
            alert("moch mawjoud");
        }else if(answer=="falseP"){
            alert("mdp ghlt");
        }else{
            goToPage('EmployeeInterface.html');
        }
    });
}

function acceptLoanRequest(loanReqCompId){
    let comp = document.getElementById(loanReqCompId);
    let amount = comp.children[1].children[1].value;
    amount = amount.subtring(0,amount.indexOf(' '));
    let sent_data = comp.children[5].innerHTML+'*' //customer ID
                    +amount+'*' //amount without ' TND'
                    +comp.children[2].children[1].value; //type (string representation)
    sendAcceptedLoanReq(sent_data).then(
        (reply) => {
            console.log("C++ replied:"+reply);
        }
    );
    comp.remove();
}

function declineLoanRequest(loanReqCompId){
    document.getElementById(loanReqCompId).remove();
    if(document.getElementsByClassName("loanReqComp").length == 0){
        let no_lq = document.createElement("p");
        no_lq.id = "noLQ";
        no_lq.innerHTML = "No Loan Requests";
        document.getElementById("mainEmpInt").appendChild(no_lq);
    }
}

/* 
Return a Loan Request Component (HTML element) from a string in JSON format
*/
function getLoanReqComponent(lrs){
    const compononent = document.createElement("div");
    compononent.id = lrs.ID_cus;
    compononent.classList.add("loanReqComp");

    const header = document.createElement("div");
    header.classList.add("loanReqHeader");
    header.innerHTML = `Loan Request By User ${lrs.ID_cus}`;

    const amount = document.createElement("div");
    amount.classList.add("loanReqField");
    amount.innerHTML = `
        <div class="loanReqFieldLabel">Amount:</div>
        <p class="loanReqFieldValue"> ${lrs.amount} TND </p>
    `;

    const type_ = document.createElement("div");
    type_.classList.add("loanReqField");
    type_.innerHTML = `
        <div class="loanReqFieldLabel">Type:</div>
        <p class="loanReqFieldValue"> ${lrs.type} </p>
    `;

    const accept_but = document.createElement("button");
    accept_but.type = "button";
    accept_but.innerText = "Accept";
    accept_but.id = "acceptBtn";
    accept_but.setAttribute("onclick",`acceptLoanRequest('${lrs.ID_cus}')`);

    const decline_but = document.createElement("button");
    decline_but.type = "button";
    decline_but.innerText = "Decile";
    decline_but.id = "declineBtn";
    decline_but.setAttribute("onclick",`declineLoanRequest('${lrs.ID_cus}')`);

    const cus_ID_footer = document.createElement("p");
    cus_ID_footer.classList.add("loanReqFooter");
    cus_ID_footer.innerText = lrs.ID_cus;

    compononent.appendChild(header);
    compononent.appendChild(amount);
    compononent.appendChild(type_);
    compononent.appendChild(accept_but);
    compononent.appendChild(decline_but);
    compononent.appendChild(cus_ID_footer);
    return compononent;
}

//CPP will send Loan Requests One by one by creating a cpp
//function, so that we can use the FIFO system mentionned in
//the project PDF
function displayLoanRequests(){
    let mainEmpInt = document.getElementById("mainEmpInt");
    mainEmpInt.innerHTML="";
    receiveQueueSize().then(
        //LoanRequests: LoanReq_1|...|LoanReq_N
        (queue_size_JSON) => {
            let size = parseInt(queue_size_JSON.size);
            if(size == 0){
                if(document.getElementById("noLQ") == null){
                    let no_lq = document.createElement("p");
                    no_lq.id = "noLQ";
                    no_lq.innerHTML = "No Loan Requests";
                    mainEmpInt.appendChild(no_lq);
                }  
            }
            for(let i = 0; i < size; i++){
                receiveCurrentLoanReq().then(
                    (loanReqStr) => {
                        mainEmpInt.appendChild(getLoanReqComponent(loanReqStr));
                    }
                )
            }
        }
    );
}

function escapeHtml(s) {
    if (s == null) return "";
    return String(s)
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#39;");
}

function viewAllCustomers() {
    const main = document.getElementById("mainEmpInt");
    main.innerHTML = "";

    const container = document.createElement("div");
    container.classList.add("EmpCustomersGrid");
    main.appendChild(container);

    getCustomerCount().then(info => {
        const count = parseInt(info.data);

        if (!count) {
            const msg = document.createElement("p");
            msg.className = "noCustomersMsg";
            msg.innerText = "No Customers Found";
            main.appendChild(msg);
            return;
        }

        for (let idx = 0; idx < count; idx++) {
            getCustomerLine(idx.toString()).then(cust => {

                const parts = cust && cust.data ? cust.data.split("*") : [];
                const [
                    id = "",
                    type = "",
                    iban = "",
                    branch = "",
                    name = "",
                    openDate = "",
                    status = "",
                    balance = "",
                    password = ""
                ] = parts;

                const sid = escapeHtml(id);
                const stype = escapeHtml(type);
                const siban = escapeHtml(iban);
                const sbranch = escapeHtml(branch);
                const sname = escapeHtml(name);
                const sopen = escapeHtml(openDate);
                const sbalance = escapeHtml(balance);
                const spassword = escapeHtml(password);

                // Build card
                const card = document.createElement("div");
                card.id = `custCard_${id}`;

                card.innerHTML = `
                    <div class="customerHeader">Account ${sid}</div>

                    <div class="customerField">
                        <span class="customerLabel">Type</span>
                        <span class="customerValue">${stype}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">IBAN</span>
                        <span class="customerValue">${siban}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Branch Code</span>
                        <span class="customerValue">${sbranch}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Name</span>
                        <span class="customerValue">${sname}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Opening Date</span>
                        <span class="customerValue">${sopen}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Status</span>
                        <span name="space_status" class="customerValue">${status}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Balance</span>
                        <span class="customerValue">${sbalance} TND</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Password</span>
                        <span class="customerValue">${spassword}</span>
                    </div>

                    <div class="customerActions">
                        <button class="miniBtn loansBtn" onclick="viewCustomerLoans('${id}')">Loans</button>
                        <button class="miniBtn transBtn" onclick="viewCustomerTransactions('${id}')">Transactions</button>
                        <button class="miniBtn chngsts" onclick="changeStatus('${id}')">Change Status</button>

                        <select class="newStatus" id="newStatus_${id}" style="display:none;">
                            <option>Choose new Status</option>
                            <option>Closed</option>
                            <option>Inactive</option>
                            <option>Active</option>
                        </select>
                    </div>
                `;

                // STATUS TEXT FIX (only for this card)
                const statusSpan = card.querySelector('[name="space_status"]');
                if (statusSpan) {
                    if (status === "0") statusSpan.innerText = "Inactive";
                    else if (status === "1") statusSpan.innerText = "Active";
                    else if (status === "-1") statusSpan.innerText = "Closed";
                }

                // APPLY CARD COLOR
                if (status === "-1") {
                    card.classList=("closedCustomerCard");
                } else if (status === "0") {
                    card.classList=("inactiveCustomerCard");
                } else {
                    card.classList=("customerCard");
                }

                container.appendChild(card);

            }).catch(err => {
                console.error("getCustomerLine failed for index", idx, err);
            });
        }
    }).catch(err => {
        console.error("getCustomerCount failed", err);
    });
}

function changeStatus(id){
    document.getElementById("newStatus_"+id).removeAttribute("style");
    let newStatus = (document.getElementById("newStatus_"+id).selectedIndex-2).toString();
    if(newStatus!="-2"){
        info=id+"*"+newStatus;
        changeStatusCPP(info).then((reply) =>{
            console.log(reply);
            viewAllCustomers();
        })
    }
}