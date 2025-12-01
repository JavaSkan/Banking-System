#ifndef QUEUE_H
#define QUEUE_H
#include "Loans.hpp"

constexpr int Max = 100;
struct Queue {
    Loan r_loans[Max];
    int front;
    int tail; 
};


#endif 