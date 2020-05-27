package com.pinat.pinatclient.Adapters;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.R;

import java.util.List;

public class TabAdapterNoListener extends RecyclerView.Adapter<TabAdapterNoListener.DevicesViewHolder> {

    List<String> itemTextList;
    Context mContext;


    public TabAdapterNoListener(List<String> itemTextList, Context mContext) {
        this.itemTextList = itemTextList;
        this.mContext = mContext;
    }

    protected static class DevicesViewHolder extends RecyclerView.ViewHolder
    {
        TextView itemText;
        public DevicesViewHolder(@NonNull View itemView) {
            super(itemView);
            this.itemText = itemView.findViewById(R.id.cardText);
        }

    }

    @NonNull
    @Override
    public DevicesViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(mContext);
        View view = layoutInflater.inflate(R.layout.item_card, parent, false);
        return new DevicesViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull DevicesViewHolder holder, int position) {
        String mac = itemTextList.get(position);
        holder.itemText.setText(mac);
    }

    @Override
    public int getItemCount() {
       return itemTextList.size();
    }

}
