package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.Adapters.TabAdapter;
import com.pinat.pinatclient.R;

import java.util.Arrays;
import java.util.List;

/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentTab3 extends Fragment {

    private static Context mContext;

    public FragmentTab3(Context context) {
        super();
        mContext = context;
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState)
    {
        View rootView = inflater.inflate(R.layout.fragment_tab3, container, false);

        // Get plugin list
        int len = getArguments().getString("plugins").length();
        String[] plugins = getArguments().getString("plugins").
                substring(1, len-1).split(",");
        List<String> pluginList = Arrays.asList(plugins);

        updateTab(pluginList, rootView);
        return rootView;
    }

    public void updateTab(List<String> pluginList, View rootView)
    {
        RecyclerView recyclerView = rootView.findViewById(R.id.pluginRecyclerView);
        TabAdapter tabAdapter;
        recyclerView.hasFixedSize();
        View.OnClickListener onClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Extract the value from the card
                TextView cardText = v.findViewById(R.id.cardText);
                String text = cardText.getText().toString();
                Toast.makeText(mContext, "Sikee: " + text, Toast.LENGTH_SHORT).show();
            }
        };

        recyclerView.setLayoutManager(new LinearLayoutManager(mContext));
        tabAdapter = new TabAdapter(pluginList, mContext, onClickListener);
        recyclerView.setAdapter(tabAdapter);
    }
}