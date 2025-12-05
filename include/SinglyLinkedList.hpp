//SinglyLinkedList.h
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#define TEMPLATE template <typename T>

TEMPLATE
struct SNode {
    T data;
    SNode<T>* next;
};

TEMPLATE
struct SList {
    SNode<T>* head=nullptr;
    int size=0;
};

#endif // SINGLYLINKEDLIST_H