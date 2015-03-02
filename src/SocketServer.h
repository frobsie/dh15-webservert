#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include <iostream>
#include <thread>
#include <unistd.h>
#include <exception>
#include <stdio.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <arpa/inet.h>
#include <string>

#include "SocketServerThread.h"

class SocketServer {
public:
    /**
     * Constructor
     */
    SocketServer();

    /**
     * Destructor
     * Zorgt voor wat cleanup
     */
    virtual ~SocketServer();

    /**
     * Template method voor het
     * starten van de server
     */
    void start();

private:
    static const char* ERROR_SOCKET_UNABLETOCREATE;
    static const char* ERROR_SOCKET_UNABLETOBIND;
    static const char* ERROR_SOCKET_UNABLETOACCEPTCLIENT;
    static const char* MSG_SERVER_STARTED;
    static const char* MSG_SERVER_LISTENING;
    static const char* MSG_CLIENT_CONNECTED;
    static const char* MSG_SERVER_PREFIX;
    static const char* MSG_CLIENT_PREFIX;

    static const int DEFAULT_SERVER_PORT;
    static const int DEFAULT_MAX_CONNECTIONS;

    static const int MSG_TYPE_1; // std:out message
    static const int MSG_TYPE_2; // log message

    int serverSocket;
    int clientSocket;

    /**
     * Maakt een socket aan op het domein "internet" (AF_INET)
     * om via streams te communiceren over default protocol (TCP)
     *
     * Als de socket niet aangemaakt kan worden (INVALID_SOCKET == -1)
     * gooien we een runtime_error exception.
     */
    void setupSocket();

    /**
     * Methode die een sockaddr_in struct vult
     * aan de hand van opgegeven parameters.
     * 
     * @param  port 
     * @return struct sockaddr_in
     */
    struct sockaddr_in fillSocketAddress(unsigned short port);

    /**
     * Prints message of specific type
     * 
     * @param type
     * @param message
     */
    void printMessage(int type, std::string message);

    /**
     * Template functie die (via de C++11 libraries)
     * een datatype om kan zetten naar een formatted string.
     * Zie : http://stackoverflow.com/a/26310318
     * 
     * @param  fmt
     * @param  args
     * @return std::string
     */
    template<typename... Args> std::string string_format(const char* fmt, Args... args) {
        size_t size = snprintf(nullptr, 0, fmt, args...);
        std::string buf;
        buf.reserve(size + 1);
        buf.resize(size);
        snprintf(&buf[0], size + 1, fmt, args...);
        return buf;
    }
};

#endif 
/* SOCKETSERVER_H_ */