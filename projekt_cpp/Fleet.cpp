#include "Fleet.hpp"

Fleet::Fleet() { 
    this->vehicles.push_back(new Car("Volkswagen", "Passat", "Black", (double)6.5, 170000, 80000, 2017, 26, 600, 190, 2000, 1735, false, true, true));
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Volkswagen", "Tiguan", "White", (double)8.5, 30000, 135000, 2018, 15, 470, 150, 2000, 1681, false, true, true));
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Toyota", "Yaris", "Red", (double)4.5, 95000, 20000, 2007, 40, 200, 90, 1300, 1000, true, false, false));
    vehicles[numberOfCars]->addAnAccident("10-02-2010", "Read-End Accident");
    vehicles[numberOfCars]->addAnAccident("15-12-2015", "Small collision");
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Mercedes-Benz", "E-class", "White", (double)12.5, 50000, 330000, 2018, 6, 640, 435, 3000, 1970, false, true, true));
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Mercedes-Benz", "ML", "Black", (double)10.5, 220000, 54000, 2009, 27, 540, 190, 3000, 2300, false, true, false));
    vehicles[numberOfCars]->addAnAccident("15-05-2012", "Side Impact");
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Volvo", "S60", "Black", 8, 5000, 165000, 2020, 1, 600, 190, 2000, 1700, false, true, true));
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Audi", "RS5", "Grey", 11, 30000, 150000, 2010, 5, 350, 450, 3000, 2000, false, true, true));
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Opel", "Astra", "Black", 5, 80000, 36000, 2017, 9, 300, 110, 1600, 1400, true, true, true));
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Ford", "Fiesta", "Silver", (double)4.5, 140000, 10000, 2007, 30, 300, 75, 1200, 1600, true, false, false));
    vehicles[numberOfCars]->addAnAccident("20-01-2009", "Runoff");
    vehicles[numberOfCars]->addAnAccident("10-07-2017", "Rear-End Collision");
    this->numberOfCars++;
    this->vehicles.push_back(new Car("Fiat", "500", "Black", 0, 45000,65000, 2016, 10, 250, 120, 0, 900, false, true, true));
    this->numberOfCars++;

    this->vehicles.push_back(new Bus("Iveco", "Rosero", "Grey", 18, 1000, 500000, 2020, 0, 2000, 200, 3000, 5000, true, true, true, 31));
    this->numberOfBuses++;
    this->vehicles.push_back(new Bus("Scania", "Touring", "White", 27, 150000, 450000, 2018, 11, 12000, 411, 13000, 8000, true, true, false, 51));
    vehicles[numberOfBuses]->addAnAccident("30-07-2019", "Little collision in Germany");
    this->numberOfBuses++;

    todaysDate.setTodaysDate();
}

void Fleet::makeAService(Date date) { 
    int choice;
    cout << "Which vehicle would You like to make a full service?" << endl;
    this->showAllVehicles();
    cout << this->numberOfBuses << this->numberOfCars << ". All vehicles" << endl;
    cin >> choice;

    while (choice < 0 || choice > this->numberOfCars + this->numberOfBuses){
        cout << "Wrong number." << endl;
        cin >> choice;
    }

    while(choice > 0 && choice < this->numberOfCars + this->numberOfBuses && vehicles[choice]->getDamaged()){
        cout << "Wrong number." << endl;
        cout << "This car is damaged. You have to repair it first." << endl;
        cin >> choice;
    }

    if (choice == this->numberOfBuses + this->numberOfCars){
        for(int i = 0; i < this->numberOfBuses + this->numberOfCars; i++){                
            if (dynamic_cast<Car*>(vehicles[i]))
                this->expenditure(100);
            
            else if(dynamic_cast<Bus*>(vehicles[i]))
                this->expenditure(200);
            
                vehicles[i]->makeFullService(date);
        }
        return;
    }

    if (dynamic_cast<Car*>(vehicles[choice]))
        this->expenditure(100);

    else if(dynamic_cast<Bus*>(vehicles[choice]))
        this->expenditure(200);

        vehicles[choice]->makeFullService(date);
}

