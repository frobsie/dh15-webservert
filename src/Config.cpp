#include "Config.h"

const string Config::CONFIG_PATH = "src/runtime.cfg";
const string Config::MSG_READ_CONFIG_PATH = "Read config file in path: ";
const string Config::MSG_START = "Start reading config file";
const string Config::MSG_READ_LINE = "Read line with data: ";
const string Config::MSG_END = "Done reading config file";
const string Config::MSG_GET_VALUE = "Get value for key '%s' with value '%s'";
const string Config::MSG_GET_VALUE_NOT_FOUND = "No record found for key '%s'";
const string Config::MSG_SET_VALUE = "Set value for key '%s' with value '%s'";
const string Config::MSG_WRITE = "Write config to file";

using namespace std;

void Config::load() {
    string line;

    log.append(Logger::LOG_TYPE_SERVER, string(MSG_READ_CONFIG_PATH) + string(CONFIG_PATH));

    ifstream infile(CONFIG_PATH);

    log.append(Logger::LOG_TYPE_SERVER, string(MSG_START));

    while (getline(infile, line)) {
        log.append(Logger::LOG_TYPE_SERVER, (string(MSG_READ_LINE) + line));
        istringstream iss(line);
        vector<string> tokens{istream_iterator<string>{iss},
                              istream_iterator<string>{}};

        string value = "";
        for(unsigned int i = 1; i < tokens.size(); i++) {
            value = value + " " + tokens[i];
        }

        configValues[tokens[0]] = value;
    }

    log.append(Logger::LOG_TYPE_SERVER, string(MSG_END));
};

string Config::get(string key) {
    if ( configValues.find(key) == configValues.end() ) {
        log.append(Logger::LOG_TYPE_SERVER, Util::string_format(MSG_GET_VALUE_NOT_FOUND.c_str(), key.c_str()));
        throw MSG_GET_VALUE_NOT_FOUND;
    }
    log.append(Logger::LOG_TYPE_SERVER, Util::string_format(MSG_GET_VALUE.c_str(), key.c_str(), configValues[key].c_str()));
    return configValues[key];
};

void Config::set(string key, string value) {
    log.append(Logger::LOG_TYPE_SERVER, Util::string_format(MSG_SET_VALUE.c_str(), key.c_str(), value.c_str()));
    configValues[key] = value;
};

void Config::write() {
    log.append(Logger::LOG_TYPE_SERVER, string(MSG_WRITE));
    ofstream oupfile;
    oupfile.open (CONFIG_PATH);
    for (map<string, string>::iterator it = configValues.begin(); it != configValues.end(); ++it)
    {
        oupfile << it->first + " " + it->second << endl;
    }

    oupfile.close();
};
