#include "Socket.h"

const std::string Socket::ERROR_SOCKET_UNABLETOCREATE = "Socket kon niet aangemaakt worden.";
const std::string Socket::ERROR_SOCKET_UNABLETOBIND = "Socket kon niet aan een poort worden gebind.";
const std::string Socket::ERROR_SOCKET_UNABLETOACCEPTCLIENT = "Client kon niet connecten.";

const int Socket::BUFFER_SIZE = 64; // max 65535

Socket::Socket() {

};

Socket::Socket(int socketDescriptor) {
    this->socketDescriptor = socketDescriptor;
};

Socket::~Socket() {
    close();
};

bool Socket::create() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socketDescriptor < 0) {
        throw std::runtime_error(std::string(ERROR_SOCKET_UNABLETOCREATE));
    }
    return true;
};

bool Socket::bind(int port) {
    // Struct vullen met 0 waarden
    memset(&address, 0, sizeof(address));

    // Relevante velden opnieuw vullen
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    // Socket koppelen aan netwerkadres
    int isBound = ::bind(socketDescriptor, (sockaddr *)&address, sizeof(address));

    if (isBound < 0) {
        return false;
    }
    return true;
};

bool Socket::listen(int maxConnections) {
    // Luisteren met maximum aantal connecties
    int isListening = ::listen(socketDescriptor, maxConnections);

    if (isListening < 0) {
        return false;
    }
    return true;
};

void Socket::close() {
    if (socketDescriptor >= 0) {
        ::close(socketDescriptor);
    }
};


ServerSocket::ServerSocket(int port, int maxConnections) {
    create();
    bind(port);
    listen(maxConnections);
};