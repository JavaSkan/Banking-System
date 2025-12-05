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


//BALIZ DO INTERFACE
function deleteCompletedLoans(){
    deleteLoan().then((reply))
}
