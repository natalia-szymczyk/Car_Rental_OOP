#include "Loan.hpp"

Loan::Loan(){
    this->exists = false;
}

Loan::Loan(double amount, int years){
    this->exists = true;
    this->amount = amount;
    this->years = years;
    this->numberOfPayments = this->years * 12;
    this->remainingAmount = this->amount * ( 1 + annualPercentageRate);
    this->remainingPayments = this->numberOfPayments;
    this->calculateLoan();
}

void Loan::calculateLoan(){
    double monthlyPercentageRate = this->annualPercentageRate / 12;
    this->monthlyPayment = (double) (this->amount
         * (monthlyPercentageRate * pow(monthlyPercentageRate + 1, this->numberOfPayments))
            / (pow(monthlyPercentageRate + 1, this->numberOfPayments) - 1));

    cout << "Amount of credit: " <<  this->amount << endl;
    cout << "Total amount to be paid: " <<  this->remainingAmount << endl;
    cout << "Period: " <<  this->years << endl;
    cout << "Monthly payment: " <<  this->monthlyPayment << endl;
}

double Loan::payMonthly(){
    if(remainingPayments-- != 0){
        this->remainingAmount -= this->monthlyPayment;
        return this->monthlyPayment;
    }
    else{
        this->exists = false;
        return 0;
    }
}

double Loan::getRemainingAmount() {
    return this->remainingAmount;
}

void Loan::setRemainingAmount(double remainingAmount) {
    this->remainingAmount = remainingAmount;
}

int Loan::getRemainingPayments() {
    return this->remainingPayments;
}

void Loan::setRemainingPayments(int remainingPayments) {
    this->remainingPayments = remainingPayments;
}

double Loan::getAmount() {
    return this->amount;
}

void Loan::setAmount(int amount) {
    this->amount = amount;
}

int Loan::getYears() {
    return this->years;
}

void Loan::setYears(int years) {
    this->years = years;
}

double Loan::getMonthlyPayment() {
    return this->monthlyPayment;
}

void Loan::setMonthlyPayment(double monthlyPayment) {
    this->monthlyPayment = monthlyPayment;
}
