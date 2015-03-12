#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>
#include <stdexcept>
#include <netinet/in.h> // sockaddr_in, socket()
#include <unistd.h> // close()
#include <string.h> // memset()

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "Logger.h"

class Socket {
public:
    Socket();
    Socket(int socketDescriptor);
    virtual ~Socket();

    bool create();
    bool bind(int port); 
    bool listen(int maxConnections);
    void close();

    /** Instantie van de logger */
    Logger log;

    // moet protected worden, iets met friend class doen @ socketserver
    int socketDescriptor;
    
private:
    static const std::string ERROR_SOCKET_UNABLETOCREATE;
    static const std::string ERROR_SOCKET_UNABLETOBIND;
    static const std::string ERROR_SOCKET_UNABLETOACCEPTCLIENT;

    static const int BUFFER_SIZE;

    
    struct sockaddr_in address;
};

class ServerSocket : public Socket {
public:
    ServerSocket(int port, int maxConnections);
};

#endif
/* SOCKET_H_ */