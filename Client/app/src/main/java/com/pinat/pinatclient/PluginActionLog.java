package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;
import android.util.TypedValue;
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
                            showLog(logEntries, plugin, action);
                        } catch (JSONException e) {
                            Log.d(TAG, "onResponse: nothing to show");
                            TextView title = findViewById(R.id.log_title);
                            title.setTextSize(TypedValue.COMPLEX_UNIT_SP, 14);
                            try {
                                String status = response.getString("status");
                                if (status.equals("success"))
                                {
                                    title.setText("Action completed successfully, that's all we know.");
                                }
                                else
                                {
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
                if (error != null) {
                    Log.d(TAG, "onErrorResponse: " + error.getMessage());
                }
            }
        });

        VolleySingleton.getInstance(getApplicationContext()).addToRequestQueue(request);
    }

    void showLog(List<SimpleLogEntry> logs, String plugin, String action)
    {
        TextView logTitle = findViewById(R.id.log_title);
        logTitle.setText(action+": " + plugin);
        RecyclerView recyclerView = findViewById(R.id.action_log_recycler_view);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        RootActionsAdapter rootActionsAdapter = new RootActionsAdapter(logs, this);
        recyclerView.setAdapter(rootActionsAdapter);
    }
}
