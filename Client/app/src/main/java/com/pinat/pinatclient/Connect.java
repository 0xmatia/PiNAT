package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.pinat.pinatclient.utils.VolleySingleton;
import com.pinat.pinatclient.utils.Constants;

import java.util.regex.Matcher;

public class Connect extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


    }

    public void connect(View view)
    {
        final Context context = view.getContext();
        // Get the request queue
        RequestQueue requestQueue = VolleySingleton.getInstance(this.getApplicationContext())
                .getRequestQueue();

        //Todo: Add loading animation while fetching data

        // Get views:
        EditText ipAddress = (EditText)findViewById(R.id.ipAddress);
        EditText portNumber = (EditText)findViewById(R.id.portNumber);
        Button connectBtn = (Button) findViewById(R.id.connectBtn);
        final TextView data = (TextView) findViewById(R.id.data);

        data.setTextColor(getResources().getColor(R.color.colorAccent));

        // Verify input
        Matcher matcher = Constants.IP_ADDRESS.matcher(ipAddress.getText().toString());
        if (!matcher.matches())
        {
            data.setText("It doesn't look like a valid IP address...");
            return;
        }

        try {
            int port = Integer.parseInt(portNumber.getText().toString());
            if (port < 0 || port > 65535)
            {
                data.setText("Invalid port number!");
                return;
            }
        }
        catch (NumberFormatException e)
        {
           return;
        }
        ///////////////////////////////////

        String url = "http://" + ipAddress.getText().toString() + ":"
                + portNumber.getText().toString();
        Constants.ENDPOINT = url;
        Log.d("Log", Constants.ENDPOINT);

        //construct request
        StringRequest stringRequest = new StringRequest(Request.Method.GET, Constants.ENDPOINT,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        data.setTextColor(getResources().getColor(R.color.colorSuccess));
                        data.setText("Connected! Now loading...");

                        Intent intent = new Intent(context, General.class);
                        Bundle bundle = new Bundle();
                        bundle.putString("response", response);
                        intent.putExtras(bundle);
                        startActivity(intent);
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                if (error != null)
                {
                    data.setTextColor(getResources().getColor(R.color.colorError));
                    data.setText("Looks like the server is offline or something terrible has" +
                            " happened. Please try again later.");
                    Log.d("Error", "Connection error");
                }
            }
        });

        requestQueue.add(stringRequest);
    }
}
