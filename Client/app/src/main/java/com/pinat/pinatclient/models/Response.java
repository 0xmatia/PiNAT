package com.pinat.pinatclient.models;

import com.google.gson.annotations.SerializedName;

public class Response {
    private String status;
    private boolean online;
    private String[] actions;
    private String[] plugins;

    public Response(String status, boolean online, String[] actions, String[] plugins) {
        this.status = status;
        this.online = online;
        this.actions = actions;
        this.plugins = plugins;
    }

    public String getStatus() {
        return status;
    }

    public boolean isOnline() {
        return online;
    }

    public String[] getActions() {
        return actions;
    }

    public String[] getPlugins() {
        return plugins;
    }
}
