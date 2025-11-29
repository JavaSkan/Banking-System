#include <webview.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

#include <MiscFuncs.hpp>
#include <SinglyLinkedListMeth.hpp>
#include <customer.hpp>
#define TEMPLATE template <typename T>
using namespace std;

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
bool isValidEmail(const string& email) {
    int atPos = -1; // index to search for @
    for (int i = 0; i < (int)email.size(); i++) {
        if (email[i] == '@') {
            if (atPos != -1) return false;
            atPos = i;
        }
    }
    if (atPos == -1) return false;
    // check if @ exists once

    string local = email.substr(0, atPos);
    string domain = email.substr(atPos + 1);

    if (local.empty() || domain.empty()) return false;

    if (local.front() == '.' || local.back() == '.') return false;
    int i=0;


    while (i < (int)local.size()) {
        char c = local[i];
        if (!(isalnum(c) || c == '.' || c == '_' || c == '-')) return false;
        if (i > 0 && c == '.' && local[i - 1] == '.') return false;
        i++;
    }

    int dotFound = 0;
    for (int i = 0; i < (int)domain.size(); i++) {
        if (domain[i] == '.') {
            dotFound = 1;
            break;
        }
    }
    if (!dotFound) return false;

    int start = 0;
    while (true) {
        int end = -1;
        for (int i = start; i < (int)domain.size(); i++) {
            if (domain[i] == '.') {
                end = i;
                break;
            }
        }

        string label;
        if (end == -1) label = domain.substr(start);
        else label = domain.substr(start, end - start);

        if (label.empty()) return false;
        if (!isalnum(label.front()) || !isalnum(label.back())) return false;

        for (int i = 0; i < (int)label.size(); i++) {
            char c = label[i];
            if (!(isalnum(c) || c == '-')) return false;
        }

        if (end == -1) break;
        start = end + 1;
    }

    int lastDot = -1;
    for (int i = 0; i < (int)domain.size(); i++) {
        if (domain[i] == '.') lastDot = i;
    }
    string tld = domain.substr(lastDot + 1);
    if ((int)tld.size() < 2) return false;

    return true;
}


int random(int min, int max) {
    static bool SEEDED = false; //constant to not reseed (faza comme quoi)
    if (!SEEDED) {
        srand(static_cast<unsigned>(time(nullptr))); // :)
        SEEDED = true;
    }
    int randomNumber = min + rand() % (max - min + 1);
    return randomNumber;
}


long long strToLongLong(const string& s) { //wlh ktebha aziz , fa5r el c++
    long long result = 0;

    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9')
            return 0;

        result = result * 10 + (s[i] - '0');
    }

    return result;
}


