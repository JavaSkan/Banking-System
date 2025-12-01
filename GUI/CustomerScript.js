let LoanCount=4;

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
            
            const list = LoanString.data.split("*");   // list[0]..list[9]
            // Parse the incoming string
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
                innerCell.innerText = celltext[j]+list[j];  // safe fallback
               innerRow.appendChild(innerCell);
               innerTable.appendChild(innerRow);
               }
              /*
              LoanString=getLoansLine(i.toString());
              const list = LoanString.split("*");   // list[0]..list[9]
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
                   let innerCell = document.createElement("td");
                   innerCell.innerText = LoanString ??"oops";  // safe fallback

                   innerCell.id = `Loan${i}_${j}`
                   //innerCell.innerText = celltext[j]+list[j];  // safe fallback
                   
                   innerRow.appendChild(innerCell);
                   innerTable.appendChild(innerRow);
                }
                */
            });
        cell.append(innerTable);
        row.appendChild(cell);
        table.appendChild(row);
    }
}

/*function  getLoansLine(i){
    loans=[
        "L001*1*5*200*0.2*100*100*1-1-2025*2-2-2027",
        "L002*1*5*200*0.2*100*100*1-1-2025*2-2-2027",
        "L003*1*5*200*0.2*100*100*1-1-2025*2-2-2027",
        "L004*1*5*200*0.2*100*100*1-1-2025*2-2-2027"
    ]
    return loans[i];
}*/