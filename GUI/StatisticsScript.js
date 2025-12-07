function viewStatistics() {
    const main=document.getElementById("mainEmpInt");
    main.innerHTML=""; // Clear screen

    const container=document.createElement("div");
    container.classList.add("statsContainer");
    
    container.innerHTML=`
        <h2 class="formHeader">Bank Statistics</h2>
        
        <div class="statsGrid" id="statsGrid">
        </div>
        
        <div class="statsControls">
            <h3>Loan Statistics Filters</h3>
            
            <div class="controlGroup">
                <label>Count by Type:</label>
                <select id="statLoanType" class="employeeFilter">
                    <option value="1">Car</option>
                    <option value="2">Home</option>
                    <option value="3">Student</option>
                    <option value="4">Business</option>
                </select>
                <button class="miniBtn" onclick="updateLoanTypeStat()">Check</button>
                <span id="loanTypeResult" class="statResultValue">--</span>
            </div>

            <div class="controlGroup">
                <label>Count by Status:</label>
                <select id="statLoanStatus" class="employeeFilter">
                    <option value="5">Active</option>
                    <option value="6">Completed</option>
                    <option value="7">Overdue</option>
                </select>
                <button class="miniBtn" onclick="updateLoanStatusStat()">Check</button>
                <span id="loanStatusResult" class="statResultValue">--</span>
            </div>

            <div class="controlGroup dateRangeGroup">
                <label>Active Loans (Date Range):</label>
                <div style="display:flex; gap:5px; flex-grow:1;">
                    <input type="date" id="statLoanStartDate" class="employeeFormInput borderedInp">
                    <input type="date" id="statLoanEndDate" class="employeeFormInput borderedInp">
                </div>
                <button class="miniBtn" onclick="updateActiveLoansRangeStat()">Check</button>
                <span id="loanDateRangeResult" class="statResultValue">--</span>
            </div>
        </div>

        <div class="statsControls">
            <h3>Employee Statistics Filters</h3>
            
            <div class="controlGroup">
                <label>Count by Branch:</label>
                <select id="statEmployeeBranch" class="employeeFilter">
                    <option value="1">Central (1)</option>
                    <option value="2">North (2)</option>
                    <option value="3">South (3)</option>
                </select>
                <button class="miniBtn" onclick="updateEmpByBranchStat()">Check</button>
                <span id="employeeBranchResult" class="statResultValue">--</span>
            </div>
        </div>
    `;
    main.appendChild(container);

    fetchGeneralStats();
}

function createStatCard(label, value) {
    return `
        <div class="statCard">
            <div class="statLabel">${label}</div>
            <div class="statValue">${value}</div>
        </div>
    `;}
// Fetches and displays the static, general statistics
function fetchGeneralStats() {
    const grid=document.getElementById("statsGrid");
    
    getGlobalTotalLoans().then(reply => {grid.innerHTML += createStatCard("Total Loans", reply.data);});

    getGlobalTotalEmployees().then(reply => {grid.innerHTML += createStatCard("Total Employees", reply.data);});
    getCustomerMostLoans().then(reply => {grid.innerHTML += createStatCard("Most Loans", reply.data);});
    getCustomerHighestBalance().then(reply => {grid.innerHTML += createStatCard("Highest Balance", reply.data);});
    getCustomerLowestBalance().then(reply => {grid.innerHTML += createStatCard("Lowest Balance", reply.data);});}

function updateLoanTypeStat() {
    const type=document.getElementById("statLoanType").value;
    getLoansByType(type).then(reply => {
        document.getElementById("loanTypeResult").innerText=reply.data;
    });
}
function updateLoanStatusStat() {
    const status=document.getElementById("statLoanStatus").value;
    getLoansByStatus(status).then(reply => {
        document.getElementById("loanStatusResult").innerText=reply.data;
    });
}
function updateActiveLoansRangeStat() {
    const startDate=document.getElementById("statLoanStartDate").value;
    const endDate=document.getElementById("statLoanEndDate").value;
    if (!startDate || !endDate) {
        document.getElementById("loanDateRangeResult").innerText="Error: Need Dates";
        return;
    }
    const toDDMMYYYY=(iso) => {
        const [y, m, d]=iso.split("-");
        return `${d}-${m}-${y}`;
    };//html ijiblek YYYY-MMM-DD ama el code ye5edh DD-MM-YYYY
    const startFixed=toDDMMYYYY(startDate);
    const endFixed=toDDMMYYYY(endDate);
    // C++ expects "DD-MM-YYYY*DD-MM-YYYY"
    const datesInfo=startFixed + "*" + endFixed;
    getActiveLoansInRange(datesInfo).then(reply => {
        document.getElementById("loanDateRangeResult").innerText=reply.data;
    });
}
// Function to handle NEW: Employee Count by Branch
function updateEmpByBranchStat() {
    const branchCode=document.getElementById("statEmployeeBranch").value;
    getEmpByBranch(branchCode).then(reply => {
        document.getElementById("employeeBranchResult").innerText=reply.data;
    });
}