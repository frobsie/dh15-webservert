/*
 * SocketServer.cpp
 *
 *  Created on: 13 feb. 2015
 *      Author: Johan
 */

#include "SocketServer.h"

const char * SocketServer::ERROR_SOCKET_UNABLETOCREATE = "Socket kon niet aangemaakt worden.";
const char * SocketServer::ERROR_SOCKET_UNABLETOBIND = "Socket kon niet aan een poort worden gebind.";
const char * SocketServer::ERROR_WIN32_COULDNOTSTARTWSA = "Kon WinSock niet laden.";

const int SocketServer::DEFAULT_SERVER_PORT = 2000;
const int SocketServer::DEFAULT_MAX_CONNECTIONS = 10;

SocketServer::SocketServer() {
	serverSocket = 0;
	clientSocket = 0;
}

SocketServer::~SocketServer() {
	WSACleanup();

	if (serverSocket != -1) {
		close(serverSocket);
	}
}

void SocketServer::setupWSA()  {
    WSADATA info;
    if (WSAStartup(MAKEWORD(2,0), &info)) {
    	std::__throw_runtime_error(ERROR_SOCKET_UNABLETOCREATE);
    }
}

void SocketServer::setupSocket() {
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocket == INVALID_SOCKET) {
		std::__throw_runtime_error(ERROR_SOCKET_UNABLETOCREATE);
	}

	sockaddr_in socketAddress = fillSocketAddress(DEFAULT_SERVER_PORT);

	// Socket koppelen aan netwerkadres
	bind(serverSocket, (sockaddr *)&socketAddress, sizeof(sockaddr_in));

	// Queue voorbereiden op een maximum aantal connections
	listen(serverSocket, DEFAULT_MAX_CONNECTIONS);

	std::cout << "Server started" << std::endl;
}

struct sockaddr_in SocketServer::fillSocketAddress(u_short port) {
	sockaddr_in address;

	// Struct vullen met 0
	memset(&address, 0, sizeof(address));

	// Relevante velden opnieuw vullen
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	return address;
}

void SocketServer::start() {
	try {
		setupWSA();
		setupSocket();

		// Start de server loop
		while(true) {
			// TODO
			// - client address struct + size vullen
			// - socket naar nieuwe thread pompen
			clientSocket = accept(serverSocket, NULL, NULL);
		}

	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
