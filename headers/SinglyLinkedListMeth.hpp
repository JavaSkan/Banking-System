#ifndef SINGLYLINKEDLISTMETH_H
#define SINGLYLINKEDLISTMETH_H
#define TEMPLATE template <typename T>
#include "SinglyLinkedList.hpp"

TEMPLATE Node<T>* createNode(T value);
TEMPLATE void destroyNode(Node<T>* node);
TEMPLATE List<T> createList();
TEMPLATE void destroyList(List<T>* L);
TEMPLATE bool isEmpty(const List<T>& L);
TEMPLATE bool isFull(const List<T>& L);
TEMPLATE int listSize(const List<T>& L);
TEMPLATE bool insert(List<T>* L, int e, int pos);
TEMPLATE bool removeAt(List<T>* L, int pos);
TEMPLATE T getElement(const List<T>& L, int pos);
TEMPLATE void displayList(const List<T>& L);
TEMPLATE bool isUnique (const List<T>& L, int value);

TEMPLATE List<T> CopyList(const List<T>& L);
TEMPLATE bool CompareLists(const List<T>& L1, const List<T>& L2);


#endif // SINGLYLINKEDLISTMETH_H