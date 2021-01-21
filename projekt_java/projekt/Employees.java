package projekt;

import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

public abstract class Employees {
    public ArrayList<Employee> employees = new ArrayList<Employee>();
    Scanner input = new Scanner(System.in);
    Date todaysDate = new Date();
    private int choice, choice2;
    private float salary = 3000;

    public Employees() throws ParseException {
        this.employees.add(new Employee("John", "Smith", "01-01-2020"));
        this.employees.add(new Employee("Thomas", "Jones", "02-02-2020"));
        this.employees.add(new Employee("Thomas", "Jones", "02-02-2020"));
        // this.employees.add(new Employee("James", "Taylor", "04-04-2020"));
        // this.employees.add(new Employee("Olivia", "Davies", "05-05-2020"));
        // this.employees.add(new Employee("Emily", "Evans", "06-06-2020"));
        // this.employees.add(new Employee("Isabella", "Thomson", "07-07-2020"));
        // this.employees.add(new Employee("Mary", "Johnson", "08-08-2020"));

    }  

    public void hireAnEmployee(Date dateOfEmployment) throws ParseException{
        System.out.println("Enter the first name of new employee: ");
        String firstName = input.next();
        System.out.println("Enter the last name of new employee: ");
        String lastName = input.next();

        this.employees.add(new Employee(firstName, lastName, dateOfEmployment));
    }

    public void hireAnEmployee(String dateOfEmployment) throws ParseException {
        System.out.println("Enter the first name of new employee: ");
        String firstName = input.next();
        System.out.println("Enter the last name of new employee: ");
        String lastName = input.next();

        this.employees.add(new Employee(firstName, lastName, dateOfEmployment));
    }

    public float dismissAnEmployee(){
        System.out.println("Which employee would You like to dismiss?");
        this.showAllEmployees();
        choice = input.nextInt();

        while (choice < 0 || choice >= this.employees.size()){
            System.out.println("Wrong number.");
            choice = input.nextInt();
        }

        System.out.println("1. Disciplinary dismissal");
        System.out.println("2. Dismissal with a severance pay");
        choice2 = input.nextInt();

        while (choice2 != 1 && choice2 != 2){
            System.out.println("Wrong number.");
            choice2 = input.nextInt();
        }

        if(choice2 == 1){
            this.employees.remove(choice);
            return 0;
        }
        else if(choice2 == 2){
            this.employees.remove(choice);
            return 3*salary;
        }
        return 0;
    }

    public void showAllEmployees(){
        for(int i = 0; i < this.employees.size(); i++ ){
            System.out.print(i);
            this.employees.get(i).introduceEmployee();
        }
    }
}
