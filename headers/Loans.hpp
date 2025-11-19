#ifndef LOANS_H
#define LOANS_H

#include "Dates.hpp"
#include <iostream>
using namespace std;

//Loan Types
#define LNT_CAR 1
#define LNT_HOME 2
#define LNT_STUDENT 3
#define LNT_BUSINESS 4

//Loan Status
#define LNS_ACTIVE 5
#define LNS_COMPLETED 6
#define LNS_OVERDUE 7

struct Loan{
    int loadId;
    int type;
    float pr_amount; //principle amount
    float it_rate; //interest rate
    float am_paid; //amount paid
    float rm_balance; //remaining balance
    Date start_date;
    Date end_date;
    int status;
};

string loanTypeStr(int t);
string loanStatusStr(int s);
void displayLoan(const Loan& l);

#endif