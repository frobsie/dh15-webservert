#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <stdio.h>
#include <string.h>

#include "Util.h"
#include "Logger.h"

class Config {
public:
    /**
     * Methode voor het laden van de config file
     */
    void load();

    /**
     * Get config value
     * @param   key
     * @return string
     */
    std::string get(std::string key);


    /**
     * Set config value
     * @param   key
     * @param   value
     */
    void set(std::string key, std::string value);

    /**
     * Methode voor het schrijven naar de config file
     */
    void write();

private:
    static const string PREFIX;
    static const string CONFIG_PATH;
    static const string MSG_READ_CONFIG_PATH;
    static const string MSG_START;
    static const string MSG_READ_LINE;
    static const string MSG_END;
    static const string MSG_GET_VALUE;
    static const string MSG_GET_VALUE_NOT_FOUND;
    static const string MSG_SET_VALUE;
    static const string MSG_WRITE;

    Logger log;

    std::map<std::string, std::string> configValues;
};

#endif
/* CONFIG_H_ */