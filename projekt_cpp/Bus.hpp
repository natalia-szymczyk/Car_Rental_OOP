#ifndef Bus_hpp
#define Bus_hpp

#include "Vehicle.hpp"

class Bus: public Vehicle {
    private:
        int yearOfProduction, bootCapacity, mass, enginePower, engineCapacity, numberOfRentals, numberOfPassengers;
        double consumption, counter, value;
        string brand, model, color;
        bool manual, airConditioning, damaged, accidentFree, available;
        Date lastService, takenTo, todaysDate;
        int choice;
        string inputData;
        vector <Accident> historyOfAccidents;

        double calculatePrice(int timeChoice);
        
    public:
        Bus(string brand, string model, string color, double consumption, double counter, double value, int yearOfProduction, int numberOfRentals, int bootCapacity, int enginePower, int engineCapacity, int mass, bool manual, bool airConditioning, bool accidentFree, int numberOfPassengers);
        Bus(string brand, string model, int yearOfProduction, double counter);
        Bus();
        virtual ~Bus(){};

        void updateCounter(double kilometers) override;
        double calculateFuelConsumption(double kilometers) override;
        void showVehicleInfo(int i) override;
        void showVehicleSpecificInformation() override;
        // void makeFullService();
        void makeFullService(Date date) override;
        double calculateDailyPrice() override;
        double calculateWeeklyPrice() override;
        double calculateMonthlyPrice() override;
        double calculateAdditionalInsurance() override;
        double negotiate(double negotiate, double price) override;
        void addAnAccident(Date date) override;
        // void addAnAccident(string date) override;
        void addAnAccident(string date, string description) override;
        void readAccidents() override;

    
        Date getTakenTo();
        void setTakenTo(Date takenTo);
        string getBrand();
        void setBrand(string brand);
        string getModel();
        void setModel(string model);
        string getColor();
        void setColor(string color);
        double getConsumption();
        void setConsumption(double consumption);
        double getCounter();
        void setCounter(double counter);
        double getValue();
        void setValue(double value);
        int getYearOfProduction();
        void setYearOfProduction(int yearOfProduction);
        int getNumberOfRentals();
        void setNumberOfRentals(int numberOFRentals);
        bool isManual();
        bool getManual();
        void setManual(bool manual);
        bool isAvailable();
        bool getAvailable();
        void setAvailable(bool available);
        bool isAirConditioning();
        bool getAirConditioning();
        void setAirConditioning(bool airConditioning);
        bool isDamaged();
        bool getDamaged();
        void setDamaged(bool damaged);
        bool isAccidentFree();
        bool getAccidentFree();
        void setAccidentFree(bool accidentFree);
        int getBootCapacity();
        void setBootCapacity(int bootCapacity);
        int getEnginePower();
        void setEnginePower(int enginePower);
        int getEngineCapacity();
        void setEngineCapacity(int engineCapacity);
        int getNumberOfPassengers();
        void setNumberOfPassengers(int numberOfPassengers);
        int getMass();
        void setMass(int mass);
        Date getLastService();
        void setLastService(Date lastService);


};

#endif