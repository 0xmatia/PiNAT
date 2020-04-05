package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.google.gson.Gson;
import com.pinat.pinatclient.Adapters.EvilTwinAdapter;
import com.pinat.pinatclient.models.EvilTwinResponse;
import com.pinat.pinatclient.utils.Constants;
import com.pinat.pinatclient.utils.VolleySingleton;

import java.util.Arrays;
import java.util.List;

public class EvilTwinLog extends AppCompatActivity {
    private static final String TAG = "LogActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.evil_twin_activity);

        Bundle params = getIntent().getExtras();
        if (params == null) return;
        final String action = params.getString("action");
        Log.d(TAG, "onCreate: Action: " + action);


        // Make a request
        String url = Constants.ENDPOINT + "/" + action;
        Log.d(TAG, "onCreate: " + url);
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Gson gson = new Gson();
                        EvilTwinResponse evilTwinResponse = gson.fromJson(response, EvilTwinResponse.class);
                        if (evilTwinResponse.getStatus().equals("success")) //always true :/
                        {
                            Log.d(TAG, "onResponse: " + response);
                            showLog(evilTwinResponse, action);
                        }
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                if (error != null)
                {
                    Log.d(TAG, "onErrorResponse: " + error.getCause());
                }
            }
        });

        VolleySingleton.getInstance(getApplicationContext()).addToRequestQueue(stringRequest);
    }

    void showLog(EvilTwinResponse evilTwinResponse, String action)
    {
        TextView logTitle = findViewById(R.id.logTitle);
        logTitle.setText(action + ":");
        List<EvilTwinResponse.Log> logList = Arrays.asList(evilTwinResponse.getLog());
        RecyclerView recyclerView = findViewById(R.id.evilTwinRecyclerView);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        EvilTwinAdapter evilTwinAdapter = new EvilTwinAdapter(logList, this);;
        recyclerView.setAdapter(evilTwinAdapter);
    }
}
