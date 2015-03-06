#ifndef UTIL_H_
#define UTIL_H_

#include <string>

using namespace std;

class Util {
public:
    /**
     * Geeft huidige datum & tijd terug
     * in het format YYYY-MM-DD.HH-II-SS
     * Zie : http://en.cppreference.com/w/cpp/chrono/c/strftime
     * 
     * @return char
     */
    static std::string currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }

    /**
     * Template functie die (via de C++11 libraries)
     * een datatype om kan zetten naar een formatted string.
     * Zie : http://stackoverflow.com/a/26310318
     * 
     * @param  fmt
     * @param  args
     * @return std::string
     */
    template<typename... Args> 
        static std::string string_format(const char* fmt, Args... args) {
            size_t size = snprintf(nullptr, 0, fmt, args...);
            std::string buf;
            buf.reserve(size + 1);
            buf.resize(size);
            snprintf(&buf[0], size + 1, fmt, args...);
            return buf;
        };

    /**
     * Template functie die via stringstreams
     * een string omzet naar een getal.
     * Zie : http://www.cplusplus.com/forum/articles/9645/#msg56762
     * 
     * @param  str
     * @return
     */
    template <typename T>
        static long atoi(const std::basic_string<T> &str){
            std::basic_stringstream<T> stream(str);
            long res;
            return !(stream >>res)?0:res;
        };
};

#endif
/* UTIL_H_ */