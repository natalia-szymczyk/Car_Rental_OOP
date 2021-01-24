#pragma once

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include "Date.hpp"
#include "Accident.hpp"
#include <vector>
#include <algorithm>

class Vehicle {
    public:
        Vehicle() { };
        virtual void updateCounter(double kilometers) = 0;
        virtual double calculateFuelConsumption(double kilometers) = 0;
        virtual void showVehicleInfo(int i) = 0;
        virtual void showVehicleSpecificInformation() = 0;
        // virtual void makeFullService();
        virtual void makeFullService(Date date) = 0;
        virtual double calculateDailyPrice() = 0;
        virtual double calculateWeeklyPrice() = 0;
        virtual double calculateMonthlyPrice() = 0;
        virtual double calculateAdditionalInsurance() = 0;
        virtual double negotiate(double negotiate, double price) = 0;
        virtual void addAnAccident(Date date) = 0;
        // virtual void addAnAccident(string date) = 0;
        virtual void addAnAccident(string date, string description) = 0;
        virtual void readAccidents() = 0;
        virtual ~Vehicle() { };

        virtual Date getTakenTo() = 0;
        virtual void setTakenTo(Date takenTo) = 0;
        virtual string getBrand() = 0;
        virtual void setBrand(string brand) = 0;
        virtual string getModel() = 0;
        virtual void setModel(string model) = 0;
        virtual string getColor() = 0;
        virtual void setColor(string color) = 0;
        virtual double getConsumption() = 0;
        virtual void setConsumption(double consumption) = 0;
        virtual double getCounter() = 0;
        virtual void setCounter(double counter) = 0;
        virtual double getValue() = 0;
        virtual void setValue(double value) = 0;
        virtual int getYearOfProduction() = 0;
        virtual void setYearOfProduction(int yearOfProduction) = 0;
        virtual int getNumberOfRentals() = 0;
        virtual void setNumberOfRentals(int numberOFRentals) = 0;
        virtual bool getManual() = 0;
        virtual void setManual(bool manual) = 0;
        virtual bool getAvailable() = 0;
        virtual void setAvailable(bool available) = 0;
        virtual bool getAirConditioning() = 0;
        virtual void setAirConditioning(bool airConditioning) = 0;
        virtual bool getDamaged() = 0;
        virtual void setDamaged(bool damaged) = 0;
        virtual bool getAccidentFree() = 0;
        virtual void setAccidentFree(bool accidentFree) = 0;
        virtual int getBootCapacity() = 0;
        virtual void setBootCapacity(int bootCapacity) = 0;
        virtual int getEnginePower() = 0;
        virtual void setEnginePower(int enginePower) = 0;
        virtual int getEngineCapacity() = 0;
        virtual void setEngineCapacity(int engineCapacity) = 0;
        virtual int getNumberOfPassengers() = 0;
        virtual void setNumberOfPassengers(int numberOfPassengers) = 0;
        virtual int getMass() = 0;
        virtual void setMass(int mass) = 0;
        virtual Date getLastService() = 0;
        virtual void setLastService(Date lastService) = 0;
};

#endif