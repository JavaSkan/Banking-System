#ifndef EMPLOYEETASKS_H
#define EMPLOYEETASKS_H
#include <customer.hpp>
#include <array.hpp>
#include <Employee.hpp>
#include <Loans.hpp>
#include <Queue.hpp>
#include <arrayMeth.hpp>
#include <iostream>
#include <cstring>
#include <SinglyLinkedList.hpp>

SList<Loan> completed_loans;

TEMPLATE Array<T> createEmployeeArray();
int init_employeeArray(Array<Employee>& EmplArray);
string addEmployee(const string& infoJSON);
int addEmployeeToCsv(const Employee& e);
int deleteEmployee(Array<Employee>* eArr);
int modifyEmployee(Employee& e);
int displayAlpha(const Array<Employee>& eArr);
int displayEarliest(const Array<Employee>& eArr);
int displayMostRecently(const Array<Employee>& eArr);
int addCustomer(Array<Customer>* cArr);
int displayAccounts(const Array<Customer>& cArr);
int changeStatus(Customer* c);
int deleteCustomer(Array<Customer>* cArr, Customer c);
/*probably was alread made;
int displayLoans()
*/
/*
string changeStatusLoan(const string& infoJSON);   //left for melik
string deleteLoan(const string& infoJSON);   //melik
int acceptLoan(Queue* q,DList* Dl);  //melik
int declineLoan(Loan* L);     //melik
//leaving managing transaction logs for later cuw dunno how to do that
int finalizeDay(Array<Customer>, SList<Transaction> Sl);   //melik
*/


#include "EmployeeTasks.tpp"
#endif