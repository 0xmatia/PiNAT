package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.pinat.pinatclient.Adapters.PluginActionsListAdapter;
import com.pinat.pinatclient.utils.Constants;
import com.pinat.pinatclient.utils.VolleySingleton;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.util.LinkedList;
import java.util.List;

public class PluginActionList extends AppCompatActivity {

    private static Context CONTEXT = null;
    private static final String TAG = "PluginActions";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_plugin_actions);
        CONTEXT = this;

        Bundle params = getIntent().getExtras();
        if (params == null) return;
        final String plugin = params.getString("plugin"); // Get response, pass to the adapter
        String url = Constants.ENDPOINT + "/plugin/" + plugin;

        Log.d(TAG, "onCreate: " + url);
        final List<String> actions = new LinkedList<>();
        // make a request
        JsonObjectRequest stringRequest = new JsonObjectRequest(Request.Method.GET, url, null,
                new Response.Listener<JSONObject> () {
                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, "onResponse: " + response);
                        try {
                            String status = response.getString("status");
                            if (status.equals("success"))
                            {
                                JSONArray jsonArray = response.getJSONArray("actions");
                                for (int i = 0; i < jsonArray.length(); i++)
                                {
                                    actions.add(jsonArray.get(i).toString());
                                }
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                            Toast.makeText(PluginActionList.this,
                                    "Something wrong and unexpected has happened",
                                    Toast.LENGTH_SHORT).show();
                        }
                        showActions(actions, plugin);
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
       VolleySingleton.getInstance(this).addToRequestQueue(stringRequest);
    }

    void showActions(final List<String> actions, final String plugin)
    {
        RecyclerView recyclerView = findViewById(R.id.plugin_action_recycler_view);
        PluginActionsListAdapter adapter = new PluginActionsListAdapter(actions, CONTEXT);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(CONTEXT));
        recyclerView.setAdapter(adapter);


        adapter.setOnItemClickListener(new PluginActionsListAdapter.ClickListener() {
            @Override
            public void onItemClick(int position, View v) {
                Intent intent = new Intent(CONTEXT, PluginActionLog.class);
                intent.putExtra("action", actions.get(position));
                intent.putExtra("plugin", plugin);
                startActivity(intent);
            }
        });
    }
}
