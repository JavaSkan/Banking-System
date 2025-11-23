#ifndef LOANS_H
#define LOANS_H

#include "Dates.hpp"
#include <iostream>
using namespace std;

//Loan Types
constexpr int LNT_CAR = 1;
constexpr int LNT_HOME = 2;
constexpr int LNT_STUDENT = 3;
constexpr int LNT_BUSINESS = 4;

//Loan Status
constexpr int LNS_ACTIVE = 5;
constexpr int LNS_COMPLETED = 6;
constexpr int LNS_OVERDUE = 7;

struct Loan{
    int loadId;
    int type;
<<<<<<< HEAD
    float pr_amount; //principle amount
    float it_rate; //interest rate
=======
    float prAmount; //principle amount
    float itRate; //interest rate
>>>>>>> f37345e662495694a89d0ead31e19a30e2b2c280
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