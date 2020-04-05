package com.pinat.pinatclient;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.google.gson.Gson;
import com.pinat.pinatclient.Adapters.ActionViewAdapter;
import com.pinat.pinatclient.Adapters.PluginActionsListAdapter;
import com.pinat.pinatclient.models.PluginActionModel;
import com.pinat.pinatclient.utils.Constants;
import com.pinat.pinatclient.utils.VolleySingleton;

import java.util.Arrays;

public class PluginActions extends AppCompatActivity {

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
        String url = Constants.ENDPOINT + "/" + plugin;

        Log.d(TAG, "onCreate: " + url);
        // make a request
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Log.d(TAG, "onResponse: " + response);
                        Gson gson = new Gson();
                        PluginActionModel pluginActionModel = gson.fromJson(response, PluginActionModel.class);
                        showActions(pluginActionModel.getActions(), plugin);
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

    void showActions(final String[] actions, final String plugin)
    {
        RecyclerView recyclerView = findViewById(R.id.plugin_action_recycler_view);
        PluginActionsListAdapter adapter = new PluginActionsListAdapter(Arrays.asList(actions), CONTEXT);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(CONTEXT));
        recyclerView.setAdapter(adapter);


        adapter.setOnItemClickListener(new PluginActionsListAdapter.ClickListener() {
            @Override
            public void onItemClick(int position, View v) {
                Log.d(TAG, "onItemClick: " + actions[position]);
                Intent intent = new Intent(CONTEXT, ActionLog.class);
                intent.putExtra("action", actions[position]);
                intent.putExtra("plugin", plugin);
                startActivity(intent);
            }
        });
    }
}
