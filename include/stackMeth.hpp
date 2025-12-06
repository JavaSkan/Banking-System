#ifndef STACKMETH_H
#define STACKMETH_H

#include <iostream>
#include <sstream>
#include <Stack.hpp>

Stack createStack();
void push(Stack& s, Transaction value);
Transaction pop(Stack& s);
Transaction top(const Stack& s);
bool isEmpty(const Stack& s);
bool isFull(const Stack& s);
Stack copyStack(const Stack& S);

/*
Returns a string representation of a Stack
in the form of STACK[number_of_elements/TRANSACTION1/.../TRANSACTION_N]
*/
string stackToString(const Stack& s);

/*
Return a Stack struct from a string
NOTE: PARAMETER 's' MUST RESPECT THE FORMAT
OF stackToString !!
*/
Stack stringToStack(string s);

#endif