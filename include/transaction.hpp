//defining transactions to be able to use the stack
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;

#include "Dates.hpp"

constexpr int TR_WITHDRAWAL = 0;
constexpr int TR_DEPOSIT = 1;

struct Transaction{
    string ID;
    int accountNumber;
    int type;
    float amount;
    Date date;
};



#endif
