package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.Adapters.ActionViewAdapter;
import com.pinat.pinatclient.RootActionLog;
import com.pinat.pinatclient.R;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentTab2 extends Fragment {

    private static Context context;
    private static final String TAG = "FragmentTab2";

    public FragmentTab2(Context c) {
        context = c;
    }

    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.fragment_tab2, container, false);

        // Convert to list of actions. VERY HACKY
        int len = getArguments().getString("actions").length();
        String[] actions = getArguments().getString("actions").
                substring(1, len - 1).split(", ");
        List<String> actionList = new LinkedList<>(Arrays.asList(actions));
        for (int i = 0; i< actionList.size(); i++) {
            if (actionList.get(i).equals("network_status"))
            {
                actionList.remove(i);
            }
        }
        Log.d(TAG, "Actions: " + actionList);
        updateTab(actionList, rootView);
        return rootView;
    }

    public void updateTab(final List<String> actionList, View rootView) {
        RecyclerView recyclerView = rootView.findViewById(R.id.actions_recycler_view);
        recyclerView.hasFixedSize();
        recyclerView.setLayoutManager(new LinearLayoutManager(context));
        ActionViewAdapter actionViewAdapter = new ActionViewAdapter(actionList, context);;
        actionViewAdapter.setOnItemClickListener(new ActionViewAdapter.ClickListener() {
            @Override
            public void onItemClick(int position, View v) {
                Log.d(TAG, "onItemClick: Clicked: " + actionList.get(position));
                Intent intent = new Intent(context, RootActionLog.class);
                Bundle bundle = new Bundle();
                bundle.putString("action", actionList.get(position));
                intent.putExtras(bundle);
                startActivity(intent);
            }

        });
        recyclerView.setAdapter(actionViewAdapter);
    }

}