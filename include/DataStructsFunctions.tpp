#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "SinglyLinkedList.hpp"
#include "arrayMeth.hpp"
#include "customer.hpp"
using namespace std;

//do u remember , the 21st night of september?♫♪♫♪

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
TEMPLATE

bool isUnique(const SList<T>& L, string value) {
    SNode<T>* current = L.head;
    while (current != nullptr) {
        if (current->data.ID == value) {
            return false;
        }
        current = current->next;
    }
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
TEMPLATE
void IDGenCustomer(const Array<T>& arr,T& e){
    bool test=false;
    while (!test){
        int temp = random(1000000000,1999999999);
        long long ID = temp*1000+random(0,999);
        string sID = to_string(ID);
        e.ID = sID;
        test = isUniqueInArray(arr,e);
    }
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
string RIBGen(Customer Cus){
    string RIB = "67"+Cus.branchCode+Cus.ID;
    long long temp = strToLongLong(RIB);
    RIB = RIB + to_string(97 - (temp%97));
    return(RIB);
}

string IBANGen(Customer Cus){
    string IBAN = "TN59" + RIBGen(Cus);
    return(IBAN);
}

