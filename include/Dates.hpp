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
extern Date CurrentDate;



void displayDate(const Date& d);
int compareDates(Date& d1, Date& d2);
string getDateJS(const string& dateInfoJSON);

#endif //DATES_H