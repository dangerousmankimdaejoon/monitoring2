package com.example.demo.controller;

import com.example.demo.service.TcpClientService;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.util.List;

@RestController
@RequestMapping("/api")
public class DataController {

    private final TcpClientService tcpClientService;

    public DataController(TcpClientService tcpClientService) {
        this.tcpClientService = tcpClientService;
    }

    @GetMapping("/data")
    public String getData() {
        return tcpClientService.getLastReceivedData();
    }

    @GetMapping("/dataQueue")
    public List<String> getDataQueue() {
        return tcpClientService.getDataQueue();
    }
}