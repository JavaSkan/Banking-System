#ifndef STACK_H
#define STACK_H

#include <Transaction.hpp>

constexpr int MAX_STACK_ELEMENTS = 1024;

struct Stack {
    Transaction data[MAX_STACK_ELEMENTS];
    int top = -1;
    //int size = 0;
    //int capacity = 1;
};

#endif