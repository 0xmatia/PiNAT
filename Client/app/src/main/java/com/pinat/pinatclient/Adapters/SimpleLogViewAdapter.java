package com.pinat.pinatclient.Adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.pinat.pinatclient.R;
import com.pinat.pinatclient.models.SimpleLogEntry;

import java.util.List;

public class SimpleLogViewAdapter extends RecyclerView.Adapter<SimpleLogViewAdapter.LogCardHolder> {
    List<SimpleLogEntry> log;
    Context mContext;

    public SimpleLogViewAdapter(List<SimpleLogEntry> logs, Context mContext) {
        this.log = logs;
        this.mContext = mContext;
    }

    protected static class LogCardHolder extends RecyclerView.ViewHolder {
        TextView timeStamp;
        TextView logContent;

        public LogCardHolder(@NonNull View itemView) {
            super(itemView);
            this.timeStamp = itemView.findViewById(R.id.timeStampID);
            this.logContent = itemView.findViewById(R.id.logContent);
        }

    }

    @NonNull
    @Override
    public LogCardHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(mContext);
        View view = layoutInflater.inflate(R.layout.log_card, parent, false);
        return new LogCardHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull LogCardHolder holder, int position) {
        SimpleLogEntry logEntry = log.get(position);
        holder.timeStamp.setText(logEntry.getTimestamp());
        holder.logContent.setText(logEntry.getLog());
    }

    @Override
    public int getItemCount() {
        return log.size();
    }

}
