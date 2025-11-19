#include "../headers/Dates.hpp"

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