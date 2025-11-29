//Defining the customer structure
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <sstream>
#include <string>
#include <cstdlib>
#include <SinglyLinkedListMeth.hpp>
#include <stackMeth.hpp>
#include <DoublyLinkedListMeth.hpp>
#include <arrayMeth.hpp>
#include <Loans.hpp>
#include <transaction.hpp>
#include <Branches.hpp>
#include <MiscFuncs.hpp>
using namespace std;
#define TEMPLATE template <typename T>

//Account Status
constexpr int CST_INACTIVE = 0;
constexpr int CST_ACTIVE = 1;
constexpr int CST_CLOSED = -1;
//Status values can only be one of the 3 above

struct Customer{
    string ID;
    //is the account number
    string type;
    string IBAN;
    string branchCode;
    string name;
    Date openingDate;
    int status;
    float balance;
    DList* loans;
    Stack* transactions;
    
};


int addCustomerToCsv(const Customer& Cus);
int init_customerArray(Array<Customer>& Cusarr);
TEMPLATE Array<T> createCustomerArray();
string createNewCustomer(const string& infoJSON);
string RIBGen(const Customer& Cus);
string IBANGen(const Customer& Cus);
string IDGenCustomer();
TEMPLATE bool isUnique(const SList<T>& L, string value);



#endif