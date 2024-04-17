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
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class ChangePasswordActivity extends AppCompatActivity {

    private EditText oldPassword;
    private EditText newPassword;
    private EditText confirmNewPassword;

    private Button confirm;

    private String tempEmail;

    private FirebaseAuth auth;
    private FirebaseDatabase rootNode;
    private DatabaseReference reference;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_password);

        Bundle extra = getIntent().getExtras();
        if (extra != null) {
            tempEmail = extra.getString("key");
            //The key argument here must match that used in the other activity
        }

        oldPassword = findViewById(R.id.inputOldPassword);
        newPassword = findViewById(R.id.inputNewPassword);
        confirmNewPassword = findViewById(R.id.inputConfirmNewPassword);

        confirm = findViewById(R.id.confirmButton2);

        auth = FirebaseAuth.getInstance();
        rootNode = FirebaseDatabase.getInstance("https://my-vehicle-v2-firebase-default-rtdb.europe-west1.firebasedatabase.app/");
        reference = rootNode.getReference().child("USERS");


        confirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String oldPasswordText = oldPassword.getText().toString();
                String newPasswordText = newPassword.getText().toString();
                String confirmNewPasswordText = confirmNewPassword.getText().toString();
                if(TextUtils.isEmpty(oldPasswordText) || TextUtils.isEmpty(newPasswordText)){
                    Toast.makeText(ChangePasswordActivity.this , "Empty Credentials" , Toast.LENGTH_SHORT).show();
                }
                else if(newPasswordText.length() < 6){
                    Toast.makeText(ChangePasswordActivity.this , "Password is too Short" , Toast.LENGTH_SHORT).show();
                }
                else if(!newPasswordText.equals(confirmNewPasswordText)){
                    Toast.makeText(ChangePasswordActivity.this , "Password Mismatch" , Toast.LENGTH_SHORT).show();
                }
                else {
                    /* Call the Change Password Method */
                    changePassword(oldPasswordText , newPasswordText);
                }

            }
        });

    }

    private void changePassword(String oldPasswordText , String newPasswordText) {
        reference.child(tempEmail).get().addOnCompleteListener(new OnCompleteListener<DataSnapshot>() {
            @Override
            public void onComplete(@NonNull Task<DataSnapshot> task) {
                DataSnapshot snapshot = task.getResult();
                String oldPassword = String.valueOf(snapshot.child("Password").getValue());
                if(oldPassword.equals(oldPasswordText)){
                    auth.getCurrentUser().updatePassword(newPasswordText);
                    reference.child(tempEmail).child("Password").setValue(newPasswordText);
                    Toast.makeText(ChangePasswordActivity.this , "Password Changed" , Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(ChangePasswordActivity.this , MainActivity.class);
                    startActivity(intent);
                    finish();
                }
                else {
                    Toast.makeText(ChangePasswordActivity.this , "Incorrect Password" , Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}


