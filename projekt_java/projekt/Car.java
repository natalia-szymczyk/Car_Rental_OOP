package projekt;

import java.text.*;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

public class Car implements Vehicle{
    private String brand, model, color;
    private float consumption, counter, value;
    private int yearOfProduction, bootCapacity, mass, enginePower, engineCapacity, numberOfRentals, numberOfPassengers;
    public boolean manual, airConditioning, damaged, accidentFree, available;
    private Date lastService, takenTo, todaysDate = new Date();
    private int choice;
    private String inputData;
    private SimpleDateFormat sdformat = new SimpleDateFormat("dd-MM-yyyy");
    public ArrayList<Accident> historyOfAccidents = new ArrayList<Accident>();
    Scanner input = new Scanner(System.in);


    public Car(String brand, String model, String color, float consumption, float counter, float value, int yearOfProduction,
    int numberOfRentals, int bootCapacity, int enginePower, int engineCapacity, int mass, boolean manual, boolean airConditioning, boolean accidentFree){
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
        setTakenTo(null);
        setLastService(todaysDate);
    }

    public Car(String brand, String model, int yearOfProduction, float counter){
        this(brand, model, "", 7, counter, 0, yearOfProduction, 0, 0, 0, 0, 0, true, true, true);
    }
    public Car(){
        this("", "", 0, 0);
    }
    
    @Override
    public void updateCounter(float kilometers){
        this.counter += kilometers;
    }

    @Override
    public float calculateFuelConsumption(float kilometers){
        return (kilometers*this.consumption)/100;
    }

    @Override
    public void showVehicleInfo(int i){
        String stringAvailable = "NO";
        if(this.getAvailable())
            stringAvailable = "YES";

        System.out.format("%2d %7s%18s%15s%12d%12.1f%14d \n", i, stringAvailable, this.brand, this.model, this.yearOfProduction, this.consumption, this.bootCapacity);
    }

    @Override
    public void showVehicleSpecificInformation(){
        String stringManual = "NO", stringAirConditioning = "NO";
        if(this.getManual())
            stringManual = "YES";

        if(this.getAirConditioning())
            stringAirConditioning = "YES";
        
        System.out.format("%15s%10s%10s%10s%15s%19s%19s%19s%10s%19s \n", "Brand", "Model", "Color", "Year", "Consumption", "Boot capacity", "Engine Power", "Engine capacity", "Manual", "Air Conditioning"); 
        System.out.format("%15s%10s%10s%10d%13.1f%17d%19d%17d%14s%14s \n", 
        this.brand, this.model, this.color, this.yearOfProduction, this.consumption, this.bootCapacity, this.enginePower, this.engineCapacity, stringManual, stringAirConditioning); 
    
        if(!this.getAccidentFree())
            this.readAccidents();
        
        if(!this.getAvailable())
            System.out.println("Taken to " + this.sdformat.format(this.getTakenTo()));
    }

    @Override
    public void makeFullService(Date date){
        this.setLastService(date);    
        System.out.println("Date of service of " + getBrand() + " " + getModel() + ": " + sdformat.format(this.getLastService()));
    }

    @Override
    public void makeFullService() throws ParseException{
        System.out.println("Would You like to make a full service today(1) or enter another date(2)?");
        this.choice = input.nextInt();
        
        while (choice != 1 && choice != 2){
            System.out.println("Wrong number. Enter 1 or 2.");
            choice = input.nextInt();
        }

        if (choice == 1)
            setLastService(todaysDate);
        else if(choice == 2){
            System.out.println("Enter the data in format dd-MM-yyyy: ");
            inputData = input.next();
            setLastService(sdformat.parse(inputData));
            while (lastService.compareTo(todaysDate) > 0){
                System.out.println("Wrong date.");
                inputData = input.next();
                setLastService(sdformat.parse(inputData));
            }
        }            
        System.out.println("Date of service of " + getBrand() + " " + getModel() + ": " + sdformat.format(getLastService()));
    }

    @Override
    public float calculateDailyPrice(){
        float basePrice = 20 + this.getValue() * (float)0.001;

        if(this.getAirConditioning() == true){
            basePrice += 20;
        }
        if(this.getAccidentFree() == true){
            basePrice *= 1.05;
        }
        if(this.getManual() == false){
            basePrice += 30;
        }

        return basePrice;
    }

    @Override
    public float calculateWeeklyPrice(){
        return this.calculateDailyPrice() * 7 * (float)0.8;
    }

    @Override
    public float calculateMonthlyPrice(){
        return this.calculateDailyPrice() * 30 * (float)0.65;
    }

    @Override
    public float calculateAdditionalInsurance(){
        return this.getValue() * (float)0.0001 + 30; 
    }

