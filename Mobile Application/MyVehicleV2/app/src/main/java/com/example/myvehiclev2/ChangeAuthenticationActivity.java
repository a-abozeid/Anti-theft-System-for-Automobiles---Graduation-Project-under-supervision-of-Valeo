package com.example.myvehiclev2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class ChangeAuthenticationActivity extends AppCompatActivity {

    private Button passcodeOp, passcodeRFIDOp, passcodeRIFDFaceIDOp;
    String phoneNum = "+201064177433";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_authentication);

        SmsManager smsManager= SmsManager.getDefault();

        passcodeOp = findViewById(R.id.passcodeOption);
        passcodeRFIDOp = findViewById(R.id.passcodeRFIDOption);
        passcodeRIFDFaceIDOp = findViewById(R.id.passcodeRFIDFaceOption);

        passcodeOp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String text = "auth = op1";
                smsManager.sendTextMessage(phoneNum, null, text, null, null);
                Toast.makeText(ChangeAuthenticationActivity.this , "Sent!" , Toast.LENGTH_SHORT).show();
            }
        });

        passcodeRFIDOp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String text = "auth = op2";
                smsManager.sendTextMessage(phoneNum, null, text, null, null);
                Toast.makeText(ChangeAuthenticationActivity.this , "Sent!" , Toast.LENGTH_SHORT).show();
            }
        });

        passcodeRIFDFaceIDOp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String text = "auth = op3";
                smsManager.sendTextMessage(phoneNum, null, text, null, null);
                Toast.makeText(ChangeAuthenticationActivity.this , "Sent!" , Toast.LENGTH_SHORT).show();
            }
        });
    }
}