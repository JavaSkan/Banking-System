#include <windows.h> // for GetFullPathNameA
#include <webview.h>
#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/CustomerInterface.hpp"
#include "../include/EmployeeInterface.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
string lastJsValue;

webview::webview w(true, nullptr);
// Global webview

// Global variable to store value from JS

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


int main() {
    setup();
    init_quit();
    init_CppJs("");
    init_JsCpp();
    w.run();
    return 0;
}
