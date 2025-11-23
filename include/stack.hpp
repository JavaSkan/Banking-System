#ifndef STACK_H
#define STACK_H 
#include "transaction.hpp"
struct Stack {
    Transaction* data = nullptr;
    int size = 0;
    int capacity = 1;
};



#endif