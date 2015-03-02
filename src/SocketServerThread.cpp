#include "SocketServerThread.h"

SocketServerThread::SocketServerThread() {

}

SocketServerThread::~SocketServerThread() {

}

void SocketServerThread::run(int clientSocket) {
    send(clientSocket, "VERBONDEN\n", 9, 0);
}