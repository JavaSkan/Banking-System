#ifndef DOUBLYLINKEDLISTMETH_H
#define DOUBLYLINKEDLISTMETH_H

#include "DoublyLinkedList.hpp"
#include <iostream>
using namespace std;

D_list createList();
void destroyList(D_list* L);
D_list CopyList(const D_list& L);
bool CompareLists(const D_list& L1, const D_list& L2);

bool isEmpty(const D_list& L);
bool isFull(const D_list& L);
int listSize(const D_list& L);

Node* createNode(Loan value);
void destroyNode(Node* node);
int insert(D_list* L, Loan e, int pos);
int removeAt(D_list* L, int pos);
Loan getElement(const D_list& L, int pos);
void displayList(const D_list& L);


#endif // DOUBLYLINKEDLISTMETH_H