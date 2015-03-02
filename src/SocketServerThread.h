#ifndef SOCKETSERVERTHREAD_H_
#define SOCKETSERVERTHREAD_H_

#include <netinet/in.h>
#include <iostream>

class SocketServerThread {
public:

    SocketServerThread();
    virtual ~SocketServerThread();

    void run(int clientSocket);
};

#endif 
/* SOCKETSERVERTHREAD_H_ */