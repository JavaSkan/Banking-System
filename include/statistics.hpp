#ifndef STATISTICS_H
#define STATISTICS_H

#include "Customer.hpp"
#include "Employee.hpp"
#include "Loans.hpp"

//9adech famma min loan
int getTotalLoans(Customer Cus[], int nCus);

//9adech famma min loan fi kol type
int countLoansByType(Customer Cus[], int nCus, const int type);

//9adech famma min loan 7asb lstatus mte3ou
int countLoansByStatus(Customer Cus[], int nCus, const int status);

//loans li mizlt date mt3hom
int countActiveLoansInRange(Customer Cus[], int nCus, const Date& startDate, const Date& endDate);

//Customer li 3ndou akther loans
Customer* CustomerMostLoans(Customer Cus[], int nCus);

//akther Customer korza
Customer* CustomerHighestBalance(Customer Cus[], int nCus);

//akther Customer mnatef
Customer* CustomerLowestBalance(Customer Cus[], int nCus);

//9dech famma min employee
int totalEmp(employee Emp[], int nEmp);

//9dch famma min employee fi kol branch
int countEmpByBranch(employee Emp[], int nEmp, int branchCode);

#endif
