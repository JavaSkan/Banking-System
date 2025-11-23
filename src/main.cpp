#include <windows.h> // for GetFullPathNameA
#include <webview.h>
#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/DataStructsFunctions.hpp"
#include "../include/CustomerInterface.hpp"
#include "../include/EmployeeInterface.hpp"
#include "../include/bankBranch.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream> // for files
#include <sstream> // for stringstream

using namespace std;
// Global variable to store value from JS
string lastJsValue;
// Global webview
webview::webview w(true, nullptr);

//function ta3melek lista ta3 bounouk
TEMPLATE
SList<Bank>BranchesList() {
    ifstream file("assets/BankBranches.csv");
    if (!file.is_open()) {
        cerr << "Cannot open file!" << endl;
        return createList<Bank>();   // return EMPTY LIST
    }

    SList<Bank> BL = createList<Bank>();
    Bank data;
    string line;
    int pos = 1;

    while (getline(file, line)) {
        stringstream ss(line);
        if (!getline(ss, data.branchName, ',') || !getline(ss, data.ID, ',')) {
            continue; // skip malformed lines
        }
        insert<Bank>(&BL, data, pos);
        pos++;
    }

    file.close();
    return BL;
}

// Helper: escape string for JSON
string json_escape(const string &s) {
    string result = "\"";
    for (char c : s) {
        switch(c) {
            case '\"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default: result += c; break;
        }
    }
    result += "\"";
    return result;
}

// Setup WebView
void setup() {
    char fullPath[MAX_PATH];
    GetFullPathNameA("gui\\index.html", MAX_PATH, fullPath, nullptr);
    string html_url = "file:///" + string(fullPath);
    
    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);
    w.navigate(html_url);
}


// Bind C++ message to JS
void init_CppJs(const string &obj) {
    w.bind("getCppObj", [obj](const string&) -> string {
        return json_escape(obj); // must be valid JSON string
    });
}

// Bind JS to C++ to receive values
void init_JsCpp() {
    w.bind("sendToCppFunc", [](const string &arg) -> string {
        lastJsValue = arg;  // store for later use
        return "\"\"" ;
    });
}

// Bind JS function to C++ close action
void init_quit(){
    w.bind("closeWindow", [](const std::string&) -> string {
        w.terminate(); // closes the WebView window
        return "\"Closed\""; // must return valid JSON string
    });
}
void SessBank(const Bank& sess_bank) {
    w.bind("getBranchInfo", [sess_bank](const std::string&) -> std::string {
        std::string combined = sess_bank.branchName + "*" + sess_bank.ID;
        return "{\"data\":\"" + combined + "\"}";
    });
}



Bank randomBank(){
    SList<Bank> BL=BranchesList<Bank>();
    int BL_size=listSize<Bank>(BL);
    Bank B=getElement<Bank>(BL,random(1,BL_size));
    return(B);
    /*
    Bank test;
    test.branchName="Tunis";
    test.ID="1";
    return(test);
    */
}


int main() {
    setup();
    init_quit();
    init_CppJs("");
    init_JsCpp();
    Bank random_bank=randomBank();
    SessBank(random_bank);
    w.run();
    return 0;
}
