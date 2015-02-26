/*
 * SocketServer.h
 *
 *  Created on: 13 feb. 2015
 *      Author: Johan
 */

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include <iostream>
#include <unistd.h>
#include <string>
#include <exception>
#include <WinSock2.h>

class SocketServer {
public:
	/**
	 * Constructor
	 */
	SocketServer();

	/**
	 * Destructor
	 * Zorgt voor wat cleanup omtrent
	 * de Winsock lib en sluit daarna
	 * de socket.
	 */
	virtual ~SocketServer();

	/**
	 * Template method voor het
	 * starten van de server
	 */
	void start();

private:
	static const char* ERROR_SOCKET_UNABLETOCREATE;
	static const char* ERROR_SOCKET_UNABLETOBIND;
	static const char* ERROR_WIN32_COULDNOTSTARTWSA;

	static const int DEFAULT_SERVER_PORT;
	static const int DEFAULT_MAX_CONNECTIONS;

	int serverSocket;
	int clientSocket;

	/**
	 * Zorgt voor het initialiseren van
	 * de winsock library, zodat er gebruik
	 * gemaakt kan worden van sockets.
	 */
	void setupWSA();

	/**
	 * Maakt een socket aan op het domein "internet" (AF_INET)
	 * om via streams te communiceren over default protocol (TCP)
	 *
	 * Als de socket niet aangemaakt kan worden (INVALID_SOCKET == -1)
	 * gooien we een runtime_error exception.
	 */
	void setupSocket();

	/**
	 * Methode die een sockaddr_in struct vult
	 * aan de hand van opgegeven parameters
	 */
	struct sockaddr_in fillSocketAddress(u_short port);
};

#endif /* SOCKETSERVER_H_ */