void Fleet::expenditure(double amount) { 
    int choice;
    choice = this->budget.expenditure(amount, todaysDate);
    if(choice == 2){
        this->sellAVehicle();
        this->expenditure(amount);
    }
    else if(choice == 3){
        expenses = this->forecastExpenses();
        possession = this->calculatePossession();
        decision = this->budget.applyForALoan(amount, todaysDate, expenses, possession);
        if (decision == 1)
            this->expenditure(amount);
        else if(decision == 0){
            cout << "\nWe are sorry that Your company did not receive the loan. " << endl;
            cout << "Unfortunately, it turns out that Your company do not have the money for this expense. " << endl;
            cout << "The only option to stay in the bussiness is to sell a vehicle, to earn some money." << endl;
            cout << "Do You agree to this option? " << endl;
            cout << "(1) Yes  (2) No" << endl;
            cin >> decision;

            while (decision != 1 && decision != 2){
                cout << "Wrong number." << endl;
                cin >> decision;
            }

            if(decision == 1){
                this->sellAVehicle();
                this->expenditure(amount);
            }
            else{
                cout << "You are out of the business." << endl;
                exit(0);
            }
        }
    }
}

void Fleet::buyAVehicle() { 
    int inputInt, boolCar, choice, choiceType;
    double inputdouble;
    string inputString;

    cout << "Car(1) or bus(2)?" << endl;
    cin >> choiceType;

    while (choiceType != 1 && choiceType != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choiceType;
    }

    cout << "New(1) or used(2)?" << endl;
    cin >> choice;

    while (choice != 1 && choice != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choice;
    }

    cout << "Value: " << endl;
    cin >> price;
    this->expenditure(price);

    index = this->numberOfCars + this->numberOfBuses;

    if (choiceType == 1){
        vehicles.push_back(new Car());
        this->numberOfCars++;
    }
    else if(choiceType == 2){
        vehicles.push_back(new Bus());
        this->numberOfBuses++;

        cout << "Number of passengers: " << endl;
        cin >> inputInt;
        vehicles[index]->setNumberOfPassengers(inputInt);
    }

    vehicles[index]->setValue(price);      

    cout << "Brand: " << endl;
    cin >> inputString;
    vehicles[index]->setBrand(inputString);

    cout << "Model: " << endl;
    cin >> inputString;
    vehicles[index]->setModel(inputString);

    cout << "Color: " << endl;
    cin >> inputString;
    vehicles[index]->setColor(inputString);

    cout << "Consumption: " << endl;
    cin >> inputdouble;
    vehicles[index]->setConsumption(inputdouble);

    cout << "Boot capacity: " << endl;
    cin >> inputInt;
    vehicles[index]->setBootCapacity(inputInt);

    cout << "Engine power: " << endl;
    cin >> inputInt;
    vehicles[index]->setEnginePower(inputInt);

    cout << "Engine capacity: " << endl;
    cin >> inputInt;
    vehicles[index]->setEngineCapacity(inputInt);

    cout << "Mass: " << endl;
    cin >> inputInt;
    vehicles[index]->setMass(inputInt);

    cout << "Manual: (1)Yes (2)No" << endl;
    cin >> boolCar;

    while (boolCar != 1 && boolCar != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        boolCar = inputInt;
    }

    bool manual, boolAir = true;

    if(boolCar == 1){
        manual = true;
    }
    else if(boolCar == 2){
        manual = false;
    }
    vehicles[index]->setManual(manual);

    if(choice == 1){
        inputdouble = 0;
        inputInt = 2021;
        vehicles[index]->setCounter(inputdouble);
        vehicles[index]->setYearOfProduction(inputInt);
        vehicles[index]->setAirConditioning(boolAir);
        vehicles[index]->setAccidentFree(boolAir);            
    }
    else if(choice == 2){           
        cout << "Counter: " << endl;
        cin >> inputdouble;
        vehicles[index]->setCounter(inputdouble);

        cout << "Year of production: " << endl;
        cin >> inputInt;
        vehicles[index]->setYearOfProduction(inputInt);

        cout << "Air Conditioning: (1)Yes (2)No" << endl;
        cin >> boolCar;            
        while (boolCar != 1 && boolCar != 2){
            cout << "Wrong number. Enter 1 or 2." << endl;
            boolCar = inputInt;
        }
        if(boolCar == 1){
            vehicles[index]->setAirConditioning(true);
        }
        else if(boolCar == 2){
            vehicles[index]->setAirConditioning(false);
        }

        cout << "Accident free: (1)Yes (2)No" << endl;
        cin >> boolCar;   
        while (boolCar != 1 && boolCar != 2){
            cout << "Wrong number. Enter 1 or 2." << endl;
            cin >> boolCar;
        }
        if(boolCar == 1){
            vehicles[index]->setAccidentFree(true);
        }
        else if(boolCar == 2){
            vehicles[index]->setAccidentFree(false);
        }
    }

    vehicles[index]->showVehicleSpecificInformation();
}

