package com.pinat.pinatclient.Adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.R;
import java.util.List;

public class TabAdapter extends RecyclerView.Adapter<TabAdapter.DevicesViewHolder> {

    List<String> itemTextList;
    Context mContext;
    View.OnClickListener listener;


    public TabAdapter(List<String> itemTextList, Context mContext, View.OnClickListener onClickListener) {
        this.itemTextList = itemTextList;
        this.mContext = mContext;
        this.listener = onClickListener;
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
        view.setOnClickListener(listener);
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
