#include <windows.h>
#include <webview.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/DataStructsFunctions.hpp"
#include "../include/bankBranch.hpp"

using namespace std;

// Global WebView
webview::webview w(true, nullptr);

// Store last JS value
string lastJsValue;

// Escape string for JSON
string json_escape(const string &s) {
    string result = "\"";
    for (char c : s) {
        switch(c){
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

// Read bank branches from CSV
SList<Bank> BranchesList() {
    ifstream file("assets/BankBranches.csv");
    SList<Bank> BL = createList<Bank>();
    if(!file.is_open()){
        cerr << "Cannot open file!" << endl;
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

// Pick a random bank from the list
Bank randomBank() {
    SList<Bank> BL = BranchesList();
    int size = listSize<Bank>(BL);
    if(size == 0) {
        Bank dummy; dummy.branchName="Unknown"; dummy.ID="0"; return dummy;
    }
    srand((unsigned int)time(0));
    int idx = rand() % size + 1;
    return getElement<Bank>(BL, idx);
}

// Setup WebView bindings
void setupBindings(Bank &sess_bank) {
    // Send value from JS to C++
    w.bind("sendToCppFunc", [](const string &arg) -> string {
        lastJsValue = arg;
        cout << "Value from JS: " << arg << endl;
        return "\"\"";  // must be valid JSON
    });

    // Close window
    w.bind("closeWindow", [](const string&) -> string {
        w.terminate();
        return "\"Closed\"";
    });

    // Get branch info
    w.bind("getBranchInfo", [sess_bank](const string&) -> string {
        string combined = sess_bank.branchName + "*" + sess_bank.ID;
        return "{\"data\":\"" + combined + "\"}";
    });

    // **CORRECTED CHECKPLS BINDING (USING w.eval())**
    w.bind("checkpls", [](const std::string &arg) -> std::string {
        std::cout << "[C++] checkpls called with: " << arg << std::endl;

        bool isValid = true; 
        
        // Validation logic: check if empty or contains non-alpha characters
        if (arg.empty()) {
            isValid = false;
        } else {
            for (char c : arg) {
                if (!isalpha(static_cast<unsigned char>(c))) {
                    isValid = false;
                    break;
                }
            }
        }
        
        // 1. Convert boolean to string "true" or "false"
        std::string result_str = isValid ? "true" : "false";

        // 2. Use w.eval() to execute a JavaScript function 'handleCheckResult'
        // This is highly reliable for sending results back.
        std::string js_call = "handleCheckResult(" + result_str + ");";
        w.eval(js_call);

        // 3. Return an empty, valid JSON string to satisfy the binding's signature
        return "\"\"";
    });
    
    // The previous getInfo binding is removed/replaced by checkpls

    // Return a test string to JS
    w.bind("getCppObj", [](const string&) -> string {
        return "\"Hello from C++!\"";
    });
}

// Setup WebView
void setupWebView(Bank &sess_bank) {
    char fullPath[MAX_PATH];
    GetFullPathNameA("gui\\index.html", MAX_PATH, fullPath, nullptr);
    string html_url = "file:///" + string(fullPath);

    w.set_title("Banking System");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);

    setupBindings(sess_bank);

    w.navigate(html_url);
}

int main() {
    Bank bank = randomBank();
    cout << "Loaded Bank: " << bank.branchName << " (" << bank.ID << ")" << endl;

    setupWebView(bank);
    w.run();
    return 0;
}