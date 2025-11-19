#ifndef ARRAYMETH_H
#define ARRAYMETH_H
#include "Array.hpp"
#include <iostream>
using namespace std;

#define TEMPLATE template <typename T>

// --- Definitions ---
TEMPLATE
Array<T> createArray() {
    return Array<T>{nullptr, 0};
}

TEMPLATE
void destroyArray(Array<T>* p) {
    delete[] p->data;
    p->size = 0;
}

TEMPLATE
bool isEmpty(const Array<T>& p) {
    return p.size == 0;
}

TEMPLATE
bool isFull(const Array<T>& p) {
    return p.data != nullptr && p.size > 0; // example, adjust logic as needed
}

TEMPLATE
int arraySize(const Array<T>& p) {
    return p.size;
}

TEMPLATE
void displayArray(const Array<T>& p) {
    for (int i = 0; i < p.size; ++i)
        cout << p.data[i] << " ";
    cout << endl;
}

TEMPLATE
Array<T> copyArray(const Array<T>& p) {
    Array<T> c;
    c.size = p.size;
    c.data = new T[c.size];
    for (int i = 0; i < c.size; ++i)
        c.data[i] = p.data[i];
    return c;
}

#endif
