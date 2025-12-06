#ifndef CUSTOMERMETH_H
#define CUSTOMERMETH_H
#include <customer.hpp>
#include <string>
#include "arrayMeth.hpp"
#include "SinglyLinkedListMeth.hpp"


int addCustomerToCsv(const Customer& Cus);
int init_customerArray(Array<Customer>& Cusarr);
string customerToCsvLine(const Customer& Cus);
std::string customerToStr(const Customer& Cus);
TEMPLATE Array<T> createCustomerArray();
string createNewCustomer(const string& infoJSON);
string RIBGen(const Customer& Cus);
string IBANGen(const Customer& Cus);
string IDGenCustomer();
TEMPLATE bool isUnique(const SList<T>& L, string value);
string passwordGen(int size);

#include "Customer.tpp"
#endif