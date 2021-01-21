package projekt;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;
import static java.util.Calendar.*;

public class Fleet{
    private ArrayList<Vehicle> vehicles = new ArrayList<Vehicle>();
    Management budget = new Budget(1000000);
    private int numberOfCars = 0, numberOfBuses = 0, decision;
    Scanner input = new Scanner(System.in);
    private int choice, choicePeriod, choiceRepair, choiceInsurance, choiceNegotiation, choiceType, index;
    private float price, kilometers, expenses, possession;
    Random generator = new Random();
    private SimpleDateFormat sdformat = new SimpleDateFormat("dd-MM-yyyy");
    Date todaysDate = new Date();

    public Fleet() throws ParseException{
        this.vehicles.add(new Car("Volkswagen", "Passat", "Black", (float)6.5, 170000, 80000, 2017, 26, 600, 190, 2000, 1735, false, true, true));
        this.numberOfCars++;
        this.vehicles.add( new Car("Volkswagen", "Tiguan", "White", (float)8.5, 30000, 135000, 2018, 15, 470, 150, 2000, 1681, false, true, true));
        this.numberOfCars++;
        this.vehicles.add(new Car("Toyota", "Yaris", "Red", (float)4.5, 95000, 20000, 2007, 40, 200, 90, 1300, 1000, true, false, false));
        this.vehicles.get(numberOfCars).addAnAccident("10-02-2010", "Read-End Accident");
        this.vehicles.get(numberOfCars).addAnAccident("15-12-2015", "Small collision");
        this.numberOfCars++;
        this.vehicles.add(new Car("Mercedes-Benz", "E-class", "White", (float)12.5, 50000, 330000, 2018, 6, 640, 435, 3000, 1970, false, true, true));
        this.numberOfCars++;
        this.vehicles.add(new Car("Mercedes-Benz", "ML", "Black", (float)10.5, 220000, 54000, 2009, 27, 540, 190, 3000, 2300, false, true, false));
        this.vehicles.get(numberOfCars).addAnAccident("15-05-2012", "Side Impact");
        this.numberOfCars++;
        this.vehicles.add(new Car("Volvo", "S60", "Black", 8, 5000, 165000, 2020, 1, 600, 190, 2000, 1700, false, true, true));
        this.numberOfCars++;
        this.vehicles.add(new Car("Audi", "RS5", "Grey", 11, 30000, 150000, 2010, 5, 350, 450, 3000, 2000, false, true, true));
        this.numberOfCars++;
        this.vehicles.add(new Car("Opel", "Astra", "Black", 5, 80000, 36000, 2017, 9, 300, 110, 1600, 1400, true, true, true));
        this.numberOfCars++;
        this.vehicles.add(new Car("Ford", "Fiesta", "Silver", (float)4.5, 140000, 10000, 2007, 30, 300, 75, 1200, 1600, true, false, false));
        this.vehicles.get(numberOfCars).addAnAccident("20-01-2009", "Runoff");
        this.vehicles.get(numberOfCars).addAnAccident("10-07-2017", "Rear-End Collision");
        this.numberOfCars++;
        this.vehicles.add(new Car("Fiat", "500", "Black", 0, 45000,65000, 2016, 10, 250, 120, 0, 900, false, true, true));
        this.numberOfCars++;

        this.vehicles.add(new Bus("Iveco", "Rosero", "Grey", 18, 1000, 500_000, 2020, 0, 2000, 200, 3000, 5000, true, true, true, 31));
        this.numberOfBuses++;
        this.vehicles.add(new Bus("Scania", "Touring", "White", 27, 150_000, 450_000, 2018, 11, 12_000, 411, 13_000, 8000, true, true, false, 51));
        this.vehicles.get(numberOfBuses).addAnAccident("30-07-2019", "Little collision in Germany");
        this.numberOfBuses++;
    }

