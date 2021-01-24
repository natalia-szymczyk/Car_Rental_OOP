#include "Budget.hpp"

Budget::Budget(){
    Employees();
    this->setBudget(0);
    todaysDate.setTodaysDate();   
}

Budget::Budget(double budget){
    Employees();
    setBudget(budget);
    todaysDate.setTodaysDate();  
}

string Budget::formatDate(Date date){

    cout << date.convertToString() << endl;

    string stringDate;
    string stringMonth = to_string(date.getMonth());
    string stringYear = to_string(date.getYear());

    stringMonth.insert(stringMonth.begin(), 2 - stringMonth.length(), '0');
    stringYear.insert(stringYear.begin(), 4 - stringYear.length(), '0');

    stringDate = stringMonth.append("-").append(stringYear);

    return stringDate;
}

void Budget::impact(double amount, Date date){
    string month = this->formatDate(date); 

    cout << "IMPACT " << amount << " date " << month << endl;

    if(map.count(month) == 0)
        map.insert(pair<string, double>(month, 0));

    map[month] += amount;

    this->budget += amount;
}

int Budget::expenditure(double amount, Date date){
    string month = this->formatDate(date); 
    double choice;

    cout << "EXPENDITURE " << amount << " date " << month << endl;

    if(map.count(month) == 0)
        map.insert(pair<string, double>(month, 0));
    
    map[month] -= amount;       

    if(this->getBudget() - amount >= 0){
        this->budget -= amount;
        return 0;
    }
    else{
        cout << "\nThere is not enought money in the budget. " << endl;
        cout << "You can try apply for a loan or sell a car. Otherwise, You will go bankrupt." << endl;
        cout << "1. Apply for a loan" << endl;
        cout << "2. Sell a car" << endl;
        cout << "3. Declare bankruptcy" << endl;
        cin >> choice;

        while (!(choice == 1 || choice == 2 || choice == 3)){
            cout << "Wrong number." << endl;
            cin >> choice;
        }

        if(choice == 1){
            return 3;
        }
        else if (choice == 2){
            return 2;                
        }
        else if (choice == 3){
            cout << "You are out of the business." << endl;
            exit(0);
        }
    }
    return 1;
}

void Budget::checkMonth(Date date){
    string month = this->formatDate(date); 
    int monthsBetween = this->todaysDate.getMonthsBetween(date); 

    cout << "Today: " << this->todaysDate.convertToString() << endl;
    cout << "Other: " << date.convertToString() << endl;
    cout << monthsBetween << endl;
    
    Date date2 = Date(todaysDate);

    for(int i = 0; i < monthsBetween; i++){
        date2.addMonthsToDate(1);
        cout << this->formatDate(date2) << endl;
        this->calculatePayments(date2);            
    }

    if(map.count(month) == 0){
        double sum = this->calculateWages() + this->calculateMonthlyPayment();
        this->expenditure(sum, date);
        cout << "Monthly payments per " << month << ": " << sum << endl;
    }

    this->setTodaysDate(date);
}

void Budget::summarizeBudgetForTheMonths(){
    cout << "Summarize: " << endl;

    for(auto it = map.cbegin(); it != map.cend(); ++it){
        cout << it->first << ": " << it->second<< " " << "\n";
    }
}

int Budget::applyForALoan(double amount, Date date, double expenses, double possesion){

    if(this->loan.exists == true){
        if(this->loan.getRemainingPayments() != 0){
            cout << "\nYou must first pay off the current loan" << endl;
            return 0;
        }
    }

    if (map.size() < 5){
        cout << "\nThe company has been in bussiness for too short a time. " << endl;
        cout << "The loan cannot be granted. " << endl;
        return 0;
    }

    if(amount > possesion){
        cout << "\nThe bank will not grant a loan because there is no financial security" << endl;
        return 0;
    }

    int i = 0;
    double sum = 0;

    for(auto it = map.cbegin(); it != map.cend(); ++it){
        if (i >= this->map.size() - 5){
            cout << it->first << ": " << it->second<< " " << "\n";
            sum += it->second;
        }
        i++;
    }

    cout << "Amount of credit: " << amount << endl;
    cout << "Total earnings: " << sum << endl;
    cout << "Forecast expenses: " << expenses << endl;
    cout << "Possessed property: " << possesion << endl;

    if (sum < 0){
        cout << "\nThe company is not profitable. There is no financial balance. " << endl;
        return 0;
    }
    if (expenses > amount){
        cout << "\nThe company has too much expenses. The company is not creditworthy. " << endl;
        return 0;
    }

    int years;
    cout << "For how many years would You like to take a loan? " << endl;
    cin >> years;

    while(years < 0 || years > 30){
        cout << "The period must be less than 30 years. " << endl;
        cin >> years;
    }

    cout << "The loan application has been approved." << endl;

    loan = Loan(amount, years);

    return 1;
}


double Budget::calculateWages(){
    double wages = this->employees.size() * this->salary;
    return wages;
}

void Budget::calculatePayments(Date date){
    string month = this->formatDate(date); 
    double wages = this->employees.size() * this->salary;
    double loanPayment = this->calculateMonthlyPayment();
    double sum = wages + loanPayment;

    if(map.count(month) == 0){
        this->expenditure(sum, date);
        cout << "Overdue monthly payments per " << month << ": " << sum << endl;
    }        
}

double Budget::calculateMonthlyPayment(){
    if(this->loan.exists == true){
        if(this->loan.getRemainingPayments() != 0){
            double amount = this->loan.payMonthly();
            if(amount == 0){
                cout << "The loan has been repaid. " << endl;
                return 0;
            }
            else{
                return amount;
            }
        }
        else
            return 0;
    }
    else
        return 0;
}


Date Budget::getTodaysDate() {
    return this->todaysDate;
}

void Budget::setTodaysDate(Date todaysDate) {
    this->todaysDate = todaysDate;
}

double Budget::getBudget() {
    return this->budget;
}

void Budget::setBudget(double budget) {
    this->budget = budget;
}