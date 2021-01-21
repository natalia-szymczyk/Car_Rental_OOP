package projekt;

import java.text.*;
import java.util.Date;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws ParseException {

        Scanner input = new Scanner(System.in);
        Text text = new Text();

        int choice = 1, choice2 = 1, test = 0;
        float amount;

        Date todaysDate = new Date();
        SimpleDateFormat sdformat = new SimpleDateFormat("dd-MM-yyyy");


        Fleet fleet = new Fleet();
        text.printText();

        do{
            System.out.print("Enter the number: ");
            choice = input.nextInt();

            switch (choice) {
                case 0:                    
                    break;

                case 1:
                    fleet.rentAVehicle(todaysDate);
                    break;
            
                case 2:
                    fleet.sellAVehicle();
                    break;

                case 3:
                    fleet.buyAVehicle();
                    break;

                case 4:
                    fleet.repairAVehicle();
                    break;

                case 5:
                    fleet.reportAccident(todaysDate);
                    break;

                case 6:
                    fleet.showAvailableCars();
                    break;

                case 7:
                    fleet.sortCars();
                    break;

                case 8:
                    fleet.showAllBuses();
                    break;

                case 9:
                    fleet.showSpecificInformation();
                    break;

                case 10:
                    fleet.makeAService(todaysDate);
                    break;

                case 11:
                    fleet.calculateFuel();
                    break;

                case 12:
                    new Text().printEmployeeText();

                    do{                       
                        System.out.print("Number: ");
                        choice2 = input.nextInt();
                        switch (choice2) {
                            case 0:
                                break;
                                
                            case 1:
                                fleet.budget.hireAnEmployee(todaysDate);
                                break;

                            case 2:
                                amount = fleet.budget.dismissAnEmployee();
                                fleet.expenditure(amount);
                                break;

                            case 3:
                                fleet.budget.showAllEmployees();
                                break;

                            case 4:
                                System.out.println("Enter the amonut: ");
                                amount = input.nextFloat();
                                fleet.budget.impact(amount, todaysDate);
                                break;

                            case 5:
                                System.out.println("Enter the amonut: ");
                                amount = input.nextFloat();
                                fleet.expenditure(amount);
                                break;

                            case 6:
                                System.out.println("Total budget amount: " + fleet.budget.getBudget());
                                break;

                            case 7:
                                fleet.budget.summarizeBudgetForTheMonths();
                                break;

                            case 8:
                                float currentExpenses = fleet.forecastExpenses();
                                float possession = fleet.calculatePossession();
                                System.out.println("How much money would You like to take for a loan? ");
                                amount = input.nextFloat();
                                fleet.budget.applyForALoan(amount, todaysDate, currentExpenses, possession);
                                break;


                        
                            default:
                                text.printEmployeeText();
                                break;
                        }
                } while (choice2 != 0);                  

                    break;

                case 13:
                    System.out.println("Enter the date in format dd-MM-yyyy");
                    String dateFromInputString = input.next();
                    while(test == 0){
                        try {            
                            todaysDate = sdformat.parse(dateFromInputString);
                            test = 1;
                        } catch (Exception e) {
                            System.out.println("Invalid format");
                        }
                    }
                    if (test == 1)
                        todaysDate = fleet.changeDate(dateFromInputString);
   
                    break;

                    
                default:
                    System.out.println("Unknown operation.");
                    text.printText();
                    break;
            }

        }while (choice != 0);

        input.close();        
    }

}
