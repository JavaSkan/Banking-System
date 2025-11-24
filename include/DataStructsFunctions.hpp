#include "SinglyLinkedListMeth.hpp"
#include "arrayMeth.hpp"
#include "customer.hpp"
#include <string>
#ifndef DATASTRUCTSFUNCTIONS_H
#define DATASTRUCTSFUNCTIONS_H
#define TEMPLATE template <typename T>
using namespace std;

TEMPLATE int IDGen(const SList<T>&L,char type);
TEMPLATE bool isUnique(const SList<T>& L, int value);
bool isValidEmail(const string& email);
int random(int min, int max);
TEMPLATE void IDGenCustomer(const Array<T>& arr, T& e);
string RIBGen(Customer Cus);
string IBANGen(Customer Cus);
#include "DataStructsFunctions.tpp"
#endif