#ifndef EMPLOYEETASKS_H
#define EMPLOYEETASKS_H
#include "customer.hpp"
#include "array.hpp"
#include "Employee.hpp"
#include "Loans.hpp"
#include "Queue.hpp"
#include <iostream>

int addEmployee(Array<Employee>* eArr);
int deleteEmployee(Array<Employee>*  eArr);
int modifyEmployee(Employee e);
int displayAlphaconst (Array<Employee>& eArr);
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
int deleteLoan(DList* Dlist,SList<Loan>* clist,Loan L);
int acceptLoan();



#endif