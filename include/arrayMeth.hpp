#ifndef ARRAYMETH_H
#define ARRAYMETH_H
#include <array.hpp>
#include <iostream>
using namespace std;

#define TEMPLATE template <typename T>

// --- Definitions ---
TEMPLATE Array<T> createArray(int capacity);
TEMPLATE void destroyArray(Array<T>* p);

TEMPLATE bool isEmpty(const Array<T>& p);
TEMPLATE bool isFull(const Array<T>& p);
TEMPLATE int arraySize(const Array<T>& p);
/* 
TEMPLATE void displayArray(const Array<T>& p);
*/

TEMPLATE int addElement(Array<T>* p, T e, int pos);
TEMPLATE void removeAtArray(Array<T>* p, int pos);
TEMPLATE Array<T> copyArray(const Array<T>& p);
TEMPLATE void resizeArray(Array<T>& p, int newCapacity);

TEMPLATE bool isUniqueInArray(const Array<T>& p, T e);
TEMPLATE int searchByID(const Array<T>& p,string ID);



#include "arrayMeth.tpp"

#endif
