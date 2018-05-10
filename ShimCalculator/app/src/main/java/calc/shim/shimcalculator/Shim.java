package calc.shim.shimcalculator;

import android.widget.EditText;

/**
 * Created by Jonah on 5/26/2017.
 */

public class Shim {

    // Default constructor
    Shim() {
        specified = 0.0;
        clearance = 0.0;
        thickness = 0.0;
    }

    // Variables
    private double specified;
    private double clearance;
    private double thickness;

    // Getters and setters
    public double getSpecified() {
        return specified;
    }

    public void setSpecified(double specified) {
        this.specified = specified;
    }

    public double getClearance() {
        return clearance;
    }

    public void setClearance(double clearance) {
        this.clearance = clearance;
    }

    public double getThickness() {
        return thickness;
    }

    public void setThickness(double thickness) {
        this.thickness = thickness;
    }
    public double calculateShim() {
       return (clearance - specified) + thickness;
    }
}
