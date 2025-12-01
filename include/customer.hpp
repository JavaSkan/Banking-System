//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <sstream>
#include <string>
#include <SinglyLinkedListMeth.hpp>
#include <stackMeth.hpp>
#include <DoublyLinkedListMeth.hpp>
using namespace std;
#define TEMPLATE template <typename T>

//Account Status
constexpr int CST_INACTIVE = 0;
constexpr int CST_ACTIVE = 1;
constexpr int CST_CLOSED = -1;
//Status values can only be one of the 3 above

struct Customer{
    string ID="";
    //is the account number
    string type="";
    string IBAN="";
    string branchCode="";
    string name="";
    Date openingDate={0,0,0};
    int status=2;
    float balance=0;
    DList loans;
    Stack transactions;
    string password="";
};

#endif