#ifndef TRANSACTIONMETH_H
#define TRANSACTIONMETH_H

#include <sstream>
#include "Transaction.hpp"

/*
Returns a string representation of a Transaction
in the form of TRANSACTION[ID|accountNumber|type|amount|Date]
Date is also represented in string form, check dateToString method
in Dates.hpp
*/
string transactionToString(const Transaction& tr);

/*
Return a Transaction struct from a string
NOTE: PARAMETER 's' MUST RESPECT THE FORMAT
OF transactionToString !!
*/
Transaction stringToTransaction(string s);
#endif