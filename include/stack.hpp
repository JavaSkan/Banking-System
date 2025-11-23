<<<<<<< HEAD
//Stack.hpp
#ifndef STACK_H
#define STACK_H 

struct Stack{


=======
#ifndef STACK_H
#define STACK_H 
#include "transaction.hpp"
struct Stack {
    Transaction* data = nullptr;
    int size = 0;
    int capacity = 1;
>>>>>>> f37345e662495694a89d0ead31e19a30e2b2c280
};



#endif