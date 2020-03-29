package com.pinat.pinatclient.models;

import com.google.gson.annotations.SerializedName;

public class Response {
    private String status;
    @SerializedName("connected entities")
    private String[] entities;
    private String[] actions;
    private String[] plugins;

    public String getStatus() {
        return status;
    }

    public String[] getEntities() {
        return entities;
    }

    public String[] getActions() {
        return actions;
    }

    public String[] getPlugins() {
        return plugins;
    }

    public Response(String status, String entities[], String[] actions, String[] plugins) {
        this.status = status;
        this.entities = entities;
        this.actions = actions;
        this.plugins = plugins;
    }
}
