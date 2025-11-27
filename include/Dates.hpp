#ifndef DATES_H
#define DATES_H

#include <iostream>
using namespace std;

struct Date
{
    int day;
    int month;
    int year;
};

/*
Compares two Dates
returns -1 if d1 < d2
returns 0  if d1 == d2
returns 1  if d1 > d2
*/

//Displays a date struct without a \n
void displayDate(const Date& d);
int compareDates(Date& d1, Date& d2);

#endif //DATES_H