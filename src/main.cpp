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
#include <Customer.tpp>

using namespace std;

// --- GLOBAL VARIABLES ---
webview::webview w(true, nullptr);
// --- GUI SETUP ---
string lastJsValue;
string Cus_acc_type;
string Cus_name;

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
    Array CustArray=createCustomerArray<Customer>();
    init_customerArray(CustArray);


    cout << "[C++] Hello, console!" << endl;

    globalSessBank = randomBank();
    cout << "[C++] Loaded Bank: " << globalSessBank.branchName << " (" << globalSessBank.ID << ")" << endl;

    setupWebView();

    w.run();
    return 0;
}
