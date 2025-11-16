#ifndef ARRAYMETH_H
#define ARRAYMETH-H
#include "array.hpp"
#define TEMPLATE template <typename T>

TEMPLATE array<T> createArray();
TEMPLATE void destroyArray(array<T>* p);
TEMPLATE bool isEmpty(const array<T>& p);
TEMPLATE bool isFull(const array<T>& p);


#endif