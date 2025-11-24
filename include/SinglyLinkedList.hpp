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
SNode<T>* head;
int size;
};

#endif // SINGLYLINKEDLIST_H