#include <iostream>
#include <string>
#include <cctype>
#include "SinglyLinkedListMeth.hpp"
#define TEMPLATE template <typename T>
using namespace std;

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
int IDGen(const List<T>&L,char type){
    int ID;
    if(isEmpty(L)){
        switch (type){
        case 'E':
            ID=10;
            break;
        case 'C':
            ID=11;
            break;
        case 'L':
            ID=12;
            break;
        case 'T':
            ID=13;
            break;
    }
    }  else {
        Node<T>* current = L.head;
        while (current->next != nullptr) {
            current = current->next;
        }
        ID = current->data.ID + 10;  // now current is valid
    }
    return ID; 
}

