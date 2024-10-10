package com.example.demo.model;

import java.io.Serializable;
import java.util.Objects;

public class SessionId implements Serializable {

    private int instNo;
    private String logtime;
    private int sid;

    public SessionId() {}

    public SessionId(int instNo, String logtime, int sid) {
        this.instNo = instNo;
        this.logtime = logtime;
        this.sid = sid;
    }

    public int getInstNo() {
        return instNo;
    }

    public void setInstNo(int instNo) {
        this.instNo = instNo;
    }

    public String getLogtime() {
        return logtime;
    }

    public void setLogtime(String logtime) {
        this.logtime = logtime;
    }

    public int getSid() {
        return sid;
    }

    public void setSid(int sid) {
        this.sid = sid;
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SessionId that = (SessionId) o;
        return instNo == that.instNo && Objects.equals(logtime, that.logtime) && sid == that.sid;
    }

    @Override
    public int hashCode() {
        return Objects.hash(instNo, logtime, sid);
    }
}