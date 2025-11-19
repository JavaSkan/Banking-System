#ifndef LOANS_H
#define LOANS_H

#include "Dates.hpp"
#include <iostream>
using namespace std;

enum LoanType{
    CAR,
    HOME,
    STUDENT,
    BUSINESS
};

enum LoanStatus{
    ACTIVE,
    COMPLETED,
    OVERDUE
};

struct Loan{
    int loadId;
    LoanType type;
    float pr_amount; //principle amount
    float it_rate; //interest rate
    float am_paid; //amount paid
    float rm_balance; //remaining balance
    Date start_date;
    Date end_date;
    LoanStatus status;
};

string loanTypeStr(LoanType t);
string loanStatusStr(LoanStatus s);
void displayLoan(const Loan& l);

#endif