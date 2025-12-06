#include <windows.h>
#include <webview.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

#include <SinglyLinkedListMeth.hpp>
#include <DoublyLinkedListMeth.hpp>
#include <arrayMeth.hpp>
#include <Branches.hpp>
#include <Dates.hpp>
#include <MiscFuncs.hpp>
#include <customerMeth.hpp>
#include <LoansMeth.hpp>
#include <Employee.hpp>
#include <EmployeeTasks.hpp>
#include <QueueMeth.hpp>

using namespace std;

// --- GUI SETUP ---
webview::webview w(true, nullptr);
// --- GLOBAL VARIABLES ---
string lastJsValue;
Customer LoggedInCustomer;
Employee LoggedInEmployee;
Customer SelectedCustomer;
Queue* currentLoanReqs = createQueue();



//the csv had an initial date manually written
void getDateFromCSV(){
    ifstream file("assets/Date.csv");
    if(!file.is_open()){
        cerr<<"Cannot open file . assets/Date.csv"<<endl;
    }
    else {
        string line;
        getline(file,line);
        CurrentDate = stringToDate(line);
    }
    file.close();    
}

//Load loans requests from csv files
//Should be called when an employee logs in 
void loadLoanReqs(){
    ifstream file("assets/LoanRequests.csv"); 
    if(!file.is_open()){
        cerr << "Cannot open file: assets/LoanRequests.csv" << endl;
    }else{
        string line;
        string info[4];
        LoanRequest current_loan_req = {};
        while(getline(file,line)){
            splitStr(line,',',info,4);
            current_loan_req.ID_customer = info[0];
            current_loan_req.loan.type = stoi(info[1]);
            current_loan_req.loan.pr_amount = stof(info[2]);
            current_loan_req.loan.start_date = CurrentDate;
            current_loan_req.loan.end_date = {CurrentDate.day,CurrentDate.month,CurrentDate.year+stoi(info[3])};
            enqueue(currentLoanReqs,current_loan_req);
        }
    }
    file.close();
}

/*
Called when employee either deleles or accepts a loan request
Always deletes the first line.
*/
void deleteLoanReqFromCSV(){
    fstream file("assets/LoanRequests.csv",ios::in); 
    if(!file.is_open()){
        cerr << "Cannot open file: assets/LoanRequests.csv (first try)" << endl;
        return;
    }
    Array<string> lines = createArray<string>(50);
    string line;
    while(getline(file,line)){
        addElement(&lines,line,lines.size);
    }
    file.close();
    file.open("assets/LoanRequests.csv",ios::out | ios::trunc);
    if(!file.is_open()){
        cerr << "Cannot open file: assets/LoanRequests.csv (second try)" << endl;
        return;
    }
    for(int i = 1; i < lines.size; i++){
        file << lines.data[i] << '\n';
    }
    file.close();
}

void init_completedLoansList(){
    ifstream file("assets/CompletedLoans.csv");
    if(!file.is_open()){
        cerr<<"Cannot open the completed loans file " <<endl;
    }
    else {
        string line;
        getline(file,line);
        completed_loans = stringToSL(line);
    }
    file.close();
}

void init_TransactionList(){
    ifstream file("assets/Transactions.csv");
    if(!file.is_open()){
        cerr<<"Cannot open the Transactions file " <<endl;
    }
    else {
        string line;
        getline(file,line);
        finalized_transactions = stringToSLTr(line);
    }
    file.close();
}

string getSpecificLoan(int pos){ 
    Loan current;
    string LoansString;
    current=getElement(LoggedInCustomer.loans,pos);
    LoansString=loanToString(current);
    cout<<endl<<LoansString;
    LoansString=LoansString.substr(5,LoansString.size()-6);
    cout<<LoansString;
    return LoansString ;
}



