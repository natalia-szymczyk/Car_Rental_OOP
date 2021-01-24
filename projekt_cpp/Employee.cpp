#include "Employee.hpp"

Employee::Employee(string firstName, string lastName, string dateFromInputstring){
    setFirstName(firstName);
    setLastName(lastName);
    setWorkedMonths(0);
    setStartDate(Date(dateFromInputstring));
}

Employee::Employee(string firstName, string lastName, Date dateFromInput){
    setFirstName(firstName);
    setLastName(lastName);
    setWorkedMonths(0);
    setStartDate(dateFromInput);
}

int Employee::calculateWorkedMonths(Date todaysDate){
    return this->startDate.getMonthsBetween(todaysDate);
}

Date Employee::getStartDate() {
    return this->startDate;
}

void Employee::setStartDate(Date startDate) {
    this->startDate = startDate;
}

int Employee::getWorkedMonths() {
    return this->workedMonths;
}

void Employee::setWorkedMonths(int workedMonths) {
    this->workedMonths = workedMonths;
}

string Employee::getFirstName() {
    return this->firstName;
}

void Employee::setFirstName(string firstName) {
    this->firstName = firstName;
}

string Employee::getLastName() {
    return this->lastName;
}

void Employee::setLastName(string lastName) {
    this->lastName = lastName;
}

void Employee::introduceEmployee(){
    cout << this->getFirstName() << setw(8) << this->getLastName() << setw(15) << this->getStartDate().convertToString() << endl;
}


