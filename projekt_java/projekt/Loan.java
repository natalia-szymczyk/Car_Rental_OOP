package projekt;

public class Loan {
    private float amount;
    private float remainingAmount;
    private int years;
    private float monthlyPayment;
    private float annualPercentageRate = 0.08f;
    private int numberOfPayments;
    private int remainingPayments;
    
    public Loan(float amount, int years){
        this.amount = amount;
        this.years = years;
        this.numberOfPayments = this.years * 12;
        this.remainingAmount = this.amount * ( 1 + annualPercentageRate);
        this.remainingPayments = this.numberOfPayments;
        this.calculateLoan();
    }

    private void calculateLoan(){
        float monthlyPercentageRate = this.annualPercentageRate / 12;
        this.monthlyPayment = (float) (this.amount
                * (monthlyPercentageRate * Math.pow(monthlyPercentageRate + 1, this.numberOfPayments))
                / (Math.pow(monthlyPercentageRate + 1, this.numberOfPayments) - 1));

        System.out.println("Amount of credit: " + this.amount);
        System.out.println("Total amount to be paid: " + this.remainingAmount);
        System.out.println("Period: " + this.years);
        System.out.println("Monthly payment: " + this.monthlyPayment);
    }

    public float payMonthly(){
        if(remainingPayments-- != 0){
            this.remainingAmount -= this.monthlyPayment;
            return this.monthlyPayment;
        }
        else{
            return 0;
        }
    }

    public float getRemainingAmount() {
        return this.remainingAmount;
    }

    public void setRemainingAmount(float remainingAmount) {
        this.remainingAmount = remainingAmount;
    }

    public int getRemainingPayments() {
        return this.remainingPayments;
    }

    public void setRemainingPayments(int remainingPayments) {
        this.remainingPayments = remainingPayments;
    }

    public float getAmount() {
        return this.amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public int getYears() {
        return this.years;
    }

    public void setYears(int years) {
        this.years = years;
    }

    public float getMonthlyPayment() {
        return this.monthlyPayment;
    }

    public void setMonthlyPayment(float monthlyPayment) {
        this.monthlyPayment = monthlyPayment;
    }
}
