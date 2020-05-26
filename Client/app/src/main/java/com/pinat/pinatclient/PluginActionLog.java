package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;
import android.util.TypedValue;
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


public class PluginActionLog extends AppCompatActivity {

    private static final String TAG = "ActionLog";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_action_log);

        Bundle params = getIntent().getExtras();
        if (params == null) return;
        final String plugin = params.getString("plugin");
        final String action = params.getString("action");

        String url = Constants.ENDPOINT + "/plugin/" + plugin + "/" + action;
        Log.d(TAG, "onCreate: " + url);
        verifyArgs(url, action, plugin);
    }

    void verifyArgs(final String url, final String action, final String plugin) {
        final List<String> args = new LinkedList<>();
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            String status = response.getString("status");
                            if (status.equals("success")) {
                                JSONArray jsonArray = response.getJSONArray("args");
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    args.add(jsonArray.get(i).toString());
                                }
                                makeRequest(url, action, plugin, args);
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
                    Log.e(TAG, "onErrorResponse: Failure:" + error.getMessage());

                }
            }
        });
        VolleySingleton.getInstance(this).addToRequestQueue(request);
    }

    void makeRequest(final String url, final String action, final String plugin, List<String> args) {
        //At this point I request arguments from the user, but at this point this option is not supported.
        if (args.size() != 0) {
        } //do stuff
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.POST, url, null,
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        List<SimpleLogEntry> logEntries = new ArrayList<>();
                        Log.d(TAG, "onResponse: " + response);
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
                            showLog(logEntries, plugin, action);
                        } catch (JSONException e) {
                            stopLoading();
                            Log.d(TAG, "onResponse: nothing to show");
                            TextView title = findViewById(R.id.log_title);
                            title.setTextSize(TypedValue.COMPLEX_UNIT_SP, 14);
                            try {
                                String status = response.getString("status");
                                if (status.equals("success")) {
                                    title.setText("Action completed successfully, that's all we know.");
                                } else {
                                    title.setText("Something went wrong: " + status);
                                }

                            } catch (JSONException ex) {
                                stopLoading();
                                ex.printStackTrace();
                                title.setText("Unknown error.");
                            }
                        }
                    }
                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                if (error != null) {
                    stopLoading();
                    Log.d(TAG, "onErrorResponse: " + error.getMessage());
                }
            }
        });

        VolleySingleton.getInstance(getApplicationContext()).addToRequestQueue(request);
    }

    void showLog(List<SimpleLogEntry> logs, String plugin, String action) {
        stopLoading();
        TextView logTitle = findViewById(R.id.log_title);
        logTitle.setText(action + ": " + plugin);
        RecyclerView recyclerView = findViewById(R.id.action_log_recycler_view);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        RootActionsAdapter rootActionsAdapter = new RootActionsAdapter(logs, this);
        recyclerView.setAdapter(rootActionsAdapter);
    }

    void stopLoading() {
        // Stop loading symbol
        ProgressBar pb = findViewById(R.id.progressBarPluginActionLog);
        pb.setVisibility(View.INVISIBLE);
        //Show recycle view + title
        RecyclerView recyclerView = findViewById(R.id.action_log_recycler_view);
        recyclerView.setVisibility(View.VISIBLE);
        TextView view = findViewById(R.id.log_title);
        view.setVisibility(View.VISIBLE);
    }
}
