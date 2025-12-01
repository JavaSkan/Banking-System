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

using namespace std;

// --- GUI SETUP ---
webview::webview w(true, nullptr);
// --- GLOBAL VARIABLES ---
string lastJsValue;
string Cus_acc_type;
string Cus_name;
Customer LoggedInCustomer;



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

// --- SETUP FUNCTIONS ---
void setupBindings() {
    w.bind("closeWindow", closeWindow);
    w.bind("sendDate",getDateJS);
    w.bind("getInfo", getInfo);
    w.bind("goToPage", goToPageCpp);
    w.bind("sendRegCusInfo",createNewCustomer);
    w.bind("getLoansLine",sendLoanInfo);
}
void setupWebView() {
    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);
    setupBindings();
    w.navigate(path("CustomerInterface.html"));
}

// --- MAIN ---
int main() {
    //y7el lconsole
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    LoggedInCustomer.loans=createList();
    insert(&LoggedInCustomer.loans,{"L001", 1, 5, 200, 0.2, 100, 100, {1,1,2025},{2,2,2027}},LoggedInCustomer.loans.size+1);
    insert(&LoggedInCustomer.loans,{"L002", 1, 5, 200, 0.2, 100, 100, {1,1,2025},{2,2,2027}},LoggedInCustomer.loans.size+1);
    insert(&LoggedInCustomer.loans,{"L003", 1, 5, 200, 0.2, 100, 100, {1,1,2025},{2,2,2027}},LoggedInCustomer.loans.size+1);
    insert(&LoggedInCustomer.loans,{"L004", 1, 5, 200, 0.2, 100, 100, {1,1,2025},{2,2,2027}},LoggedInCustomer.loans.size+1);
    Array CustArray=createCustomerArray<Customer>();
    
    init_customerArray(CustArray);


    cout << "[C++] Hello, console!" << endl;

    globalSessBank = randomBank();
    cout << "[C++] Loaded Bank: " << globalSessBank.branchName << " (" << globalSessBank.ID << ")" << endl;

    setupWebView();

    w.run();
    return 0;
}
