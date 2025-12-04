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
Queue* currentLoanReqs = createQueue();


string getSpecificLoan(int pos){
    Loan current;
    string LoansString;
    current=getElement(LoggedInCustomer.loans,pos);
    LoansString=loanToString(current);
    cout<<endl<<LoansString;
    LoansString=LoansString.substr(5,LoansString.size()-6);
    cout<<LoansString;
    return LoansString ;
   //return "test"+to_string(pos);
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
        cout<<password<<"/"<<custArray.data[CustomerPos].password;
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

string sendLoggedInfoJS(const string&){
    string info = LoggedInCustomer.name + "*" + to_string(LoggedInCustomer.balance);
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

string sendLoanInfo(string i){return "{\"data\":\"" + getSpecificLoan(stoi(unJSON(i)))+ "\"}";}


string closeWindow(const string&) {
    w.terminate();
    return "\"Closed\"";
}
string goToPageCpp(const string& pageJSON) {
    cout<<endl<<"test";
    string page=unJSON(pageJSON);
    cout<<pageJSON<<" "<<page;
    w.navigate(path(page));
    return "\"page changed\"";
}
string getInfo(const string&) {
    string sDate = to_string(CurrentDate.day) + "-" + to_string(CurrentDate.month) + "-" + to_string(CurrentDate.year);
    string combined = globalSessBank.branchName + "*" + globalSessBank.ID+'*'+sDate;
    return "{\"data\":\"" + combined + "\"}";
}

string receiveLoanFromJS(const string& infoJSON){  
    ofstream file("assets/LoanRequests.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/LoanRequests.csv" << endl;
    }else{
        if(LoggedInCustomer.ID == ""){
            cerr << "[ERROR-receiveLoanFromJS]: No logged in customer" << endl;
            return "\"NOLOGCUS\"";
        }
        string info = unJSON(infoJSON);
        cout << "[DEBUG-receiveLoanFromJS/rep]: " << LoggedInCustomer.ID << endl;
        string loanRequestLine = LoggedInCustomer.ID + "," + replace(info,"*",",");
        file << loanRequestLine << endl;
    }
    file.close();
    return "\"true\"";
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


// --- SETUP FUNCTIONS ---
void setupBindings() {
    w.bind("closeWindow", closeWindow);
    w.bind("sendDate",getDateJS);
    w.bind("getInfo", getInfo);
    w.bind("goToPage", goToPageCpp);
    w.bind("sendRegCusInfo",createNewCustomer);
    w.bind("getLoansLine",sendLoanInfo);
    w.bind("sendLoanToCPP",receiveLoanFromJS);
    w.bind("CustLoginCPP",CustLoginCpp);
    w.bind("EmplLoginCPP",EmplLoginCpp);
    w.bind("getLoanCount",sendLoanCountJS);
    w.bind("sendRegEmplInfo",addEmployee);
    w.bind("getLoggedInCustomerInformationFromCPlusPlus",sendLoggedInfoJS); //chkoun ya3mel atwel esm function challenge
    w.bind("depositCPP",deposit);
    w.bind("withdrawCPP",withdraw);
    w.bind("getTransactionCPP",sendTransactionsJS);
    //w.bind("statusChangeCPP",changeStatusLoan);

}
void setupWebView() {
    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);
    HWND h = (HWND) w.window().value();
    RemoveMenu(GetSystemMenu(h, FALSE), SC_CLOSE, MF_BYCOMMAND);
    SetWindowLong(h, GWL_STYLE, GetWindowLong(h, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));
    SetWindowPos(h, 0, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);

    setupBindings();
    w.navigate(path("index.html"));
}


// --- MAIN ---
int main() {
    //y7el lconsole
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    init_customerArray(custArray);
    cout<<"*********************************"<<endl;
    init_employeeArray(EmplArray);

    cout << "[C++] Hello, console!" << endl;

    globalSessBank = randomBank();
    cout << "[C++] Loaded Bank: " << globalSessBank.branchName << " (" << globalSessBank.ID << ")" << endl;

    setupWebView();

    w.run();
    destroyQueue(currentLoanReqs);
    //LEZEM NA3MLOU DESTROY L AY HAJA DYNAMIC 5DEMNA BEHA
    return 0;
}
