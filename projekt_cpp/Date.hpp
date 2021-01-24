#ifndef Date_hpp
#define Date_hpp

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std; 

class Date {
    private:
        int day, month, year;

    public:
        Date();
        Date(int day, int month, int year);
        Date(string date);
        void setTodaysDate();
        void changeDate(int day, int month, int year);
        void addDaysToDate(int days);
        void addMonthsToDate(int months);
        string convertToString();
        int getMonthsBetween(Date date);
        int checkIfAfter(Date date);
        void setDate(Date date);
        
        int getDay();
        int getMonth();
        int getYear();
        void setDay(int day);
        void setMonth(int month);
        void setYear(int year);
};

#endif