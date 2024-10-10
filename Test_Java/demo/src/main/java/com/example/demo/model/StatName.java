package com.example.demo.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

@Entity
@Table(name = "statname")
public class StatName {
    
    @Id
    @Column(name = "statistic_no")
    private int statisticNo;
    private String name;
    
    public int getStatisticNo() {
        return statisticNo;
    }

    public void setStatisticNo(int statisticNo) {
        this.statisticNo = statisticNo;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}