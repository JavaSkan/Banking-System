//SinglyLinkedList.h
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H
#define TEMPLATE template <typename T>

TEMPLATE
struct Node {
    T data;
    Node<T>* next;
};

TEMPLATE
struct S_list {
Node<T>* head;
int size;
};

#endif // SINGLYLINKEDLIST_H