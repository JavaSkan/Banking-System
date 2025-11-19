#include "../headers/DoublyLinkedListMeth.hpp"

D_list createList() {
    return D_list{ nullptr, nullptr, 0 };
}

void destroyList(D_list* L) {
    if (!L) return;
    Node* current = L->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        destroyNode(temp);
    }
    L->head = nullptr ;
    L->tail = nullptr;
    L->size = 0;
}

bool isEmpty(const D_list& L) {
    return L.size == 0;
}

int listSize(const D_list& L) {
    return L.size;
}

bool isFull(const D_list& L) {
    Node* test = new (nothrow) Node;
    if (!test) return true;
    delete test;
    return false;
}

bool CompareLists(const D_list& L1, const D_list& L2) {
    if (L1.size != L2.size) return false;

    Node* p1 = L1.head;
    Node* p2 = L2.head;

    while (p1) {
        if (p1->data.loadId != p2->data.loadId) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}

D_list CopyList(const D_list& L) {
    D_list newList = createList();
    Node* current = L.head;
    Node* tail = nullptr; // keep track of last node in new list
    while (current) {
        Node* n = createNode(current->data);
        if (!n) {
        cerr << "Memory allocation failed while copying\n";
            destroyList(&newList);
            return createList();
        }
        n->prev = tail; // set previous pointer
        if (!newList.head) {
            newList.head = n;
        } else {
            tail->next = n; // link previous node to new node
        }
        tail = n; // update tail
        current = current->next;
    }
    newList.tail = tail; // set tail of new list
    newList.size = L.size;
    return newList;
}

void displayList(const D_list& L) {
    if (isEmpty(L)) {
        cout << "List is empty\n";
        return;
    }
    Node* current = L.head;
    while (current) {
        displayLoan(current->data);
        current = current->next;
    }
    cout << "NULL\n";
}

Node* createNode(Loan value) {
    Node* node = new (nothrow) Node{value, nullptr, nullptr };
    if (!node) cout << "Memory allocation failed for node\n";
    return node;
}

void destroyNode(Node* node) {
    delete node;
}

Loan getElement(const D_list& L, int pos) {
    if (isEmpty(L)) {
        cerr << "List is empty\n";
        return {};
    }
    if (pos < 1 || pos > L.size) {
        cerr << "Invalid position\n";
        return {};
    }
    Node* current;
    if(L.size - pos > pos){
        current = L.head;
        for (int i = 1; i < pos; i++) {
            current = current->next;
        }
    }else{
        current = L.tail;
        for (int i = L.size; i > pos; i--) {
            current = current->prev;
        }
    }
    return current->data;
}

int insert(D_list* L, Loan e, int pos) {
    if (!L) return 0;
    if (pos < 1 || pos > L->size + 1) { //Invalid Pos
        cout << "Invalid position\n";
        return 0;
    }
    Node* n = createNode(e);
    if (!n) return 0;
    if (isEmpty(*L)) { //Empty List
        L->head = n;
        L->tail = n;
    }else if (pos == 1) { // pos = first
        n->next = L->head;
        L->head->prev = n;
        L->head = n;
    }
    else if (pos == L->size + 1) { // pos = last
        n->prev = L->tail;
        L->tail->next = n;
        L->tail = n;
    }else { // general case
        Node* current;
        Node* prev;
        if(L->size - pos > pos){
            prev = nullptr;
            current = L->head;
            for (int i = 1; i < pos; i++) {
                prev = current;
                current = current->next;
            }
        }else{
            prev = L->tail->prev;
            current = L->tail;
            for (int i = L->size; i > pos; i--) {
                current = prev;
                prev = prev->prev;
            }
        }
        prev->next = n;
        n->prev = prev;
        n->next = current;
        current->prev = n;
    }
    L->size++;
    return 1;
}

int removeAt(D_list* L, int pos) {
    if (!L || isEmpty(*L)) { //Empty List
        cout << "List is empty\n";
        return 0;
    }
    if (pos < 1 || pos > L->size) { // Invalid pos
        cout << "Invalid position\n";
        return 0;
    }
    Node* current;
    if (L->size == 1) {
        current = L->head;
        L->head = nullptr;
        L->tail = nullptr;
    }
    else if (pos == 1) { // pos = first
        current = L->head;
        L->head = L->head->next;
        L->head->prev = nullptr;
    }
    else if (pos == L->size) { // pos = last
        current = L->tail;
        L->tail = L->tail->prev;
        L->tail->next = nullptr;
    }
    else { // General case
        Node* current;
        Node* prevNode;
        if(L->size - pos > pos){
            prevNode = nullptr;
            current = L->head;
            for (int i = 1; i < pos; i++) {
                prevNode = current;
                current = current->next;
            }
        }else{
            prevNode = L->tail->prev;
            current = L->tail;
            for (int i = L->size; i > pos; i--) {
                current = prevNode;
                prevNode = prevNode->prev;
            }
        }
        current->next->prev = prevNode;
        prevNode->next = current->next;
    }
    destroyNode(current);
    L->size--;
    return 1;
}