    public void makeAService(Date date){
        System.out.println("Which vehicle would You like to make a full service?");
        this.showAllVehicles();
        System.out.println(this.numberOfBuses + this.numberOfCars + ". All vehicles");
        choice = input.nextInt();

        while (choice < 0 || choice > this.numberOfCars + this.numberOfBuses){
            System.out.println("Wrong number.");
            choice = input.nextInt();
        }

        while(choice > 0 && choice < this.numberOfCars + this.numberOfBuses && this.vehicles.get(choice).getDamaged()){
            System.out.println("Wrong number.");
            System.out.println("This car is damaged. You have to repair it first.");
            choice = input.nextInt();
        }
        
        if (choice == this.numberOfBuses + this.numberOfCars){
            for(int i = 0; i < this.numberOfBuses + this.numberOfCars; i++){                
                if (this.vehicles.get(i) instanceof Car)
                    this.expenditure(100);
                
                else if(this.vehicles.get(i) instanceof Bus)
                    this.expenditure(200);
                
                    this.vehicles.get(i).makeFullService(date);
            }
            return;
        }

        if (this.vehicles.get(choice) instanceof Car)
            this.expenditure(100);
        
        else if(this.vehicles.get(choice) instanceof Bus)
            this.expenditure(200);
        
            this.vehicles.get(choice).makeFullService(date);
    }

    public void expenditure(float amount){
        choice = this.budget.expenditure(amount, todaysDate);
        if(choice == 2){
            this.sellAVehicle();
            this.expenditure(amount);
        }
        else if(choice == 3){
            expenses = this.forecastExpenses();
            possession = this.calculatePossession();
            decision = this.budget.applyForALoan(amount, todaysDate, expenses, possession);
            if (decision == 1)
                this.expenditure(amount);
            else if(decision == 0){
                System.out.println("\nWe are sorry that Your company did not receive the loan. ");
                System.out.println("Unfortunately, it turns out that Your company do not have the money for this expense. ");
                System.out.println("The only option to stay in the bussiness is to sell a vehicle, to earn some money.");
                System.out.println("Do You agree to this option? ");
                System.out.println("(1) Yes  (2) No");
                decision = input.nextInt();

                while (decision != 1 && decision != 2){
                    System.out.println("Wrong number.");
                    decision = input.nextInt();
                }

                if(decision == 1){
                    this.sellAVehicle();
                    this.expenditure(amount);
                }
                else{
                    System.out.println("You are out of the business.");
                    System.exit(0);
                }
            }
        }
    }

    public void buyAVehicle(){
        System.out.println("Car(1) or bus(2)?");
        choiceType = input.nextInt();

        while (choiceType != 1 && choiceType != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choiceType = input.nextInt();
        }

        System.out.println("New(1) or used(2)?");
        choice = input.nextInt();

        while (choice != 1 && choice != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choice = input.nextInt();
        }

        System.out.println("Value: ");
        price = input.nextFloat();
        this.expenditure(price);

        index = this.numberOfCars + this.numberOfBuses;

        if (choiceType == 1){
            this.vehicles.add(new Car());
            this.numberOfCars++;
        }
        else if(choiceType == 2){
            this.vehicles.add(new Bus());
            this.numberOfBuses++;

            System.out.println("Number of passengers: ");
            this.vehicles.get(index).setNumberOfPassengers(input.nextInt());
        }

        this.vehicles.get(index).setValue(price);      

        System.out.println("Brand: ");
        this.vehicles.get(index).setBrand(input.next());

        System.out.println("Model: ");
        this.vehicles.get(index).setModel(input.next());

        System.out.println("Color: ");
        this.vehicles.get(index).setColor(input.next());

        System.out.println("Consumption: ");
        this.vehicles.get(index).setConsumption(input.nextFloat());

        System.out.println("Boot capacity: ");
        this.vehicles.get(index).setBootCapacity(input.nextInt());

        System.out.println("Engine power: ");
        this.vehicles.get(index).setEnginePower(input.nextInt());

        System.out.println("Engine capacity: ");
        this.vehicles.get(index).setEngineCapacity(input.nextInt());

        System.out.println("Mass: ");
        this.vehicles.get(index).setMass(input.nextInt());

        System.out.println("Manual: (1)Yes (2)No");
        int boolCar = input.nextInt();            
        while (boolCar != 1 && boolCar != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            boolCar = input.nextInt();
        }
        if(boolCar == 1){
            this.vehicles.get(index).setManual(true);
        }
        else if(boolCar == 2){
            this.vehicles.get(index).setManual(false);
        }

        if(choice == 1){
            this.vehicles.get(index).setCounter(0);
            this.vehicles.get(index).setYearOfProduction(2020);
            this.vehicles.get(index).setAirConditioning(true);
            this.vehicles.get(index).setAccidentFree(true);            
        }
        else if(choice == 2){                
            System.out.println("Counter: ");
            this.vehicles.get(index).setCounter(input.nextFloat());

            System.out.println("Year of production: ");
            this.vehicles.get(index).setYearOfProduction(input.nextInt());

            System.out.println("Air Conditioning: (1)Yes (2)No");
            boolCar = input.nextInt();            
            while (boolCar != 1 && boolCar != 2){
                System.out.println("Wrong number. Enter 1 or 2.");
                boolCar = input.nextInt();
            }
            if(boolCar == 1){
                this.vehicles.get(index).setAirConditioning(true);
            }
            else if(boolCar == 2){
                this.vehicles.get(index).setAirConditioning(false);
            }

            System.out.println("Accident free: (1)Yes (2)No");
            boolCar = input.nextInt();            
            while (boolCar != 1 && boolCar != 2){
                System.out.println("Wrong number. Enter 1 or 2.");
                boolCar = input.nextInt();
            }
            if(boolCar == 1){
                this.vehicles.get(index).setAccidentFree(true);
            }
            else if(boolCar == 2){
                this.vehicles.get(index).setAccidentFree(false);
            }
        }
        
        this.vehicles.get(index).showVehicleSpecificInformation();
    }

