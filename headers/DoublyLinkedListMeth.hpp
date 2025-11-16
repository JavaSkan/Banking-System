#ifndef DOUBLYLINKEDLISTMETH_H
#define DOUBLYLINKEDLISTMETH_H

#include "DoublyLinkedList.hpp"
#include <iostream>
using namespace std;

List createList();
void destroyList(List* L);
List CopyList(const List& L);
bool CompareLists(const List& L1, const List& L2);

bool isEmpty(const List& L);
bool isFull(const List& L);
int listSize(const List& L);

Node* createNode(Loan value);
void destroyNode(Node* node);
int insert(List* L, Loan e, int pos);
int removeAt(List* L, int pos);
Loan getElement(const List& L, int pos);
void displayList(const List& L);


#endif // DOUBLYLINKEDLISTMETH_H