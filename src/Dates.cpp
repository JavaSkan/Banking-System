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

string dateToString(const Date& d){
    stringstream s;
    s << d.day << "-" << d.month << "-" << d.year;
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