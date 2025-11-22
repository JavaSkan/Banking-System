#include <windows.h> // for GetFullPathNameA
#include <webview.h>
#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/CustomerInterface.hpp"
#include "../include/EmployeeInterface.hpp"
#include <iostream>
#include <string>

using namespace std;

webview::webview w(true, nullptr);
// Global webview

// Global variable to store value from JS
string lastJsValue;

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

    w.set_title("HTML Window");
    w.set_size(800, 600, WEBVIEW_HINT_NONE);
    w.navigate(html_url);
}


// Bind C++ message to JS
void CppJs(const string &obj) {
    w.bind("getCppObj", [obj](const string&) -> string {
        return json_escape(obj); // must be valid JSON string
    });
}

// Bind JS to C++ to receive values
void JsCpp() {
    w.bind("sendToCppFunc", [](const string &arg) -> string {
        cout << "Received from JS: " << arg << endl;
        lastJsValue = arg;  // store for later use
        return json_escape("C++ got: " + arg);
    });
}

int main() {
    cout<<"test";
    setup();

    // Send value from C++ to JS
    string message = "Hello from C++!";
    CppJs(message);
    JsCpp();
    cout << lastJsValue;
    CppJs(lastJsValue);
    w.run();

    return 0;
}
