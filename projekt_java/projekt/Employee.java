package projekt;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.Date;

public class Employee {

    protected String firstName, lastName;
    public int workedMonths;
    public Date startDate;
    private SimpleDateFormat sdformat = new SimpleDateFormat("dd-MM-yyyy");
    private SimpleDateFormat sdformat2 = new SimpleDateFormat("yyyy-MM-dd");

    public Employee(String firstName, String lastName, String dateFromInputString) throws ParseException{
        setFirstName(firstName);
        setLastName(lastName);
        setWorkedMonths(0);
        Date dateFromInput = sdformat.parse(dateFromInputString);
        setStartDate(dateFromInput);
    }

    public Employee(String firstName, String lastName, Date dateFromInput) throws ParseException{
        setFirstName(firstName);
        setLastName(lastName);
        setWorkedMonths(0);
        setStartDate(dateFromInput);
    }

    public int calculateWorkedMonths(Date todaysDate) throws ParseException{
        String firstDate = sdformat2.format(todaysDate);
        String secondDate = sdformat2.format(this.startDate);
        long monthsBetween = ChronoUnit.MONTHS.between(LocalDate.parse(secondDate).withDayOfMonth(1), LocalDate.parse(firstDate).withDayOfMonth(1));

        setWorkedMonths((int)monthsBetween);

        return (int)monthsBetween;
    }

    public Date getStartDate() {
        return this.startDate;
    }

    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    public int getWorkedMonths() {
        return this.workedMonths;
    }

    public void setWorkedMonths(int workedMonths) {
        this.workedMonths = workedMonths;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void introduceEmployee(){
        System.out.format("%10s%10s%15s \n", this.getFirstName(), this.getLastName(), sdformat.format(this.getStartDate()));
    }

}