string EmplLoginCpp(const string& LoginInfoJSON){
    string LoginInfo=unJSON(LoginInfoJSON);
    string ID;
    string password;
    string infoParts[2];
    int n = splitStr(LoginInfo, '*',infoParts,2);
    ID=infoParts[0];
    password=infoParts[1];
    int EmployeePos=searchByID<Employee>(EmplArray,ID);
    if( EmployeePos==-1){
        return "\"false\"";
    }else{
        if(EmplArray.data[EmployeePos].password==password){
            LoggedInEmployee=EmplArray.data[EmployeePos];
            loadLoanReqs();
            return LoggedInEmployee.ID;
        }else{
            return "\"falseP\"";
        }
    }
}

string CustLoginCpp(const string& LoginInfoJSON){
    string LoginInfo=unJSON(LoginInfoJSON);
    string accNum;
    string password;
    string infoParts[2];
    splitStr(LoginInfo, '*',infoParts,2);
    accNum=infoParts[0];
    password=infoParts[1];
    int CustomerPos=searchByID<Customer>(custArray,accNum);
    if( CustomerPos==-1){
        return "\"false\"";
    }else{
        if(custArray.data[CustomerPos].password==password){
            LoggedInCustomer=custArray.data[CustomerPos];
            return LoggedInCustomer.ID;
        }else{
            return "\"falseP\"";
        }
    }
}

string sendLoanCountJS(const string&){
    return "{\"data\":\"" + to_string(LoggedInCustomer.loans.size)+ "\"}";
}
string sendCustomerCount(const string&){
    return "{\"data\":\"" + to_string(custArray.size) + "\"}";
}

string sendCusLoggedInfoJS(const string&){
    string info = LoggedInCustomer.name + "*" + to_string(LoggedInCustomer.balance);
    return "{\"data\":\"" + info + "\"}";

}
string sendEmpLoggedInfoJS(const string&){
    string info = LoggedInEmployee.ID+ "*" +(LoggedInEmployee.Name+" "+LoggedInEmployee.LastName);
    return "{\"data\":\"" + info + "\"}";


}
// TRANSACTIONS
bool existsID(const Stack& s, const string& id) {
    for (int i = s.top; i >= 0; i--) {
        if (s.data[i].ID == id) return true;
    }
    return false;
}

string TranIdGen(){
    string id;
    do {
        id = to_string(random(0,9999));
        while(id.size()<4){
            id="0"+id;
        } 
    } while (existsID(LoggedInCustomer.transactions, id));
    return "T"+id;
}
Transaction createNewTransaction(int type,float amount){
    Transaction T;
    T.accountNumber=LoggedInCustomer.ID;
    T.ID=TranIdGen();
    T.amount=amount;
    T.type=type;
    T.date=CurrentDate;
    return T;
}
string deposit(const string& amountJSON){
    int amount=stoi(unJSON(amountJSON));
    LoggedInCustomer.balance+=amount;
    updateCustomerInCsv(LoggedInCustomer);
    push(LoggedInCustomer.transactions,createNewTransaction(1,amount));
    return "\"true\"";
}
string withdraw(const string& amountJSON){
    int amount=stoi(unJSON(amountJSON));
    LoggedInCustomer.balance-=amount;
    push(LoggedInCustomer.transactions,createNewTransaction(0,amount));
    updateCustomerInCsv(LoggedInCustomer);
    return "\"true\"";
}

string getSpecificCustomerStr(int i){
    Customer Cus=custArray.data[i];
    string CustomerString=customerToStr(Cus);
    return CustomerString;
}
string sendLoanInfo(const string& i){return "{\"data\":\"" + getSpecificLoan(stoi(unJSON(i)))+ "\"}";}

string sendCustomerLine(const string& i){
    return "{\"data\":\"" +getSpecificCustomerStr(stoi(unJSON(i))) + "\"}";}

