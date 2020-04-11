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
import com.pinat.pinatclient.models.SimpleLogEntry;

import java.util.List;

public class RootActionsAdapter extends RecyclerView.Adapter<RootActionsAdapter.LogCardHolder> {
    //Todo: maybe change its name - it can also be an adapter of other log activities
    List<SimpleLogEntry> log;
    Context mContext;
    private static final String TAG = "RootActionsAdapter";

    public RootActionsAdapter(List<SimpleLogEntry> logs, Context mContext) {
        this.log = logs;
        this.mContext = mContext;
    }

    protected static class LogCardHolder extends RecyclerView.ViewHolder
    {
        TextView timeStamp;
        TextView logContent;
        View divider;
        public LogCardHolder(@NonNull View itemView) {
            super(itemView);
            this.timeStamp = itemView.findViewById(R.id.timeStampID);
            this.logContent = itemView.findViewById(R.id.logContent);
            this.divider = itemView.findViewById(R.id.dividerRootAction);
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
        if (holder.timeStamp.getText().equals("-"))
        {
            Log.d(TAG, "LogCardHolder: here");
            if (holder.timeStamp.getParent() != null)
            {
                ((ViewGroup) holder.timeStamp.getParent()).removeView(holder.timeStamp);
            }
            if (holder.divider.getParent() != null)
            {
                ((ViewGroup) holder.divider.getParent()).removeView(holder.divider);
            }
        }
        holder.logContent.setText(logEntry.getLog());
    }

    @Override
    public int getItemCount() {
       return log.size();
    }

}
