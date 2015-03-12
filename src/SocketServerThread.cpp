#include "SocketServerThread.h"

const int SocketServerThread::BUFSIZE = 64;

SocketServerThread::SocketServerThread() {
    
};

int SocketServerThread::run(int socketDescriptor) {
    // TODO
    // - Dit zou richting de Socket class moeten
    char buffer[BUFSIZE];
    ssize_t bytes_read = 0;

    printf("Socket descriptor: %d\n", socketDescriptor);
    
    bytes_read = recv(socketDescriptor, buffer, BUFSIZE - 1, 0);

    while (bytes_read > 0) {
        buffer[bytes_read] = 0;
        printf("Buffer: %s\n", buffer); 
        bytes_read = recv(socketDescriptor, buffer, BUFSIZE - 1, 0);
    }

    // Recv kapt ermee
    if (bytes_read == -1) {    
        return -1;
    }
    return 0;
};