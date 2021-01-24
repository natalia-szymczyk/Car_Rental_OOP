#include "Bus.hpp"

Bus::Bus(string brand, string model, string color, double consumption, double counter, double value, int yearOfProduction,
int numberOfRentals, int bootCapacity, int enginePower, int engineCapacity, int mass, bool manual, bool airConditioning, bool accidentFree,
int numberOfPassengers){
    setBrand(brand);
    setModel(model);
    setColor(color);
    setConsumption(consumption);
    setCounter(counter);
    setValue(value);
    setYearOfProduction(yearOfProduction);
    setNumberOfRentals(numberOfRentals);
    setBootCapacity(bootCapacity);
    setEnginePower(enginePower);
    setEngineCapacity(engineCapacity);
    setMass(mass);
    setManual(manual);
    setAirConditioning(airConditioning);    
    setAccidentFree(accidentFree);
    setDamaged(false);
    setAvailable(true);
    todaysDate.setTodaysDate();
    setLastService(todaysDate);
    setNumberOfPassengers(numberOfPassengers);
}

Bus::Bus(string brand, string model, int yearOfProduction, double counter){
    Bus(brand, model, "", 7, counter, 0, yearOfProduction, 0, 0, 0, 0, 0, true, true, true, 20);
}

Bus::Bus(){
    Bus("", "", 0, 0);
}

void Bus::updateCounter(double kilometers){
    this->counter += kilometers; 
}

double Bus::calculateFuelConsumption(double kilometers){ 
    return (kilometers * this->consumption)/100;
}

void Bus::showVehicleInfo(int i){
    string stringAvailable = "NO";
    if(this->getAvailable())
        stringAvailable = "YES";

    // cout << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    cout << i << ". " << stringAvailable << setw(20) << this->getBrand() << setw(15) << this->getModel() << setw(15) << this->getColor() << setw(15) << this->getYearOfProduction() << setw(15) << this->getConsumption() << setw(20) << this->getBootCapacity() << setw(15) << this->getNumberOfPassengers() << " passengers" << endl;
}

void Bus::showVehicleSpecificInformation(){ 
    string stringManual = "NO", stringAirConditioning = "NO";
    if(this->getManual())
        stringManual = "YES";
    if(this->getAirConditioning())
        stringAirConditioning = "NO";

    cout << setw(15) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(15) << "Consumption" << setw(20) << "Boot Capacity" << setw(15) << "Engine Power" << setw(20) << "Engine Capacity" << setw(12) << "Manual" << setw(20) << "Air Conditioning" << setw(25) << "Number of passengers" << endl;
    cout << setw(15) << this->getBrand() << setw(15) << this->getModel() << setw(15) << this->getColor() << setw(15) << this->getYearOfProduction() << setw(10) << this->getConsumption() << setw(20) << this->getBootCapacity() << setw(15) << this->getEnginePower() << setw(18) << this->getEngineCapacity() << setw(17) << this->getManual() << setw(15) << this->getAirConditioning() << setw(20) << this->getNumberOfPassengers() << endl;
}

// void Bus::makeFullService(){ 


// }

void Bus::makeFullService(Date date){ 
    this->setLastService(date);
    cout << "Date of service of " << this->getBrand() << " " << this->getModel() << ": " << this->getLastService().convertToString() << endl;
}

