//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

//Account Status
#define CST_INACTIVE 8
#define CST_ACTIVE   9
#define CST_CLOSED   10
//Status values can only be one of the 3 above

struct customer{
    int ID;
    //is the account number
    string type;
    string IBAN;
    string name;
    string openingDate;
    int status;
    float balance;
};

#endif