    public void rentAVehicle(Date date){
        System.out.println("Would Tou like to rent a car(1) or a bus(2)?");
        choiceType = input.nextInt();

        while (choiceType != 1 && choiceType != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choiceType = input.nextInt();
        }

        int counter = 0, test = 1;

        if(choiceType == 1){
            for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
                if(this.vehicles.get(i).isDamaged() == false && this.vehicles.get(i).isAvailable() == true && this.vehicles.get(i) instanceof Car){                
                    counter++;
                }
            }
            if(counter == 0){
                System.out.println("We are sorry. There are no cars available. ");
                return;
            }
            System.out.println("Which car would You like to rent?");
            this.showAvailableCars();
            choice = input.nextInt();
            
            while(test != 0){
                test = 0;
                if(choice < 0 || choice > this.numberOfCars + this.numberOfBuses)
                    test++;                
                else if(this.vehicles.get(choice).getAvailable() == false)
                    test++;
                else if(!(this.vehicles.get(choice) instanceof Car))
                    test++;

                if(test != 0){
                    System.out.println("Wrong number.");
                    choice = input.nextInt();
                }                
            }
        }

        else if (choiceType == 2){
            for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
                if(this.vehicles.get(i).isDamaged() == false && this.vehicles.get(i).isAvailable() == true && this.vehicles.get(i) instanceof Bus){                
                    counter++;
                }
            }
            if(counter == 0){
                System.out.println("We are sorry. There are no buses available. ");
                return;
            }
            System.out.println("Which bus would You like to rent?");
            this.showAvailableBuses();
            choice = input.nextInt();

