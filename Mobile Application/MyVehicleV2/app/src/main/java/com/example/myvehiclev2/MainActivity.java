package com.example.myvehiclev2;

import android.Manifest;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity {

    /* Private Global Variable for Sign Out Button */
    private Button findMyVehicle;
    private Button changePassword;
    private Button signOut;
    private Button engineLock, engineUnlock;
    private Button changeAuth;

    private RequestQueue queue;
    String latitude, longitude;

    String tempEmail;
    String phoneNum = "+201064177433";

    private DatabaseReference reference;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.SEND_SMS}, 100);
        SmsManager smsManager= SmsManager.getDefault();
        queue = Volley.newRequestQueue(this);

        Bundle extra = getIntent().getExtras();
        if (extra != null) {
            tempEmail = extra.getString("key");
            //The key argument here must match that used in the other activity
        }

        reference = FirebaseDatabase.getInstance("https://my-vehicle-v2-firebase-default-rtdb.europe-west1.firebasedatabase.app/").getReference("USERS");

        findMyVehicle = findViewById(R.id.findMyVehicleButton);
        changePassword = findViewById(R.id.changePasswordButton);
        signOut = findViewById(R.id.signOutButton);
        engineLock = findViewById(R.id.engineLockButton);
        engineUnlock = findViewById(R.id.engineUnlockButton);
        changeAuth = findViewById(R.id.changeAuthButton);

        engineLock.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String text = "systemOff";
                smsManager.sendTextMessage(phoneNum, null, text, null, null);
                Toast.makeText(MainActivity.this , "Sent!" , Toast.LENGTH_SHORT).show();
            }
        });

        engineUnlock.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String text = "systemOn";
                smsManager.sendTextMessage(phoneNum, null, text, null, null);
                Toast.makeText(MainActivity.this , "Sent!" , Toast.LENGTH_SHORT).show();
            }
        });

        findMyVehicle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String locUrl = "https://api.thingspeak.com/channels/1708386/feeds.json?results=2";

                JsonObjectRequest latReq = new JsonObjectRequest(Request.Method.GET, locUrl, null, new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            JSONArray arr = response.getJSONArray("feeds");
                            JSONObject obj = arr.getJSONObject(arr.length()-1);
                            latitude = obj.getString("field1");
                            longitude = obj.getString("field2");
                            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("geo:<" + latitude  + ">,<" + longitude + ">?q=<" + latitude  + ">,<" + longitude + ">"));
                            startActivity(intent);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }, new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        error.printStackTrace();
                    }
                });
                queue.add(latReq);
            }
        });


        signOut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseAuth.getInstance().signOut();
                Toast.makeText(MainActivity.this , "Signed Out" , Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(MainActivity.this , LoginActivity.class);
                startActivity(intent);
                finish();
            }
        });


        changePassword.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this , ChangePasswordActivity.class);
                intent.putExtra("key", tempEmail);
                startActivity(intent);
            }
        });

        changeAuth.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this , ChangeAuthenticationActivity.class);
                startActivity(intent);
            }
        });
    }
}