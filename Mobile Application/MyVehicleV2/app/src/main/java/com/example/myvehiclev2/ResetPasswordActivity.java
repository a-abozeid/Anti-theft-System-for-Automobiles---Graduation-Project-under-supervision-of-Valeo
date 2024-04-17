package com.example.myvehiclev2;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

public class ResetPasswordActivity extends AppCompatActivity {

    private EditText email;
    private EditText chassisNumber;

    /* Private Global Variable for Register Button */
    private Button confirm;

    private FirebaseAuth auth;
    private DatabaseReference reference;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reset_password);

        email = findViewById(R.id.inputEmail2);
        chassisNumber = findViewById(R.id.inputChassisNumber2);
        confirm = findViewById(R.id.confirmButton);

        auth = FirebaseAuth.getInstance();
        reference = FirebaseDatabase.getInstance("https://my-vehicle-v2-firebase-default-rtdb.europe-west1.firebasedatabase.app").getReference("USERS");

        confirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String chassisNumberText = chassisNumber.getText().toString();
                String emailText = email.getText().toString();

                if(TextUtils.isEmpty(chassisNumberText) || TextUtils.isEmpty(emailText)){
                    Toast.makeText(ResetPasswordActivity.this , "Empty Credentials" , Toast.LENGTH_SHORT).show();
                }
                else{
                    checkData(emailText , chassisNumberText);
                }
            }
        });
    }

    private void checkData(String emailText, String chassisNumberText) {

        String tempEmail = emailText.replace(".", "!");
        Query checkChassis = reference.orderByChild("Chassis Number").equalTo(chassisNumberText);
        checkChassis.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if(snapshot.exists()){
                    String emailDatabase = snapshot.child(tempEmail).child("E-mail").getValue(String.class);
                    if(emailDatabase != null && emailDatabase.equals(emailText)){
                        auth.sendPasswordResetEmail(emailText).addOnSuccessListener(new OnSuccessListener<Void>() {
                            @Override
                            public void onSuccess(Void unused) {
                                Toast.makeText(ResetPasswordActivity.this , "Reset link sent to email" , Toast.LENGTH_SHORT).show();
                                Intent intent = new Intent(ResetPasswordActivity.this , LoginActivity.class);
                                startActivity(intent);
                                finish();
                            }
                        });
                    }
                    else
                        Toast.makeText(ResetPasswordActivity.this , "Wrong Email or Chassis Number" , Toast.LENGTH_SHORT).show();
                }
                else
                    Toast.makeText(ResetPasswordActivity.this , "User doesn't exist" , Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });

    }
}