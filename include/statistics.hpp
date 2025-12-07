#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <iostream>
#include <string>
#include "DoublyLinkedListMeth.hpp"
#include "arrayMeth.hpp"
#include "Customer.hpp"
#include "Employee.hpp"
#include "Dates.hpp"

using namespace std;

// --- CORE LOGIC FUNCTIONS (Unchanged logic, just declarations) ---
int getTotalLoans(const Array<Customer>& Cus);
int countLoansByType(const Array<Customer>& Cus, int nCus, int type);
int countLoansByStatus(const Array<Customer>& Cus, int nCus, int status);
int countActiveLoansInRange(const Array<Customer>& Cus, int nCus, Date startDate, Date endDate);
Customer* customerMostLoans(const Array<Customer>& Cus, int nCus);
Customer* customerHighestBalance(const Array<Customer>& Cus, int nCus);
Customer* customerLowestBalance(const Array<Customer>& Cus, int nCus);
int totalEmp(const Array<Employee>& Emp);
int countEmpByBranch(const Array<Employee>& Emp, int branchCode);

// --- COMMUNICATION WRAPPERS (To be bound in main.cpp) ---
// These receive strings from JS and return JSON strings
string sendTotalLoans(const string&);
string sendLoansByTypeCount(const string& typeJSON);
string sendLoansByStatusCount(const string& statusJSON);
string sendActiveLoansInRangeCount(const string& datesJSON); // Expects "start*end"
string sendCustomerMostLoans(const string&);
string sendCustomerHighestBalance(const string&);
string sendCustomerLowestBalance(const string&);
string sendTotalEmployees(const string&);
string sendEmpByBranchCount(const string& branchJSON);

#endif