#ifndef LOANSMETH_H
#define LOANSMETH_H

#include <Loans.hpp>

string loanTypeStr(int t);
string loanStatusStr(int s);
void displayLoan(const Loan& l);

/*
Returns a string representation of a Loan struct
in the form of: LOAN[ID*type*status*pr_amount*it_rate*am_paid*...*end_date]
*/
string loanToString(const Loan& l);

/*
Return a Loan struct from a string
NOTE: PARAMETER 's' MUST RESPECT THE FORMAT
OF loanToString !!
*/
Loan stringToLoan(string s);

#endif