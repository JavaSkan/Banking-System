//Defining the customer structure
#ifndef Employee_H
#define EMPLOYEE_H
#include "Dates.hpp"
#include <string>
using namespace std;

struct employee{
    string ID;
    string Name;
    string LastName;
    string Adress;
    float Salary;
    Date HireDate;
    int bankBranch;
};
#endif