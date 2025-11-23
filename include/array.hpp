//defining BETTER arrays
#ifndef ARRAY_H
#define ARRAY_H
#define TEMPLATE template <typename T>

TEMPLATE
struct Array{
    T* data=nullptr;
    int size=0;
    //size expresses the number of elements in the array, how much space is used;
    int capacity = 1;
    //capacity expresses how much memory is allocated for the array;
};


#endif