package calc.shim.shimcalculator;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Make four shims
    final Shim exLeft  = new Shim();
    final Shim exRight = new Shim();
    final Shim inLeft  = new Shim();
    final Shim inRight = new Shim();

    double ParseDouble(String strNumber) {
        if (strNumber != null && strNumber.length() > 0) {
            try {
                return Double.parseDouble(strNumber);
            } catch(Exception e) {
                return -1;
            }
        }
        else return 0;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button calculate_btn = (Button) this.findViewById(R.id.calculate_btn);

        calculate_btn.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplication(), Display.class);

                setTolerances();
                setGap();
                setThickness();

                // call each shims calculate function
                String eL = doubleString(exLeft.calculateShim());
                String eR = doubleString(exRight.calculateShim());
                String iL = doubleString(inLeft.calculateShim());
                String iR = doubleString(inRight.calculateShim());

                // Place Calculated values into a bundle
                Bundle extras = new Bundle();

                extras.putString("S1", eL);
                extras.putString("S2", eR);
                extras.putString("S3", iL);
                extras.putString("S4", iR);

                // Send bundle over to display activity
                intent.putExtras(extras);
                startActivity(intent);
            }

        });
    }

    public void setTolerances() {
        final EditText eTolerance1 = (EditText)(findViewById(R.id.ex_specified_tolerance));
        final EditText iTolerance1 = (EditText)(findViewById(R.id.in_specified_tolerance));

        // Set the Specified Tolerance of each shim
        double eTolerance2   = ParseDouble(eTolerance1.getText().toString());
        exLeft.setSpecified(eTolerance2);
        exRight.setSpecified(eTolerance2);

        double iTolerance2 = ParseDouble(iTolerance1.getText().toString());
        inLeft.setSpecified(iTolerance2);
        inRight.setSpecified(iTolerance2);


    }

    public void setGap() {
        // Set current gap for each shim
        final EditText eLeftGap  = (EditText)(findViewById(R.id.ex_lGap));
        final EditText eRightGap = (EditText) (findViewById(R.id.ex_rGap));
        final EditText iLeftGap  = (EditText)(findViewById(R.id.in_lGap));
        final EditText iRightGap = (EditText) (findViewById(R.id.in_rGap));

        double eLeftGap2  = ParseDouble(eLeftGap.getText().toString());
        double eRightGap2 = ParseDouble(eRightGap.getText().toString());

        exLeft.setClearance(eLeftGap2);
        exRight.setClearance(eRightGap2);

        double iLeftGap2  = ParseDouble(iLeftGap.getText().toString());
        double iRightGap2 = ParseDouble(iRightGap.getText().toString());

        inLeft.setClearance(iLeftGap2);
        inRight.setClearance(iRightGap2);
    }

    public void setThickness() {
        // Set thickness of each shim
        final EditText eLeftThickness  = (EditText)(findViewById(R.id.ex_lThickness));
        final EditText eRightThickness = (EditText) (findViewById(R.id.ex_rThickness));
        final EditText iLeftThickness  = (EditText)(findViewById(R.id.in_lThickness));
        final EditText iRightThickness = (EditText) (findViewById(R.id.in_rThickness));

        double eLeftThickness2  = ParseDouble(eLeftThickness.getText().toString());
        double eRightThickness2 = ParseDouble(eRightThickness.getText().toString());

        exLeft.setThickness(eLeftThickness2);
        exRight.setThickness(eRightThickness2);

        double iLeftThickness2  = ParseDouble(iLeftThickness.getText().toString());
        double iRightThickness2 = ParseDouble(iRightThickness.getText().toString());

        inLeft.setThickness(iLeftThickness2);
        inRight.setThickness(iRightThickness2);
    }

    public String doubleString(double value){
        return Double.toString(value);
    }
}