void Fleet::rentAVehicle(Date date) { 
    int choice, choicePeriod, choiceRepair, choiceInsurance, choiceNegotiation, choiceType;
    cout << "Would Tou like to rent a car(1) or a bus(2)?" << endl;
    cin >> choiceType;

    while (choiceType != 1 && choiceType != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choiceType;
    }

    int counter = 0, test = 1;

    if(choiceType == 1){
        for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
            if(vehicles[i]->getDamaged() == false && vehicles[i]->getAvailable() == true && dynamic_cast<Car*>(vehicles[i])){                
                counter++;
            }
        }
        if(counter == 0){
            cout << "We are sorry. There are no cars available. " << endl;
            return;
        }
        cout << "Which car would You like to rent?" << endl;
        this->showAvailableCars();
        cin >> choice;
        
        while(test != 0){
            test = 0;
            if(choice < 0 || choice > this->numberOfCars + this->numberOfBuses)
                test++;                
            else if(vehicles[choice]->getAvailable() == false)
                test++;
            else if(!(dynamic_cast<Car*>(vehicles[choice])))
                test++;

            if(test != 0){
                cout << "Wrong number." << endl;
                cin >> choice;
            }                
        }
    }

    else if (choiceType == 2){
        for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
            if(vehicles[i]->getDamaged() == false && vehicles[i]->getAvailable() == true && dynamic_cast<Bus*>(vehicles[i])){                
                counter++;
            }
        }
        if(counter == 0){
            cout << "We are sorry. There are no buses available. " << endl;
            return;
        }
        cout << "Which bus would You like to rent?" << endl;
        this->showAvailableBuses();
        cin >> choice;

        while(test != 0){
            test = 0;
            if(choice < 0 || choice > this->numberOfCars + this->numberOfBuses)
                test++;                
            else if(vehicles[choice]->getAvailable() == false)
                test++;
            else if(!(dynamic_cast<Bus*>(vehicles[choice])))
                test++;

            if(test != 0){
                cout << "Wrong number." << endl;
                cin >> choice;
            }                
        }

    }

    cout << "For how long would You like to rent this vehicle?" << endl;
    cout << "1. For one day. " << endl;
    cout << "2. For a week. " << endl;
    cout << "3. For a month. " << endl;
    cin >> choicePeriod;

    while (!(choicePeriod == 1 || choicePeriod == 2 || choicePeriod == 3)){
        cout << "Wrong number." << endl;
        cin >> choicePeriod;
    }

    if (choicePeriod == 1){
        price = vehicles[choice]->calculateDailyPrice();
        cout << "Daily price of " <<  vehicles[choice]->getBrand() << " " <<  vehicles[choice]->getModel() << " is " <<  price << endl;            
    }
    else if(choicePeriod == 2){            
        price = vehicles[choice]->calculateWeeklyPrice();
        cout << "Weekly price of " <<  vehicles[choice]->getBrand() << " " <<  vehicles[choice]->getModel() << " is " <<  price << endl; 
    }
    else if(choicePeriod == 3){            
        price = vehicles[choice]->calculateMonthlyPrice();
        cout << "Monthly price of " <<  vehicles[choice]->getBrand() << " " <<  vehicles[choice]->getModel() << " is " <<  price << endl; 
    }            


    cout << "Would you like to have an addictional insurance?" << endl;
    cout << "1. Yes \n2. No" << endl;
    cin >> choiceInsurance;

    while (choiceInsurance != 1 && choiceInsurance != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choiceInsurance;
    }
    if(choiceInsurance == 1){
        price += vehicles[choice]->calculateAdditionalInsurance() * pow(choicePeriod, 3);
    }

    cout << "The total price is " <<  price << ". Are you satisfied with the cost of renting?" << endl;
    cout << "1. Yes \n2. No" << endl;
    cin >> choiceNegotiation;

    while ( choiceNegotiation != 1 &&  choiceNegotiation != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choiceNegotiation;
    }

    if( choiceNegotiation == 2){
        cout << "What would You like to do then?" << endl;
        cout << "1. Negotiate the price. " << endl;
        cout << "2. Resign" << endl;
        cin >> choiceNegotiation;

        while ( choiceNegotiation != 1 && choiceNegotiation != 2){
            cout << "Wrong number. Enter 1 or 2." << endl;
            cin >> choiceNegotiation;
        }

        double amount;
        if(choiceNegotiation == 1){
            cout << "What price do You suggest?" << endl;
            cin >> amount;
            price = vehicles[choice]->negotiate(amount, price);

            if(price == 0){
                return;
            }

        }
        else if(choiceNegotiation == 2){
            cout << "We are sorry that we did not meet the requirements" << endl;
            return;
        }
    }

    int tmpNumber = vehicles[choice]->getNumberOfRentals() + 1;
    vehicles[choice]->setNumberOfRentals(tmpNumber);
    vehicles[choice]->setAvailable(false);

    this->budget.impact(price, todaysDate);

    cout << "Today is: " << todaysDate.convertToString() << endl;

    Date rentDate;
    rentDate.setDate(todaysDate);

    if (choicePeriod == 1){
        kilometers = rand() % 500;
        rentDate.addDaysToDate(1);
        cout << "The vehicle will be taken until: " << rentDate.convertToString() << endl;
    }
    else if(choicePeriod == 2){   
        kilometers = (rand() % 300) * 7;      
        rentDate.addDaysToDate(7);
        cout << "The vehicle will be taken until: " << rentDate.convertToString() << endl;
    }
    else if(choicePeriod == 3){
        kilometers = (rand() % 200) * 30;      
        rentDate.addDaysToDate(30);
        cout << "The vehicle will be taken until: " << rentDate.convertToString() << endl;
    }

    if (choiceType == 1)
        vehicles[choice]->updateCounter(kilometers);

    vehicles[choice]->setTakenTo(rentDate);
}

