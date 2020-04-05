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
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.JsonRequest;
import com.android.volley.toolbox.StringRequest;
import com.google.gson.Gson;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.pinat.pinatclient.Adapters.SimpleLogViewAdapter;
import com.pinat.pinatclient.models.PluginActionModel;
import com.pinat.pinatclient.models.SimpleLogEntry;
import com.pinat.pinatclient.utils.Constants;
import com.pinat.pinatclient.utils.VolleySingleton;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public class ActionLog extends AppCompatActivity {

    private static final String TAG = "ActionLog";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_action_log);

        Bundle params = getIntent().getExtras();
        if (params == null) return;
        final String plugin = params.getString("plugin");
        final String action = params.getString("action");
        String url = Constants.ENDPOINT + "/" + plugin + "/" + action;

        Log.d(TAG, "onCreate: " + url);
        // make a request
        JsonObjectRequest stringRequest = new JsonObjectRequest(Request.Method.GET, url, null,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        List<SimpleLogEntry> logEntries = new ArrayList<>();
                        try {
                            JSONArray jsonArray = response.getJSONArray("result");
                            for(int i = 0; i < jsonArray.length(); i++)
                            {
                                SimpleLogEntry simpleLogEntry = new SimpleLogEntry();
                                String log = "";
                                JSONObject objectInArray = jsonArray.getJSONObject(i);
                                JSONArray keys = objectInArray.names();
                                for (int j = 0; j<keys.length(); j++)
                                {
                                    String key = keys.getString(j);
                                    String value = objectInArray.get(keys.getString(j)).toString();
                                    if (key.equals("time") || key.equals("timestamp") || key.equals("Timestamp"))
                                    {
                                        Log.d(TAG, "onResponse bla: " + key);
                                        simpleLogEntry.setTimestamp(value);
                                    }
                                    else {
                                        log += key + ": " + value + "\n";
                                    }
                                }
                                simpleLogEntry.setLog(log);
                                Log.d(TAG, "onResponse bla: " + simpleLogEntry);
                                logEntries.add(simpleLogEntry);
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        showLog(logEntries, plugin, action);
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                if (error != null)
                {
                    Log.e(TAG, "onErrorResponse: Failure:");
                    error.getCause();
                }
            }
        });
        VolleySingleton.getInstance(this).addToRequestQueue(stringRequest);
    }

    void showLog(List<SimpleLogEntry> logs, String plugin, String action)
    {
        TextView logTitle = findViewById(R.id.log_title);
        logTitle.setText(action+": " + plugin);
        RecyclerView recyclerView = findViewById(R.id.action_log_recycler_view);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        SimpleLogViewAdapter evilTwinAdapter = new SimpleLogViewAdapter(logs, this);;
        recyclerView.setAdapter(evilTwinAdapter);
    }
}
