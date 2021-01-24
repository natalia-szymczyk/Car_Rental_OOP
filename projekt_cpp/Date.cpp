#include "Date.hpp"

Date::Date(){ }

Date::Date(int day, int month, int year)  {
    while (year < 2021 || month < 1 || month > 12 || day < 0 || (day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) || (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) || (day > 28 && month == 2 && (year % 4 > 0)) || (day > 29 && month == 2 && (year % 4 == 0))) {
        cout << "Wprowadzona data jest niepoprawna." << endl;
        
        cout << "Wprowadz dzien ponownie: " << endl;
        cin >> day;

        cout << "Wprowadz miesiac ponownie: " << endl;
        cin >> month;

        cout << "Wprowadz rok ponownie: " << endl;
        cin >> year;
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(string date){
    string day, month, year;

    day.push_back(date.at(0));
    day.push_back(date.at(1));

    month.push_back(date.at(3));
    month.push_back(date.at(4));

    year.push_back(date.at(6));
    year.push_back(date.at(7));
    year.push_back(date.at(8));
    year.push_back(date.at(9));

    this->day = stoi(day);
    this->month = stoi(month);
    this->year = stoi(year);
}

void Date::setTodaysDate() {
    time_t currentTime = time(0);
    tm* ltm = localtime(&currentTime);

    this->day = ltm->tm_mday;
    this->month = ltm->tm_mon + 1;
    this->year = ltm->tm_year + 1900;
}

void Date::setDate(Date date){
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
}

void Date::changeDate(int day, int month, int year) {
    while (year < 0 || month < 1 || month > 12 || day < 0 || (day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) || (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) || (day > 28 && month == 2 && (year % 4 > 0)) || (day > 29 && month == 2 && (year % 4 == 0))) {
        cout << "Wprowadzona data jest niepoprawna." << endl;

        cout << "Wprowadz dzien ponownie: " << endl;
        cin >> day;

        cout << "Wprowadz miesiac ponownie: " << endl;
        cin >> month;

        cout << "Wprowadz rok ponownie: " << endl;
        cin >> year;
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::checkIfAfter(Date date){
    if((date.year > this->year)){
        return 1;
    }
    else if((date.year == this->year) && (date.month > this->month)){
        return 1;
    }
    else if((date.year == this->year) && (date.month == this->month) && (date.day > this->day)){
        return 1;
    }

    return 0;
}

string Date::convertToString() {
    string stringDate;
    string stringDay = to_string(this->day);
    string stringMonth = to_string(this->month);
    string stringYear = to_string(this->year);

    stringDay.insert(stringDay.begin(), 2 - stringDay.length(), '0');
    stringMonth.insert(stringMonth.begin(), 2 - stringMonth.length(), '0');
    stringYear.insert(stringYear.begin(), 4 - stringYear.length(), '0');

    stringDate = stringDay.append("-").append(stringMonth).append("-").append(stringYear);
    
    return stringDate;
}

int Date::getMonthsBetween(Date date){
    int months = 0;

    if (this->year == date.year){
        months = date.month - this->month;
    }
    else if(this->year < date.year){
        if(this->month > date.month){
            months += (12 - this->month + date.month);   
        }     
        else {
            months += date.month - this->month;   
            months += 12 * (date.year - this->year);
        } 
    }
    
    return months;
}

void Date::addDaysToDate(int days){

    struct tm  t = { 0 };
    t.tm_mday = this->day;
    t.tm_mon = this->month - 1;
    t.tm_year = this->year - 1900;

    t.tm_mday += days;

    mktime(&t);

    this->day = t.tm_mday;
    this->month = t.tm_mon + 1;
    this->year = t.tm_year + 1900;
}

void Date::addMonthsToDate(int months){

    struct tm  t = { 0 };
    t.tm_mday = this->day;
    t.tm_mon = this->month - 1;
    t.tm_year = this->year - 1900;

    t.tm_mon += months;

    mktime(&t);

    this->day = t.tm_mday;
    this->month = t.tm_mon + 1;
    this->year = t.tm_year + 1900;
}

int Date::getDay(){
    return this->day;
}

void Date::setDay(int day){
    this->day = day;
}

int Date::getMonth(){
    return this->month;
}

void Date::setMonth(int month){
    this->month = month;
}

int Date::getYear(){
    return this->year;
}

void Date::setYear(int year){
    this->year = year;
}