Date Fleet::changeDate(string dateFromInputString) { 
    Date dateFromInput;

    try {            
        dateFromInput = Date(dateFromInputString);
    } catch (int e) {
        cout << "Invalid format" << endl;
        return todaysDate;
    }

    if (todaysDate.checkIfAfter(dateFromInput) == 0){
        cout << "Wrong date. " << endl;
        return todaysDate;
    }

    this->setTodaysDate(dateFromInput);
    this->budget.checkMonth(todaysDate);

    int difference;

    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        if(vehicles[i]->getAvailable() == false && vehicles[i]->getTakenTo().checkIfAfter(todaysDate)){ 
            vehicles[i]->setAvailable(true);
        }

        difference = (vehicles[i]->getLastService()).getMonthsBetween(todaysDate);

        if(difference > 12){       
            cout << "Out of date vehicle inspection: " << vehicles[i]->getBrand() << " " << vehicles[i]->getModel() 
                    <<  ". A fine of 500 was imposed." << endl;
            this->expenditure(500);
        }
    }

    return this->todaysDate;
}

void Fleet::showAvailableCars(){
    cout << "Available" << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        if(vehicles[i]->getDamaged() == false && vehicles[i]->getAvailable() == true && dynamic_cast<Car*>(vehicles[i])){                
            vehicles[i]->showVehicleInfo(i);
        }
    }
}

