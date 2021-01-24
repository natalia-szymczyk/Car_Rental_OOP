#include <iostream>

#include "Text.hpp"
#include "Date.hpp"
#include "Vehicle.hpp"
#include "Car.hpp"
#include "Bus.hpp"
#include "Employee.hpp"
#include "Budget.hpp"
#include "Fleet.hpp"

using namespace std;

int main(){
    Date todaysDate;
    todaysDate.setTodaysDate();
    cout << todaysDate.convertToString() << endl;

    int choice = 1, choice2 = 1, test = 0;
    double amount, currentExpenses, possesion;

    Text text;
    text.printText();

    Fleet fleet;

    do{
        cout << "Enter the number: " << endl;
        cin >> choice;

        switch (choice){
        case 0:
            break;
        
        case 1:{
            fleet.rentAVehicle(todaysDate);
        }break;
        
        case 2:{
            fleet.sellAVehicle();
        }break;
        
        case 3:{
            fleet.buyAVehicle();
        }break;
        
        case 4:{
            fleet.repairAVehicle();
        }break;
        
        case 5:{
            fleet.reportAccident(todaysDate);  
        }break;
        
        case 6:{
            fleet.showAvailableCars();
        }break;            
        
        case 7:{
            fleet.sortCars();
        }break;
        
        case 8:{
            fleet.showAllBuses();
        }break;
        
        case 9:{
            fleet.showSpecificInformation();
        }break;
        
        case 10:{
            fleet.makeAService(todaysDate);
        }break;
        
        case 11:{
            fleet.calculateFuel();          
        }break;
        
        case 12:{
            text.printEmployeeText();
            do{
                cout << "Enter the number: " << endl;
                cin >> choice2;

                switch (choice2){
                    case 0:{
                        
                    }break;                        
                    
                    case 1:{                    
                        fleet.budget.hireAnEmployee(todaysDate);
                        
                    }break;
                    
                    case 2:{
                        amount = fleet.budget.dismissAnEmployee();
                        fleet.expenditure(amount);                
                        
                    }break;
                    
                    case 3:{
                        fleet.budget.showAllEmployees();  
                        
                    }break;
                    
                    case 4:{
                        cout << "Enter the amount: " << endl;
                        cin >> amount;
                        fleet.budget.impact(amount, todaysDate);                
                        
                    }break;
                    
                    case 5:{
                        cout << "Enter the amount: " << endl;
                        cin >> amount;
                        fleet.expenditure(amount);                   
                        
                    }break;
                    
                    case 6:{
                        cout << "Total budget amount: " << setprecision(10) << fleet.budget.getBudget() << endl;
                        
                    }break;
                    
                    case 7:{
                        fleet.budget.summarizeBudgetForTheMonths();
                        
                    }break;
                    
                    case 8:{
                        currentExpenses = fleet.forecastExpenses();
                        possesion = fleet.calculatePossession();
                        cout << "How much money would You like to take for a loan? " << endl;
                        cin >> amount;
                        fleet.budget.applyForALoan(amount, todaysDate, currentExpenses, possesion);                                            
                    }break;
                                
                    default:{
                        text.printEmployeeText();
                        
                    }break;
                }
                    
            } while (choice2 != 0);   

        }break;
        
        case 13:{
            int day, month, year;
            cout << "Enter the date in format dd mm yyyy " << endl;
            cin >> day >> month >> year;
            todaysDate.changeDate(day, month, year);   
            fleet.changeDate(todaysDate.convertToString()); 
        }break;

        default:{
            cout << "Unknown operation " << endl;
            text.printText();
        }break;

        }
        
    } while (choice != 0);    

    return 0;    
}