    @Override
    public float negotiate(float negotiate, float price){
        if(negotiate > price){
            System.out.println("No problem for us.");
            return negotiate;
        }

        if(negotiate < (price * (float)0.9)){
            System.out.println("Your suggested price is too low. ");
            System.out.println("We can offer You " + Math.max(price*(float)0.9, (negotiate + price)/2));
            System.out.println("Do You accept this offer?");
            System.out.println("1. Yes \n2. No");
            this.choice = input.nextInt();
        
            while (choice != 1 && choice != 2){
                System.out.println("Wrong number. Enter 1 or 2.");
                choice = input.nextInt();
            }

            if(choice == 1){
                System.out.println("Great.");
                return Math.max(price*(float)0.9, (negotiate + price)/2);
            }
            if(choice == 2){
                System.out.println("Would You like to resign (1) or try to negotiate again(2)? ");
                this.choice = input.nextInt();
        
                while (choice != 1 && choice != 2){
                    System.out.println("Wrong number. Enter 1 or 2.");
                    choice = input.nextInt();
                }
                
                if(choice == 1){
                    System.out.println("We are sorry that we did not meet the requirements");
                    return 0;
                }
                else if(choice == 2){
                    System.out.println("What price do You suggest?");
                    negotiate = input.nextFloat();

                    if(negotiate > price){
                        System.out.println("No problem for us.");
                        return negotiate;
                    }  

                    if(negotiate < (price * (float)0.83)){
                        System.out.println("Your suggested price is too low. ");
                        System.out.println("We can offer You " + Math.max(price*(float)0.83, (negotiate + price)/2));
                        System.out.println("Do You accept this offer?");
                        System.out.println("1. Yes \n2. No");
                        this.choice = input.nextInt();
                    
                        while (choice != 1 && choice != 2){
                            System.out.println("Wrong number. Enter 1 or 2.");
                            choice = input.nextInt();
                        }
            
                        if(choice == 1){
                            System.out.println("Great.");
                            return Math.max(price*(float)0.9, (negotiate + price)/2);
                        }
                        else if(choice == 2){
                            System.out.println("We are sorry that we did not meet the requirements");
                            return 0;
                        }
                    }
                }
            }
        }

        System.out.println("We can agree to this proposal. ");

        return negotiate;
    }

    @Override
    public void addAnAccident(Date date){
        System.out.println("Describe the accident: ");
        String description = input.nextLine();

        this.historyOfAccidents.add(new Accident(date, description));
    }

    @Override
    public void addAnAccident(String date) throws ParseException {
        System.out.println("Describe the accident: ");
        String description = input.nextLine();

        this.historyOfAccidents.add(new Accident(sdformat.parse(date), description));
    }

    @Override
    public void addAnAccident(String date, String description) throws ParseException {
        this.historyOfAccidents.add(new Accident(sdformat.parse(date), description));
    }

    @Override
    public void readAccidents(){
        if (this.getAccidentFree()){
            System.out.println("The car is accident free. ");
            return;
        }
        if (this.historyOfAccidents.size() == 0){
            System.out.println("The car accident history is empty");
            return;
        }
        System.out.println("Accidents: ");

        for (int i = 0; i < this.historyOfAccidents.size(); i++){
            System.out.format("%12s ", "");
            System.out.print(this.sdformat.format(this.historyOfAccidents.get(i).getDate()) + ": ");
            System.out.println(this.historyOfAccidents.get(i).getDescription());
        }
    }

    public Date getTakenTo() {
        return this.takenTo;
    }

    public void setTakenTo(Date takenTo) {
        this.takenTo = takenTo;
    }

    public String getBrand() {
        return this.brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getModel() {
        return this.model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getColor() {
        return this.color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public float getConsumption() {
        return this.consumption;
    }

    public void setConsumption(float consumption) {
        this.consumption = consumption;
    }

    public float getCounter() {
        return this.counter;
    }

    public void setCounter(float counter) {
        this.counter = counter;
    }

    public float getValue() {
        return this.value;
    }

    public void setValue(float value) {
        this.value = value;
    }

    public int getYearOfProduction() {
        return this.yearOfProduction;
    }

    public void setYearOfProduction(int yearOfProduction) {
        this.yearOfProduction = yearOfProduction;
    }

    public int getNumberOfRentals() {
        return this.numberOfRentals;
    }

    public void setNumberOfRentals(int numberOFRentals) {
        this.numberOfRentals = numberOFRentals;
    }

    public boolean isManual() {
        return this.manual;
    }

    public boolean getManual() {
        return this.manual;
    }

    public void setManual(boolean manual) {
        this.manual = manual;
    }

    public boolean isAvailable() {
        return this.available;
    }

    public boolean getAvailable() {
        return this.available;
    }

    public void setAvailable(boolean available) {
        this.available = available;
    }

    public boolean isAirConditioning() {
        return this.airConditioning;
    }

    public boolean getAirConditioning() {
        return this.airConditioning;
    }

    public void setAirConditioning(boolean airConditioning) {
        this.airConditioning = airConditioning;
    }

    public boolean isDamaged() {
        return this.damaged;
    }

    public boolean getDamaged() {
        return this.damaged;
    }

    public void setDamaged(boolean damaged) {
        this.damaged = damaged;
    }

    public boolean isAccidentFree() {
        return this.accidentFree;
    }

    public boolean getAccidentFree() {
        return this.accidentFree;
    }

    public void setAccidentFree(boolean accidentFree) {
        this.accidentFree = accidentFree;
    }

    public int getBootCapacity() {
        return this.bootCapacity;
    }

    public void setBootCapacity(int bootCapacity) {
        this.bootCapacity = bootCapacity;
    }

    public int getEnginePower() {
        return this.enginePower;
    }

    public void setEnginePower(int enginePower) {
        this.enginePower = enginePower;
    }

    public int getEngineCapacity() {
        return this.engineCapacity;
    }

    public int getMass() {
        return this.mass;
    }

    public void setMass(int mass) {
        this.mass = mass;
    }

    public int getNumberOfPassengers() {
        return this.numberOfPassengers;
    }

    public void setNumberOfPassengers(int numberOfPassengers) {
        this.numberOfPassengers = numberOfPassengers;
    }

    public void setEngineCapacity(int engineCapacity) {
        this.engineCapacity = engineCapacity;
    }

    public Date getLastService() {
        return this.lastService;
    }

    public void setLastService(Date lastService) {
        this.lastService = lastService;
    }
}
