let LoanCount=2;

function table() {
    let table = document.getElementById("LoansTable");
    if (!table) return;

    table.classList.add("LoansTab");

    for (let i = 0; i < LoanCount; i++) { 
        let row = document.createElement("tr");
        let cell = document.createElement("td");
        cell.id = `Loan${i}`;
        let innerTable = document.createElement("table");
        getLoansLine(i.toString()).then((LoanString) => {

            // Parse the incoming string
            const list = LoanString.data.split("*");   // list[0]..list[9]
            const celltext=[
                "Loan ID : ",
                "Loan Type : ",
                "Loan Status : ",
                "Loan Primary Amount : ",
                "Loan Interest Rate : ",
                "Loan Amount paid : ",
                "Loan Remaining Balance : ",
                "Loan Start Date : ",
                "Loan End DateID : ",
            ]
            // [Id,type,lstatus,pr_amnt,ir,ap,rb,sd,ed]

            for (let j = 0; j < 9; j++) {
                let innerRow = document.createElement("tr");
                let innerCell = document.createElement("td");

                innerCell.id = `Loan${i}_${j}`
                innerCell.innerText = celltext+list[j];  // safe fallback

                innerRow.appendChild(innerCell);
                innerTable.appendChild(innerRow);
            }
        });

        cell.append(innerTable);
        row.appendChild(cell);
        table.appendChild(row);
    }
}