double Bus::calculatePrice(int timeChoice){
    double basePrice;
    int kilometers;

    if(this->getNumberOfPassengers() <= 35){
        basePrice = (double)3.5;
    }
    else{
        basePrice = (double)4;
    }

    if(this->getAirConditioning() == true){
        basePrice += 0.25;
    }
    if(this->getAccidentFree() == true){
        basePrice += 0.25;
    }
    if(this->getYearOfProduction() >= 2020){
        basePrice += 1;
    }

    cout << "How many kilometers do You expect the trip will have?" << endl;
    cin >> kilometers;
    basePrice *= kilometers;
    this->updateCounter(kilometers);

    cout << "Would You like to rent a bus with a driver?" << endl;
    cout << "1. Yes \n2. No" << endl;
    cin >> this->choice;

    while (this->choice != 1 && this->choice != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> this->choice;
    }

    if(this->choice == 1){
        basePrice += 300 * timeChoice;
    }  

    if(timeChoice == 1){
        if (this->getNumberOfPassengers() > 45 && basePrice < 1500){
            basePrice = 1500;
        }
        if (this->getNumberOfPassengers() < 45 && basePrice < 1200){
            basePrice = 1200;
        }
    }
    
    if(timeChoice == 7){
        if (this->getNumberOfPassengers() > 45 && basePrice < 9500){
            basePrice = 8500;
        }
        if (this->getNumberOfPassengers() < 45 && basePrice < 8200){
            basePrice = 8200;
        }
    }
    
    if(timeChoice == 30){
        if (this->getNumberOfPassengers() > 45 && basePrice < 40000){
            basePrice = 40000;
        }
        if (this->getNumberOfPassengers() < 45 && basePrice < 32000){
            basePrice = 32000;
        }
    }

    return basePrice;
}

double Bus::calculateDailyPrice(){ 
    return this->calculatePrice(1);
}

double Bus::calculateWeeklyPrice(){ 
    return this->calculatePrice(1);
}

double Bus::calculateMonthlyPrice(){ 
    return this->calculatePrice(7);
}

double Bus::calculateAdditionalInsurance(){ 
    return this->getValue() * (double)0.0001 + 300; 
}

