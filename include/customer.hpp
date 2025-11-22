//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "DoublyLinkedList.hpp"
#include "stack.hpp"
using namespace std;

//Account Status
constexpr int CST_INACTIVE = 0;
constexpr int CST_ACTIVE = 1;
constexpr int CST_CLOSED = -1;
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
    int branchCode;
    DList loans;
    Stack transactions;

};

#endif