package com.example.myvehiclev2;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class LoginActivity extends AppCompatActivity {

    /* Private Global Variables for Editing Text Boxes */
    private EditText email;
    private EditText password;

    /* Private Global Variables for Login and Register Buttons */
    private Button login;
    private Button forgotYourPassword;
    private Button secureYourVehicle;

    private FirebaseAuth auth;
    private DatabaseReference reference;
    private FirebaseUser user;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        email = findViewById(R.id.inputEmail);
        password = findViewById(R.id.inputPassword);

        login = findViewById(R.id.signInButton);
        forgotYourPassword = findViewById(R.id.forgotYourPasswordButton);
        secureYourVehicle = findViewById(R.id.secureYourVehicleButton);

        auth = FirebaseAuth.getInstance();
        reference = FirebaseDatabase.getInstance("https://my-vehicle-v2-firebase-default-rtdb.europe-west1.firebasedatabase.app/").getReference("USERS");

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String emailText = email.getText().toString();
                String passwordText = password.getText().toString();

                if(TextUtils.isEmpty(emailText) || TextUtils.isEmpty(passwordText)){
                    Toast.makeText(LoginActivity.this , "Empty Credentials" , Toast.LENGTH_SHORT).show();
                }
                else{
                    /* Call The Login Method */
                    loginUser(emailText , passwordText);
                }
            }
        });


        forgotYourPassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(LoginActivity.this , ResetPasswordActivity.class);
                startActivity(intent);
            }
        });

        secureYourVehicle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(LoginActivity.this , RegisterActivity.class);
                startActivity(intent);
            }
        });
    }

    private void loginUser(String email, String password) {
        auth.signInWithEmailAndPassword(email , password).addOnCompleteListener(LoginActivity.this , new OnCompleteListener<AuthResult>(){
            @Override

            public void onComplete(@NonNull Task<AuthResult> task) {
                if (task.isSuccessful()) {
                    user = auth.getCurrentUser();
                    if(true){
                        Toast.makeText(LoginActivity.this, "Welcome!", Toast.LENGTH_SHORT).show();
                        String tempEmail = email.replace(".", "!");
                        reference.child(tempEmail).child("Password").setValue(password);

                        Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                        intent.putExtra("key", tempEmail);
                        startActivity(intent);
                        finish();
                    }
                    else {
                        Toast.makeText(LoginActivity.this, "Please Verify your E-mail Address", Toast.LENGTH_SHORT).show();
                        auth.getCurrentUser().sendEmailVerification().addOnSuccessListener(new OnSuccessListener<Void>() {
                            @Override
                            public void onSuccess(Void unused) {
                                Toast.makeText(LoginActivity.this , "a Verification E-mail has been sent to your E-mail Address" , Toast.LENGTH_SHORT).show();
                            }
                        });
                    }

                }

                else {
                    Toast.makeText(LoginActivity.this, "Incorrect E-mail or Password", Toast.LENGTH_SHORT).show();
                }
            }
        });

    }
}