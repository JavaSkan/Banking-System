/* 
#include <windows.h>
#include <webview.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "InterfaceFuncs.hpp"

// --- GLOBAL VARIABLES ---
webview::webview w(true, nullptr);

string lastJsValue;
string Cus_acc_type;
string Cus_name;
Bank globalSessBank; // Store the current bank globally

// --- UTILITY FUNCTIONS ---

SList<Bank> BranchesList() {
    ifstream file("assets/BankBranches.csv"); 
    SList<Bank> BL = createList<Bank>();
    if(!file.is_open()){
        cerr << "Cannot open file: assets/BankBranches.csv" << endl;
        return BL;
    }
    string line;
    int pos = 1;
    while(getline(file, line)){
        stringstream ss(line);
        Bank data;
        if(!getline(ss, data.branchName, ',') || !getline(ss, data.ID, ',')) continue; 
        insert<Bank>(&BL, data, pos++);
    }
    return BL;
}

Bank randomBank() {
    SList<Bank> BL = BranchesList();
    int size = listSize<Bank>(BL);
    if(size == 0) {
        Bank dummy; dummy.branchName="Unknown"; dummy.ID="0"; 
        return dummy;
    }
    srand((unsigned int)time(NULL)); 
    int idx = rand() % size + 1;
    return getElement<Bank>(BL, idx);
}

//USUAL FUNCTIONS

//tna7ilek el [] mta3 json
string unJSON(const string& input) {
    string result;
    for(char c : input){
        if(c!='['&&c!='"'&&c!=']'){
            result+=c;
        }
    }
    return result;
}
//tesna3lek absolute path b variable file name ( faza bech nbadel men page l page)
string path(string togoto) {
    char fullPath[MAX_PATH];
    string combined = "gui\\" + togoto;           // concatenate strings properly
    GetFullPathNameA(combined.c_str(), MAX_PATH, fullPath, nullptr); 
    string html_url = "file:///" + string(fullPath);
    return html_url;
}
void splitStr(const string& s, char splitter, string& left, string& right) {
    int pos = s.find(splitter);
    if (pos != string::npos) {
        left = s.substr(0, pos);
        right = s.substr(pos + 1);
    } else {
        left = s;
        right = "";
    }
}

bool createSmallTestFile(const string& filename, const string& str1, const string& str2) {
    ofstream file(filename, ios::out); 
    if (!file.is_open()) {
        cerr << "FAILED to create file: " << filename << endl;
        return false;
    }
    cout << "[C++] SUCCESS: File created at: " << filename << endl;
    file << str1 << "\n" << str2 << "\n";
    file.close();
    return true;
}

// --- WEBVIEW CALLBACK FUNCTIONS ---


string sendtocpp(const string& msg) {
    cout<<msg;
    lastJsValue=msg;createSmallTestFile("testbelehie5dem.txt",lastJsValue,"");
    return "\"ok\"";
}
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
string getfromcpp(const string&) {
    return lastJsValue; // valid JSON string
}

string getBranchInfo(const string&) {
    string combined = globalSessBank.branchName + "*" + globalSessBank.ID;
    return "{\"data\":\"" + combined + "\"}";
}

// --- SETUP FUNCTIONS ---
void setupBindings() {
    w.bind("closeWindow", closeWindow);
    w.bind("getBranchInfo", getBranchInfo);
    w.bind("getInfo", sendtocpp);
    w.bind("getFromCpp", getfromcpp);
    w.bind("goToPage", goToPageCpp);
    
}
void setupWebView() {

    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);

    setupBindings();

    w.navigate(path("index.html"));
    
}
*/