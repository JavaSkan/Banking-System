//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
using namespace std;

enum status{
    Inactive,
    Active,
    Closed

    
};
//Status values can only be one of the 3 above 

struct customer{
    int ID;
    //is the account number
    string type;
    string IBAN;
    string name;
    string openingDate;
    status status;
    float balance;

    


};




#endif