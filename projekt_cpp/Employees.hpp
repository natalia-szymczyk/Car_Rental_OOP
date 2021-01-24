#ifndef Employees_hpp
#define Employees_hpp

#include "Employee.hpp"

class Employees{
    private:
        int salary = 3000;

    public:
        vector <Employee> employees;
        Date todaysDate;

        Employees(){
            this->employees.push_back(Employee("John", "Smith", "01-01-2020"));
            this->employees.push_back(Employee("Thomas", "Jones", "02-02-2020"));
            this->employees.push_back(Employee("Thomas", "Jones", "02-02-2020"));
            this->employees.push_back(Employee("James", "Taylor", "04-04-2020"));
            this->employees.push_back(Employee("Olivia", "Davies", "05-05-2020"));
            this->employees.push_back(Employee("Emily", "Evans", "06-06-2020"));
            this->employees.push_back(Employee("Isabella", "Thomson", "07-07-2020"));
            this->employees.push_back(Employee("Mary", "Johnson", "08-08-2020"));
        }

        virtual void hireAnEmployee(Date dateOfEmployment){
            string firstName, lastName;
            cout << "Enter the first name of new employee: " << endl;
            cin >> firstName;
            cout << "Enter the last name of new employee: " << endl;
            cin >> lastName;

            this->employees.push_back(Employee(firstName, lastName, dateOfEmployment));
        }

        virtual void hireAnEmployee(string dateOfEmployment){
            string firstName, lastName;
            cout << "Enter the first name of new employee: " << endl;
            cin >> firstName;
            cout << "Enter the last name of new employee: " << endl;
            cin >> lastName;

            this->employees.push_back(Employee(firstName, lastName, dateOfEmployment));
        }

        virtual int dismissAnEmployee(){                
            int choice, choice2;
            
            cout << "Which employee would You like to dismiss?" << endl;
            this->showAllEmployees();
            cin >> choice;

            while (choice < 0 || choice >= this->employees.size()){
                cout << "Wrong number." << endl;
                cin >> choice;
            }

            cout << "1. Disciplinary dismissal" << endl;
            cout << "2. Dismissal with a severance pay" << endl;
            cin >> choice2;

            while (choice2 != 1 && choice2 != 2){
                cout << "Wrong number." << endl;
                cin >> choice2;
            }

            if(choice2 == 1){
                this->employees.erase(this->employees.begin() + choice2);
                return 0;
            }
            else if(choice2 == 2){
                this->employees.erase(this->employees.begin() + choice2);
                return 3*salary;
            }
            return 0;
        }

        virtual void showAllEmployees(){
            for(int i = 0; i < this->employees.size(); i++ ){
                cout << i << ". ";
                this->employees[i].introduceEmployee();
            }           
        }

        virtual ~Employees(){ };
};

#endif