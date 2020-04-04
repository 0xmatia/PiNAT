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

public class SimpleCardListAdapter extends RecyclerView.Adapter<SimpleCardListAdapter.CardHolder> {

    public static ClickListener clickListener;
    List<String> cardText;
    Context mContext;

    public interface ClickListener {
        void onItemClick(int position, View v);
    }

    public SimpleCardListAdapter(List<String> cardText, Context mContext) {
        this.cardText = cardText;
        this.mContext = mContext;
    }

    protected static class CardHolder extends RecyclerView.ViewHolder
        implements View.OnClickListener
    {
        TextView itemText;
        public CardHolder(@NonNull View itemView) {
            super(itemView);
            itemView.setOnClickListener(this);
            this.itemText = itemView.findViewById(R.id.cardText);
        }

        @Override
        public void onClick(View v) {
            if (SimpleCardListAdapter.clickListener != null)
            {
                clickListener.onItemClick(getAdapterPosition(), v);
            }
        }
    }

    public void setOnItemClickListener(ClickListener clickListener) {
        this.clickListener = clickListener;
    }

    @NonNull
    @Override
    public CardHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(mContext);
        View view = layoutInflater.inflate(R.layout.item_card, parent, false);
        return new CardHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull CardHolder holder, int position) {
        String mac = cardText.get(position);
        holder.itemText.setText(mac);
    }

    @Override
    public int getItemCount() {
       return cardText.size();
    }

}
