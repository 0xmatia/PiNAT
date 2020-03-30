package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.pinat.pinatclient.R;

/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentTab1 extends Fragment {

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

        LinearLayout linearLayout = (LinearLayout) rootView.findViewById(R.id.devicesLayout);

        //Todo: view in a nice way, maybe in a cardView
        for (String mac : macs)
        {
            TextView textView = new TextView(context);
            textView.setText(mac);
            linearLayout.addView(textView);

        }
        return rootView;
    }
}