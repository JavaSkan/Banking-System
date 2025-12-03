function getloggedinfo(){
    let space_name=document.getElementById("CustomerName");
    let space_balance=document.getElementById("CustomerBalance");
    getLoggedInCustomerInformationFromCPlusPlus().then((answer)=>{
        const [name,balance] = answer.data.split("*");
        space_name.innerText=name;
        space_balance.innerText=balance;
        Customer_balance=parseInt(balance)
    })
}

function delASIDE(){
    document.getElementById("aside").innerHTML="";
}
function requestLoan(){
    const main = document.getElementById("mainCustInt");
    main.innerHTML = "";

    const formCard = document.createElement("div");
    formCard.className = "LoanCard";

    formCard.innerHTML = `
        <div class="LoanHeader">Request a New Loan</div>
        <div class="LoanInfoGrid" style="grid-template-columns:1fr">
            <div class="LoanField">
                <label class="LoanLabel">Loan Type:</label>
                <select id="loanType">
                    <option>Car</option><option>Home</option><option>Student</option><option>Business</option>
                </select>
            </div>
            <div class="LoanField">
                <label class="LoanLabel">Amount (TND):</label>
                <input type="number" id="loanAmount" value="1000" min="1000" step="100">
            </div>
            <div class="LoanField">
                <label class="LoanLabel">Duration (years):</label>
                <input type="number" id="loanDuration" value="1" min="1">
            </div>
        </div>
        <button class="loginBtn" style="margin-top:15px" onclick="sendLoanReq()">Submit Loan Request</button>
    `;

    main.appendChild(formCard);
}
function showLoans() {
    let main = document.getElementById("mainCustInt");
    main.innerHTML = "";
    const LT = document.createElement("div");
    LT.classList.add("LoansTab");
    LT.id="LoansTable";
    main.appendChild(LT);

    getLoanCount().then((info) => {
        LoanCount=parseInt( info.data );
    
        if (LoanCount == 0) {
            let noLoansMsg = document.createElement("p");
            noLoansMsg.classList.add("noLoansMsg");
            noLoansMsg.innerText = "No Loans";
            main.appendChild(noLoansMsg);
            return;
        }
    
        const container = document.getElementById("LoansTable");
        if (!container) return;
    
        container.classList.add("LoansGrid");
    
        for (let i = 0; i < LoanCount; i++) {
            const card = document.createElement("div");
            card.classList.add("LoanCard");
    
            const header = document.createElement("div");
            header.classList.add("LoanHeader");
            header.innerText = `Loan ${i + 1}`;
            card.appendChild(header);
    
            const infoGrid = document.createElement("div");
            infoGrid.classList.add("LoanInfoGrid");
            card.appendChild(infoGrid);
    
            getLoansLine((i + 1).toString()).then((LoanString) => {
                const list = LoanString.data.split("*");
                let type=list[1];
                let status=list[2];
                switch (type){
                    case "1":list[1]="Car";break;
                    case "2":list[1]="Home";break;
                    case "3":list[1]="Student";break;
                    case "4":list[1]="Business";break;
                }
                switch (status){
                    case "5":list[2]="Active";break;
                    case "6":list[2]="Completed";break;
                    case "7":list[2]="Overdue";break;
                }
                const labels = [
                    "ID",
                    "Type",
                    "Status",
                    "Primary Amount",
                    "Interest Rate",
                    "Amount Paid",
                    "Remaining Balance",
                    "Start Date",
                    "End Date",
                ];
    
                for (let j = 0; j < 9; j++) {
                    const line = document.createElement("div");
                    line.classList.add("LoanField");
    
                    line.innerHTML = `
                        <span class="LoanLabel">${labels[j]}</span>
                        <span class="LoanValue">${list[j] ?? ""}</span>
                    `;
    
                    infoGrid.appendChild(line);
                }
            });
    
            container.appendChild(card);
        }
    })      //Gets the number of loans from the logged in user

}

// --- Withdraw Page ---
function withdrawMoney() {
    const main = document.getElementById("mainCustInt");
    main.innerHTML = "";

    const card = document.createElement("div");
    card.className = "LoanCard"; // reuse styling

    card.innerHTML = `
        <div class="LoanHeader">Withdraw Money</div>
        <div class="LoanInfoGrid" style="grid-template-columns:1fr">
            <div class="LoanField">
                <label class="LoanLabel">Select Denomination:</label>
                <input type="number" min="0" step="10"id="withdrawAmount">
            </div>
        </div>
        <button class="loginBtn" style="margin-top:15px" onclick="withdraw()">Withdraw</button>
    `;
    main.appendChild(card);
    document.getElementById("withdrawAmount").max = parseInt(document.getElementById("CustomerBalance").innerText);
}

// --- Deposit Page ---
function depositMoney() {
    const main = document.getElementById("mainCustInt");
    main.innerHTML = "";

    const card = document.createElement("div");
    card.className = "LoanCard";

    card.innerHTML = `
        <div class="LoanHeader">Deposit Money</div>
        <div class="LoanInfoGrid" style="grid-template-columns:1fr">
            <div class="LoanField">
                <label class="LoanLabel">Amount (TND):</label>
                <input type="number" id="depositAmount" min="1" placeholder="Enter amount">
            </div>
        </div>
        <button class="loginBtn" style="margin-top:15px" onclick="deposit()">Deposit</button>
    `;
    main.appendChild(card);
}
function deposit(){
    let amount=document.getElementById("depositAmount").value;
    depositCPP(amount).then((reply) => {
        if(reply="Amount Added"){
            location.reload(); //reload page to update the balance 3al isar
        }
    })
}