void Fleet::showAvailableBuses(){
    cout << "Available" << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        if(vehicles[i]->getDamaged() == false && vehicles[i]->getAvailable() == true && dynamic_cast<Bus*>(vehicles[i])){                
            vehicles[i]->showVehicleInfo(i);
        }
    }
}

void Fleet::showAvailableVehicles(){
    cout << "Available" << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        if(vehicles[i]->getDamaged() == false && vehicles[i]->getAvailable() == true){                
            vehicles[i]->showVehicleInfo(i);
        }
    }
}

void Fleet::showAllCars(){
    cout << "Available" << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        if (dynamic_cast<Car*>(vehicles[i])){
            vehicles[i]->showVehicleInfo(i);
        }
    }
}

void Fleet::showAllBuses(){
    cout << "Available" << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        if (dynamic_cast<Bus*>(vehicles[i])){
            vehicles[i]->showVehicleInfo(i);
        }
    }
}

void Fleet::showAllVehicles(){
    cout << "Available" << setw(16) << "Brand" << setw(15) << "Model" << setw(15) << "Color" << setw(15) << "Year" << setw(20) << "Consumption" << setw(20) << "Boot Capacity" << endl;
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        vehicles[i]->showVehicleInfo(i);
    }
}

void Fleet::showSpecificInformation() { 
    int choice;
    cout << "About which vehicle would You like to see specific information?" << endl;
    this->showAllVehicles();
    cin >> choice;

    while (choice < 0 || choice >= this->numberOfCars + this->numberOfBuses){
        cout << "Wrong number." << endl;
        cin >> choice;
    }

    vehicles[choice]->showVehicleSpecificInformation();
}

void Fleet::reportAccident(Date date) { 
    int choice, choiceRepair;
    cout << "Which vehicle would You like to report as a damaged?" << endl;
    this->showAllVehicles();
    cin >> choice;

    while (choice < 0 || choice >= this->numberOfCars + this->numberOfBuses || vehicles[choice]->getDamaged()){
        cout << "Wrong number." << endl;
        if(vehicles[choice]->getDamaged())
            cout << "This car is already damaged. " << endl;
            cin >> choice;
    }

    vehicles[choice]->setDamaged(true);
    vehicles[choice]->setAccidentFree(false);
    vehicles[choice]->setAvailable(false);
    vehicles[choice]->addAnAccident(date);

    cout << "Would You like to have the car repaired now?" << endl;
    cout << "(1) Yes (2) No" << endl;

    cin >> choiceRepair;

    while ( choiceRepair != 1 &&  choiceRepair != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choiceRepair;
    }

    if(choiceRepair == 1){
        // cout << "naprawiamy " << endl;
        this->repairAVehicle(vehicles[choice]);
    }
}

void Fleet::sellAVehicle() { 
    int choice;
    cout << "Which vehicle would You like to sell?" << endl;
    this->showAvailableVehicles();
    cin >> choice;

    while (choice < 0 || choice >= this->numberOfCars + this->numberOfBuses){
        cout << "Wrong number." << endl;
        cin >> choice;
    }

    if(vehicles[choice]->getDamaged() == true)
        price = vehicles[choice]->getValue() * (double)0.5;
    else
        price = vehicles[choice]->getValue();

    this->budget.impact(price, todaysDate);

    vector<Vehicle*>::iterator position = find(vehicles.begin(), vehicles.end(), vehicles[choice]);
    if (position != vehicles.end())
        vehicles.erase(position);

    if(choice < this->numberOfCars)
        this->numberOfCars--;
    else
        this->numberOfBuses--;
}

