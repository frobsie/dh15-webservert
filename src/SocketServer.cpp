#include "SocketServer.h"

const string SocketServer::ERROR_SOCKET_UNABLETOCREATE = "Socket kon niet aangemaakt worden.";
const string SocketServer::ERROR_SOCKET_UNABLETOBIND = "Socket kon niet aan een poort worden gebind.";
const string SocketServer::ERROR_SOCKET_UNABLETOACCEPTCLIENT = "Client kon niet connecten.";
const string SocketServer::MSG_SERVER_STARTED = "Server started.";
const string SocketServer::MSG_SERVER_STOPPED = "Server stopped.";
const string SocketServer::MSG_SERVER_LISTENING = "Listening on port: ";
const string SocketServer::MSG_CLIENT_CONNECTED = "Client connected from %s on port %d.";
const string SocketServer::CONFIG_KEY_PORT = "webport";
const string SocketServer::CONFIG_KEY_MAXCONNECTIONS = "maxconnections";

using namespace std;

SocketServer::SocketServer() {
    /** Config inladen */
    config.load();

    // File descriptors resetten
    serverSocket = 0;
    clientSocket = 0;
};

SocketServer::~SocketServer() {
    // Alleen serversocket sluiten als deze
    // aanwezig is
    if (serverSocket >= 0) {
        close(serverSocket);
    }

    // Entry aan log toevoegen
    log.append(Logger::LOG_TYPE_SERVER, string(MSG_SERVER_STOPPED));
};

void SocketServer::setupSocket() {
    int port = Util::atoi(config.get(CONFIG_KEY_PORT));
    int maxConnections = Util::atoi(config.get(CONFIG_KEY_MAXCONNECTIONS));

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0) {
        throw std::runtime_error(string(ERROR_SOCKET_UNABLETOCREATE));
    }

    sockaddr_in socketAddress = fillSocketAddress(port);

    // Socket koppelen aan netwerkadres
    bind(serverSocket, (sockaddr *)&socketAddress, sizeof(sockaddr_in));

    // Queue voorbereiden op een maximum aantal connections
    listen(serverSocket, maxConnections);

    log.append(Logger::LOG_TYPE_SERVER, string(MSG_SERVER_STARTED) );
    log.append(Logger::LOG_TYPE_SERVER, (string(MSG_SERVER_LISTENING) + to_string(port)) );
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

    // Grootte van de socket bepalen
    socklen_t clilen;
    clilen = sizeof(cli_addr);

    try {
        setupSocket();

        // Start de server loop
        while( (clientSocket = accept(serverSocket, (struct sockaddr *) &cli_addr, &clilen)) ) {
            
            if (clientSocket < 0) {
                throw std::runtime_error(string(ERROR_SOCKET_UNABLETOACCEPTCLIENT));
            }

            log.append(Logger::LOG_TYPE_ACCESS, Util::string_format(
                MSG_CLIENT_CONNECTED.c_str(),
                inet_ntoa(cli_addr.sin_addr),
                ntohs(cli_addr.sin_port)
            ));
            
            SocketServerThread sst;
            thread t(&SocketServerThread::run, &sst, clientSocket);

            t.detach();
        }

    } catch(exception& e) {
        // TODO
    }
};