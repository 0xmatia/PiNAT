package com.pinat.pinatclient.models;


public class SimpleLogEntry {
    private String timestamp;
    private String log;

    public SimpleLogEntry() {

    }

    public void setLog(String log) {
        this.log = log;
    }

    public void setTimestamp(String timestamp) {
        this.timestamp = timestamp;
    }

    public String getTimestamp() {
        return timestamp;
    }

    public String getLog() {
        return log;
    }

    @Override
    public String toString() {
        return "SimpleLogEntry{" +
                "timestamp='" + timestamp + '\'' +
                ", log='" + log + '\'' +
                '}';
    }
}
