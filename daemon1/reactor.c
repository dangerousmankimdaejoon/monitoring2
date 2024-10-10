#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>

#include "reactor.h"
#include "prm.h"
#include "common.h"

void handle_client_message(int client_sock, StatQueue *queue) {

    char buffer[8192];
    int bytes_read;

    bytes_read = read(client_sock, buffer, sizeof(buffer) - 1);

    buffer[bytes_read] = '\0';
    buffer[strcspn(buffer, "\r\n")] = '\0';

    printf("Received message from client %d: %s\n", client_sock, buffer);

    if (strcmp(buffer, "get_data") == 0) {
        /* stat */
        int offset = 0;
        int i=0;
        int first=0;
        
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "{\"TIME\":%s, \"SYSSTAT\":[", queue->time[queue->rear]);

        while (i < queue->data_count[0]) {
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, "{\"INDX\": %d, \"VALUE\": %lu, \"SYS\": %lu}",
                                                queue->data[queue->rear][i].INDX,
                                                queue->data[queue->rear][i].VALUE,
                                                queue->data[queue->rear][i].SYS);
            i++;
            
            if (offset >= sizeof(buffer) - 100) {
                send(client_sock, buffer, offset, 0);
                if(first==0) {
                    printf("send start : %20.20s ...", buffer);
                    first=1;
                }
                //printf("%s", buffer);
                offset = 0;
            }
            if (i < queue->data_count[0]) {
                offset += snprintf(buffer + offset, sizeof(buffer) - offset, ",");
            }
        }
        
        if (offset > 0) {
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, "],");
            send(client_sock, buffer, offset, 0);
            //printf("%s", buffer);
        } else {
            send(client_sock, "],", 2, 0);
            //printf("%s", buffer);
        }

        /* session */
        offset = 0;
        i = 0;

        offset += snprintf(buffer + offset, sizeof(buffer) - offset, " \"SESSION\":[");

        while (i < queue->data_count[1]) {
            char temp_buffer [12288];

            char escaped_sql_text[2000];
            char escaped_action[200];

            escapeJsonString(queue->user[queue->rear][i].SQL_TEXT, escaped_sql_text, sizeof(escaped_sql_text));
            escapeJsonString(queue->user[queue->rear][i].ACTION, escaped_action, sizeof(escaped_action));

            int len = snprintf(temp_buffer, sizeof(temp_buffer), 
                            "{\"SID\": %lu, \"SERIAL\": %lu, \"USERNAME\":\"%s\", \"STATUS\":\"%s\", "
                            "\"SCHEMA_\": %lu, \"SCHEMANAME\":\"%s\", \"OSUSER\":\"%s\", \"PROCESS\":\"%s\", "
                            "\"MACHINE\":\"%s\", \"PORT\": %lu, \"TERMINAL\":\"%s\", \"PROGRAM\":\"%s\", "
                            "\"SQL_ADDRESS\":\"%8lx\", \"SQL_ID\":\"%s\", \"SQL_TEXT\":\"%s\", \"MODULE\":\"%s\", \"ACTION\":\"%s\", "
                            "\"CLIENT_INFO\":\"%s\", \"LOGON_TIME\":\"%s\", \"EVENT\": %lu, \"P1\": %lu, \"P1TEXT\":\"%s\", "
                            "\"P2\": %lu, \"P2TEXT\":\"%s\", \"P3\": %lu, \"P3TEXT\":\"%s\", \"BLOCKING_SESSION_STATUS\":\"%s\", "
                            "\"BLOCKING_INSTANCE\": %lu, \"BLOCKING_SESSION\": %lu, "
                            "\"FINAL_BLOCKING_SESSION_STATUS\":\"%s\", \"FINAL_BLOCKING_INSTANCE\": %lu, \"FINAL_BLOCKING_SESSION\": %lu}",
                            queue->user[queue->rear][i].SID,
                            queue->user[queue->rear][i].SERIAL_,
                            queue->user[queue->rear][i].USERNAME,
                            queue->user[queue->rear][i].STATUS,
                            queue->user[queue->rear][i].SCHEMA_,
                            queue->user[queue->rear][i].SCHEMANAME,
                            queue->user[queue->rear][i].OSUSER,
                            queue->user[queue->rear][i].PROCESS,
                            queue->user[queue->rear][i].MACHINE,
                            queue->user[queue->rear][i].PORT,
                            queue->user[queue->rear][i].TERMINAL,
                            queue->user[queue->rear][i].PROGRAM,
                            queue->user[queue->rear][i].SQL_ADDRESS,
                            queue->user[queue->rear][i].SQL_ID,
                            escaped_sql_text,
                            queue->user[queue->rear][i].MODULE,
                            escaped_action,
                            queue->user[queue->rear][i].CLIENT_INFO,
                            queue->user[queue->rear][i].LOGON_TIME,
                            queue->user[queue->rear][i].EVENT_,
                            queue->user[queue->rear][i].P1,
                            queue->user[queue->rear][i].P1TEXT,
                            queue->user[queue->rear][i].P2,
                            queue->user[queue->rear][i].P2TEXT,
                            queue->user[queue->rear][i].P3,
                            queue->user[queue->rear][i].P3TEXT,
                            queue->user[queue->rear][i].BLOCKING_SESSION_STATUS,
                            queue->user[queue->rear][i].BLOCKING_INSTANCE,
                            queue->user[queue->rear][i].BLOCKING_SESSION,
                            queue->user[queue->rear][i].FINAL_BLOCKING_SESSION_STATUS,
                            queue->user[queue->rear][i].FINAL_BLOCKING_INSTANCE,
                            queue->user[queue->rear][i].FINAL_BLOCKING_SESSION);
            
            int temp_offset = 0;

            while (temp_offset < len) {
                int remaining_space = sizeof(buffer) - offset - 1;
                int copy_len = (len - temp_offset > remaining_space) ? remaining_space : (len - temp_offset);
                memcpy(buffer + offset, temp_buffer + temp_offset, copy_len);
                offset += copy_len;
                temp_offset += copy_len;
                
                if (offset >= sizeof(buffer) - 1) {
                    send(client_sock, buffer, offset, 0);
                    //printf("%s", buffer);
                    offset = 0;
                }
            }
            
            i++;

            if (i < queue->data_count[1]) {
                if (offset >= sizeof(buffer) - 2) {
                    send(client_sock, buffer, offset, 0);
                    //printf("%s", buffer);
                    offset = 0;
                }
                buffer[offset++] = ',';
            }
        }

        if (offset > 0) {
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, "]}\n");
            send(client_sock, buffer, offset, 0);
            //printf("%s", buffer);
        } else {
            send(client_sock, "]}\n", 2, 0);
            //printf("%s", buffer);
        }
        printf(" (data) ... %-20.20s\n", buffer+strlen(buffer)-20);
    } else if (strcmp(buffer, "first_request") == 0) {
        
        int front = queue->front;
        int cnt = 0;

        while(cnt < queue->count) {
            /* stat */
            int i=0;
            int first=0;
            int offset = 0;

            offset += snprintf(buffer + offset, sizeof(buffer) - offset, "{\"TIME\":%s, \"SYSSTAT\":[", queue->time[front]);

            while (i < queue->data_count[0]) {
                offset += snprintf(buffer + offset, sizeof(buffer) - offset, "{\"INDX\": %d, \"VALUE\": %lu, \"SYS\": %lu}",
                                                    queue->data[front][i].INDX,
                                                    queue->data[front][i].VALUE,
                                                    queue->data[front][i].SYS);
                i++;
                
                if (offset >= sizeof(buffer) - 100) {
                    send(client_sock, buffer, offset, 0);
                    if(first==0) {
                        printf("send start : %20.20s ...", buffer);
                        first=1;
                    }
                    //printf("%s", buffer);
                    offset = 0;
                }
                if (i < queue->data_count[0]) {
                    offset += snprintf(buffer + offset, sizeof(buffer) - offset, ",");
                }
            }
            
            if (offset > 0) {
                offset += snprintf(buffer + offset, sizeof(buffer) - offset, "],");
                send(client_sock, buffer, offset, 0);
                //printf("%s", buffer);
            } else {
                send(client_sock, "],", 2, 0);
                //printf("%s", buffer);
            }

            /* session */
            offset = 0;
            i = 0;

            offset += snprintf(buffer + offset, sizeof(buffer) - offset, " \"SESSION\":[");

            while (i < queue->data_count[1]) {
                char temp_buffer [12288];

                char escaped_sql_text[2000];
                char escaped_action[200];

                escapeJsonString(queue->user[front][i].SQL_TEXT, escaped_sql_text, sizeof(escaped_sql_text));
                escapeJsonString(queue->user[front][i].ACTION, escaped_action, sizeof(escaped_action));

                int len = snprintf(temp_buffer, sizeof(temp_buffer), 
                                "{\"SID\": %lu, \"SERIAL\": %lu, \"USERNAME\":\"%s\", \"STATUS\":\"%s\", "
                                "\"SCHEMA_\": %lu, \"SCHEMANAME\":\"%s\", \"OSUSER\":\"%s\", \"PROCESS\":\"%s\", "
                                "\"MACHINE\":\"%s\", \"PORT\": %lu, \"TERMINAL\":\"%s\", \"PROGRAM\":\"%s\", "
                                "\"SQL_ADDRESS\":\"%8lx\", \"SQL_ID\":\"%s\", \"SQL_TEXT\":\"%s\", \"MODULE\":\"%s\", \"ACTION\":\"%s\", "
                                "\"CLIENT_INFO\":\"%s\", \"LOGON_TIME\":\"%s\", \"EVENT\": %lu, \"P1\": %lu, \"P1TEXT\":\"%s\", "
                                "\"P2\": %lu, \"P2TEXT\":\"%s\", \"P3\": %lu, \"P3TEXT\":\"%s\", \"BLOCKING_SESSION_STATUS\":\"%s\", "
                                "\"BLOCKING_INSTANCE\": %lu, \"BLOCKING_SESSION\": %lu, "
                                "\"FINAL_BLOCKING_SESSION_STATUS\":\"%s\", \"FINAL_BLOCKING_INSTANCE\": %lu, \"FINAL_BLOCKING_SESSION\": %lu}",
                                queue->user[front][i].SID,
                                queue->user[front][i].SERIAL_,
                                queue->user[front][i].USERNAME,
                                queue->user[front][i].STATUS,
                                queue->user[front][i].SCHEMA_,
                                queue->user[front][i].SCHEMANAME,
                                queue->user[front][i].OSUSER,
                                queue->user[front][i].PROCESS,
                                queue->user[front][i].MACHINE,
                                queue->user[front][i].PORT,
                                queue->user[front][i].TERMINAL,
                                queue->user[front][i].PROGRAM,
                                queue->user[front][i].SQL_ADDRESS,
                                queue->user[front][i].SQL_ID,
                                escaped_sql_text,
                                queue->user[front][i].MODULE,
                                escaped_action,
                                queue->user[front][i].CLIENT_INFO,
                                queue->user[front][i].LOGON_TIME,
                                queue->user[front][i].EVENT_,
                                queue->user[front][i].P1,
                                queue->user[front][i].P1TEXT,
                                queue->user[front][i].P2,
                                queue->user[front][i].P2TEXT,
                                queue->user[front][i].P3,
                                queue->user[front][i].P3TEXT,
                                queue->user[front][i].BLOCKING_SESSION_STATUS,
                                queue->user[front][i].BLOCKING_INSTANCE,
                                queue->user[front][i].BLOCKING_SESSION,
                                queue->user[front][i].FINAL_BLOCKING_SESSION_STATUS,
                                queue->user[front][i].FINAL_BLOCKING_INSTANCE,
                                queue->user[front][i].FINAL_BLOCKING_SESSION);
                
                int temp_offset = 0;

                while (temp_offset < len) {
                    int remaining_space = sizeof(buffer) - offset - 1;
                    int copy_len = (len - temp_offset > remaining_space) ? remaining_space : (len - temp_offset);
                    memcpy(buffer + offset, temp_buffer + temp_offset, copy_len);
                    offset += copy_len;
                    temp_offset += copy_len;
                    
                    if (offset >= sizeof(buffer) - 1) {
                        send(client_sock, buffer, offset, 0);
                        //printf("%s", buffer);
                        offset = 0;
                    }
                }
                
                i++;

                if (i < queue->data_count[1]) {
                    if (offset >= sizeof(buffer) - 2) {
                        send(client_sock, buffer, offset, 0);
                        //printf("%s", buffer);
                        offset = 0;
                    }
                    buffer[offset++] = ',';
                }
            }

            if (offset > 0) {
                offset += snprintf(buffer + offset, sizeof(buffer) - offset, "]}\n");
                send(client_sock, buffer, offset, 0);
                //printf("%s", buffer);
            } else {
                send(client_sock, "]}\n", 2, 0);
                //printf("%s", buffer);
            }

            printf(" (data) ... %-20.20s", buffer+strlen(buffer)-20);

            front = (front + 1) % QUEUE_SIZE;
            cnt++;
        }
        printf("\n");
    } else if (strcmp(buffer, "exit\n") == 0) {
        printf("Client requested to close the connection: socket %d\n", client_sock);
        close(client_sock);
    } else {
        char *msg = "Unknown command\n";
        send(client_sock, msg, strlen(msg), 0);
    }
}

