function clearGUI(){
    document.getElementById("asideDisplayArea").innerHTML = "";
    document.getElementById("mainEmpInt").innerHTML = "";
}

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
            alert("Employee with this ID does not Exist");
        }else if(answer=="falseP"){
            alert("Wrong password");
        }else{
            goToPage('EmployeeInterface.html');
        }
    });
}

function makeInterestRateField(lrcid){
    document.getElementById("asideDisplayArea").innerHTML = 
    `
        <div class="loanContainer">
            <div class="loanField">
                <span class="loanLabel">Interest Rate(%): </span>
                <input id="itr_${lrcid}" type="number" min="2" step="1" class="itValue" placeholder="Enter an interest rate">
            </div>
        </div>
    `;
}

function acceptLoanRequest(loanReqCompId){
    let comp = document.getElementById(loanReqCompId);
    let amount = comp.children[1].children[1].innerText;
    amount = amount.substring(0,amount.indexOf('.'));
    let itr_field = document.getElementById(`itr_${loanReqCompId}`);
    if(itr_field == null){
        makeInterestRateField(loanReqCompId);
    } else if (itr_field.value == "") {
        alert("Please enter the interest rate");
    } else if (Number(itr_field.value) < 2) {
        alert("Invalid Interest Rate. Should be minimum 2%");
    } else {
        let sent_data = comp.children[7].innerText+'*' //customer ID
                        +amount+'*' //amount without ' TND'
                        +comp.children[2].children[1].dataset.value+"*" //type (string representation)
                        +comp.children[3].children[1].dataset.value+"*" //start date (string repr)
                        +comp.children[4].children[1].dataset.value+"*"
                        +itr_field.value; //end date (string repr)
        sendAcceptedLoanReq(sent_data).then(
            (reply) => {
                console.log("C++ replied:"+reply);
            }
        );
        comp.remove();
        itr_field.remove();
        //display next loan request
        displayLoanRequest();
    }
}

function addNoLoanReqMsg(){
    if(document.getElementById("noLQ") == null){
       let no_lq = document.createElement("p");
        no_lq.classList.add("noMSG");
        no_lq.innerHTML = "No Loan Requests";
        document.getElementById("mainEmpInt").appendChild(no_lq); 
    }
}

function declineLoanRequest(loanReqCompId){
    document.getElementById(loanReqCompId).remove();
    declineLoanReq().then(
        (reply) => {
            console.log(`C++ replied: ${reply}`);
        }
    )
    //display next loan request
    displayLoanRequest();
}

