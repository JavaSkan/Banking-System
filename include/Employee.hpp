//Defining the customer structure
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Dates.hpp"
#include <string>
using namespace std;

struct Employee{
    string ID;
    string Name;
    string LastName;
    string Adress;
    float Salary;
    Date HireDate; //constant ??
    string bankBranch;
    string password;
};
#endif