void* reactor(void *arg) {
    int server_sock, client_sock, max_sd, activity;
    struct sockaddr_in address;
    int opt = 1;

    int addrlen = sizeof(address);
    fd_set readfds, writefds;

    StatQueue *queue = (StatQueue *)arg;

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(NET_PORT);

    if (bind(server_sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, 3) < 0) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", NET_PORT);
    
    int client_sockets[MAX_CLIENTS] = {0};

    while (1) {
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(server_sock, &readfds);
        max_sd = server_sock;
        
        int i;
        
        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];
            if (sd > 0) {
                FD_SET(sd, &readfds);
                FD_SET(sd, &writefds);
            }
            if (sd > max_sd) max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, &writefds, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("Select error");
        }

        if (FD_ISSET(server_sock, &readfds)) {
            if ((client_sock = accept(server_sock, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }

            printf("New connection: socket %d, IP %s, Port %d\n",
                   client_sock, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = client_sock;
                    printf("Added to client list as %d\n", i);
                    break;
                }
            }
            
            if (i == MAX_CLIENTS) {
                printf("Max clients reached. Closing connection on socket %d\n", client_sock);
                close(client_sock);
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds)) {

                char buffer[BUFFER_SIZE];
                int valread = read(sd, buffer, sizeof(buffer));

                if (valread == 0) {
                    getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    printf("Client disconnected: IP %s, Port %d\n",
                        inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    close(sd);
                    FD_CLR(sd, &writefds);
                    client_sockets[i] = 0;
                } else if (valread < 0) {
                    if (errno == ECONNRESET) {
                        printf("Read error: Connection reset by peer. Client disconnected: IP %s, Port %d\n",
                            inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                    } else {
                        perror("Read error");
                    }
                    close(sd);
                    FD_CLR(sd, &writefds);
                    client_sockets[i] = 0;
                    
                    continue;
                } else {
                    buffer[valread] = '\0';
                    printf("Received from client %d: %s\n", sd, buffer);
                }
            }

            if (client_sockets[i] != 0 && FD_ISSET(sd, &writefds)) {
                handle_client_message(sd, queue);
            }
        }
    }

    return 0;
}