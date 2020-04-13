package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.pinat.pinatclient.Adapters.RootActionsAdapter;
import com.pinat.pinatclient.models.SimpleLogEntry;
import com.pinat.pinatclient.utils.Constants;
import com.pinat.pinatclient.utils.VolleySingleton;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class RootActionLog extends AppCompatActivity {
    private static final String TAG = "LogActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.root_action_result_activity);

        Bundle params = getIntent().getExtras();
        if (params == null) return;
        final String action = params.getString("action");
        Log.d(TAG, "onCreate: Action: " + action);

        // Make a request
        String url = Constants.ENDPOINT + "/action/" + action;
        Log.d(TAG, "onCreate: " + url);
        verifyArgs(url, action);

    }

    void verifyArgs(final String url, final String action) {
        final List<String> args = new LinkedList<>();
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            Log.d(TAG, "onResponse: BLU");
                            String status = response.getString("status");
                            if (status.equals("success")) {
                                Log.d(TAG, "onResponse: HEY@");
                                JSONArray jsonArray = response.getJSONArray("args");
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    args.add(jsonArray.get(i).toString());
                                }
                                Log.d(TAG, "onResponse: " + args);
                                makeRequest(url, action, args);
                            }

                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Log.d(TAG, "onResponse: " + args);
                    }

                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                if (error != null) {
                    Log.e(TAG, "onErrorResponse: Failure:" + error.getStackTrace());

                }
            }
        });
        VolleySingleton.getInstance(this).addToRequestQueue(request);
    }

    void makeRequest(final String url, final String action, List<String> args) {
        //At this point I request arguments from the user, but at this point this option is not supported.
        Log.d(TAG, "makeRequest: sdas");
        if (args.size() != 0) {
        } // do stuff
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.POST, url, null,
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        List<SimpleLogEntry> logEntries = new ArrayList<>();
                        try {
                            JSONArray jsonArray = response.getJSONArray("result");
                            for (int i = 0; i < jsonArray.length(); i++) {
                                SimpleLogEntry simpleLogEntry = new SimpleLogEntry();
                                String log = "";
                                JSONObject objectInArray = jsonArray.getJSONObject(i);
                                JSONArray keys = objectInArray.names();
                                for (int j = 0; j < keys.length(); j++) {
                                    String key = keys.getString(j);
                                    String value = objectInArray.get(keys.getString(j)).toString();
                                    if (key.equals("time") || key.equals("timestamp") || key.equals("Timestamp")) {
                                        Log.d(TAG, "onResponse bla: " + key);
                                        simpleLogEntry.setTimestamp(value);
                                    } else {
                                        log += key + ": " + value + "\n";
                                    }
                                }
                                simpleLogEntry.setLog(log);
                                if (simpleLogEntry.getTimestamp() == null) {
                                    simpleLogEntry.setTimestamp("-");
                                }
                                Log.d(TAG, "onResponse bla: " + simpleLogEntry);
                                logEntries.add(simpleLogEntry);
                            }
                            showLog(logEntries, action);
                        } catch (JSONException e) {
                            Log.d(TAG, "onResponse: nothing to show");
                            TextView title = findViewById(R.id.logTitle);
                            try {
                                String status = response.getString("status");
                                if (status.equals("success")) {
                                    title.setText("Action completed successfully, that's all we know.");
                                } else {
                                    title.setText("Something went wrong: " + status);
                                }

                            } catch (JSONException ex) {
                                ex.printStackTrace();
                                title.setText("Unknown error.");
                            }
                        }
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                stopLoading();
                if (error != null) {
                    Log.d(TAG, "onErrorResponse: " + error.getMessage());
                }
            }
        });

        VolleySingleton.getInstance(getApplicationContext()).addToRequestQueue(request);
    }

    void showLog(List<SimpleLogEntry> logs, String action) {
        stopLoading();
        TextView logTitle = findViewById(R.id.logTitle);
        logTitle.setText(action + ":");
        RecyclerView recyclerView = findViewById(R.id.rootActionsLogRecyclerView);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(getApplicationContext()));

        RootActionsAdapter rootActionsAdapter = new RootActionsAdapter(logs, getApplicationContext());
        recyclerView.setAdapter(rootActionsAdapter);
    }

    void stopLoading() {
        // Stop loading symbol
        ProgressBar pb = findViewById(R.id.progressBarRootActionLog);
        pb.setVisibility(View.INVISIBLE);
        //Show recycle view + title
        RecyclerView recyclerView = findViewById(R.id.rootActionsLogRecyclerView);
        recyclerView.setVisibility(View.VISIBLE);
        TextView view = findViewById(R.id.logTitle);
        view.setVisibility(View.VISIBLE);
    }
}
