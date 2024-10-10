package com.example.demo.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import java.io.*;
import java.net.Socket;

import com.example.demo.model.SysStat;
import com.example.demo.model.Session;
import com.example.demo.repository.SysStatRepository;
import com.example.demo.repository.SessionRepository;
import com.example.demo.util.CircularQueue;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

@Service
public class TcpClientService {

    private Socket socket;
    private BufferedReader reader;
    private PrintWriter writer;
    private static final String SERVER_IP = "192.168.0.12";
    private static final int SERVER_PORT = 5031;
    private static final int RECONNECT_DELAY_MS = 5000;

    private String lastReceivedData = "No data received yet";
    private volatile boolean stopConnection = false;

    private static final Logger logger = Logger.getLogger(TcpClientService.class.getName());

    private final CircularQueue<String> dataQueue = new CircularQueue<>(60);

    @Autowired
    private SysStatRepository sysStatRepository;

    @Autowired
    private SessionRepository sessionRepository;
    
    @PostConstruct
    public void init() {
        startConnection();
    }

    public void startConnection() {
        while (!stopConnection) {
            try {
                FileHandler fileHandler = new FileHandler("client.log", true);
                SimpleFormatter formatter = new SimpleFormatter();
                fileHandler.setFormatter(formatter);

                logger.addHandler(fileHandler);

                socket = new Socket(SERVER_IP, SERVER_PORT);
                System.out.println("Connected to the server");
                
                InputStream input = socket.getInputStream();
                reader = new BufferedReader(new InputStreamReader(input));

                OutputStream output = socket.getOutputStream();
                writer = new PrintWriter(output, true);
                
                Thread readerThread = new Thread(() -> {
                    String response;
                    ObjectMapper objectMapper = new ObjectMapper();
                    int getCnt=0;

                    try {
                        while (!socket.isClosed() && (response = reader.readLine()) != null) {
                            try {
                                lastReceivedData = response;
                                dataQueue.add(lastReceivedData);
                                /*
                                JsonNode rootNode = objectMapper.readTree(lastReceivedData);
                                JsonNode sysNode = rootNode.get("SYSSTAT");
                                JsonNode sesNode = rootNode.get("SESSION");
                                System.out.println("============================================================================================");
                                System.out.println("TEST: " + sysNode.get(9) + ", " + rootNode.get("TIME"));
    
                                if (sysNode.isArray() && sysNode.size() > 1) {
                                    JsonNode secondElement = sysNode.get(9);
                                    int value = secondElement.get("VALUE").asInt();
                                    System.out.println("9 idx VALUE: " + value);
                                }
                                for(int i=0 ; i<sesNode.size() ; i++) {
                                    if(!sesNode.get(i).get("SQL_ADDRESS").toString().replaceAll("\\s+", "").equals("\"0\""))
                                        System.out.println(sesNode.get(i).get("SQL_ADDRESS") + ", "  + sesNode.get(i).get("SID") + ", " + sesNode.get(i).get("SQL_TEXT"));
                                }
                                */
                                if(++getCnt == 20) {
                                    handleData(lastReceivedData);
                                    getCnt=0;
                                }

                                printDataQueue();
                            } catch (Exception e) {
                                System.out.println("JSON parsing error: " + e.getMessage().substring(e.getMessage().length()-100, e.getMessage().length()));
                                logger.severe("JSON parsing error: " + e.getMessage());
                                //System.out.println("Received JSON from server: " + response);
                                logger.severe("Received JSON from server: " + response);
                            } finally {
                                fileHandler.close();
                            }
                            
                            //System.out.println("Received from server: " + response);
                        }
                    } catch (IOException e) {
                        e.printStackTrace();
                        System.out.println("Connection reset or socket closed unexpectedly.");
                        attemptReconnect();
                    }
                });
                readerThread.start();

                Thread writerThread = new Thread(() -> {
                    try {
                        boolean isFirstRequest = true;
                        while (!socket.isClosed()) {
                            if (isFirstRequest) {
                                writer.println("first_request");
                                System.out.println("Sent to server: first_request");
                                isFirstRequest = false;
                            } else {
                                writer.println("get_data");
                                System.out.println("Sent to server: get_data");
                            }
                            
                            if (writer.checkError()) {
                                throw new IOException("Error writing to server. The connection might be closed.");
                            }
                            Thread.sleep(3000);
                        }
                    } catch (IOException e) {
                        System.out.println("IOException occurred: " + e.getMessage());
                        attemptReconnect(); 
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                        Thread.currentThread().interrupt();
                    }
                });
                writerThread.start();

                break;

            } catch (IOException e) {
                System.out.println("Failed to connect to the server. Retrying in 5 seconds...");
                try {
                    Thread.sleep(RECONNECT_DELAY_MS);
                } catch (InterruptedException interruptedException) {
                    interruptedException.printStackTrace();
                }
            }
        }
    }

