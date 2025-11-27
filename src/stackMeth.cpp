#include "include/stackMeth.hpp"
#include <iostream>

Stack createStack(int capacity) {
    Stack s;
    s.capacity = capacity;
    s.data = new Transaction[capacity];
    return s;
}


void push(Stack& s, Transaction t) {
    if (s.size == s.capacity) {
        Transaction* newData = new Transaction[s.capacity * 2];
        for (int i = 0; i < s.size; i++)
            newData[i] = s.data[i];
        delete[] s.data;
        s.data = newData;
        s.capacity = 2*(s.capacity);
    }
    s.data[s.size] = t;
    s.size++;
}

void destroyStack(Stack& s) {
    delete[] s.data;
    s.data = nullptr;
    s.size = 0;
    s.capacity = 0;
}

void push(Stack& s, Transaction t) {
    if (s.size == s.capacity) {
        Transaction* newData = new Transaction[s.capacity * 2];
        for (int i = 0; i < s.size; i++)
            newData[i] = s.data[i];
        delete[] s.data;
        s.data = newData;
        s.capacity *= 2;
    }
    s.data[s.size] = t;
    s.size++;
}


Transaction pop(Stack& s) {
    if (s.size == 0) {
        std::cerr << "Stack underflow!\n";
        return Transaction{}; 
    }
    s.size--;
    return s.data[s.size];
}


Transaction top(const Stack& s) {
    if (s.size == 0) {
        std::cerr << "Stack is empty!\n";
        return Transaction{};
    }
    return s.data[s.size - 1];
}

bool isEmpty(const Stack& s) {
    return s.size == 0;
}

bool isFull(const Stack& s){
    return(s.size == s.capacity);
}