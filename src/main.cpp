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

using namespace std;

// --- GUI SETUP ---
webview::webview w(true, nullptr);
// --- GLOBAL VARIABLES ---
string lastJsValue;
Customer LoggedInCustomer;
Employee LoggedInEmployee;


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
    int n = splitStr(LoginInfo, '*',infoParts,2);
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
    string info = unJSON(infoJSON);
    string infoPart[3];
    //int n = splitStr(info,'*',infoPart,3);
    return "\"received loan data successfully\"";
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

}
void setupWebView() {
    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);
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
    //LEZEM NA3MLOU DESTROY L AY HAJA DYNAMIC 5DEMNA BEHA
    return 0;
}
