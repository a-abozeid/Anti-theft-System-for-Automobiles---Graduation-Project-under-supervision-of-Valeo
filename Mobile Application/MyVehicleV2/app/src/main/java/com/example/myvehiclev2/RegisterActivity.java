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
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import java.util.HashMap;

public class RegisterActivity extends AppCompatActivity {

    /* Private Global Variables for Editing Text Boxes */
    private EditText username;
    private EditText chassisNumber;
    private EditText phoneNumber;
    private EditText email;
    private EditText password;
    private EditText confirmPassword;

    /* Private Global Variable for Register Button */
    private Button register;

    private FirebaseAuth auth;

    private FirebaseDatabase rootNode;
    private DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        username = findViewById(R.id.inputUserName);
        chassisNumber = findViewById(R.id.inputChassisNumber);
        phoneNumber = findViewById(R.id.inputPhoneNumber);
        email = findViewById(R.id.inputEmail);
        password = findViewById(R.id.inputPassword);
        confirmPassword = findViewById(R.id.inputConfirmPassword);
        register = findViewById(R.id.registerButton);

        auth = FirebaseAuth.getInstance();
        rootNode = FirebaseDatabase.getInstance("https://my-vehicle-v2-firebase-default-rtdb.europe-west1.firebasedatabase.app");
        reference = rootNode.getReference().child("USERS");



        register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String usernameText = username.getText().toString();
                String chassisNumberText = chassisNumber.getText().toString();
                String phoneNumberText = phoneNumber.getText().toString();
                String emailText = email.getText().toString();
                String passwordText = password.getText().toString();
                String confirmPasswordText = confirmPassword.getText().toString();

                if(TextUtils.isEmpty(usernameText) || TextUtils.isEmpty(chassisNumberText) || TextUtils.isEmpty(phoneNumberText)
                   || TextUtils.isEmpty(emailText) || TextUtils.isEmpty(passwordText)){
                    Toast.makeText(RegisterActivity.this , "Empty Credentials" , Toast.LENGTH_SHORT).show();
                }
                else if(phoneNumberText.length() < 11){
                    Toast.makeText(RegisterActivity.this , "Please Enter a Valid Phone Number" , Toast.LENGTH_SHORT).show();
                }
                else if(passwordText.length() < 6){
                    Toast.makeText(RegisterActivity.this , "Password is too Short" , Toast.LENGTH_SHORT).show();
                }
                else if(!passwordText.equals(confirmPasswordText)){
                    Toast.makeText(RegisterActivity.this , "Password Mismatch" , Toast.LENGTH_SHORT).show();
                }
                else {
                    /* Call the Registration Method */
                    registerUser(usernameText, chassisNumberText, phoneNumberText, emailText , passwordText);
                }
            }
        });
    }

    private void registerUser(String userName, String chassisNumber, String phoneNumber, String email, String password) {

        auth.createUserWithEmailAndPassword(email , password).addOnCompleteListener(RegisterActivity.this , new OnCompleteListener<AuthResult>() {
            @Override
            public void onComplete(@NonNull Task<AuthResult> task) {
                if(task.isSuccessful()){
                    //Realtime database *************
                    HashMap<String, String> map = new HashMap<>();
                    map.put("Username" , userName);
                    map.put("Chassis Number" , chassisNumber);
                    map.put("Phone Number" , phoneNumber);
                    map.put("E-mail" , email);
                    map.put("Password" , password);

                    String tempEmail = email.replace(".", "!");
                    reference.child(tempEmail).setValue(map);


                    Toast.makeText(RegisterActivity.this , "Registration Succeeded" , Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(RegisterActivity.this , VerificationActivity.class);
                    startActivity(intent);
                    finish();
                }
                else {
                    Toast.makeText(RegisterActivity.this , "User Already Exists on this E-mail" , Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

}