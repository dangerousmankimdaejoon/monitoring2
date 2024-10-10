package com.example.demo.model;

import java.io.Serializable;
import java.util.Objects;

public class SysStatId implements Serializable {

    private int instNo;
    private String logtime;
    private int indx;

    public SysStatId() {}

    public SysStatId(int instNo, String logtime, int indx) {
        this.instNo = instNo;
        this.logtime = logtime;
        this.indx = indx;
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

    public int getIndx() {
        return indx;
    }

    public void setIndx(int indx) {
        this.indx = indx;
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        SysStatId sysStatId = (SysStatId) o;
        return instNo == sysStatId.instNo && Objects.equals(logtime, sysStatId.logtime) && indx == sysStatId.indx;
    }

    @Override
    public int hashCode() {
        return Objects.hash(instNo, logtime, indx);
    }
}