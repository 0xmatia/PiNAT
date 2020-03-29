package com.pinat.pinatclient.ui.tabs;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import com.google.gson.Gson;
import com.pinat.pinatclient.R;
import com.pinat.pinatclient.models.Response;

import java.util.Arrays;

/**
 * A [FragmentPagerAdapter] that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
public class SectionsPagerAdapter extends FragmentPagerAdapter {

    private static String SERVER_RESPONSE;
    @StringRes
    private static final int[] TAB_TITLES = new int[]{R.string.tab_text_1, R.string.tab_text_2,
            R.string.tab_text_3};
    private final Context mContext;

    public SectionsPagerAdapter(Context context, FragmentManager fm, String response) {
        super(fm);
        mContext = context;
        SERVER_RESPONSE = response;
    }

    @Override
    public Fragment getItem(int position) {
        // getItem is called to instantiate the fragment for the given page.
        // Return a PlaceholderFragment (defined as a static inner class below).
        Fragment fragment = null;
        Bundle args = new Bundle();
        Gson gson = new Gson();
        Response response = gson.fromJson(SERVER_RESPONSE, Response.class); //parse response

        switch (position)
        {
            case 0:
            {
                args.putString("devices", Arrays.toString(response.getEntities()));
                fragment = new FragmentTab1();
                fragment.setArguments(args);
                break;
            }
            case 1:
            {
                fragment = new FragmentTab2();
                break;
            }
            case 2:
            {
                fragment = new FragmentTab3();
                break;
            }
        }
        return fragment;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        return mContext.getResources().getString(TAB_TITLES[position]);
    }

    @Override
    public int getCount() {
        // Show 3 total pages.
        return 3;
    }
}