void Fleet::repairAVehicle() { 
    int choice, choiceRepair;
    int counter = 0;

    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++)
        if(vehicles[i]->getDamaged() == true) 
            counter++;             

    if(counter == 0){
        cout << "There is no vehicle to repair" << endl;
    }
    else{
        cout << "Which car would You like to repair?" << endl;
        for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
            if(vehicles[i]->getDamaged() == true){   
                counter++;             
                vehicles[i]->showVehicleInfo(i);
            }
        }
        cin >> choice;

        while (choice < 0 || choice >= this->numberOfCars + this->numberOfBuses || !vehicles[choice]->getDamaged()){
            cout << "Wrong number." << endl;
            cin >> choice;
        }

        double carRepair = (rand() % 100) * vehicles[choice]->getValue() / 1000;

        cout << "The repair of " << vehicles[choice]->getModel() << " will cost " << carRepair << ". Would You like to repair the car(1) or scrap it(2)?" << endl;
        cin >> choiceRepair;

        while (choiceRepair != 1 && choiceRepair != 2){
            cout << "Wrong number. Enter 1 or 2." << endl;
            cin >> choiceRepair;
        }

        if (choiceRepair == 1){
            this->expenditure(carRepair);

            double newValue = vehicles[choice]->getValue() * (double)0.9;
            vehicles[choice]->setValue(newValue);
            vehicles[choice]->setDamaged(false);
            vehicles[choice]->setAvailable(true);                
        }
        else if(choiceRepair == 2){
            this->scrapACar(choice);
        }
    }
}

double Fleet::forecastExpenses() { 
    int difference = 0, expenses = 0;

    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++){
        difference = (vehicles[i]->getLastService()).getMonthsBetween(todaysDate);

        if(difference > 10 && dynamic_cast<Car*>(vehicles[i]))
            expenses += 100;
        else if(difference > 10 && dynamic_cast<Bus*>(vehicles[i]))
            expenses += 200;
    }

    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++)
        if(vehicles[i]->getDamaged() == true)
            expenses += vehicles[i]->getValue();
        
    cout << "Expenses: " << expenses << endl;

    return expenses;
}

double Fleet::calculatePossession() { 
    double sum = 0;
    for(int i = 0; i < this->numberOfCars + this->numberOfBuses; i++)
        if(vehicles[i]->getDamaged() == false && vehicles[i]->getAvailable() == true)          
            sum += vehicles[i]->getValue();
        
    return sum;
}

void Fleet::calculateFuel() { 
    int choice;
    cout << "Which vehicle would You like to calculate the fuel consumption for?" << endl;
    this->showAllVehicles();
    cin >> choice;

    while (choice < 0 || choice >= this->numberOfCars + this->numberOfBuses){
        cout << "Wrong number." << endl;
        cin >> choice;
    }

    cout << "How far will the journey be?" << endl;
    cin >> kilometers;

    while (kilometers < 0){
        cout << "The number of kilometers cannot be negative. " << endl;
        cin >> kilometers;
    }

    if(vehicles[choice]->getConsumption() == 0){
        cout << "The vehicle You have chosen is electric. It doesn't need fuel. " << endl;
        return;
    }

    cout << "The car will consume " << vehicles[choice]->calculateFuelConsumption(kilometers) << " liters of fuel. " << endl;

    cout << "The fuel cost will be around " << vehicles[choice]->calculateFuelConsumption(kilometers) * 4.7 << endl;    
}

Date Fleet::getTodaysDate() { 
    return this->todaysDate;
}

void Fleet::setTodaysDate(Date todaysDate) { 
    this->todaysDate = todaysDate;
}

