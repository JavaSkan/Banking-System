#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "Loans.hpp"

struct Node{
    Loan data;
    Node* next;
    Node* prev;
};

struct D_list {
    Node* head;
    Node* tail;
    int size;
};

#endif // DOUBLYLINKEDLIST_H