double Bus::negotiate(double negotiate, double price){ 
    if(negotiate > price){
        cout << "No problem for us." << endl;
        return negotiate;
    }

    if(negotiate < (price * (double)0.9)){
        cout << "Your suggested price is too low. " << endl;
        cout << "We can offer You " + max((int)(price * 0.9), (int)((negotiate + price)/2));
        cout << "Do You accept this offer?" << endl;
        cout << "1. Yes \n2. No" << endl;
        cin >> this->choice;
    
        while (this->choice != 1 && this->choice != 2){
            cout << "Wrong number. Enter 1 or 2." << endl;
            cin >> this->choice;
        }

        if(this->choice == 1){
            cout << "Great." << endl;
            return max(price*(double)0.9, (negotiate + price)/2);
        }
        if(this->choice == 2){
            cout << "Would You like to resign (1) or try to negotiate again(2)? " << endl;
            cin >> this->choice;
    
            while (this->choice != 1 && this->choice != 2){
                cout << "Wrong number. Enter 1 or 2." << endl;
                cin >> this->choice;
            }
            
            if(this->choice == 1){
                cout << "We are sorry that we did not meet the requirements" << endl;
                return 0;
            }
            else if(this->choice == 2){
                cout << "What price do You suggest?" << endl;
                cin >> negotiate;

                if(negotiate > price){
                    cout << "No problem for us." << endl;
                    return negotiate;
                }  

                if(negotiate < (price * (double)0.83)){
                    cout << "Your suggested price is too low. " << endl;
                    cout << "We can offer You " + max((int)(price * 0.83), (int)((negotiate + price)/2));
                    cout << "Do You accept this offer?" << endl;
                    cout << "1. Yes \n2. No" << endl;
                    cin >> this->choice;
                
                    while (this->choice != 1 && this->choice != 2){
                        cout << "Wrong number. Enter 1 or 2." << endl;
                        cin >> this->choice;
                    }
        
                    if(this->choice == 1){
                        cout << "Great." << endl;
                        return max(price*(double)0.9, (negotiate + price)/2);
                    }
                    else if(this->choice == 2){
                        cout << "We are sorry that we did not meet the requirements" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    cout << "We can agree to this proposal. " << endl;

    return negotiate;
}

void Bus::addAnAccident(Date date){ 
    string description;
    cout << "Describe the accident: " << endl;
    cin >> description;

    Accident accident = Accident(date, description);
    this->historyOfAccidents.push_back(accident);
    this->setAccidentFree(false);
}

void Bus::addAnAccident(string date, string description){ 
    Date inputDate =  Date(date);
    this->historyOfAccidents.push_back(Accident(date, description));
}

void Bus::readAccidents(){ 
    if (this->getAccidentFree()){
        cout << "The bus is accident free-> " << endl;
        return;
    }
    if (this->historyOfAccidents.size() == 0){
        cout << "The bus accident history is empty" << endl;
        return;
    }
    
    cout << "Accidents: " << endl;

    for (int i = 0; i < this->historyOfAccidents.size(); i++){
        cout << "\t" << this->historyOfAccidents[i].getDate().convertToString() + ": ";
        cout << this->historyOfAccidents[i].getDescription() << endl;
    }
}

Date Bus::getTakenTo() {
    return this->takenTo;
}

void Bus::setTakenTo(Date takenTo) {
    this->takenTo = takenTo;
}

string Bus::getBrand() {
    return this->brand;
}

void Bus::setBrand(string brand) {
    this->brand = brand;
}

string Bus::getModel() {
    return this->model;
}

void Bus::setModel(string model) {
    this->model = model;
}

string Bus::getColor() {
    return this->color;
}

void Bus::setColor(string color) {
    this->color = color;
}

double Bus::getConsumption() {
    return this->consumption;
}

void Bus::setConsumption(double consumption) {
    this->consumption = consumption;
}

double Bus::getCounter() {
    return this->counter;
}

void Bus::setCounter(double counter) {
    this->counter = counter;
}

double Bus::getValue() {
    return this->value;
}

void Bus::setValue(double value) {
    this->value = value;
}

int Bus::getYearOfProduction() {
    return this->yearOfProduction;
}

void Bus::setYearOfProduction(int yearOfProduction) {
    this->yearOfProduction = yearOfProduction;
}

int Bus::getNumberOfRentals() {
    return this->numberOfRentals;
}

void Bus::setNumberOfRentals(int numberOFRentals) {
    this->numberOfRentals = numberOFRentals;
}

bool Bus::getManual() {
    return this->manual;
}

void Bus::setManual(bool manual) {
    this->manual = manual;
}

bool Bus::getAvailable() {
    return this->available;
}

void Bus::setAvailable(bool available) {
    this->available = available;
}

bool Bus::getAirConditioning() {
    return this->airConditioning;
}

void Bus::setAirConditioning(bool airConditioning) {
    this->airConditioning = airConditioning;
}

bool Bus::getDamaged() {
    return this->damaged;
}

void Bus::setDamaged(bool damaged) {
    this->damaged = damaged;
}

bool Bus::getAccidentFree() {
    return this->accidentFree;
}

void Bus::setAccidentFree(bool accidentFree) {
    this->accidentFree = accidentFree;
}

int Bus::getBootCapacity() {
    return this->bootCapacity;
}

void Bus::setBootCapacity(int bootCapacity) {
    this->bootCapacity = bootCapacity;
}

int Bus::getEnginePower() {
    return this->enginePower;
}

void Bus::setEnginePower(int enginePower) {
    this->enginePower = enginePower;
}

int Bus::getEngineCapacity() {
    return this->engineCapacity;
}

int Bus::getMass() {
    return this->mass;
}

void Bus::setMass(int mass) {
    this->mass = mass;
}

int Bus::getNumberOfPassengers() {
    return this->numberOfPassengers;
}

void Bus::setNumberOfPassengers(int numberOfPassengers) {
    this->numberOfPassengers = numberOfPassengers;
}

void Bus::setEngineCapacity(int engineCapacity) {
    this->engineCapacity = engineCapacity;
}

Date Bus::getLastService() {
    return this->lastService;
}

void Bus::setLastService(Date lastService) {
    this->lastService = lastService;
}