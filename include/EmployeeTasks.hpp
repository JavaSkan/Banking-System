#ifndef EMPLOYEETASKS_H
#define EMPLOYEETASKS_H
#include "customer.hpp"
#include "array.hpp"
#include "Employee.hpp"
#include "Loans.hpp"
#include "Queue.hpp"
#include "arrayMeth.hpp"
#include <iostream>
#include <cstring>

void addEmployee(Array<Employee>* eArr);
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
int changeStatusLoan(Loan* L);
int deleteLoan(DList* Dl,SList<Loan>* Sl,Loan L);
int acceptLoan(Queue* q,DList* Dl);
int declineLoan(Loan* L);
//leaving managing transaction logs for later cuw dunno how to do that
int finalizeDay(Array<Customer>, SList<Transaction> Sl);



#endif