#ifndef QUEUE_H
#define QUEUE_H
#include "Loans.hpp"

constexpr int MAX_ELEM_QUEUE = 100;
struct Queue {
    Loan r_loans[MAX_ELEM_QUEUE];
    int front = -1;
    int tail = -1;
};


#endif 