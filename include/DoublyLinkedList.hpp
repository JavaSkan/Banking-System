#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <LoansMeth.hpp>

struct DNode{
    Loan data;
    DNode* next;
    DNode* prev;
};

struct DList {
    DNode* head;
    DNode* tail;
    int size;
};

#endif // DOUBLYLINKEDLIST_H