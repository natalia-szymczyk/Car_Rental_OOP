#ifndef Loan_hpp
#define Loan_hpp

#include <iostream>
#include <cmath>

using namespace std;

class Loan{
    private:
        double amount, remainingAmount, monthlyPayment, annualPercentageRate = 0.08;
        int years, numberOfPayments, remainingPayments;
        void calculateLoan();

    public:
        Loan();
        Loan(double amount, int years);
        bool exists;
        double payMonthly();
        double getRemainingAmount();
        void setRemainingAmount(double remainingAmount);
        int getRemainingPayments();
        void setRemainingPayments(int remainingPayments);
        double getAmount();
        void setAmount(int amount);
        int getYears();
        void setYears(int years);
        double getMonthlyPayment();
        void setMonthlyPayment(double monthlyPayment);

};

#endif