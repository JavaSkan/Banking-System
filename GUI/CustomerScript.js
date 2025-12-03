getLoanCount().then((info) => {LoanCount=parseInt( info.data );})      //Gets the number of loans from the logged in user
function getloggedinfo(){
    let space_name=document.getElementById("CustomerName");
    let space_balance=document.getElementById("CustomerBalance");
    getLoggedInCustomerInformationFromCPlusPlus().then((answer)=>{
        const [name,balance] = answer.data.split("*");
        space_name.innerText=name;
        space_balance.innerText=balance;
    })
}

function delASIDE(){
    document.getElementById("aside").innerHTML="";
}

function showLoans() {
    if (LoanCount == 0) {
        let main = document.getElementById("mainCustInt");
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
}



