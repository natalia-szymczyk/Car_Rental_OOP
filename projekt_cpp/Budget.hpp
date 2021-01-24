#ifndef Budget_hpp
#define Budget_hpp

#include "Date.hpp"
#include "Employees.hpp"
#include "Loan.hpp"
#include <map>

class Budget: public Employees{
    public:
        double budget;
        Date todaysDate;
        Loan loan;
        
        Budget();
        Budget(double budget);
        Date getTodaysDate();
        void setTodaysDate(Date todaysDate);
        double getBudget();
        void setBudget(double budget);
        void impact(double amount, Date date);
        int expenditure(double amount, Date date);
        void summarizeBudgetForTheMonths();
        void checkMonth(Date date);
        int applyForALoan(double amount, Date date, double expenses, double possesion);
        double calculateWages();

    private:
        map<string, double> map;
        void calculatePayments(Date date);
        double calculateMonthlyPayment();
        string formatDate(Date date);
        int salary = 3000;


};

#endif