    private void attemptReconnect() {
        System.out.println("Attempting to reconnect...");
        closeSocket();
        startConnection();
    }

    public String getLastReceivedData() {
        return lastReceivedData;
    }

    public void sendMessageToServer(String message) {
        writer.println(message);
        System.out.println("Sent to server: " + message);
    }

    public LinkedList<String> getDataQueue() {
        return dataQueue.getAll();
    }

    public void printDataQueue() {
        LinkedList<String> queueData = dataQueue.getAll();
        
        System.out.println("============================================================");
        for (int i = 0; i < queueData.size(); i++) {
            System.out.printf("Queue [%2d]: %s ...\n", i + 1, queueData.get(i).substring(0, 30));
        }
        System.out.println("============================================================");
    }

    public void closeSocket() {
        try {
            if (socket != null && !socket.isClosed()) {
                socket.close();
                System.out.println("Socket closed due to error or disconnection.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @PreDestroy
    public void cleanup() {
        closeSocket();
    }
    
    private void handleData(String jsonData) {
        ObjectMapper objectMapper = new ObjectMapper();
        try {
            JsonNode rootNode = objectMapper.readTree(jsonData);

            JsonNode sysstatNode = rootNode.get("SYSSTAT");

            if (sysstatNode != null && sysstatNode.isArray()) {

                List<SysStat> sysStatList = new ArrayList<>();
                
                for (JsonNode node : sysstatNode) {
                    SysStat sysStat = new SysStat();
                    sysStat.setInstNo(1001);
                    sysStat.setLogtime(rootNode.get("TIME").asText());
                    sysStat.setIndx(node.get("INDX").asInt());
                    sysStat.setValue(node.get("VALUE").asInt());
                    sysStat.setSys(node.get("SYS").asInt());
                    
                    sysStatList.add(sysStat);
                }
                
                sysStatRepository.saveAll(sysStatList);
            }

            JsonNode sessionNode = rootNode.get("SESSION");
            if (sessionNode != null && sessionNode.isArray()) {

                List<Session> sessionList = new ArrayList<>();

                for (JsonNode node : sessionNode) {
                    Session session = new Session();
                    session.setInstNo(1001);
                    session.setLogtime(rootNode.get("TIME").asText());
                    session.setSid(node.get("SID").asInt());
                    session.setSerial(node.get("SERIAL").asInt());
                    session.setUsername(node.get("USERNAME").asText());
                    session.setStatus(node.get("STATUS").asText());
                    session.setSchemaname(node.get("SCHEMANAME").asText());
                    session.setOsUser(node.get("OSUSER").asText());
                    session.setProcess(node.get("PROCESS").asText());
                    session.setMachine(node.get("MACHINE").asText());
                    session.setPort(node.get("PORT").asInt());
                    session.setTerminal(node.get("TERMINAL").asText());
                    session.setProgram(node.get("PROGRAM").asText());
                    session.setSqlAddress(node.get("SQL_ADDRESS").asText());
                    session.setSqlId(node.get("SQL_ID").asText());
                    session.setSqlText(node.get("SQL_TEXT").asText());
                    session.setModule(node.get("MODULE").asText());
                    session.setAction(node.get("ACTION").asText());
                    session.setClientInfo(node.get("CLIENT_INFO").asText());
                    session.setLogonTime(node.get("LOGON_TIME").asText());
                    session.setEvent(node.get("EVENT").asInt());
                    session.setP1(node.get("P1").asInt());
                    session.setP1text(node.get("P1TEXT").asText());
                    session.setP2(node.get("P2").asInt());
                    session.setP2text(node.get("P2TEXT").asText());
                    session.setP3(node.get("P3").asInt());
                    session.setP3text(node.get("P3TEXT").asText());
                    session.setBlockingSessionStatus(node.get("BLOCKING_SESSION_STATUS").asText());
                    session.setBlockingInstance(node.get("BLOCKING_INSTANCE").asInt());
                    session.setBlockingSession(node.get("BLOCKING_SESSION").asInt());
                    session.setFinalBlockingSessionStatus(node.get("FINAL_BLOCKING_SESSION_STATUS").asText());
                    session.setFinalBlockingInstance(node.get("FINAL_BLOCKING_INSTANCE").asInt());
                    session.setFinalBlockingSession(node.get("FINAL_BLOCKING_SESSION").asInt());

                    sessionList.add(session);
                }

                sessionRepository.saveAll(sessionList);
            }

        } catch (Exception e) {
            e.printStackTrace();
            logger.severe("Error processing JSON data: " + e.getMessage());
        }
    }
}