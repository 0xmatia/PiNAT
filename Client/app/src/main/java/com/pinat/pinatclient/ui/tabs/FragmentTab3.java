package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.Adapters.Tab3Adapter;
import com.pinat.pinatclient.R;

import java.util.Arrays;
import java.util.List;

/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentTab3 extends Fragment {

    private static Context mContext;
    private static final String TAG = "FragmentTab3";

    public FragmentTab3(Context context) {
        super();
        mContext = context;
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_tab3, container, false);

        // Get plugin list
        int len = getArguments().getString("plugins").length();
        String[] plugins = getArguments().getString("plugins").
                substring(1, len - 1).split(",");
        List<String> pluginList = Arrays.asList(plugins);

        updateTab(pluginList, rootView);
        return rootView;
    }

    public void updateTab(final List<String> pluginList, View rootView) {
        RecyclerView recyclerView = rootView.findViewById(R.id.pluginRecyclerView);
        Tab3Adapter tab3Adapter = new Tab3Adapter(pluginList, mContext);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(mContext));

        tab3Adapter.setOnItemClickListener(new Tab3Adapter.ClickListener() {
            @Override
            public void onItemClick(int position, View v) {
                Log.d(TAG, "onItemClick: Clicked: " + pluginList.get(position));
            }

        });
        recyclerView.setAdapter(tab3Adapter);
    }
}