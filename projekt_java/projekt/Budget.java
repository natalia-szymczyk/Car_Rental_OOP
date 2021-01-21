package projekt;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Calendar;
import java.util.Date;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.Scanner;
import java.util.TreeMap;

public class Budget extends Employees implements Management{
    public float budget;
    private Map<String, Float> map = new TreeMap<>();
    Loan loan;
    Scanner input = new Scanner(System.in);
    private SimpleDateFormat sdformat3 = new SimpleDateFormat("yyyy-MM-dd");
    private SimpleDateFormat sdformat2 = new SimpleDateFormat("MM-yyyy");
    Date todaysDate = new Date();
    private int choice2;

    public Budget() throws ParseException {
        super();
        setBudget(0);
    }  

    public Budget(float budget) throws ParseException {
        super();
        setBudget(budget);
    }
    
    @Override
    public void impact(float amount, Date date){
        String month = sdformat2.format(date); 

        System.out.println("IMPACT " + amount + " date " + month);

        if(!map.containsKey(month))
            map.put(month, 0f);

        map.put(month, map.get(month) + amount);

        this.budget += amount;
    }

    @Override
    public int expenditure(float amount, Date date){
        String month = sdformat2.format(date); 

        System.out.println("EXPENDITURE " + amount + " date " + month);

        if(!map.containsKey(month))
            map.put(month, 0f);
        
        map.put(month, map.get(month) - amount);         

        if(this.getBudget() - amount >= 0){
            this.budget -= amount;
            return 0;
        }
        else{
            System.out.println("\nThere is not enought money in the budget. ");
            System.out.println("You can try apply for a loan or sell a car. Otherwise, You will go bankrupt.");
            System.out.println("1. Apply for a loan");
            System.out.println("2. Sell a car");
            System.out.println("3. Declare bankruptcy");
            choice2 = input.nextInt();

            while (!(choice2 == 1 || choice2 == 2 || choice2 == 3)){
                System.out.println("Wrong number.");
                choice2 = input.nextInt();
            }

            if(choice2 == 1){
                return 3;
            }
            else if (choice2 == 2){
                return 2;                
            }
            else if (choice2 == 3){
                System.out.println("You are out of the business.");
                System.exit(0);
            }
        }
        return 1;
    }
    
    @Override
    public void summarizeBudgetForTheMonths(){
        System.out.println("Summarize: ");

        Set <Entry<String, Float>> entrySet = map.entrySet();
        for(Entry<String, Float> entry: entrySet){
            System.out.println(entry.getKey() + " " + entry.getValue());
        }
    }

    @Override
    public void checkMonth(Date date){
        String month = sdformat2.format(date); 
        // if(!map.containsKey(month)){
        //     float sum = this.calculateWages() + this.calculateMonthlyPayment();
        //     this.expenditure(sum, date);
        //     System.out.println("Monthly payments per " + month + ": " + sum);
        // }

        Calendar c = Calendar.getInstance();
        Date date2;
        c.setTime(todaysDate);
        long monthsBetween = ChronoUnit.MONTHS.between(
            LocalDate.parse(sdformat3.format(todaysDate)).withDayOfMonth(1),
            LocalDate.parse(sdformat3.format(date)).withDayOfMonth(1));

        for(int i = 0; i < monthsBetween; i++){
            c.add(Calendar.MONTH, 1);
            date2 = c.getTime();
            this.calculatePayments(date2);            
        }

        if(!map.containsKey(month)){
            float sum = this.calculateWages() + this.calculateMonthlyPayment();
            this.expenditure(sum, date);
            System.out.println("Monthly payments per " + month + ": " + sum);
        }

        this.setTodaysDate(date);
    }

    @Override
    public int applyForALoan(float amount, Date date, float expenses, float possesion){

        if(this.loan != null){
            if(this.loan.getRemainingPayments() != 0){
                System.out.println("\nYou must first pay off the current loan");
                return 0;
            }
        }

        if (map.size() < 5){
            System.out.println("\nThe company has been in bussiness for too short a time. ");
            System.out.println("The loan cannot be granted. ");
            return 0;
        }

        if(amount > possesion){
            System.out.println("\nThe bank will not grant a loan because there is no financial security");
            return 0;
        }

        int i = 0;
        float sum = 0;

        Set <Entry<String, Float>> entrySet = map.entrySet();
        for(Entry<String, Float> entry: entrySet){
            if (i >= map.size() - 5){                
                sum += entry.getValue();
                System.out.println(entry.getKey() + " " + entry.getValue());
            }
            i++;            
        }

        System.out.println("Amount of credit: " + amount);
        System.out.println("Total earnings: " + sum);
        System.out.println("Forecast expenses: " + expenses);
        System.out.println("Possessed property: " + possesion);

        if (sum < 0){
            System.out.println("\nThe company is not profitable. There is no financial balance. ");
            return 0;
        }
        if (expenses > amount){
            System.out.println("\nThe company has too much expenses. The company is not creditworthy. ");
            return 0;
        }

        System.out.println("For how many years would You like to take a loan? ");
        int years = input.nextInt();

        while(years < 0 || years > 30){
            System.out.println("The period must be less than 30 years. ");
            years = input.nextInt();
        }

        System.out.println("The loan application has been approved.");

        loan = new Loan(amount, years);

        return 1;
    }

    @Override
    public float calculateWages(){
        float wages = this.employees.size() * salary;
        return wages;
    }

    private void calculatePayments(Date date){
        String month = sdformat2.format(date); 
        float wages = this.employees.size() * salary;
        float loanPayment = this.calculateMonthlyPayment();
        float sum = wages + loanPayment;
        if(!map.containsKey(month)){
            this.expenditure(sum, date);
            System.out.println("Overdue monthly payments per " + month + ": " + sum);
        }        
    }

    private float calculateMonthlyPayment(){
        if(this.loan != null){
            if(this.loan.getRemainingPayments() != 0){
                float amount = this.loan.payMonthly();
                if(amount == 0){
                    System.out.println(loan);
                    System.out.println("The loan has been repaid. ");
                    loan = null;
                    System.out.println(loan);
                    return 0;
                }
                else{
                    return amount;
                }
            }
            else
                return 0;
        }
        else
            return 0;
    }

    public Date getTodaysDate() {
        return this.todaysDate;
    }

    public void setTodaysDate(Date todaysDate) {
        this.todaysDate = todaysDate;
    }

    public float getBudget() {
        return this.budget;
    }

    public void setBudget(float budget) {
        this.budget = budget;
    }
}
