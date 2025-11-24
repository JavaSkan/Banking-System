#ifndef DOUBLYLINKEDLISTMETH_H
#define DOUBLYLINKEDLISTMETH_H

#include "DoublyLinkedList.hpp"
#include <iostream>
using namespace std;

DList createList();
void destroyList(DList* L);
DList CopyList(const DList& L);
bool CompareLists(const DList& L1, const DList& L2);

bool isEmpty(const DList& L);
bool isFull(const DList& L);
int listSize(const DList& L);

DNode* createNode(Loan value);
void destroyNode(DNode* node);
int insert(DList* L, Loan e, int pos);
int removeAt(DList* L, int pos);
Loan getElement(const DList& L, int pos);
void displayList(const DList& L);


#endif // DOUBLYLINKEDLISTMETH_H