            while(test != 0){
                test = 0;
                if(choice < 0 || choice > this.numberOfCars + this.numberOfBuses)
                    test++;                
                else if(this.vehicles.get(choice).getAvailable() == false)
                    test++;
                else if(!(this.vehicles.get(choice) instanceof Bus))
                    test++;

                if(test != 0){
                    System.out.println("Wrong number.");
                    choice = input.nextInt();
                }                
            }

        }

        System.out.println("For how long would You like to rent this vehicle?");
        System.out.println("1. For one day. ");
        System.out.println("2. For a week. ");
        System.out.println("3. For a month. ");
        choicePeriod = input.nextInt();

        while (!(choicePeriod == 1 || choicePeriod == 2 || choicePeriod == 3)){
            System.out.println("Wrong number.");
            choicePeriod = input.nextInt();
        }

        if (choicePeriod == 1){
            price = this.vehicles.get(choice).calculateDailyPrice();
            System.out.println("Daily price of " + this.vehicles.get(choice).getBrand() + " " + this.vehicles.get(choice).getModel() + " is " + price);            
        }
        else if(choicePeriod == 2){            
            price = this.vehicles.get(choice).calculateWeeklyPrice();
            System.out.println("Weekly price of " + this.vehicles.get(choice).getBrand() + " " + this.vehicles.get(choice).getModel() + " is " + price);
        }
        else if(choicePeriod == 3){            
            price = this.vehicles.get(choice).calculateMonthlyPrice();
            System.out.println("Monthly price of " + this.vehicles.get(choice).getBrand() + " " + this.vehicles.get(choice).getModel() + " is " + price);
        }            


        System.out.println("Would you like to have an addictional insurance?");
        System.out.println("1. Yes \n2. No");
        choiceInsurance = input.nextInt();

        while (choiceInsurance != 1 && choiceInsurance != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choiceInsurance = input.nextInt();
        }
        if(choiceInsurance == 1){
            price += this.vehicles.get(choice).calculateAdditionalInsurance() * Math.pow(choicePeriod, 3);
        }

        System.out.println("The total price is " + price + ". Are you satisfied with the cost of renting?");
        System.out.println("1. Yes \n2. No");
        choiceNegotiation = input.nextInt();

        while ( choiceNegotiation != 1 &&  choiceNegotiation != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choiceNegotiation = input.nextInt();
        }

        if( choiceNegotiation == 2){
            System.out.println("What would You like to do then?");
            System.out.println("1. Negotiate the price. ");
            System.out.println("2. Resign");
            choiceNegotiation = input.nextInt();
    
            while ( choiceNegotiation != 1 && choiceNegotiation != 2){
                System.out.println("Wrong number. Enter 1 or 2.");
                choiceNegotiation = input.nextInt();
            }

            if(choiceNegotiation == 1){
                System.out.println("What price do You suggest?");
                float amount = input.nextFloat();
                price = this.vehicles.get(choice).negotiate(amount, price);

                if(price == 0){
                    return;
                }

            }
            else if(choiceNegotiation == 2){
                System.out.println("We are sorry that we did not meet the requirements");
                return;
            }
        }

        int tmpNumber = this.vehicles.get(choice).getNumberOfRentals() + 1;
        this.vehicles.get(choice).setNumberOfRentals(tmpNumber);
        this.vehicles.get(choice).setAvailable(false);

        this.budget.impact(price, todaysDate);

        System.out.println("Today is: " + this.sdformat.format(date));

        Calendar c = Calendar.getInstance();
        c.setTime(date);

        if (choicePeriod == 1){
            kilometers = (float)generator.nextInt(500);
            c.add(Calendar.DATE, 1);
            date = c.getTime();
            System.out.println("The vehicle will be taken until: " + this.sdformat.format(date));
        }
        else if(choicePeriod == 2){   
            kilometers = (float)generator.nextInt(300) * 7;      
            c.add(Calendar.DATE, 7);
            date = c.getTime();
            System.out.println("The vehicle will be taken until: " + this.sdformat.format(date));
        }
        else if(choicePeriod == 3){
            kilometers = (float)generator.nextInt(200) * 30;      
            c.add(Calendar.MONTH, 1);
            date = c.getTime();
            System.out.println("The vehicle will be taken until: " + this.sdformat.format(date));
        }

        if (choiceType == 1)
            this.vehicles.get(choice).updateCounter(kilometers);
        
        this.vehicles.get(choice).setTakenTo(date);
    }

    public Date changeDate(String dateFromInputString) throws ParseException {
        Date dateFromInput;

        try {            
            dateFromInput = sdformat.parse(dateFromInputString);
        } catch (Exception e) {
            System.out.println("Invalid format");
            return todaysDate;
        }

        while (dateFromInput.compareTo(todaysDate) <= 0){
            System.out.println("Wrong date. ");
            dateFromInputString = input.nextLine();
            try {            
                dateFromInput = sdformat.parse(dateFromInputString);
            } catch (Exception e) {
                System.out.println("Invalid format");
                return todaysDate;
            }
         }

        this.setTodaysDate(dateFromInput);
        this.budget.checkMonth(todaysDate);
        
        Calendar c1 = Calendar.getInstance();
        c1.setTime(todaysDate); 
        Calendar c2 = Calendar.getInstance();
        int difference;

        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if(this.vehicles.get(i).getTakenTo() != null && this.vehicles.get(i).getTakenTo().compareTo(todaysDate) <= 0){ 
                this.vehicles.get(i).setAvailable(true);
                this.vehicles.get(i).setTakenTo(null);
            }

            c2.setTime(this.vehicles.get(i).getLastService());
            difference = c2.get(YEAR) - c1.get(YEAR);
            if (c1.get(MONTH) > c2.get(MONTH) || (c1.get(MONTH) == c2.get(MONTH) && c1.get(DATE) > c2.get(DATE)))
                difference--;

            if(difference < -1){        

                System.out.println("Out of date vehicle inspection: " + this.vehicles.get(i).getBrand() + " " + this.vehicles.get(i).getModel() 
                        +  ". A fine of 500 was imposed.");
                this.expenditure(500);
            }
        }

        return this.todaysDate;
    }

    public void sortCars(){
        System.out.println("1. Sort by year");
        System.out.println("2. Sort by consumption");
        System.out.println("3. Sort by boot capacity");
        System.out.println("4. Sort by value");
        int sortChoice = input.nextInt();
        switch (sortChoice) {
            case 1:
                this.sortByYear();                            
                break;

            case 2:
                this.sortByConsumption();
                break;

            case 3:
                this.sortByBootCapacity();
                break;

            case 4:
                this.sortByValue();
                break;
        
            default:
                System.out.println("Unknown operation");
                break;
        }

    }

    private void sortByYear(){
        Comparator.comparing(Vehicle::getYearOfProduction).thenComparing(Vehicle::getYearOfProduction);
        Collections.sort(vehicles, Comparator.comparing(Vehicle::getYearOfProduction));
        Collections.reverse(vehicles);
        this.showAvailableCars();
    }

    private void sortByConsumption(){
        Comparator.comparing(Vehicle::getConsumption).thenComparing(Vehicle::getConsumption);
        Collections.sort(vehicles, Comparator.comparing(Vehicle::getConsumption));
        this.showAvailableCars();
    }

    private void sortByBootCapacity(){
        Comparator.comparing(Vehicle::getBootCapacity).thenComparing(Vehicle::getBootCapacity);
        Collections.sort(vehicles, Comparator.comparing(Vehicle::getBootCapacity));
        Collections.reverse(vehicles);
        this.showAvailableCars();
    }

    private void sortByValue(){
        Comparator.comparing(Vehicle::getValue).thenComparing(Vehicle::getValue);
        Collections.sort(vehicles, Comparator.comparing(Vehicle::getValue));
        Collections.reverse(vehicles);
        this.showAvailableCars();
    }

    public void showAvailableCars(){
        System.out.format("%13s%15s%16s%12s%15s%15s \n", "Available", "Brand", "Model", "Year", "Consumption", "Boot Capacity");
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if(this.vehicles.get(i).isDamaged() == false && this.vehicles.get(i).isAvailable() == true && this.vehicles.get(i) instanceof Car){                
                this.vehicles.get(i).showVehicleInfo(i);
            }
        }
    }

    public void showAvailableBuses(){
        System.out.format("%13s%15s%16s%12s%15s%15s \n", "Available", "Brand", "Model", "Year", "Consumption", "Boot Capacity");
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if(this.vehicles.get(i).isDamaged() == false && this.vehicles.get(i).isAvailable() == true && this.vehicles.get(i) instanceof Bus){                
                this.vehicles.get(i).showVehicleInfo(i);
            }
        }
    }

    public void showAvailableVehicles(){
        System.out.format("%13s%15s%16s%12s%15s%15s \n", "Available", "Brand", "Model", "Year", "Consumption", "Boot Capacity");
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if(this.vehicles.get(i).isDamaged() == false && this.vehicles.get(i).isAvailable() == true){                
                this.vehicles.get(i).showVehicleInfo(i);
            }
        }
    }

    public void showAllCars(){
        System.out.format("%13s%15s%16s%12s%15s%15s \n", "Available", "Brand", "Model", "Year", "Consumption", "Boot Capacity");
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if ( this.vehicles.get(i) instanceof Car){
                this.vehicles.get(i).showVehicleInfo(i);
            }
        }
    }

    public void showAllBuses(){
        System.out.format("%13s%15s%16s%12s%15s%15s%25s \n", "Available", "Brand", "Model", "Year", "Consumption", "Boot Capacity", "Number of passengers");
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if ( this.vehicles.get(i) instanceof Bus){
                this.vehicles.get(i).showVehicleInfo(i);
            }
        }
    }

    public void showAllVehicles(){
        System.out.format("%10s%15s%16s%12s%15s%15s \n", "Available", "Brand", "Model", "Year", "Consumption", "Boot Capacity");
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            this.vehicles.get(i).showVehicleInfo(i);
        }
    }

    public void showSpecificInformation(){
        System.out.println("About which vehicle would You like to see specific information?");
        this.showAllVehicles();
        choice = input.nextInt();

        while (choice < 0 || choice >= this.numberOfCars + this.numberOfBuses){
            System.out.println("Wrong number.");
            choice = input.nextInt();
        }

        this.vehicles.get(choice).showVehicleSpecificInformation();
    }
    
    public void reportAccident(Date date){
        System.out.println("Which vehicle would You like to report as a damaged?");
        this.showAllVehicles();
        choice = input.nextInt();

        while (choice < 0 || choice >= this.numberOfCars + this.numberOfBuses || this.vehicles.get(choice).getDamaged()){
            System.out.println("Wrong number.");
            if(this.vehicles.get(choice).getDamaged())
                System.out.println("This car is already damaged. ");
            choice = input.nextInt();
        }

        this.vehicles.get(choice).setDamaged(true);
        this.vehicles.get(choice).setAccidentFree(false);
        this.vehicles.get(choice).setAvailable(false);
        this.vehicles.get(choice).addAnAccident(date);

        System.out.println("Would You like to have the car repaired now?");
        System.out.println("(1) Yes (2) No");

        choiceRepair = input.nextInt();

        while ( choiceRepair != 1 &&  choiceRepair != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choiceRepair = input.nextInt();
        }

        if(choiceRepair == 1){
            System.out.println("repair will be");
            this.repairAVehicle(this.vehicles.get(choice));
        }
    }

    public void sellAVehicle(){
        System.out.println("Which vehicle would You like to sell?");
        this.showAvailableVehicles();
        choice = input.nextInt();

        while (choice < 0 || choice >= this.numberOfCars + this.numberOfBuses){
            System.out.println("Wrong number.");
            choice = input.nextInt();
        }

        if(this.vehicles.get(choice).getDamaged() == true)
            price = this.vehicles.get(choice).getValue() * (float)0.5;
        else
            price = this.vehicles.get(choice).getValue();

        this.budget.impact(price, todaysDate);

        this.vehicles.remove(choice);
        if(index < this.numberOfCars)
            this.numberOfCars--;
        else
            this.numberOfBuses--;
    }

    private void sellAVehicle(Vehicle car){

        System.out.println("The vehicle " + car.getBrand() + " " + car.getModel() + " will be sold");

        if(car.getDamaged() == true)
            price = car.getValue() * (float)0.5;
        else
            price = car.getValue();

        this.budget.impact(price, todaysDate);

        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            if(this.vehicles.get(i) == car){                
                this.vehicles.remove(car);
                if(i < this.numberOfCars){
                    this.numberOfCars--;
                }
                else{
                    this.numberOfBuses--;
                }     
            }
        }         
    }

    private void repairAVehicle(Vehicle car){

        float carRepair = generator.nextFloat() * car.getValue() / 2;

        System.out.println("The car repair will cost " + carRepair + ". Would You like to repair the car(1) or scrap it(2)?");
        choiceRepair = input.nextInt();

        while (choiceRepair != 1 && choiceRepair != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choiceRepair = input.nextInt();
        }

        if (choiceRepair == 1){
            this.expenditure(carRepair);
            
            float newValue = car.getValue() * (float)0.9;
            car.setValue(newValue);
            car.setDamaged(false);
            car.setAvailable(true);

            System.out.println("Vehicle successfully repaired");
        }
        else if(choiceRepair == 2){
            this.scrapACar(car);
        }
        
    }

    public void repairAVehicle(){
        int counter = 0;

        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++)
            if(this.vehicles.get(i).getDamaged() == true) 
                counter++;             

        if(counter == 0){
            System.out.println("There is no vehicle to repair");
        }
        else{
            System.out.println("Which car would You like to repair?");
            for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
                if(this.vehicles.get(i).getDamaged() == true){   
                    counter++;             
                    this.vehicles.get(i).showVehicleInfo(i);
                }
            }
            choice = input.nextInt();

            while (choice < 0 || choice >= this.numberOfCars + this.numberOfBuses || !this.vehicles.get(choice).getDamaged()){
                System.out.println("Wrong number.");
                choice = input.nextInt();
            }

            float carRepair = generator.nextFloat() * this.vehicles.get(choice).getValue() / 2;

            System.out.println("The repair of " + this.vehicles.get(choice).getModel() + " will cost " + carRepair + ". Would You like to repair the car(1) or scrap it(2)?");
            choiceRepair = input.nextInt();

            while (choiceRepair != 1 && choiceRepair != 2){
                System.out.println("Wrong number. Enter 1 or 2.");
                choiceRepair = input.nextInt();
            }

            if (choiceRepair == 1){
                this.expenditure(carRepair);

                float newValue = this.vehicles.get(choice).getValue() * (float)0.9;
                this.vehicles.get(choice).setValue(newValue);
                this.vehicles.get(choice).setDamaged(false);
                this.vehicles.get(choice).setAvailable(true);                
            }
            else if(choiceRepair == 2){
                this.scrapACar(choice);
            }
        }
    }

    private void scrapACar(Vehicle car){      
        float scrapValue = car.getMass() * (float)0.4;
        this.budget.impact(scrapValue, todaysDate);
        System.out.println("You earned " + scrapValue + " on scrapping a " + car.getModel() );
        this.vehicles.remove(car);
        if(index < this.numberOfCars)
            this.numberOfCars--;
        else
            this.numberOfBuses--;
    }

    private void scrapACar(int index){      
        float scrapValue = this.vehicles.get(index).getMass() * (float)0.4;
        this.budget.impact(scrapValue, todaysDate);
        System.out.println("You earned " + scrapValue + " on scrapping a " + this.vehicles.get(index).getModel() );
        
        this.vehicles.remove(index);
        if(index < this.numberOfCars)
            this.numberOfCars--;
        else
            this.numberOfBuses--;
    }

    public float forecastExpenses(){
        Calendar c1 = Calendar.getInstance();
        c1.setTime(todaysDate); 
        Calendar c2 = Calendar.getInstance();
        int difference = 0, expenses = 0;

        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++){
            c2.setTime(this.vehicles.get(i).getLastService());
            difference = c2.get(MONTH) - c1.get(MONTH);
            if(difference < -10 && this.vehicles.get(i) instanceof Car)
                expenses += 100;
            else if(difference < -10 && this.vehicles.get(i) instanceof Bus)
                expenses += 200;

            // System.out.println("expenses: " + expenses + "autp: " + this.vehicles.get(i).getModel());
        }

        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++)
            if(this.vehicles.get(i).getDamaged() == true)
                expenses += this.vehicles.get(i).getValue();
            
        System.out.println("Expenses: " + expenses);

        return expenses;
    }

    public float calculatePossession(){
        float sum = 0;
        for(int i = 0; i < this.numberOfCars + this.numberOfBuses; i++)
            if(this.vehicles.get(i).isDamaged() == false && this.vehicles.get(i).isAvailable() == true)          
                sum += this.vehicles.get(i).getValue();
            
        return sum;
    }

    public void calculateFuel(){
        System.out.println("Which vehicle would You like to calculate the fuel consumption for?");
        this.showAllVehicles();
        choice = input.nextInt();

        while (choice < 0 || choice >= this.numberOfCars + this.numberOfBuses){
            System.out.println("Wrong number.");
            choice = input.nextInt();
        }

        System.out.println("How far will the journey be?");
        kilometers = input.nextFloat();

        while (kilometers < 0){
            System.out.println("The number of kilometers cannot be negative. ");
            kilometers = input.nextFloat();
        }

        if(this.vehicles.get(choice).getConsumption() == 0){
            System.out.println("The vehicle You have chosen is electric. It doesn't need fuel. ");
            return;
        }

        System.out.println("The car will consume " + this.vehicles.get(choice).calculateFuelConsumption(kilometers) 
            + " liters of fuel. ");

        System.out.println("The fuel cost will be around " + this.vehicles.get(choice).calculateFuelConsumption(kilometers) * 4.7);
    }
    
    public Date getTodaysDate() {
        return this.todaysDate;
    }

    public void setTodaysDate(Date todaysDate) {
        this.todaysDate = todaysDate;
    }
}
