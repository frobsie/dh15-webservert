#include "SocketServer.h"

const char* SocketServer::ERROR_SOCKET_UNABLETOCREATE = "Socket kon niet aangemaakt worden.";
const char* SocketServer::ERROR_SOCKET_UNABLETOBIND = "Socket kon niet aan een poort worden gebind.";
const char* SocketServer::ERROR_SOCKET_UNABLETOACCEPTCLIENT = "Client kon niet connecten.";
const char* SocketServer::MSG_SERVER_PREFIX = "[SERVER]";
const char* SocketServer::MSG_CLIENT_PREFIX = "[CLIENT]";
const char* SocketServer::MSG_SERVER_STARTED = "Server started.";
const char* SocketServer::MSG_SERVER_LISTENING = "Listening on port: ";
const char* SocketServer::MSG_CLIENT_CONNECTED = "Client connected from %s on port %d.";

const int SocketServer::DEFAULT_SERVER_PORT = 2000;
const int SocketServer::DEFAULT_MAX_CONNECTIONS = 10;

const int SocketServer::MSG_TYPE_1 = 1;
const int SocketServer::MSG_TYPE_2 = 2;

SocketServer::SocketServer() {
    serverSocket = 0;
    clientSocket = 0;
};

SocketServer::~SocketServer() {
    if (serverSocket >= 0) {
        close(serverSocket);
    }
};

void SocketServer::setupSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        std::__throw_runtime_error(ERROR_SOCKET_UNABLETOCREATE);
    }

    sockaddr_in socketAddress = fillSocketAddress(DEFAULT_SERVER_PORT);

    // Socket koppelen aan netwerkadres
    bind(serverSocket, (sockaddr *)&socketAddress, sizeof(sockaddr_in));

    // Queue voorbereiden op een maximum aantal connections
    listen(serverSocket, DEFAULT_MAX_CONNECTIONS);

    printMessage(MSG_TYPE_1, MSG_SERVER_STARTED);
    printMessage(MSG_TYPE_1, (MSG_SERVER_LISTENING + std::to_string(DEFAULT_SERVER_PORT)));
};

struct sockaddr_in SocketServer::fillSocketAddress(unsigned short port) {
    sockaddr_in address;

    // Struct vullen met 0
    memset(&address, 0, sizeof(address));

    // Relevante velden opnieuw vullen
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    return address;
};

void SocketServer::start() {

    // Struct die gebruikt wordt om net-data 
    // van de client op te slaan
    struct sockaddr_in cli_addr;

    // Grootte van de socket
    socklen_t clilen;

    clilen = sizeof(cli_addr);

    try {
        setupSocket();

        // Start de server loop
        while( (clientSocket = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen)) ) {
            
            if (clientSocket < 0) {
                std::__throw_runtime_error(ERROR_SOCKET_UNABLETOACCEPTCLIENT);
            }
            
            SocketServerThread sst;
            std::thread t(&SocketServerThread::run, &sst, clientSocket);

            printMessage(1, string_format(
                MSG_CLIENT_CONNECTED, 
                inet_ntoa(cli_addr.sin_addr), 
                ntohs(cli_addr.sin_port)
            ));

            t.join();
        }

    } catch(std::exception& e) {
        
    }
};

void SocketServer::printMessage(int type, std::string message) {
    switch (type) {
        case MSG_TYPE_1:
            message = MSG_SERVER_PREFIX + message;
            break;
        case MSG_TYPE_2:
            message = MSG_CLIENT_PREFIX + message;
            break;
    }

    std::cout << message << std::endl;
};