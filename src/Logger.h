#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>

class Logger {
public:
    static const int LOG_TYPE_SERVER;
    static const int LOG_TYPE_ACCESS;

    /**
     * Voegt een bericht van specifiek type
     * toe aan betreffende logfile. Als de file
     * niet bestaat wordt deze aangemaakt.
     * 
     * @param type
     * @param message
     */
    void append(int type, std::string message);

private:
    static const char* LOG_FILE_SERVER;
    static const char* LOG_FILE_ACCESS;
};

#endif
/* LOGGER_H_ */