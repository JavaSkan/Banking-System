#ifndef SINGLYLINKEDLISTMETH_H
#define SINGLYLINKEDLISTMETH_H

#define TEMPLATE template <typename T>
#include "SinglyLinkedList.hpp"

TEMPLATE Node<T>* createNode(T value);
TEMPLATE void destroyNode(Node<T>* node);
TEMPLATE SList<T> createList();
TEMPLATE void destroyList(SList<T>* L);
TEMPLATE bool isEmpty(const SList<T>& L);
TEMPLATE bool isFull(const SList<T>& L);
TEMPLATE int listSize(const SList<T>& L);
TEMPLATE bool insert(SList<T>* L, T e, int pos);
TEMPLATE bool removeAt(SList<T>* L, int pos);
TEMPLATE T getElement(const SList<T>& L, int pos);
TEMPLATE void displayList(const SList<T>& L);
TEMPLATE bool isUnique (const SList<T>& L, int value);

TEMPLATE SList<T> CopyList(const SList<T>& L);
TEMPLATE bool CompareLists(const SList<T>& L1, const SList<T>& L2);

#endif // SINGLYLINKEDLISTMETH_H