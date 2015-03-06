#include "Logger.h"
#include "Util.h"

const char* Logger::LOG_FILE_SERVER = "./log/server";
const char* Logger::LOG_FILE_ACCESS = "./log/access";

const int Logger::LOG_TYPE_SERVER = 1;
const int Logger::LOG_TYPE_ACCESS = 2;

using namespace std;

void Logger::append(int type, string message) {
    std::ofstream logStream;
    string logFile;

    switch(type) {
        case LOG_TYPE_SERVER:
            logFile = string(LOG_FILE_SERVER);
            break;
        case LOG_TYPE_ACCESS:
            logFile = string(LOG_FILE_ACCESS);
            break;
    }

    logStream.open(logFile, std::ios_base::app);
    logStream << ("[" + Util::currentDateTime() + "]" + " " + message) << endl;
}