#ifndef Fleet_hpp
#define Fleet_hpp

#include "Budget.hpp"
#include "Vehicle.hpp"
#include "Car.hpp"
#include "Bus.hpp"

#include <typeinfo>
#include <stdio.h>
#include <variant>
#include <algorithm>
#include <cstdlib>
#include <iterator>

using namespace std;

class Fleet{
    private:
        vector<Vehicle*> vehicles;
        int numberOfCars = 0, numberOfBuses = 0;
        int choice, choicePeriod, choiceRepair, choiceInsurance, choiceNegotiation, choiceType, index, decision;
        double price, kilometers, expenses, possession;
        Date todaysDate;
        void sortByYear();
        void sortByConsumption();
        void sortByBootCapacity();
        void sortByValue();
        void scrapACar(Vehicle* car);
        // void scrapACar(Bus bus);
        void scrapACar(int index);
        void sellAVehicle(Vehicle* car);
        // void sellAVehicle(Bus bus);
        void repairAVehicle(Vehicle* car);
        // void repairAVehicle(Bus bus);

    public:
        Fleet();
        Budget budget = Budget(1000000);
        void makeAService(Date date);
        void expenditure(double amount);
        void buyAVehicle();
        void rentAVehicle(Date date);
        Date changeDate(string dateFromInputString);
        void sortCars();
        void showAvailableCars();
        void showAvailableBuses();
        void showAvailableVehicles();
        void showAllCars();
        void showAllBuses();
        void showAllVehicles();
        void showSpecificInformation();
        void reportAccident(Date date);
        void sellAVehicle();
        void repairAVehicle();
        double forecastExpenses();
        double calculatePossession();
        void calculateFuel();
        Date getTodaysDate();
        void setTodaysDate(Date todaysDate);

       

 

};


#endif