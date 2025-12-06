#include <Dates.hpp>
#include <MiscFuncs.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

Date CurrentDate={0,0,0};
/*
string getDateJS(const string& dateInfoJSON){
    string dateInfo=unJSON(dateInfoJSON);
    string infoParts[3];
    splitStr(dateInfo, '*',infoParts,3);
    int day=stoi(infoParts[0]);
    int month=stoi(infoParts[1]);
    int year=stoi(infoParts[2]);
    CurrentDate={day,month,year};
    return "\"Date confirmed .\"";
}
*/

void displayDate(const Date& d){
    cout << d.day << "-" << d.month << "-" << d.year;
}

string dateToString(const Date& d){
    stringstream s;
    s << to_string(d.day) << "-" << to_string(d.month) << "-" << to_string(d.year);
    return s.str();
}

Date stringToDate(string s){
    //Reminder, Date format : day-month-year
    int d, m, y;
    stringstream strs;
    //replaces '-' with ' ' to use string streams for string to value conversion
    string new_str = "";
    for(int i = 0; i < s.size(); i++){
        new_str += s[i] == '-' ? ' ' : s[i];
    }
    strs << new_str;
    strs >> d >> m >> y;
    return {d,m,y};
}

int compareDates(Date& d1, Date& d2){
    if(d1.year < d2.year){
        return -1;
    }else if(d1.year > d2.year){
        return 1;
    }else{
        if(d1.month < d2.month){
            return -1;
        }else if(d1.month > d2.month){
            return 1;
        }else{
            if(d1.day < d2.day){
                return -1;
            }else if(d1.day > d2.day){
                return 1;
            }else{
                return 0;
            }
        }
    }
}

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

void nextDay() {
    //to keep track of wether we need to increment the month
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};
    //just checks if we are in a leap year
    if (isLeap(CurrentDate.year)) {
        daysInMonth[1] = 29;
    }
    CurrentDate.day++;
    if (CurrentDate.day > daysInMonth[CurrentDate.month - 1]) {
        CurrentDate.day = 1;
        CurrentDate.month++;
        if (CurrentDate.month > 12) {
            CurrentDate.month = 1;
            CurrentDate.year++;
        }
    }
}