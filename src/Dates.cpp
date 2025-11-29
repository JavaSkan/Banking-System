#include <Dates.hpp>
#include <MiscFuncs.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

Date CurrentDate={0,0,0};

string getDateJS(const string& dateInfoJSON){
    string dateInfo=unJSON(dateInfoJSON);
    string day;
    string month;
    string year;
    string daymonth;
    splitStr(dateInfo,'&',daymonth,year);
    splitStr(daymonth,'*',day,month);
    int iday=stoi(day);
    int imonth=stoi(month);
    int iyear=stoi(year);
    CurrentDate={iday,imonth,iyear};
    return "\"Date confirmed .\"";
}

void displayDate(const Date& d){
    cout << d.day << "-" << d.month << "-" << d.year;
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