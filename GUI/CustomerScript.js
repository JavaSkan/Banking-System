let LoanCount=2;

function table() {
    let table = document.getElementById("LoansTable");
    table.classList.add("LoansTab");
    if (!table) return;
    for (let i = 0; i < LoanCount; i++) { 
        let row = document.createElement("tr");
        let cell = document.createElement("td");
        let cellId = `(Loan${i})`;
        cell.id = cellId;
        cell.style.backgroundColor="rgb(58, 58, 60)";
        row.appendChild(cell);
        table.appendChild(row);
    }
}
