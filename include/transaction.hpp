//defining transactions to be able to use the stack
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

#include "Dates.hpp"

using namespace std;

constexpr int TR_WITHDRAWAL = 0;
constexpr int TR_DEPOSIT = 1;

struct Transaction{
    string ID = "NOID";
    string accountNumber ="NOACCNUM";
    int type = -1;
    int amount = -1;
    Date date = {};
};

#endif
