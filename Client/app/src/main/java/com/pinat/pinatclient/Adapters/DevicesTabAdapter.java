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

public class DevicesTabAdapter extends RecyclerView.Adapter<DevicesTabAdapter.DevicesViewHolder> {

    List<String> deviceMacs;
    Context mContext;

    public DevicesTabAdapter(List<String> deviceMacs, Context mContext) {
        this.deviceMacs = deviceMacs;
        this.mContext = mContext;
    }

    protected static class DevicesViewHolder extends RecyclerView.ViewHolder
    {
        TextView mac;
        public DevicesViewHolder(@NonNull View itemView) {
            super(itemView);
            this.mac = itemView.findViewById(R.id.deviceMac);
        }
    }

    @NonNull
    @Override
    public DevicesViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(mContext);
        View view = layoutInflater.inflate(R.layout.device_card, parent, false);
        return new DevicesViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull DevicesViewHolder holder, int position) {
        String mac = deviceMacs.get(position);
        holder.mac.setText(mac);
    }

    @Override
    public int getItemCount() {
       return deviceMacs.size();
    }

}