/* 
Return a Loan Request Component (HTML element) from a string in JSON format
*/
function getLoanReqComponent(lrs){
    console.log(lrs);
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

    let type_value = "";
    switch(lrs.type){
        case "car": type_value = "1"; break;
        case "home": type_value = "2"; break;
        case "student": type_value = "3"; break;
        case "business": type_value = "4"; break;
    }

    const type_ = document.createElement("div");
    type_.classList.add("loanReqField");
    type_.innerHTML = `
        <div class="loanReqFieldLabel">Type:</div>
        <p class="loanReqFieldValue" data-value="${type_value}"> ${lrs.type} </p>
    `;

    const start_d = document.createElement("div");
    start_d.classList.add("loanReqField");
    start_d.innerHTML = `
        <div class="loanReqFieldLabel">Starts On:</div>
        <p class="loanReqFieldValue" data-value="${lrs.d_start}"> ${lrs.d_start} </p>
    `;

    const end_d = document.createElement("div");
    end_d.classList.add("loanReqField");
    end_d.innerHTML = `
        <div class="loanReqFieldLabel">Ends On:</div>
        <p class="loanReqFieldValue" data-value="${lrs.d_end}"> ${lrs.d_end} </p>
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
    compononent.appendChild(start_d);
    compononent.appendChild(end_d);
    compononent.appendChild(accept_but);
    compononent.appendChild(decline_but);
    compononent.appendChild(cus_ID_footer);
    return compononent;
}

//CPP will send Loan Requests One by one by creating a cpp
//function, so that we can use the FIFO system mentionned in
//the project PDF
function displayLoanRequest(){
    document.getElementById("asideDisplayArea").innerHTML = "";
    let mainEmpInt = document.getElementById("mainEmpInt");
    mainEmpInt.innerHTML="";
    receiveQueueSize().then(
        (queue_size_JSON) => {
            let size = parseInt(queue_size_JSON.size);
            if(size == 0){
                addNoLoanReqMsg();
            }else{
                receiveCurrentLoanReq().then(
                    (loanReqStr) => {
                        mainEmpInt.appendChild(getLoanReqComponent(loanReqStr));
                    }
                )
            }
        }
    );
}


function viewAllCustomers() {
    const main = document.getElementById("mainEmpInt");
    main.innerHTML = "";

    const container = document.createElement("div");
    container.classList.add("EmpCustomersGrid");

    syncLoanReqs().then(
        (reply) => {
            console.log("C++ replied: "+reply);
        }
    )

    main.appendChild(container);

    getCustomerCount().then(info => {
        const count = parseInt(info.data);

        if (!count) {
            const msg = document.createElement("p");
            msg.className = "noMSG";
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


                // Build card
                const card = document.createElement("div");
                card.id = `custCard_${id}`;

                card.innerHTML = `
                    <div class="customerHeader">Account ${id}</div>

                    <div class="customerField">
                        <span class="customerLabel">Type</span>
                        <span class="customerValue">${type}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">IBAN</span>
                        <span class="customerValue">${iban}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Branch Code</span>
                        <span class="customerValue">${branch}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Name</span>
                        <span class="customerValue">${name}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Opening Date</span>
                        <span class="customerValue">${openDate}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Status</span>
                        <span name="space_status" class="customerValue">${status}</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Balance</span>
                        <span class="customerValue">${balance} TND</span>
                    </div>

                    <div class="customerField">
                        <span class="customerLabel">Password</span>
                        <span class="customerValue">${password}</span>
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

//BALIZ DO INTERFACE
function deleteCompLoans(){
    deleteCompletedLoans().then(
        (reply) => {
            alert(reply);
            console.log("C++ replied:"+reply);
        }
    )
}

function displayEmployee(count, type) {
    const container = document.getElementById("EmpEmployeesGrid");
    container.innerHTML = "";

    for (let idx = 0; idx < count; idx++) {
        let combined = idx.toString() + "*" + type;

        getEmployeeLine(combined).then(emp => {

            const parts = emp && emp.data ? emp.data.split("*") : [];
            const [
                ID = "",
                Name = "",
                LastName = "",
                Adress = "",
                Salary = "",
                HireDate = "",
                bankBranch = "",
                password = ""
            ] = parts;

            const card = document.createElement("div");
            card.id = `empCard_${ID}`;
            card.classList.add("employeeCard");

            card.innerHTML = `
                <input readonly class="employeeHeader" value='${Name}'> <br>
                <input readonly class="employeeHeader" value='${LastName}'><br>
                <span>(${ID})</span> 

                <div class="employeeField">
                    <span class="employeeLabel">Address:</span>
                    <input readonly class="employeeValue empInp" value='${Adress}'>
                </div>

                <div class="employeeField">
                    <span class="employeeLabel">Salary(TND):</span>
                    <input readonly class="employeeValue empInp" value='${Salary}'>
                </div>

                <div class="employeeField">
                    <span class="employeeLabel">Hire Date:</span>
                    <input readonly class="employeeValue empInp" value='${HireDate}'>
                </div>

                <div class="employeeField">
                    <span class="employeeLabel">Bank Branch:</span>
                    <div id="branchField_${ID}">
                        <input readonly class="employeeValue" id='bank_${ID}' value='${bankBranch}'>
                    </div>
                </div>

                <div class="employeeField">
                    <span class="employeeLabel">Password:</span>
                    <input readonly class="employeeValue empInp" value='${password}'>
                </div>

                <div class="employeeActions">
                    <button class="ConfirmBtn" id='conBtn_${ID}' style='display:none' onclick="modifyEmployeeCPP('${ID}')">Confirm</button>
                    <button class="modifyBtn" onclick="modifyEmployee('${ID}')">Modify</button>
                    <button class="deleteBtn" onclick="deleteEmployee('${ID}')">Delete</button>
                </div>
            `;

            container.appendChild(card);

        }).catch(err => {
            console.error("getEmployeeLine failed for index", idx, err);
        });
    }
}



// ----------------------------------------
// MODIFY EMPLOYEE
// ----------------------------------------

function modifyEmployee(ID){
    const card = document.getElementById(`empCard_${ID}`);
    if (!card) return;

    const oldCode = document.getElementById(`bank_${ID}`).value;

    const branchDiv = document.getElementById(`branchField_${ID}`);

    branchDiv.innerHTML = `
        <select class='selectbank' id="branchSelect_${ID}">
            <option value="001">Tunis (001)</option>
            <option value="002">Sousse (002)</option>
            <option value="003">BenArous (003)</option>
            <option value="004">Ariana (004)</option>
            <option value="005">Nabeul (005)</option>
            <option value="006">Gaserine (006)</option>
            <option value="007">Gafsa (007)</option>
            <option value="008">Mehdia (008)</option>
            <option value="009">Sfax (009)</option>
            <option value="010">Djerba (010)</option>
            <option value="011">Mednine (011)</option>
            <option value="012">Tozeur (012)</option>
            <option value="013">Tatawin (013)</option>
            <option value="014">Bizerte (014)</option>
            <option value="015">ElKef (015)</option>
            <option value="016">Monastir (016)</option>
            <option value="017">Jandouba (017)</option>
            <option value="018">Kebeli (018)</option>
            <option value="019">SidiBouzid (019)</option>
            <option value="020">Gabes (020)</option>
            <option value="021">Seliana (021)</option>
            <option value="022">Beja (022)</option>
            <option value="023">Kairouan (023)</option>
            <option value="024">Mannouba (024)</option>
            <option value="025">Zaghouane (025)</option>
        </select>
    `;

    document.getElementById(`branchSelect_${ID}`).value = oldCode;

    const inputs = card.querySelectorAll("input[readonly]");
    inputs.forEach(inp => {
        inp.removeAttribute("readonly");
        inp.classList.add("borderedInp");
    });

    document.getElementById(`conBtn_${ID}`).style.display = "inline-block";
}



// ----------------------------------------
// SAVE MODIFIED EMPLOYEE
// ----------------------------------------

function modifyEmployeeCPP(ID){
    const card = document.getElementById(`empCard_${ID}`);
    if (!card) return;

    const inp=card.querySelectorAll(".empInp");
    const name=card.querySelectorAll(".employeeHeader")[0].value.trim();
    const lastName=card.querySelectorAll(".employeeHeader")[1].value.trim();
    const address=inp[0].value.trim();
    const salary=inp[1].value.trim();
    const hireDate=inp[2].value.trim();
    const password=inp[3].value.trim();
    const branch=document.getElementById(`branchSelect_${ID}`).value;

    const info = [
        ID,
        name,
        lastName,
        address,
        salary,
        hireDate,
        branch,
        password
    ].join("*");

    modEmployee(info).then(reply => {
        if (reply == "ok") {
            viewAllEmployees();
    getEmployeeCount().then(info => {
        const count = parseInt(info.data);
        if (!count) {
            const msg = document.createElement("p");
            msg.classList.add("noMSG");
            msg.innerText = "No Employees Found"; //T7esha partie zeyda 5tr ma yousel ela ma yamel login ama cpg dima andek safety net
            main.appendChild(msg);
            return;
        }
    });
}
    })}


// ----------------------------------------
// DELETE EMPLOYEE
// ----------------------------------------

function deleteEmployee(ID){
    delEmployee(ID).then(reply => {
        if (reply === "Deleted") {
            viewAllEmployees();
        }
    });
}
function addEmployee() {
    const main = document.getElementById("mainEmpInt");
    main.innerHTML = ""; // clear old content

    const formContainer = document.createElement("div");
    formContainer.classList.add("employeeFormContainer");

    formContainer.innerHTML = `
        <h2 class="formHeader">Add New Employee</h2>


        <div class="employeeFormField">
            <label class="employeeFormLabel">First Name:</label>
            <input type="text" id="empName" class="employeeFormInput" placeholder="Enter First Name">
        </div>

        <div class="employeeFormField">
            <label class="employeeFormLabel">Last Name:</label>
            <input type="text" id="empLastName" class="employeeFormInput" placeholder="Enter Last Name">
        </div>

        <div class="employeeFormField">
            <label class="employeeFormLabel">Address:</label>
            <input type="text" id="empAdress" class="employeeFormInput" placeholder="Enter Address">
        </div>

        <div class="employeeFormField">
            <label class="employeeFormLabel">Salary:</label>
            <input type="number" id="empSalary" class="employeeFormInput" placeholder="Enter Salary" min="0">
        </div>



        <div class="employeeFormActions">
            <button class="miniBtn modifyBtn" id="submitEmpBtn">Add Employee</button>
            <button class="miniBtn deleteBtn" id="cancelEmpBtn">Cancel</button>
        </div>
    `;

    main.appendChild(formContainer);

    // EVENT LISTENERS
    document.getElementById("submitEmpBtn").addEventListener("click", () => {
        const newEmp =
            document.getElementById("empName").value.trim()+"*"+document.getElementById("empLastName").value.trim()+"*"+document.getElementById("empAdress").value.trim()+"*"+document.getElementById("empSalary").value+"*"
        ;

        addEmployeeCPP(newEmp).then(reply => {
            console.log("Employee added:", reply);
            viewAllEmployees(); // refresh the employee list
        }).catch(err => {
            console.error("Failed to add employee:", err);
        });
    });

    document.getElementById("cancelEmpBtn").addEventListener("click", () => {
        viewAllEmployees(); // go back to employee list
    });
}

function viewAllEmployees() {
    const main = document.getElementById("mainEmpInt");
    main.innerHTML = "";

    const controlsDiv = document.createElement("div");
    controlsDiv.classList.add("EmpTopControls");
    controlsDiv.innerHTML = `
        <button class="addEmployeeBtn" onclick="addEmployee()">Add Employee</button>
        
        <select id="employeeFilter" class="employeeFilter">
            <option value="alpha">Filter by - Alphabetical Order</option>
            <option value="branch">Filter by - Bank Branch Order</option>
        </select>

        <button class="showChronoBtn" onclick="showEmplsChrono()">Show Chronologically</button>
    `;
    main.appendChild(controlsDiv);

    const container = document.createElement("div");
    container.classList.add("EmpEmployeesGrid");
    container.id = "EmpEmployeesGrid";
    main.appendChild(container);

    getEmployeeCount().then(info => {
        const count = parseInt(info.data);
        if (!count) {
            const msg = document.createElement("p");
            msg.className = "noEmployeesMsg";
            msg.innerText = "No Employees Found";
            main.appendChild(msg);
            return;
        }

        const filterSelect = document.getElementById("employeeFilter");

        displayEmployee(count, "alpha");

        filterSelect.addEventListener("change", () => {
            displayEmployee(count, filterSelect.value);
        });

    }).catch(err => {
        console.error("getEmployeeCount failed", err);
    });
}


function buildLoanContainer(cusID,lnj){
    let displayArea = document.getElementById(`asideDisplayArea`);

    const content = `
        <div class="loanContainer">
            <div class="loanField">
                <span class="loanLabel">Loan ID: </span>
                <span class="loanValue">${lnj.id}</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Type: </span>
                <span class="loanValue">${lnj.type}</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Pr. Amount: </span>
                <span class="loanValue">${lnj.amount} TND</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Int. Rate: </span>
                <span class="loanValue">${lnj.itr}%</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Amount Paid: </span>
                <span class="loanValue">${lnj.paid}  TND</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Remaining Balance: </span>
                <span class="loanValue">${lnj.rmn} TND</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Started On: </span>
                <span class="loanValue">${lnj.start}</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Ends On: </span>
                <span class="loanValue">${lnj.end}</span>
            </div>
            <select id="loanStatus_${lnj.id}" class="loanStatus" onchange="changeLoanStatus('${cusID}','${lnj.id}','loanStatus_${lnj.id}')">
                <option value="5">ACTIVE</option>
                <option value="6">COMPLETED</option>
                <option value="7">OVERDUE</option>
            </select>
        </div>
    `;
    displayArea.innerHTML += content;
    let status = document.getElementById(`loanStatus_${lnj.id}`);
    switch(lnj.status){
        case "5":
            status.children[0].setAttribute("selected","selected");
            break;
        case "6":
            status.children[1].setAttribute("selected","selected");
            break;
        case "7":
            status.children[2].setAttribute("selected","selected");
            break;
    }
    updateLoanStatusColor(`loanStatus_${lnj.id}`);
}

function buildTransationContainer(trj){
    let displayArea = document.getElementById(`asideDisplayArea`);
    const content = `
        <div class="loanContainer">
            <div class="loanField">
                <span class="loanLabel">Transaction ID: </span>
                <span class="loanValue">${trj.tid}</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Customer ID: </span>
                <span class="loanValue">${trj.cid}</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Type: </span>
                <span class="loanValue">${trj.type}</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Amount: </span>
                <span class="loanValue">${trj.amount} TND</span>
            </div>
            <div class="loanField">
                <span class="loanLabel">Done On: </span>
                <span class="loanValue">${trj.start}</span>
            </div>
        </div>
    `;
    displayArea.innerHTML += content;
}

function updateLoanStatusColor(ls_id){
    let status = document.getElementById(ls_id);
    console.log(`update status : ${status.value}`);
    switch(status.selectedIndex){
        case 0:
            status.classList = "lsActive";
            break;
        case 1:
            status.classList = "lsCompleted";
            break;
        case 2:
            status.classList = "lsOverdue";
            break;
    }
}

function changeLoanStatus(cusID,ln_id,ls_id){
    let status = document.getElementById(ls_id);
    changeLoanStatusOfCustomer(cusID+"*"+ln_id+"*"+status.value).then(
        (reply) => {
            updateLoanStatusColor(ls_id);
            console.log(`C++ replied ${reply}`);
        }
    )
}

function viewCustomerLoans(cusID){
    let displ = document.getElementById("asideDisplayArea");
    displ.innerHTML = "";
    receiveLoansOfCustomer(cusID).then(
        (loansJSON) => {
            if(loansJSON.length == 0) {
                const no_lns = document.createElement("p");
                no_lns.innerText = "No Loans for this customer";
                no_lns.classList.add("noMSG");
                displ.appendChild(no_lns);
                return;
            }
            for(let i = 0; i < loansJSON.length; i++){
                buildLoanContainer(cusID,loansJSON[i]);
            }
        }
    );
}
function showEmplsChrono() {
    const main = document.getElementById("mainEmpInt");
    main.innerHTML = "";

    const container = document.createElement("div");
    container.classList.add("EmpCustomersGrid"); 
    main.appendChild(container);

    getEarliestEmployee().then((str1) => {
        const emp1 = str1.data.split("*");

        getLatestEmployee().then((str2) => {
            const emp2 = str2.data.split("*");

            container.appendChild(createStyledEmpCard(emp1));
            container.appendChild(createStyledEmpCard(emp2));
        });
    });
}

function createStyledEmpCard(arr) {
    const [ID, Name, LastName, Address, Salary, HireDate, Branch, Password] = arr;

    const card = document.createElement("div");
    card.classList.add("customerCard"); //juste 3al style

    // HEADER
    const header = document.createElement("div");
    header.classList.add("customerHeader");
    header.textContent = `${Name} ${LastName} (#${ID})`;
    card.appendChild(header);

    // FIELD BUILDER FUNCTION
    function addField(label, value) {
        const field = document.createElement("div");
        field.classList.add("customerField");

        field.innerHTML = `
            <span class="customerLabel">${label}:</span>
            <span class="customerValue">${value}</span>
        `;

        card.appendChild(field);
    }

    addField("Address", Address);
    addField("Salary", Salary);
    addField("Hire Date", HireDate);
    addField("Branch", Branch);
    addField("Password", Password);

    return card;
}

function fin(){
    finalizeDay().then((reply)=>{console.log(reply)})
}

function viewCustomerTransactions(cusID){
    let displ = document.getElementById("asideDisplayArea");
    displ.innerHTML = "";
    receiveTransOfCustomer(cusID).then(
        (trsJSON) => {
            if(trsJSON.length == 0) {
                const no_lns = document.createElement("p");
                no_lns.innerText = "No Transaction for this customer";
                no_lns.classList.add("noMSG");
                displ.appendChild(no_lns);
                return;
            }
            for(let i = 0; i < trsJSON.length; i++){
                buildTransationContainer(trsJSON[i]);
            }
        }
    );
}

function addNewCustomer(){
    document.getElementById("mainEmpInt").innerHTML = `
        <div id="newCustomerContainer">
            <p id="newCustomerTitle">
                New Customer
            </p>
            <div id="newCustomerFieldSet">
                <input type="text" id="newCustomerName" placeholder="The New Customer's name">
                <select id="newCustomerAccType">
                    <option value="Current">Current</option>
                    <option value="Savings">Savings</option>
                </select>
            </div>
            <button type="button" onclick="createCustomer()" id="createCusBtn">Create</button>
        </div>
    `;
}

function createCustomer(){
    let name = document.getElementById("newCustomerName").value;
    if(name == ""){
        alert("Please enter the new customer's name.");
        return;
    }
    let type = document.getElementById("newCustomerAccType").value;
    sendRegCusInfo(type+"*"+name).then(
        (reply) => {
            alert(reply);
        }
    )
}