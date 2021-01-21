package projekt;

import java.util.Date;

public class Accident {
    protected Date date;
    protected String description;
    protected float compensation;

    public Accident(Date date, String description) {
        this.date = date;
        this.description = description;
    }

    public Accident() {
    }

    public Date getDate() {
        return this.date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getDescription() {
        return this.description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

}
