//============================================================================
// Name        : dh15.cpp
// Author      : Johan van der Graaff
// Version     :
// Copyright   : Ga weg joh
// Description : Ga weg joh
//============================================================================

#include "SocketServer.h"

using namespace std;

/*
Eclipse CDT :
- MinGW -> "wsock32" toevoegen aan : Project Properties -> C/C++ build -> Tool settings -> MinGW C++ Linker -> Libraries
*/
int main() {
	SocketServer server;
	server.start();

	return 0;
}
