#include <iostream>
#include "../headers/SinglyLinkedListMeth.hpp"
using namespace std;
#define TEMPLATE template <typename T>
//---------------------------------------------------------------------------------------------------------
//          EVERY FUNCTION ADDED HERE SHOULD HAVE IT'S HEADER ADDED TO 'SinglyLinkedListMeth.hpp'
//---------------------------------------------------------------------------------------------------------

TEMPLATE
List<T> createList() {
    return List<T>{ nullptr, 0 };
}
TEMPLATE
bool CompareLists(const List<T>& L1, const List<T>& L2) {
if (L1.size != L2.size) return false;

Node<T>* p1 = L1.head;
Node<T>* p2 = L2.head;

while (p1) {
    if (p1->data.ID != p2->data.ID) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}

TEMPLATE
List<T> CopyList(const List<T>& L) {
    List<T> newList = createList<T>();
    Node<T>* current = L.head;
    Node<T>* tail = nullptr;

    while (current) {
        Node<T>* n = createNode<T>(current->data);
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

void displayList(const List<T>& L) {
    if (isEmpty(L)) {
        cout << "List is empty\n";
        return;
    }
    Node<T>* current = L.head;
    while (current) {
    cout << current->data << " -> ";
    current = current->next;
    }
    cout << "NULL\n";
}



TEMPLATE

void destroyList(List<T>* L) {
    if (!L) return;
    Node<T>* current = L->head;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        destroyNode(temp);
    }
    L->head = nullptr;
    L->size = 0; 
}
TEMPLATE
int getElement(const List<T>& L, int pos) {
    if (isEmpty(L)) {
        cerr << "\nList is empty\n";
        return -1;
    }
    if (pos < 1 || pos > L.size) {
        cerr << "\nInvalid position\n";
        return -1;
    }
    Node<T>* current = L.head;
    for (int i = 1; i < pos; i++) {
        current = current->next;
    }
    return current->data;
}
TEMPLATE
bool removeAt(List<T>* L, int pos) {
    if (!L || isEmpty(*L)) {
        cerr << "\nList is empty";
        return false;
    }
    if (pos < 1 || pos > L->size) {
        cerr << "\nInvalid position";
        return false;
    }
    Node<T>* prev = nullptr;
    Node<T>* current = L->head;
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
bool insert(List<T>* L, T e, int pos) {
    if (!L) return false;
    if (pos < 1 || pos > L->size + 1) {
        cerr << "\nInvalid position";
        return 0;
    }
    Node<T>* n = createNode(e);
    if (!n) return 0;
    if (pos == 1) {
        n->next = L->head;
        L->head = n;
    }else {
        Node<T>* prev = nullptr;
        Node<T>* current = L->head;
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

bool isEmpty(const List<T>& L) {
    return L.size == 0;
}
TEMPLATE

int listSize(const List<T>& L) {
    return L.size;
}
TEMPLATE

bool isFull(const List<T>& L) {
    Node<T>* test = new (nothrow) Node<T>;
    if (!test) return true;
    delete test;
    return false;
}
TEMPLATE

void destroyNode(Node<T>* node) {
    delete node;
}
TEMPLATE

Node<T>* createNode(T value) {
    Node<T>* node = new (nothrow) Node<T>{ value, nullptr };
    if (!node) {
        cerr << "\nMemory allocation failed for node\n";
    }
    return node;
}

TEMPLATE

bool isUnique(const List<T>& L, int value) {
    Node<T>* current = L.head;
    while (current != nullptr) {
        if (current->data.ID == value) {
            return false;
        }
        current = current->next;
    }
    return true; 
}
TEMPLATE
int IDGen(const List<T>&L,char type){
    int ID;
    if(isEmpty(L)){
        switch (type){
        case 'E':
            ID=10;
        case 'C':
            ID=11;
        case 'L':
            ID=12;
        case 'T':
            ID=13;
    }
    }else{
        Node<T>* current = L.head;
        while (current != nullptr) {
            current = current->next;
        }
        ID=(current->data.ID)+10 
    }
    return ID; 
}
