#include <DoublyLinkedListMeth.hpp>

DList createList() {
    return DList{ nullptr, nullptr, 0 };
}

void destroyList(DList* L) {
    if (!L) return;
    DNode* current = L->head;
    while (current) {
        DNode* temp = current;
        current = current->next;
        destroyNode(temp);
    }
    L->head = nullptr ;
    L->tail = nullptr;
    L->size = 0;
}

bool isEmpty(const DList& L) {
    return L.size == 0;
}

int listSize(const DList& L) {
    return L.size;
}

bool isFull(const DList& L) {
    DNode* test = new (nothrow) DNode;
    if (!test) return true;
    delete test;
    return false;
}

bool CompareLists(const DList& L1, const DList& L2) {
    if (L1.size != L2.size) return false;

    DNode* p1 = L1.head;
    DNode* p2 = L2.head;

    while (p1) {
        if (p1->data.ID != p2->data.ID) return false;
        p1 = p1->next;
        p2 = p2->next;
    }
    return true;
}

DList CopyList(const DList& L) {
    DList newList = createList();
    DNode* current = L.head;
    DNode* tail = nullptr; // keep track of last node in new list
    while (current) {
        DNode* n = createNode(current->data);
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

void displayList(const DList& L) {
    if (isEmpty(L)) {
        cout << "DList is empty\n";
        return;
    }
    DNode* current = L.head;
    while (current) {
        displayLoan(current->data);
        current = current->next;
    }
    cout << "NULL\n";
}

DNode* createNode(Loan value) {
    DNode* node = new (nothrow) DNode{value, nullptr, nullptr };
    if (!node) cout << "Memory allocation failed for node\n";
    return node;
}

void destroyNode(DNode* node) {
    delete node;
}

Loan getElement(const DList& L, int pos) {
    if (isEmpty(L)) {
        cerr << "List is empty\n";
        return {};
    }
    if (pos < 1 || pos > L.size) {
        cerr << "Invalid position\n";
        return {};
    }
    DNode* current;
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

int insert(DList* L, Loan e, int pos) {
    if (!L) return 0;
    if (pos < 1 || pos > L->size + 1) { //Invalid Pos
        cout << "Invalid position\n";
        return 0;
    }
    DNode* n = createNode(e);
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
        DNode* current;
        DNode* prev;
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

int removeAt(DList* L, int pos) {
    if (!L || isEmpty(*L)) { //Empty List
        cout << "List is empty\n";
        return 0;
    }
    if (pos < 1 || pos > L->size) { // Invalid pos
        cout << "Invalid position\n";
        return 0;
    }
    DNode* current;
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
        DNode* current;
        DNode* prevNode;
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

string DLToString(const DList& dl){
    if(isEmpty(dl)) return "DLL[]";
    stringstream ss;
    ss << "DLL[" << dl.size << "$";
    DNode* cur = dl.head;
    while(cur){
        //if it's the last node, the ternary expr ensure that the separator '$'
        //is not added at the end
        ss << loanToString(cur->data) << (cur != dl.tail ? "$" : "]");
        cur = cur->next;
    }
    return ss.str();
}

DList stringToDL(string s){
    DList res = createList();
    string sub = "";
    for(int i = 4; i < s.size()-1; i++){
        //replace '$' separator with a space, useful for string stream
        //manipulation
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

int searchByID(const DList& L,string ID){
    if (isEmpty(L)) { 
        cout<<"Cannot search in an empty list"<<endl;
        return 0;
    }
    int pos = 1;
    DNode* current = L.head;
    while(pos<=L.size){
        if (current->data.ID != ID){
            current = current->next;
        }
    }
    return (pos>L.size)? -1:pos;
    //learned this today

}