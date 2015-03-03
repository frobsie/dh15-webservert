#ifndef SOCKETSERVERTHREAD_H_
#define SOCKETSERVERTHREAD_H_

#include <netinet/in.h>
#include <iostream>
#include <string.h>

class SocketServerThread {
public:
    static const char* MSG_GREETINGS;
    static const char* MSG_REPEAT;

    SocketServerThread();
    virtual ~SocketServerThread();

    void run(int clientSocket);
};

#endif 
/* SOCKETSERVERTHREAD_H_ */