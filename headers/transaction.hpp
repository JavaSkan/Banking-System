//defining transactions to be able to use the stack
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;

enum Type{
    WITHDRAYAL,
    DEPOSIT
};

struct Transaction{
    int ID;
    int accountNumber;
    Type type;
    float amount;
    string date;
};



#endif
