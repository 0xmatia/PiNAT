package com.pinat.pinatclient.ui.tabs;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;

import com.pinat.pinatclient.R;

import static android.content.Intent.getIntent;

/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentTab1 extends Fragment {
    @Override
    public View onCreateView(
            @NonNull LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState)
    {
        String response = getArguments().getString("devices");
        Log.d("Utils", response);
        return inflater.inflate(R.layout.fragment_tab1, container, false);
    }
}