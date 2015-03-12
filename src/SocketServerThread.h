#ifndef SOCKETSERVERTHREAD_H_
#define SOCKETSERVERTHREAD_H_

#include <netinet/in.h>
#include <iostream>
#include <string.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <thread>

#include "Socket.h"
#include "Logger.h"

class SocketServerThread {
public:
    static const int BUFSIZE;

    SocketServerThread();

    int run(int socket);

private:
    /** Instantie van de logger */
    Logger log;
};

#endif
/* SOCKETSERVERTHREAD_H_ */