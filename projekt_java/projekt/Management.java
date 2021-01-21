package projekt;

import java.text.ParseException;
import java.util.Date;

public interface Management {
    float salary = 3000;

    public void impact(float amount, Date date);
    public int expenditure(float amount, Date date);
    public void summarizeBudgetForTheMonths();
    public void hireAnEmployee(String dateOfEmployment) throws ParseException;
    public void showAllEmployees();
    public float calculateWages();
    public void checkMonth(Date date);
    public float getBudget();
    public int applyForALoan(float amount, Date todaysDate, float expenses, float possession);
    
    public void hireAnEmployee(Date date) throws ParseException;
	public float dismissAnEmployee();
}
