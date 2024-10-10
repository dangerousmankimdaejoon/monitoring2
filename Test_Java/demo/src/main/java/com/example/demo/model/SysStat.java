package com.example.demo.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.IdClass;
import jakarta.persistence.Table;


@Entity
@Table(name = "sysstat")
@IdClass(SysStatId.class)
public class SysStat {

    @Id
    @Column(name = "inst_no", nullable = false)
    private int instNo;
    
    @Id
    @Column(name = "logtime", nullable = false, length = 14)
    private String logtime;

    @Id
    @Column(name = "indx", nullable = false)
    private int indx;

    @Column(name = "value", nullable = false)
    private int value;

    @Column(name = "sys", nullable = false)
    private int sys;

    public SysStat() {}

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

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getSys() {
        return sys;
    }

    public void setSys(int sys) {
        this.sys = sys;
    }
}