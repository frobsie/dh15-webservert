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

using namespace std;
class Config {
public:
    /**
     * Constructor
     */
    Config();

    /**
     * Destructor
     * Zorgt voor wat cleanup
     */
    virtual ~Config();

    /**
     * Methode voor het laden van de config file
     */
    void load();

    /**
     * Get config value
     * @param   key
     * @return string
     */
    string get(string key);


    /**
     * Set config value
     * @param   key
     * @param   value
     */
    void set(string key, string value);

    /**
     * Methode voor het schrijven naar de config file
     */
    void write();

private:
    static const char* PREFIX;
    static const char* CONFIG_PATH;
    static const char* MSG_READ_CONFIG_PATH;
    static const char* MSG_START;
    static const char* MSG_READ_LINE;
    static const char* MSG_END;
    static const char* MSG_GET_VALUE;
    static const char* MSG_GET_VALUE_NOT_FOUND;
    static const char* MSG_SET_VALUE;
    static const char* MSG_WRITE;

    map<string, string> configValues;


    /**
     * Template functie die (via de C++11 libraries)
     * een datatype om kan zetten naar een formatted string.
     * Zie : http://stackoverflow.com/a/26310318
     *
     * @param  fmt
     * @param  args
     * @return std::string
     */
    template<typename... Args> std::string string_format(const char* fmt, Args... args) {
        size_t size = snprintf(nullptr, 0, fmt, args...);
        std::string buf;
        buf.reserve(size + 1);
        buf.resize(size);
        snprintf(&buf[0], size + 1, fmt, args...);
        return buf;
    }
};

#endif
/* CONFIG_H_ */