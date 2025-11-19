#ifndef SINGLYLINKEDLISTMETH_H
#define SINGLYLINKEDLISTMETH_H

#define TEMPLATE template <typename T>
#include "SinglyLinkedList.hpp"

TEMPLATE Node<T>* createNode(T value);
TEMPLATE void destroyNode(Node<T>* node);
TEMPLATE S_list<T> createList();
TEMPLATE void destroyList(S_list<T>* L);
TEMPLATE bool isEmpty(const S_list<T>& L);
TEMPLATE bool isFull(const S_list<T>& L);
TEMPLATE int listSize(const S_list<T>& L);
TEMPLATE bool insert(S_list<T>* L, T e, int pos);
TEMPLATE bool removeAt(S_list<T>* L, int pos);
TEMPLATE T getElement(const S_list<T>& L, int pos);
TEMPLATE void displayList(const S_list<T>& L);
TEMPLATE bool isUnique (const S_list<T>& L, int value);

TEMPLATE S_list<T> CopyList(const S_list<T>& L);
TEMPLATE bool CompareLists(const S_list<T>& L1, const S_list<T>& L2);

#endif // SINGLYLINKEDLISTMETH_H