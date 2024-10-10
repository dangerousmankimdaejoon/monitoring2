package com.example.demo.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.example.demo.model.StatName;
import com.example.demo.repository.StatNameRepository;

import java.util.List;

@Service
public class StatService {
    
    @Autowired
    private StatNameRepository statNameRepository;

    public List<StatName> getAllStatNames() {
        return statNameRepository.findAll();
    }
}