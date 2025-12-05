#include <iostream>
#include "SinglyLinkedListMeth.hpp"


using namespace std;
#define TEMPLATE template <typename T>
//---------------------------------------------------------------------------------------------------------
//          EVERY FUNCTION ADDED HERE SHOULD HAVE IT'S HEADER ADDED TO 'SinglyLinkedListMeth.hpp'
//---------------------------------------------------------------------------------------------------------

TEMPLATE
SList<T> createList() {
    return SList<T>{ nullptr, 0 };
}
TEMPLATE
bool CompareLists(const SList<T>& L1, const SList<T>& L2) {
if (L1.size != L2.size) return false;

SNode<T>* p1 = L1.head;
SNode<T>* p2 = L2.head;

while (p1) {
    if (p1->data.ID != p2->data.ID) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}

TEMPLATE
SList<T> CopyList(const SList<T>& L) {
    SList<T> newList = createList<T>();
    SNode<T>* current = L.head;
    SNode<T>* tail = nullptr;

    while (current) {
        SNode<T>* n = createNode(current->data);
        if (!n) {
            cerr << "\nMemory allocation failed while copying\n";
            destroyList(&newList);
            return createList<T>();
        }

        if (!newList.head) {
            newList.head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }

        current = current->next;
    }

    newList.size = L.size;
    return newList;
}


TEMPLATE

void displayList(const SList<T>& L) {
    if (isEmpty(L)) {
        cout << "List is empty\n";
        return;
    }
    SNode<T>* current = L.head;
    while (current) {
    cout << current->data << " -> ";
    current = current->next;
    }
    cout << "NULL\n";
}



TEMPLATE

void destroyList(SList<T>* L) {
    if (!L) return;
    SNode<T>* current = L->head;
    while (current) {
        SNode<T>* temp = current;
        current = current->next;
        destroyNode(temp);
    }
    L->head = nullptr;
    L->size = 0; 
}
TEMPLATE
T getElement(const SList<T>& L, int pos) {
    if (isEmpty(L)) {
        cerr << "\nList is empty\n";
        return {};
    }
    if (pos < 1 || pos > L.size) {
        cerr << "\nInvalid position\n";
        return {};
    }
    SNode<T>* current = L.head;
    for (int i = 1; i < pos; i++) {
        current = current->next;
    }
    return current->data;
}
TEMPLATE
bool removeAt(SList<T>* L, int pos) {
    if (!L || isEmpty(*L)) {
        cerr << "\nList is empty";
        return false;
    }
    if (pos < 1 || pos > L->size) {
        cerr << "\nInvalid position";
        return false;
    }
    SNode<T>* prev = nullptr;
    SNode<T>* current = L->head;
    if (pos == 1) {
        L->head = current->next;
    }else {
        for (int i = 1; i < pos; i++) {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
    }
    destroyNode(current);
    L->size--;
    return true;
}
TEMPLATE
bool insert(SList<T>* L, T e, int pos) {
    if (!L) return false;
    if (pos < 1 || pos > L->size + 1) {
        cerr << "\nInvalid position";
        return 0;
    }
    SNode<T>* n = createNode(e);
    if (!n) return 0;
    if (pos == 1) {
        n->next = L->head;
        L->head = n;
    }else {
        SNode<T>* prev = nullptr;
        SNode<T>* current = L->head;
        for (int i = 1; i < pos; i++) {
            prev = current;
            current = current->next;
        }
        prev->next = n;
        n->next = current;
    }
    L->size++;
    return true;
}
TEMPLATE

bool isEmpty(const SList<T>& L) {
    return L.size == 0;
}
TEMPLATE

int listSize(const SList<T>& L) {
    return L.size;
}
TEMPLATE

bool isFull(const SList<T>& L) {
    SNode<T>* test = new (nothrow) SNode<T>;
    if (!test) return true;
    delete test;
    return false;
}
TEMPLATE

void destroyNode(SNode<T>* Snode) {
    delete Snode;
}
TEMPLATE

SNode<T>* createNode(T value) {
    SNode<T>* Snode = new (nothrow) SNode<T>{ value, nullptr };
    if (!Snode) {
        cerr << "\nMemory allocation failed for Snode\n";
    }
    return Snode;
}

TEMPLATE

SList<T> stringToSL(string s){
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

