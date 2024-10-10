package com.example.demo.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.IdClass;
import jakarta.persistence.Table;


@Entity
@Table(name = "session")
@IdClass(SessionId.class)
public class Session {

    @Id
    @Column(name = "inst_no", nullable = false)
    private int instNo;

    @Id
    @Column(name = "logtime", nullable = false, length = 14)
    private String logtime;

    @Id
    @Column(name = "sid", nullable = false)
    private int sid;

    @Column(name = "serial", nullable = false)
    private int serial;

    @Column(name = "username", length = 50)
    private String username;

    @Column(name = "status", length = 10)
    private String status;

    @Column(name = "schemaname", length = 50)
    private String schemaname;

    @Column(name = "osuser", length = 50)
    private String osUser;

    @Column(name = "process", length = 10)
    private String process;

    @Column(name = "machine", length = 50)
    private String machine;

    @Column(name = "port")
    private int port;

    @Column(name = "terminal", length = 50)
    private String terminal;

    @Column(name = "program", length = 100)
    private String program;

    @Column(name = "sql_address", length = 20)
    private String sqlAddress;

    @Column(name = "sql_id", length = 20)
    private String sqlId;

    @Column(name = "sql_text", columnDefinition = "TEXT")
    private String sqlText;

    @Column(name = "module", length = 50)
    private String module;

    @Column(name = "action", length = 50)
    private String action;

    @Column(name = "client_info", length = 50)
    private String clientInfo;

    @Column(name = "logon_time")
    private String logonTime;

    @Column(name = "event")
    private int event;

    @Column(name = "p1")
    private int p1;

    @Column(name = "p1text", length = 100)
    private String p1text;

    @Column(name = "p2")
    private int p2;

    @Column(name = "p2text", length = 100)
    private String p2text;

    @Column(name = "p3")
    private int p3;

    @Column(name = "p3text", length = 100)
    private String p3text;

    @Column(name = "blocking_session_status", length = 50)
    private String blockingSessionStatus;

    @Column(name = "blocking_instance")
    private int blockingInstance;

    @Column(name = "blocking_session")
    private int blockingSession;

    @Column(name = "final_blocking_session_status", length = 50)
    private String finalBlockingSessionStatus;

    @Column(name = "final_blocking_instance")
    private int finalBlockingInstance;

    @Column(name = "final_blocking_session")
    private int finalBlockingSession;

    public Session() {}

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

    public int getSerial() {
        return serial;
    }

    public void setSerial(int serial) {
        this.serial = serial;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getSchemaname() {
        return schemaname;
    }

    public void setSchemaname(String schemaname) {
        this.schemaname = schemaname;
    }

    public String getOsUser() {
        return osUser;
    }

    public void setOsUser(String osUser) {
        this.osUser = osUser;
    }

    public String getProcess() {
        return process;
    }

    public void setProcess(String process) {
        this.process = process;
    }

    public String getMachine() {
        return machine;
    }

    public void setMachine(String machine) {
        this.machine = machine;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public String getTerminal() {
        return terminal;
    }

    public void setTerminal(String terminal) {
        this.terminal = terminal;
    }

    public String getProgram() {
        return program;
    }

    public void setProgram(String program) {
        this.program = program;
    }

    public String getSqlAddress() {
        return sqlAddress;
    }

    public void setSqlAddress(String sqlAddress) {
        this.sqlAddress = sqlAddress;
    }

    public String getSqlId() {
        return sqlId;
    }

    public void setSqlId(String sqlId) {
        this.sqlId = sqlId;
    }

    public String getSqlText() {
        return sqlText;
    }

    public void setSqlText(String sqlText) {
        this.sqlText = sqlText;
    }

    public String getModule() {
        return module;
    }

    public void setModule(String module) {
        this.module = module;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    public String getClientInfo() {
        return clientInfo;
    }

    public void setClientInfo(String clientInfo) {
        this.clientInfo = clientInfo;
    }

    public String getLogonTime() {
        return logonTime;
    }

    public void setLogonTime(String logonTime) {
        this.logonTime = logonTime;
    }

    public int getEvent() {
        return event;
    }

    public void setEvent(int event) {
        this.event = event;
    }

    public int getP1() {
        return p1;
    }

    public void setP1(int p1) {
        this.p1 = p1;
    }

    public String getP1text() {
        return p1text;
    }

    public void setP1text(String p1text) {
        this.p1text = p1text;
    }

    public int getP2() {
        return p2;
    }

    public void setP2(int p2) {
        this.p2 = p2;
    }

    public String getP2text() {
        return p2text;
    }

    public void setP2text(String p2text) {
        this.p2text = p2text;
    }

    public int getP3() {
        return p3;
    }

    public void setP3(int p3) {
        this.p3 = p3;
    }

    public String getP3text() {
        return p3text;
    }

    public void setP3text(String p3text) {
        this.p3text = p3text;
    }

    public String getBlockingSessionStatus() {
        return blockingSessionStatus;
    }

    public void setBlockingSessionStatus(String blockingSessionStatus) {
        this.blockingSessionStatus = blockingSessionStatus;
    }

    public int getBlockingInstance() {
        return blockingInstance;
    }

    public void setBlockingInstance(int blockingInstance) {
        this.blockingInstance = blockingInstance;
    }

    public int getBlockingSession() {
        return blockingSession;
    }

    public void setBlockingSession(int blockingSession) {
        this.blockingSession = blockingSession;
    }

    public String getFinalBlockingSessionStatus() {
        return finalBlockingSessionStatus;
    }

    public void setFinalBlockingSessionStatus(String finalBlockingSessionStatus) {
        this.finalBlockingSessionStatus = finalBlockingSessionStatus;
    }

    public int getFinalBlockingInstance() {
        return finalBlockingInstance;
    }

    public void setFinalBlockingInstance(int finalBlockingInstance) {
        this.finalBlockingInstance = finalBlockingInstance;
    }

    public int getFinalBlockingSession() {
        return finalBlockingSession;
    }

    public void setFinalBlockingSession(int finalBlockingSession) {
        this.finalBlockingSession = finalBlockingSession;
    }
}