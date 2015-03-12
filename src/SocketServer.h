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
#include <vector>

#include "Util.h"
#include "Logger.h"
#include "Config.h"
#include "Socket.h"
#include "SocketServerThread.h"

class SocketServer {
public:
    /**
     * Constructor
     */
    SocketServer();

    /**
     * Template method voor het
     * starten van de server
     */
    void start();

private:
    static const std::string ERROR_SOCKET_UNABLETOCREATE;
    static const std::string ERROR_SOCKET_UNABLETOBIND;
    static const std::string ERROR_SOCKET_UNABLETOACCEPTCLIENT;
    static const std::string MSG_SERVER_STARTED;
    static const std::string MSG_SERVER_STOPPED;
    static const std::string MSG_SERVER_LISTENING;
    static const std::string MSG_CLIENT_CONNECTED;
    static const std::string MSG_SERVER_PREFIX;
    static const std::string MSG_CLIENT_PREFIX;

    static const std::string CONFIG_KEY_PORT;
    static const std::string CONFIG_KEY_MAXCONNECTIONS;

    static const int DEFAULT_SERVER_PORT;
    static const int DEFAULT_MAX_CONNECTIONS;
    
    /** Instantie van de logger */
    Logger log;

    /** Instantie van config object */
    Config config;
};

#endif 
/* SOCKETSERVER_H_ */