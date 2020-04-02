package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.Adapters.TabAdapterNoListener;
import com.pinat.pinatclient.R;

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
            Bundle savedInstanceState)
    {
        View rootView = inflater.inflate(R.layout.fragment_tab1, container, false);

        int len = getArguments().getString("devices").length();
        String[] macs = getArguments().getString("devices").
                substring(1, len-1).split(",");

        List<String> macList = Arrays.asList(macs);

        updateTab(macList, rootView);
        return rootView;
    }

    public void updateTab(final List<String> macs, View rootView)
    {
        RecyclerView recyclerView = rootView.findViewById(R.id.devicesRecyclerView);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(context));

        TabAdapterNoListener tabAdapter = new TabAdapterNoListener(macs, context);
        recyclerView.setAdapter(tabAdapter);
    }

}