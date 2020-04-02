package com.pinat.pinatclient.Adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.R;
import com.pinat.pinatclient.models.EvilTwinResponse;

import java.util.List;

public class EvilTwinAdapter extends RecyclerView.Adapter<EvilTwinAdapter.DevicesViewHolder> {
    //Todo: maybe change its name - it can also be an adapter of other log activities
    List<EvilTwinResponse.Log> log;
    Context mContext;

    public EvilTwinAdapter(List<EvilTwinResponse.Log> logs, Context mContext) {
        this.log = logs;
        this.mContext = mContext;
    }

    protected static class DevicesViewHolder extends RecyclerView.ViewHolder
    {
        TextView timeStamp;
        TextView logContent;
        public DevicesViewHolder(@NonNull View itemView) {
            super(itemView);
            this.timeStamp = itemView.findViewById(R.id.timeStampID);
            this.logContent = itemView.findViewById(R.id.logContent);
        }

    }

    @NonNull
    @Override
    public DevicesViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(mContext);
        View view = layoutInflater.inflate(R.layout.log_card, parent, false);
        return new DevicesViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull DevicesViewHolder holder, int position) {
        EvilTwinResponse.Log logEntry = log.get(position);
        holder.timeStamp.setText(logEntry.getTimeStamp());
        holder.logContent.setText(logEntry.getLogContent());
    }

    @Override
    public int getItemCount() {
       return log.size();
    }

}
