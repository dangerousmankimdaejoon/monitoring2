package com.example.demo.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import com.example.demo.model.StatName;
import com.example.demo.service.StatService;

import java.util.List;

@RestController
public class StatController {
    
    @Autowired
    private StatService statService;

    @GetMapping("/statnames")
    public List<StatName> getStatNames() {
        return statService.getAllStatNames();
    }
}