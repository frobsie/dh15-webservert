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
};

void SocketServer::start() {
    int port = Util::atoi(config.get(CONFIG_KEY_PORT));
    int maxConnections = Util::atoi(config.get(CONFIG_KEY_MAXCONNECTIONS));

    std::vector<std::thread> threads;
    int threadId = 0;

    try {
        ServerSocket serverSocket(port, maxConnections);       

        int client;
        struct sockaddr_in client_addr;
        socklen_t clientlen = sizeof(client_addr);

        // blocking
        while ((client = accept(serverSocket.socketDescriptor,(struct sockaddr *)&client_addr,&clientlen)) > 0) {
            cout << "Client connected" << endl;

            // Nieuwe thread maken en pushen in de vector
            SocketServerThread sst;
            threads.push_back(std::thread(&SocketServerThread::run, &sst, client));

            std::cout << "Thread created " + threadId << std::endl;

            threadId++;
        }

        //Join the threads with the main thread
        for(auto &t : threads){
            t.join();
        }

        // Serversocket sluiten
        serverSocket.close();

    } catch(std::exception &ex) {
        std::cout << ex.what();
    }
};