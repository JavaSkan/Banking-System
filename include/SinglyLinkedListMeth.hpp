#ifndef SINGLYLINKEDLISTMETH_H
#define SINGLYLINKEDLISTMETH_H

#define TEMPLATE template <typename T>
#include "SinglyLinkedList.hpp"

TEMPLATE SList<T> createList();
TEMPLATE void destroyList(SList<T>* L);
TEMPLATE int listSize(const SList<T>& L);
TEMPLATE bool isFull(const SList<T>& L);
TEMPLATE bool isEmpty(const SList<T>& L);
TEMPLATE T getElement(const SList<T>& L, int pos);
TEMPLATE void displayList(const SList<T>& L);
TEMPLATE SList<T> CopyList(const SList<T>& L);
TEMPLATE bool CompareLists(const SList<T>& L1, const SList<T>& L2);
TEMPLATE SNode<T>* createNode(T value);
TEMPLATE void destroyNode(SNode<T>* node);
TEMPLATE bool insert(SList<T>* L, T e, int pos);
TEMPLATE bool removeAt(SList<T>* L, int pos);

#include "SinglyLinkedListMeth.tpp"
#endif // SINGLYLINKEDLISTMETH_H