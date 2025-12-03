#ifndef QUEUEMETH_H
#define QUEUEMETH_H
#include "Queue.hpp"
#include <iostream>

Queue* createQueue();

int queueSize(const Queue& q);
bool isEmpty(const Queue& q);
bool isFull(const Queue& q);


int enqueue(Queue* q, LoanRequest L);
LoanRequest dequeue(Queue* q);
LoanRequest front(const Queue& q);

void destroyQueue(Queue* q);

#endif