void Fleet::sortCars() { 
    cout << "1. Sort by year" << endl;
    cout << "2. Sort by consumption" << endl;
    cout << "3. Sort by boot capacity" << endl;
    cout << "4. Sort by value" << endl;
    int sortChoice;
    cin >> sortChoice;

    switch (sortChoice) {
        case 1:
            this->sortByYear();                            
            break;

        case 2:
            this->sortByConsumption();
            break;

        case 3:
            this->sortByBootCapacity();
            break;

        case 4:
            this->sortByValue();
            break;

        default:
            cout << "Unknown operation" << endl;
            break;
    }

    this->showAllCars();
}

void Fleet::sortByYear() { 
    sort(vehicles.begin(), vehicles.begin() + this->numberOfCars, [](Vehicle* &l, Vehicle* &r) { return l->getYearOfProduction() > r->getYearOfProduction(); });
}

void Fleet::sortByConsumption() { 
    sort(vehicles.begin(), vehicles.begin() + this->numberOfCars, [](Vehicle* &l, Vehicle* &r) { return l->getConsumption() < r->getConsumption(); });
}

void Fleet::sortByBootCapacity() { 
    sort(vehicles.begin(), vehicles.begin() + this->numberOfCars, [](Vehicle* &l, Vehicle* &r) { return l->getBootCapacity() > r->getBootCapacity(); });
}

void Fleet::sortByValue() { 
    sort(vehicles.begin(), vehicles.begin() + this->numberOfCars, [](Vehicle* &l, Vehicle* &r) { return l->getValue() > r->getValue(); });
}

void Fleet::scrapACar(Vehicle* car) { 
    double scrapValue = car->getMass() * (double)0.4;
    this->budget.impact(scrapValue, todaysDate);
    cout << "You earned " << scrapValue << " on scrapping a " << car->getModel() << endl;

    vector<Vehicle*>::iterator position = find(vehicles.begin(), vehicles.end(), car);
    if (position != vehicles.end())
        vehicles.erase(position);

    if(index < this->numberOfCars)
        this->numberOfCars--;
    else
        this->numberOfBuses--;
}

void Fleet::scrapACar(int index) { 
    double scrapValue = vehicles[index]->getMass() * (double)0.4;
    this->budget.impact(scrapValue, todaysDate);
    cout << "You earned " << scrapValue << " on scrapping a " << vehicles[index]->getModel() << endl;
    
    vector<Vehicle*>::iterator position = find(vehicles.begin(), vehicles.end(), vehicles[index]);
    if (position != vehicles.end())
        vehicles.erase(position);

    if(index < this->numberOfCars)
        this->numberOfCars--;
    else
        this->numberOfBuses--;
}

void Fleet::sellAVehicle(Vehicle* car) { 
    cout << "The vehicle " << car->getBrand() << " " << car->getModel() << " will be sold" << endl;

    if(car->getDamaged() == true)
        price = car->getValue() * (double)0.5;
    else
        price = car->getValue();
        
    this->budget.impact(price, todaysDate);

    vector<Vehicle*>::iterator position = find(vehicles.begin(), vehicles.end(), car);
    if (position != vehicles.end())
        vehicles.erase(position);

    if(index < this->numberOfCars)
        this->numberOfCars--;
    else
        this->numberOfBuses--;

}

void Fleet::repairAVehicle(Vehicle* car) { 
    int choiceRepair;
    double carRepair = (rand() % 100) * (car->getValue()) / 100;

    cout << "The car repair will cost " << carRepair << ". Would You like to repair the car(1) or scrap it(2)?" << endl;
    cin >> choiceRepair;

    while (choiceRepair != 1 && choiceRepair != 2){
        cout << "Wrong number. Enter 1 or 2." << endl;
        cin >> choiceRepair;
    }

    if (choiceRepair == 1){
        this->expenditure(carRepair);
        
        double newValue = car->getValue() * (double)0.9;
        car->setValue(newValue);
        car->setDamaged(false);
        car->setAvailable(true);

        cout << "Vehicle successfully repaired" << endl;
    }
    else if(choiceRepair == 2){
        this->scrapACar(car);
    }
}


