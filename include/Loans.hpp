#ifndef LOANS_H
#define LOANS_H

#include <iostream>
#include <Dates.hpp>

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
    string ID = "";
    int type = LNT_CAR;
    int status = LNS_OVERDUE;
    float pr_amount = -1.0; //principle amount
    float it_rate = 0.0; //interest rate
    float am_paid = 0.0; //amount paid
    float rm_balance = 0.0; //remaining balance
    Date start_date;
    Date end_date;
};

struct LoanRequest{
    Loan loan = {};
    int duration = 0;
    string ID_customer = "NO-CUSTOMER";
};

#endif