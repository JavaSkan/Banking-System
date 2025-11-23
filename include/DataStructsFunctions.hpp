#include "SinglyLinkedListMeth.hpp"
#include <string>
#ifndef DATASTRUCTSFUNCTIONS_H
#define DATASTRUCTSFUNCTIONS_H
#define TEMPLATE template <typename T>
using namespace std;

TEMPLATE int IDGen(const SList<T>&L,char type);
TEMPLATE bool isUnique(const SList<T>& L, int value);
bool isValidEmail(const string& email);
int random(int min, int max);
#include "DataStructsFunctions.tpp"
#endif