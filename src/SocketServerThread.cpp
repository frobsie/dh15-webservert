#include "SocketServerThread.h"

const char* SocketServerThread::MSG_GREETINGS = "Greetings! I am your connection handler\n";
const char* SocketServerThread::MSG_REPEAT = "Now type something and i shall repeat what you type \n";

SocketServerThread::SocketServerThread() {

}

SocketServerThread::~SocketServerThread() {

}

void SocketServerThread::run(int clientSocket) {
    //Get the socket descriptor
    int read_size;
    char client_message[2000];

    send(clientSocket, "VERBONDEN\n", 9, 0);

    //Send some messages to the client
    send(clientSocket , SocketServerThread::MSG_GREETINGS , strlen(SocketServerThread::MSG_GREETINGS), 0);

    send(clientSocket , SocketServerThread::MSG_REPEAT , strlen(SocketServerThread::MSG_REPEAT), 0);

    //Receive a message from client
    while( (read_size = recv(clientSocket , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        send(clientSocket , client_message , strlen(client_message), 0);
    }

    if(read_size == 0)
    {
        //puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
};