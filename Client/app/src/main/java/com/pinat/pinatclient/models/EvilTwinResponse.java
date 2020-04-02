package com.pinat.pinatclient.models;

import com.google.gson.annotations.SerializedName;

public class EvilTwinResponse {
    private String status;
    private Log[] log;

    public EvilTwinResponse(String status, Log[] log) {
        this.status = status;
        this.log = log;
    }

    public String getStatus() {
        return status;
    }

    public Log[] getLog() {
        return log;
    }

    public static class Log
    {
        @SerializedName("SSID")
        private String ssid;
        @SerializedName("Time")
        private String timeStamp;

        public Log(String ssid, String timeStamp) {
            this.ssid = ssid;
            this.timeStamp = timeStamp;
        }

        public String getLogContent()
        {
            return "SSID: " + this.ssid;
        }

        public String getTimeStamp() {
            return timeStamp;
        }
    }
}
