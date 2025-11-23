#ifndef STACKMETH_H
#define STACKMETH_H
#include "stack.hpp"
#include <iostream>

Stack createStack(int capacity);
void push(Stack& s, int value);
Transaction pop(Stack& s);
Transaction top(const Stack& s);
bool isEmpty(const Stack& s);


#endif