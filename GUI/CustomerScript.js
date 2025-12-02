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

function table() {
    alert(LoanCount);
    if(LoanCount==0){
        let main=document.getElementById("mainCustInt");
        let noLoansMsg = document.createElement("p");
        noLoansMsg.classList.add("noLoansMsg");
        noLoansMsg.innerText="No Loans";
        main.appendChild(noLoansMsg);
        return;
    }else{
        let table = document.getElementById("LoansTable");
        if (!table) return;
            table.classList.add("LoansTab");
            let row = document.createElement("tr");
        for (let i = 0; i < LoanCount; i++) { 
            let cell = document.createElement("td");cell.id = `Loan${i}`;
            let innerTable = document.createElement("table");innerTable.classList.add("InnerLoansTab");

            getLoansLine((i+1).toString()).then((LoanString) => {
                const list = LoanString.data.split("*");   // list[0]..list[9]
                // Parse the incoming string
                const celltext=[
                    "ID : ",
                    "Type : ",
                    "Status : ",
                    "Primary Amount : ",
                    "Interest Rate : ",
                    "Amount paid : ",
                    "Remaining Balance : ",
                    "Start Date : ",
                    "End DateID : ",
                ]
                // [Id,type,lstatus,pr_amnt,ir,ap,rb,sd,ed]
                
                for (let j = 0; j < 9; j++) {
                    let innerRow = document.createElement("tr");
                    innerRow.classList.add("innerRow")
                    let innerCell = document.createElement("td");
                
                innerCell.id = `Loan${i}_${j}`
                innerCell.innerText = celltext[j]+list[j];  // safe fallback
                innerRow.appendChild(innerCell);
                innerTable.appendChild(innerRow);
            }
        });
        cell.append(innerTable);
        row.appendChild(cell);
        table.appendChild(row);
    }
}
}

