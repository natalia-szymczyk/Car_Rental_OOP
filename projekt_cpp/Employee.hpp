#ifndef Employee_hpp
#define Employee_hpp

#include "Date.hpp"

class Employee{
    protected:
        string firstName, lastName;
    
    public:
        int workedMonths;
        Date startDate;

        Employee(string firstName, string lastName, string dateFromInputstring);
        Employee(string firstName, string lastName, Date dateFromInput);
        int calculateWorkedMonths(Date todaysDate);
        Date getStartDate();
        void setStartDate(Date startDate);
        int getWorkedMonths();
        void setWorkedMonths(int workedMonths);
        string getFirstName();
        void setFirstName(string firstName);
        string getLastName();
        void setLastName(string lastName);
        void introduceEmployee();
};

#endif