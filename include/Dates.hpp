#ifndef DATES_H
#define DATES_H
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Date
{
    int day = 1;
    int month = 1;
    int year = 1970;
};
extern Date CurrentDate;


//Displays a date struct without a \n
void displayDate(const Date& d);

/* 
Returns a string representation of a Date
in the form of day-month-year
*/
string dateToString(const Date& d);

/*
Return a Date struct from a string
NOTE: PARAMETER 's' MUST RESPECT THE FORMAT
OF dateToString !!
*/
Date stringToDate(string s);

/*
Compares two Dates
returns -1 if d1 < d2
returns 0  if d1 == d2
returns 1  if d1 > d2
*/

int compareDates(const Date& d1, const Date& d2);
//string getDateJS(const string& dateInfoJSON);

bool isLeap(int y);
void nextDay();

#endif //DATES_H