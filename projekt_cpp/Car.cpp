#include "Car.hpp"

Car::Car(string brand, string model, string color, double consumption, double counter, double value, int yearOfProduction,
int numberOfRentals, int bootCapacity, int enginePower, int engineCapacity, int mass, bool manual, bool airConditioning, bool accidentFree){
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
}

Car::Car(string brand, string model, int yearOfProduction, double counter){
    Car(brand, model, "", 7, counter, 0, yearOfProduction, 0, 0, 0, 0, 0, true, true, true);
}

Car::Car(){
    Car("", "", 0, 0);
}

void Car::updateCounter(double kilometers){
    this->counter += kilometers; 
}

double Car::calculateFuelConsumption(double kilometers){ 
    return (kilometers * this->consumption)/100;
}

void Car::showVehicleInfo(int i){
    string stringAvailable = "NO";
    if(this->getAvailable())
        stringAvailable = "YES";

    // cout << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    cout << i << ". " << stringAvailable << setw(20) << this->getBrand() << setw(15) << this->getModel() << setw(15) << this->getColor() << setw(15) << this->getYearOfProduction() << setw(15) << this->getConsumption() << setw(20) << this->getBootCapacity() << endl;
}

void Car::showVehicleSpecificInformation(){ 
    string stringManual = "NO", stringAirConditioning = "NO";
    if(this->getManual())
        stringManual = "YES";
    if(this->getAirConditioning())
        stringAirConditioning = "NO";

    cout << setw(15) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(15) << "Consumption" << setw(20) << "Boot Capacity" << setw(15) << "Engine Power" << setw(20) << "Engine Capacity" << setw(12) << "Manual" << setw(20) << "Air Conditioning" << endl;
    cout << setw(15) << this->getBrand() << setw(15) << this->getModel() << setw(15) << this->getColor() << setw(15) << this->getYearOfProduction() << setw(10) << this->getConsumption() << setw(20) << this->getBootCapacity() << setw(15) << this->getEnginePower() << setw(18) << this->getEngineCapacity() << setw(17) << stringManual << setw(15) << stringAirConditioning << endl;
}

// void Car::makeFullService(){ 


// }

void Car::makeFullService(Date date){ 
    this->setLastService(date);
    cout << "Date of service of " << this->getBrand() << " " << this->getModel() << ": " << this->getLastService().convertToString() << endl;
}

double Car::calculateDailyPrice(){ 
    double basePrice = 20 + this->getValue() * (double)0.001;

    if(this->getAirConditioning() == true){
        basePrice += 20;
    }
    if(this->getAccidentFree() == true){
        basePrice *= 1.05;
    }
    if(this->getManual() == false){
        basePrice += 30;
    }

    return basePrice;
}

double Car::calculateWeeklyPrice(){ 
    return this->calculateDailyPrice() * 7 * 0.8;
}

double Car::calculateMonthlyPrice(){ 
    return this->calculateDailyPrice() * 30 * 0.65;
}

double Car::calculateAdditionalInsurance(){ 
    return this->getValue() * 0.0001 + 30;
}

double Car::negotiate(double negotiate, double price){ 
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

void Car::addAnAccident(Date date){ 
    string description;
    cout << "Describe the accident: " << endl;
    cin >> description;

    Accident accident = Accident(date, description);
    this->historyOfAccidents.push_back(accident);
    this->setAccidentFree(false);
}

void Car::addAnAccident(string date, string description){ 
    Date inputDate =  Date(date);
    this->historyOfAccidents.push_back(Accident(date, description));
}

void Car::readAccidents(){ 
    if (this->getAccidentFree()){
        cout << "The car is accident free-> " << endl;
        return;
    }
    if (this->historyOfAccidents.size() == 0){
        cout << "The car accident history is empty" << endl;
        return;
    }
    cout << "\t" << "Accidents: " << endl;

    for (int i = 0; i < this->historyOfAccidents.size(); i++){
        cout << "\t" << this->historyOfAccidents[i].getDate().convertToString() + ": ";
        cout << this->historyOfAccidents[i].getDescription() << endl;
    }
}

Date Car::getTakenTo() {
    return this->takenTo;
}

void Car::setTakenTo(Date takenTo) {
    this->takenTo = takenTo;
}

string Car::getBrand() {
    return this->brand;
}

void Car::setBrand(string brand) {
    this->brand = brand;
}

string Car::getModel() {
    return this->model;
}

void Car::setModel(string model) {
    this->model = model;
}

string Car::getColor() {
    return this->color;
}

void Car::setColor(string color) {
    this->color = color;
}

double Car::getConsumption() {
    return this->consumption;
}

void Car::setConsumption(double consumption) {
    this->consumption = consumption;
}

double Car::getCounter() {
    return this->counter;
}

void Car::setCounter(double counter) {
    this->counter = counter;
}

double Car::getValue() {
    return this->value;
}

void Car::setValue(double value) {
    this->value = value;
}

int Car::getYearOfProduction() {
    return this->yearOfProduction;
}

void Car::setYearOfProduction(int yearOfProduction) {
    this->yearOfProduction = yearOfProduction;
}

int Car::getNumberOfRentals() {
    return this->numberOfRentals;
}

void Car::setNumberOfRentals(int numberOFRentals) {
    this->numberOfRentals = numberOFRentals;
}

bool Car::getManual() {
    return this->manual;
}

void Car::setManual(bool manual) {
    this->manual = manual;
}

bool Car::getAvailable() {
    return this->available;
}

void Car::setAvailable(bool available) {
    this->available = available;
}

bool Car::getAirConditioning() {
    return this->airConditioning;
}

void Car::setAirConditioning(bool airConditioning) {
    this->airConditioning = airConditioning;
}

bool Car::getDamaged() {
    return this->damaged;
}

void Car::setDamaged(bool damaged) {
    this->damaged = damaged;
}

bool Car::getAccidentFree() {
    return this->accidentFree;
}

void Car::setAccidentFree(bool accidentFree) {
    this->accidentFree = accidentFree;
}

int Car::getBootCapacity() {
    return this->bootCapacity;
}

void Car::setBootCapacity(int bootCapacity) {
    this->bootCapacity = bootCapacity;
}

int Car::getEnginePower() {
    return this->enginePower;
}

void Car::setEnginePower(int enginePower) {
    this->enginePower = enginePower;
}

int Car::getEngineCapacity() {
    return this->engineCapacity;
}

int Car::getMass() {
    return this->mass;
}

void Car::setMass(int mass) {
    this->mass = mass;
}

int Car::getNumberOfPassengers() {
    return this->numberOfPassengers;
}

void Car::setNumberOfPassengers(int numberOfPassengers) {
    this->numberOfPassengers = numberOfPassengers;
}

void Car::setEngineCapacity(int engineCapacity) {
    this->engineCapacity = engineCapacity;
}

Date Car::getLastService() {
    return this->lastService;
}

void Car::setLastService(Date lastService) {
    this->lastService = lastService;
}