#include <webview.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include <MiscFuncs.hpp>


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

int findIn(const string& hay,const char needle){
    int i=0;
    int pos=-1;
    while(i<hay.size()&& pos==-1){
        if(hay[i]==needle){
            pos=i;
        }
    }
    return pos;
}

int splitStr(const string& s,char splitter,string out[],int maxParts) {
    int idx = 0;
    string current = "";

    for (char c : s) {
        if (c == splitter) {
            if (idx < maxParts)
                out[idx++] = current;

            current = "";
        } else {
            current += c;
        }
    }

    if (idx < maxParts)
        out[idx++] = current;

    return idx; // number of filled parts
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

string trim(string s){
    string out;
    int b = 0, e = s.size()-1;
    while(b < s.size() && s[b] == ' ') b++;
    while(e >= 0 && s[e] == ' ') e--;
    for(int i = b; i <= e; i++){
        if(s[i] == ' ' && s[i+1] == ' ') continue;
        out += s[i];
    }
    return out;
}

bool isAlpha(string s) {
    int i = 0;
    while(i < s.size() && (s[i] == ' ' || (s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))) i++;
    return i == s.size();
}

bool checkName(string name){
    name = trim(name);
    return name != "" && isAlpha(name);
}

bool isSub(const string& org, const string& sub, int beg, string& buf){
    int i = beg; buf = "";
    while(i < org.size() && i-beg < sub.size() && org[i] == sub[i-beg]){
        buf += org[i];
        i++;
    }
    return (i-beg) == sub.size();
}

string replace(string input, string rep, string repw){
    if(rep == "") return input;
    string out = "";
    string buf = "";
    int i = 0;
    while(i < input.size()){
        if(input[i] != rep[0]){
            out += input[i];
            i++;
            continue;
        }
        if(isSub(input,rep,i,buf)){
            out += repw;
            i += rep.size();
        }else{
            out += buf;
            i += buf.size();
        }
    }
    return out;
}

string toLower(string s) {
    string res = "";  
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A');
        }
        res = res + c;
    }
    return res;
}
string passwordGen(int size){
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&-_=+:?";
    string password;
    for(int i=0;i<size;i++){
        password+=chars[random(0,chars.size())];
    }
    return password;
}

SList<Loan> stringToSL(string s){
    SList<Loan> res = createList<Loan>();
    string sub = "";
    for(int i = 4; i < s.size()-1; i++){
        sub += (s[i] == '$' ? ' ' : s[i]);
    }
    if(sub == "") return {};
    stringstream ss;
    ss << sub;
    int size;
    ss >> size;
    string cur_loan_str;
    for(int i = 1; i <= size; i++){
        ss >> cur_loan_str;
        insert(&res,stringToLoan(cur_loan_str),res.size+1);
    }
    return res;
}

string SLToString(const SList<Loan>& sl){
    if(isEmpty(sl)) return "SLL[]";
    stringstream ss;
    ss << "SLL[" << sl.size << "$";
    SNode<Loan>* cur = sl.head;
    int i = 1;
    while(cur && i<=sl.size){
        ss << loanToString(cur->data) << (i<sl.size ? "$" : "]");
        cur = cur->next;
    }
    return ss.str();
}

string SLTrToString(const SList<Transaction>& sl){
    if(isEmpty(sl)) return "SLL[]";
    stringstream ss;
    ss << "SLL[" << sl.size << "$";
    SNode<Transaction>* cur = sl.head;
    int i = 1;
    while(cur && i<=sl.size){
        ss << transactionToString(cur->data) << (i<sl.size ? "$" : "]");
        cur = cur->next;
    }
    return ss.str();
}

SList<Transaction> stringToSLTr(string s){
    SList<Transaction> res = createList<Transaction>();
    string sub = "";
    for(int i = 4; i < s.size()-1; i++){
        sub += (s[i] == '$' ? ' ' : s[i]);
    }
    if(sub == "") return {};
    stringstream ss;
    ss << sub;
    int size;
    ss >> size;
    string cur_transaction_str;
    for(int i = 1; i <= size; i++){
        ss >> cur_transaction_str;
        insert(&res,stringToTransaction(cur_transaction_str),res.size+1);
    }
    return res;
}

int updateCompletedLoansCsv(const SList<Loan>& sl){
    ofstream file("assets/CompletedLoans.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/CompletedLoans.csv" << endl;
        file.close();
        return -1;
    }
    string line = SLToString(sl);
    file << line << endl;
    file.close();
    return 1;
}

int updateTransactionsCsv(const SList<Transaction>& sl){
    ofstream file("assets/Transactions.csv",ios::app);
    if (!file.is_open()){
        cerr << "Cannot open file : assets/Transactions.csv" << endl;
        file.close();
        return -1;
    }
    string line =SLTrToString(sl);
    file << line << endl;
    file.close();
    return 1;
}