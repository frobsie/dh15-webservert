#include "SocketServer.h"
#include "Config.h"

using namespace std;

int main() {
    Config config;
    config.load();

    SocketServer server;
    server.start();
    
    return 0;
}

