//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
<<<<<<< HEAD
using namespace std;

//Account Status
#define CST_INACTIVE 8
#define CST_ACTIVE   9
#define CST_CLOSED   10
=======
#include "DoublyLinkedList.hpp"
#include "stack.hpp"
using namespace std;

//Account Status
constexpr int CST_INACTIVE = 0;
constexpr int CST_ACTIVE = 1;
constexpr int CST_CLOSED = -1;
>>>>>>> f37345e662495694a89d0ead31e19a30e2b2c280
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
<<<<<<< HEAD
=======
    int branchCode;
    DList loans;
    Stack transactions;

>>>>>>> f37345e662495694a89d0ead31e19a30e2b2c280
};

#endif