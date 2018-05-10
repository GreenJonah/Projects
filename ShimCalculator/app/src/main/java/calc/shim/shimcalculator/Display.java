package calc.shim.shimcalculator;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import static android.R.attr.defaultValue;

/**
 * Created by Jonah on 6/5/2017.
 */

public class Display extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dislplay);

        // Get the intents
        Intent receiveIntent = getIntent();

        // Unbundle the intents and set the new values
        String S1 = receiveIntent.getStringExtra("S1");
        TextView T1 = (TextView) findViewById(R.id.ex_left_calc);

        String S2 = receiveIntent.getStringExtra("S2");
        TextView T2 = (TextView) findViewById(R.id.ex_right_calc);

        String S3 = receiveIntent.getStringExtra("S3");
        TextView T3 = (TextView) findViewById(R.id.in_left_calc);

        String S4 = receiveIntent.getStringExtra("S4");
        TextView T4 = (TextView) findViewById(R.id.in_right_calc);

        // Display the new values
        T1.setText(S1);
        T2.setText(S2);
        T3.setText(S3);
        T4.setText(S4);
    }
}
