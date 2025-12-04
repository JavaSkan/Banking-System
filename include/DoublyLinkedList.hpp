#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <LoansMeth.hpp>
#include <stackMeth.hpp>

struct DNode{
    Loan data={};
    DNode* next=nullptr;
    DNode* prev=nullptr;
};

struct DList {
    DNode* head=nullptr;
    DNode* tail=nullptr;
    int size=0;
};

#endif // DOUBLYLINKEDLIST_H