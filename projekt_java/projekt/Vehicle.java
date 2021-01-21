package projekt;

import java.text.ParseException;
import java.util.Date;

public interface Vehicle {
    // popelnilam blad w dokumentacji: nie powinnam wpisywac field w interfejsie, bo sa one: public, static, final
    //a kazdy pojazd ma indywidualne
    int carService = 100;
    int busService = 200;

    public void updateCounter(float kilometers);
    public float calculateFuelConsumption(float kilometers);
    public void showVehicleInfo(int i);
    public void showVehicleSpecificInformation();
    public void makeFullService() throws ParseException;
    public void makeFullService(Date date);
    public float calculateDailyPrice();
    public float calculateWeeklyPrice();
    public float calculateMonthlyPrice();
    public float calculateAdditionalInsurance();
    public float negotiate(float negotiate, float price);
    public void addAnAccident(Date date);
    public void addAnAccident(String date) throws ParseException;
    public void addAnAccident(String date, String description) throws ParseException;
    public void readAccidents();

    //getters and setters

    public Date getTakenTo();
    public void setTakenTo(Date takenTo);
    public String getBrand();
    public void setBrand(String brand);
    public String getModel();
    public void setModel(String model);
    public String getColor();
    public void setColor(String color);
    public float getConsumption();
    public void setConsumption(float consumption);
    public float getCounter();
    public void setCounter(float counter);
    public float getValue();
    public void setValue(float value);
    public int getYearOfProduction();
    public void setYearOfProduction(int yearOfProduction);
    public int getNumberOfRentals();
    public void setNumberOfRentals(int numberOFRentals);
    public boolean isManual();
    public boolean getManual();
    public void setManual(boolean manual);
    public boolean isAvailable();
    public boolean getAvailable();
    public void setAvailable(boolean available);
    public boolean isAirConditioning();
    public boolean getAirConditioning();
    public void setAirConditioning(boolean airConditioning);
    public boolean isDamaged();
    public boolean getDamaged();
    public void setDamaged(boolean damaged);
    public boolean isAccidentFree();
    public boolean getAccidentFree();
    public void setAccidentFree(boolean accidentFree);
    public int getBootCapacity();
    public void setBootCapacity(int bootCapacity);
    public int getEnginePower();
    public void setEnginePower(int enginePower);
    public int getEngineCapacity();
    public void setEngineCapacity(int engineCapacity);
    public int getNumberOfPassengers();
    public void setNumberOfPassengers(int numberOfPassengers);
    public int getMass();
    public void setMass(int mass);
    public Date getLastService();
    public void setLastService(Date lastService);
}
