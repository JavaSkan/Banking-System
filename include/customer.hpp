//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;

enum Status{
    INACTIVE,
    ACTIVE,
    CLOSED
};
//Status values can only be one of the 3 above 

struct customer{
    int ID;
    //is the account number
    string type;
    string IBAN;
    string name;
    string openingDate;
    Status status;
    float balance;
};




#endif