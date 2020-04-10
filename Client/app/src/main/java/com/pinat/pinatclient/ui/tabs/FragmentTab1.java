package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.pinat.pinatclient.Adapters.TabAdapterNoListener;
import com.pinat.pinatclient.General;
import com.pinat.pinatclient.R;
import com.pinat.pinatclient.models.SimpleLogEntry;
import com.pinat.pinatclient.utils.Constants;
import com.pinat.pinatclient.utils.VolleySingleton;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentTab1 extends Fragment {

    private static final String TAG = "FragmentTab1";
    private static Context context;

    public FragmentTab1(Context c) {
        super();
        context = c;
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_tab1, container, false);

        getDevicesList(rootView);
        return rootView;
    }

    public void updateTab(final List<String> macs, View rootView) {
        if (macs == null) {
            Log.d(TAG, "updateTab: Why is the list null?");
            return;
        }
        RecyclerView recyclerView = rootView.findViewById(R.id.devicesRecyclerView);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(context));

        TabAdapterNoListener tabAdapter = new TabAdapterNoListener(macs, context);
        recyclerView.setAdapter(tabAdapter);
    }

    private void getDevicesList(final View rootView) {
        // - This is the url for network status. I know we don't need to supply any args
        String url = Constants.ENDPOINT + "/action/network_status";
        final List<String> list = new ArrayList<>();
        JsonObjectRequest request = new JsonObjectRequest(Request.Method.POST, url, null,
                new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            JSONArray jsonArray = response.getJSONArray("result");
                            if (jsonArray != null) {
                                for (int i = 0; i < jsonArray.length(); i++) {
                                    list.add(jsonArray.get(i).toString());
                                }
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                        Log.d(TAG, "onResponse: " + list);
                        updateTab(list, rootView);
                    }

                }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                if (error != null) {
                    Log.e(TAG, "onErrorResponse: Failure:" + error.getMessage());

                }
            }
        });
        VolleySingleton.getInstance(context).addToRequestQueue(request);
    }

}