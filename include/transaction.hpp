//defining transactions to be able to use the stack
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;

#include "Dates.hpp"

<<<<<<< HEAD
enum Type{
    WITHDRAYAL,
    DEPOSIT
};
=======
constexpr int TR_WITHDRAWAL = 0;
constexpr int TR_DEPOSIT = 1;
>>>>>>> f37345e662495694a89d0ead31e19a30e2b2c280

struct Transaction{
    int ID;
    int accountNumber;
<<<<<<< HEAD
    Type type;
=======
    int type;
>>>>>>> f37345e662495694a89d0ead31e19a30e2b2c280
    float amount;
    Date date;
};



#endif
