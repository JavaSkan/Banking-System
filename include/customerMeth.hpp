#ifndef CUSTOMERMETH_H
#define CUSTOMERMETH_H

#include <SinglyLinkedListMeth.hpp>
#include <DoublyLinkedListMeth.hpp>
#include <arrayMeth.hpp>
#include <Branches.hpp>
#include <Dates.hpp>
#include <MiscFuncs.hpp>
#include <LoansMeth.hpp>

int addCustomerToCsv(const Customer& Cus);
int init_customerArray(Array<Customer>& Cusarr);
TEMPLATE Array<T> createCustomerArray();
string createNewCustomer(const string& infoJSON);
string RIBGen(const Customer& Cus);
string IBANGen(const Customer& Cus);
string IDGenCustomer();
TEMPLATE bool isUnique(const SList<T>& L, string value);
string passwordGen(int size);

#include "Customer.tpp"
#endif