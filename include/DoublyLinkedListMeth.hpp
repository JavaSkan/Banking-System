#ifndef DOUBLYLINKEDLISTMETH_H
#define DOUBLYLINKEDLISTMETH_H

#include <iostream>
#include <DoublyLinkedList.hpp>
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

int searchByID(const DList& L, string ID);

/* 
Returns a string representation of a DoublyLinkedList
in the form of DLL[size$Loan1$...$LoanN]
*/
string DLToString(const DList& dl);

/*
Return a DoublyLinkedList of Loans from a string
NOTE: PARAMETER 's' MUST RESPECT THE FORMAT
OF DLToString !!
*/
DList stringToDL(string s);

#endif // DOUBLYLINKEDLISTMETH_H