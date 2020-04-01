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
public class FragmentTab2 extends Fragment {

    private static Context context;

    public FragmentTab2(Context c) {
        context = c;
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState)
    {
        View rootView =  inflater.inflate(R.layout.fragment_tab2, container, false);

        // Convert to list of actions
        int len = getArguments().getString("actions").length();
        String[] actions = getArguments().getString("actions").
                substring(1, len-1).split(",");
        List<String> actionList = Arrays.asList(actions);


        updateTab(actionList, rootView);
        return  rootView;
    }

    public void updateTab(List<String> actionList, View rootView)
    {
        RecyclerView recyclerView = rootView.findViewById(R.id.actions_recycler_view);
        TabAdapter tabAdapter;
        recyclerView.hasFixedSize();
        View.OnClickListener onClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Extract the value from the card
                TextView cardText = v.findViewById(R.id.cardText);
                String text = cardText.getText().toString();
                Toast.makeText(context, "LOL: " + text, Toast.LENGTH_SHORT).show();
            }
        };

        recyclerView.setLayoutManager(new LinearLayoutManager(context));
        tabAdapter = new TabAdapter(actionList, context, onClickListener);
        recyclerView.setAdapter(tabAdapter);
    }
}