//---------------------------------------------
string getSpecificEmployeeStr(const Array<Employee>& arr,int i){
    Employee emp=arr.data[i];
    string EmployeeString=employeeToStr(emp);
    return EmployeeString; //brojla da5alt el camel case fel pascal case ama bara barka
}
void sortAlpha(Array<Employee>& arr) {
    for (int i = 0; i < arr.size - 1; i++) {
        for (int j = 0; j < arr.size - i - 1; j++) {
            if (arr.data[j].LastName > arr.data[j + 1].LastName) {
                Employee temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
        }
    }
}
void grpBankBranch(Array<Employee>& arr) {
    for (int i = 0; i < arr.size - 1; i++) {
        for (int j = 0; j < arr.size - i - 1; j++) {
            if (arr.data[j].bankBranch > arr.data[j + 1].bankBranch) {
                Employee temp = arr.data[j];
                arr.data[j] = arr.data[j + 1];
                arr.data[j + 1] = temp;
            }
        }
    }
}


string sendEmployeeLine(const string& infoJSON){
    string info=unJSON(infoJSON);
    string parts[2];
    splitStr(info,'*',parts,2);
    string i=parts[0];
    string type=parts[1];
    Array<Employee> copy =copyArray(EmplArray);
    if(type=="alpha"){
        sortAlpha(copy);
        return "{\"data\":\"" +getSpecificEmployeeStr(copy,stoi(i)) + "\"}";
    }else{
        if(type=="branch"){
        grpBankBranch(copy);
        return "{\"data\":\"" +getSpecificEmployeeStr(copy,stoi(i)) + "\"}";}
    }
    return "\"false\"";
}
string modifyEmployee(const string& infoJSON){
    string info=unJSON(infoJSON);
    string parts[8];
    splitStr(info,'*',parts,8);
    for(int i=0;i<7;i++){
        cout<<endl<<parts[i];
    }
    splitStr(info,'*',parts,8);
    int pos=searchByID(EmplArray,parts[0]);
    EmplArray.data[pos].Name=parts[1];
    EmplArray.data[pos].LastName=parts[2];
    EmplArray.data[pos].Adress=parts[3];
    EmplArray.data[pos].Salary=stof(parts[4]);
    EmplArray.data[pos].HireDate=stringToDate(parts[5]);
    EmplArray.data[pos].bankBranch=parts[6];
    EmplArray.data[pos].password=parts[7];
    updateEmployeeInCsv(EmplArray.data[pos]);
    return "\"ok\"";    
}
string deleteEmployee(const string& infoJSON){
    string info=unJSON(infoJSON);
    int pos=searchByID(EmplArray,info);
    deleteEmployeeFromCsv(EmplArray.data[pos]);
    removeAtArray(&EmplArray,pos);
    return"\"Deleted\"";
}
//---------------------------------------------------------------

string closeWindow(const string&) {
    w.terminate();
    return "\"Closed\"";
}
string goToPageCpp(const string& pageJSON) { //ybadel el page eli ywari feha el webview
    string page=unJSON(pageJSON);
    cout<<endl<<pageJSON<<" "<<page;
    w.navigate(path(page));
    return "\"page changed\"";
}
string getInfo(const string&) {
    string sDate = to_string(CurrentDate.day) + "-" + to_string(CurrentDate.month) + "-" + to_string(CurrentDate.year);
    string combined = globalSessBank.branchName + "*" + globalSessBank.ID+'*'+sDate;
    return "{\"data\":\"" + combined + "\"}";
}

string receiveLoanReq(const string& infoJSON){  
    ofstream file("assets/LoanRequests.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/LoanRequests.csv" << endl;
    }else{
        if(LoggedInCustomer.ID == ""){
            cerr << "[ERROR-receiveLoanReq]: No logged in customer" << endl;
            return "\"NOLOGCUS\"";
        }
        string info = unJSON(infoJSON);
        string loanRequestLine = LoggedInCustomer.ID + "," + replace(info,"*",",");
        file << loanRequestLine << endl;
    }
    file.close();
    return "\"Received Loan Request\"";
}

string sendSizeOfQueue(const string&){
    return "{\"size\":\"" + to_string(queueSize(*currentLoanReqs)) +"\"}";
}

string sendCurrentLoanReq(const string&){
    LoanRequest curLR = dequeue(currentLoanReqs);
    string ret = "{\"ID_cus\":\"" + curLR.ID_customer                       + "\","
                 + "\"amount\":\"" + to_string(curLR.loan.pr_amount)        + "\","
                 + "\"type\":\"" + loanTypeStr(curLR.loan.type)             + "\","
                 + "\"d_start\":\"" + dateToString(curLR.loan.start_date)   + "\","
                 + "\"d_end\":\"" + dateToString(curLR.loan.end_date)       + "\"}";
    return ret;
}

string addAcceptedLoanReq(const string& infoJSON){
    string info = unJSON(infoJSON);
    string loanReqInfo[5];
    splitStr(info,'*',loanReqInfo,5);
    int i = searchByID(custArray,loanReqInfo[0]);
    if(i == -1) {
        cout << "[DEBUG-addAcceptedLoanReq(customer id)]: " << loanReqInfo[0] << endl;
        return "\"Failed at addAcceptedLoanReq\"";
    }
    //add a loan to the customer
    Loan acceptedLoan;
    acceptedLoan.ID = "L"+loanReqInfo[0]+to_string(listSize(custArray.data[i].loans)+1);
    acceptedLoan.pr_amount = stof(loanReqInfo[1]);
    acceptedLoan.type = stoi(loanReqInfo[2]);
    acceptedLoan.am_paid = 0;
    acceptedLoan.rm_balance = acceptedLoan.pr_amount; //temporary
    acceptedLoan.it_rate = 0.12;
    acceptedLoan.status = LNS_ACTIVE;
    acceptedLoan.start_date = stringToDate(loanReqInfo[3]);
    acceptedLoan.end_date = stringToDate(loanReqInfo[4]);
    //std::cout << "[DEBUG-addAcceptedLoanReq(accepted loan)]: " << loanToString(acceptedLoan) << std::endl;
    insert(&custArray.data[i].loans,acceptedLoan,custArray.size+1);
    deleteLoanReqFromCSV();
    updateCustomerInCsv(custArray.data[i]);
    return "\"Added Accepted Loan Request in CPP\"";
}

/*
The only purpose of this function is to delete
the loan request permanently from the CSV file
to respect the FIFO system
*/
string declineLoanReq(const string&){
    deleteLoanReqFromCSV();
    return "\"[DEBUG@declineLoanReq]: Deleted loan req from csv\"";
}

string sendTransactionsJS(const string&){
    string combined;
    string info;
    int count=LoggedInCustomer.transactions.top+1;
    for (int i = 0; i <count; i++)
    {
    info=
    LoggedInCustomer.transactions.data[i].accountNumber+"*"+
    to_string(LoggedInCustomer.transactions.data[i].amount)+"*"+
    dateToString(LoggedInCustomer.transactions.data[i].date)+"*"+
    LoggedInCustomer.transactions.data[i].ID+"*"+
    to_string(LoggedInCustomer.transactions.data[i].type);
        if(i==count-1){
            combined+=info;
        }else{
            combined+=info+"/";
        }
    }
    return "{\"data\":\"" + combined + "\"}";
}
string undoTranCPP(const string&){
    if(isEmpty(LoggedInCustomer.transactions)){
        return "\"false\"";
    }else{
        Transaction t = top(LoggedInCustomer.transactions);
        if (compareDates(t.date,CurrentDate)!=-1){
            Transaction val=pop(LoggedInCustomer.transactions);
            updateCustomerInCsv(LoggedInCustomer);
            return "\"true\"";
        }
        else{
            cout<<"Cannot undo old transactions"<<endl;
            return "\"falseOld\"";
        }
    }
    
}
string sendEmployeeCount(const string&){
    return "{\"data\":\"" + to_string(EmplArray.size) + "\"}";
}

string sendLoansOfCustomer(const string& idJSON){
    string id = unJSON(idJSON); //only contains customer ID
    int cus_index = searchByID(custArray,id);
    string sent = "[";
    string loanJSONString;
    DNode* current = custArray.data[cus_index].loans.head;
    while(current){
        loanJSONString = "{\"id\":\"" + current->data.ID                          + "\","
                        + "\"type\":\"" + loanTypeStr(current->data.type)         + "\","
                        + "\"status\":\"" + to_string(current->data.status)       + "\","
                        + "\"amount\":\"" + to_string(current->data.pr_amount)    + "\","
                        + "\"itr\":\"" + to_string(current->data.it_rate*100)     + "\","
                        + "\"paid\":\"" + to_string(current->data.am_paid)        + "\","
                        + "\"rmn\":\"" + to_string(current->data.rm_balance)      + "\","
                        + "\"start\":\"" + dateToString(current->data.start_date) + "\","
                        + "\"end\":\"" + dateToString(current->data.end_date)     + "\"}";
        current = current->next;
        //if it's the last loan, don't add comma in the end
        sent += loanJSONString + (current == nullptr ? "" : ",");
    }
    sent += "]";
    return sent;
}

string updateLoanStatusOfCustomer(const string& statusJSON){
    string info[3];
    string unjson = unJSON(statusJSON);
    //ID*LoanID*newStatus
    splitStr(unjson,'*',info,3);
    int c_idx = searchByID(custArray,info[0]);
    if(c_idx == -1) {
        cerr << "[DEBUG@updateLoanStatusOfCustomer]: unable to find customer" << endl;
        return "\"fail\"";
    }
    int l_idx  = searchByID(custArray.data[c_idx].loans,info[1]);
    if(l_idx == -1){
        cerr << "[DEBUG@updateLoanStatusOfCustomer]: unable to find loan of customer" << endl;
        return "\"fail\"";
    }
    DNode* cur = custArray.data[c_idx].loans.head;
    for(int i = 1; i < l_idx; i++){
        cur = cur->next;
    }
    cur->data.status = stoi(info[2]);
    updateCustomerInCsv(custArray.data[c_idx]);
    return "\"Updated Loan(" + info[1] + ") Status Of Customer " + info[0] + " to " + info[2] + "\"";
}
string sendEarliestEmpl(const string&){
    Employee e=earliestEmployee();
    string eString=e.ID+"*"+e.Name+"*"+e.LastName+"*"+e.Adress+"*"+to_string(e.Salary)+"*"+dateToString(e.HireDate)+"*"+e.bankBranch+"*"+e.password;
    return "{\"data\":\"" + eString + "\"}";

}
string sendLatestEmpl(const string&){
    Employee e=latestEmployee();
    string eString=e.ID+"*"+e.Name+"*"+e.LastName+"*"+e.Adress+"*"+to_string(e.Salary)+"*"+dateToString(e.HireDate)+"*"+e.bankBranch+"*"+e.password;
    return "{\"data\":\"" + eString + "\"}";

}

string sendTransOfCustomer(const string& idJSON){
    string id = unJSON(idJSON); //only contains customer ID
    int cus_index = searchByID(custArray,id);
    string sent = "[";
    string transJSONString;
    Stack copy = copyStack(custArray.data[cus_index].transactions);
    Transaction tr;
    while(!isEmpty(copy)){
        tr = pop(copy);
        transJSONString = "{\"tid\":\"" + tr.ID                     + "\","
                        + "\"cid\":\"" + tr.accountNumber           + "\","
                        + "\"type\":\"" + transTypeToStr(tr.type)   + "\","
                        + "\"amount\":\"" + to_string(tr.amount)    + "\","
                        + "\"start\":\"" + dateToString(tr.date)    + "\"}";
        //if it's the last transaction, don't add comma in the end
        sent += transJSONString + (isEmpty(copy) ? "" : ",");
    }
    sent += "]";
    return sent;
}

// --- SETUP FUNCTIONS ---


void setupBindings() {  // binds functions to JavaScript so that they're visible and usable
    w.bind("closeWindow", closeWindow);
    //w.bind("sendDate",getDateJS);
    w.bind("getInfo", getInfo); //sends general information about session : bank branch and date
    w.bind("goToPage", goToPageCpp);
    w.bind("sendRegCusInfo",createNewCustomer);
    w.bind("getLoansLine",sendLoanInfo);
    w.bind("sendLoanToCPP",receiveLoanReq);
    w.bind("modEmployee",modifyEmployee);
    w.bind("delEmployee",deleteEmployee);
    w.bind("getCustomerLine",sendCustomerLine);
    w.bind("getEmployeeLine",sendEmployeeLine);
    w.bind("getEarliestEmployee",sendEarliestEmpl);
    w.bind("getLatestEmployee",sendLatestEmpl);
    w.bind("CustLoginCPP",CustLoginCpp);
    w.bind("EmplLoginCPP",EmplLoginCpp);
    w.bind("getLoggedEmployeeInfoCPP",sendEmpLoggedInfoJS);
    w.bind("getCustomerCount",sendCustomerCount);
    w.bind("getEmployeeCount",sendEmployeeCount);
    w.bind("getLoanCount",sendLoanCountJS);
    w.bind("addEmployeeCPP",addEmployee);
    w.bind("getLoggedInCustomerInformationFromCPlusPlus",sendCusLoggedInfoJS); //chkoun ya3mel atwel esm function challenge
    w.bind("depositCPP",deposit);
    //w.bind("statusChangeCPP",changeStatusLoan);
    w.bind("receiveQueueSize",sendSizeOfQueue);
    w.bind("receiveCurrentLoanReq",sendCurrentLoanReq);
    w.bind("sendAcceptedLoanReq",addAcceptedLoanReq);
    //w.bind("sendAcceptedLoanReq",receiveAcceptedLoanReq);
    w.bind("changeStatusCPP", changeStatus);
    w.bind("withdrawCPP",withdraw);
    w.bind("getTransactionCPP",sendTransactionsJS);
    w.bind("undoTranCPP",undoTranCPP);
    //w.bind("statusChangeCPP",changeStatusLoan);
    w.bind("deleteCompletedLoans",deleteLoan);
    
    w.bind("receiveLoansOfCustomer",sendLoansOfCustomer);
    w.bind("changeLoanStatusOfCustomer",updateLoanStatusOfCustomer);
    w.bind("declineLoanReq",declineLoanReq);
    w.bind("receiveTransOfCustomer",sendTransOfCustomer);
}

void setupWebView() {
    w.set_title("Banking System");
    w.set_size(960, 720, WEBVIEW_HINT_NONE);

    setupBindings();
    w.navigate(path("index.html")); 
    //path is required to get the absolute path and not relative , na3rech 3leh relative ma 5dmtech
}

// --- MAIN ---
int main() {
    //y7el lconsole
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    getDateFromCSV();

    init_customerArray(custArray);
    cout<<"*********************************"<<endl;
    init_employeeArray(EmplArray);
    init_completedLoansList();
    init_TransactionList();

    cout << "[C++] Hello, console!" << endl;

    globalSessBank = randomBank();
    cout << "[C++] Loaded Bank: " << globalSessBank.branchName << " (" << globalSessBank.ID << ")" << endl;

    setupWebView();

    w.run();
    destroyQueue(currentLoanReqs);
    //LEZEM NA3MLOU DESTROY L AY HAJA DYNAMIC 5DEMNA BEHA
    return 0;
}
