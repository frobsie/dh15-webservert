#include "Config.h"

const char* Config::PREFIX = "[CONFIG] ";
const char* Config::CONFIG_PATH = "src/runtime.cfg";
const char* Config::MSG_READ_CONFIG_PATH = "Read config file in path: ";
const char* Config::MSG_START = "Start reading config file";
const char* Config::MSG_READ_LINE = "Read line with data: ";
const char* Config::MSG_END = "Done reading config file";
const char* Config::MSG_GET_VALUE = "Get value for key '%s' with value '%s'";
const char* Config::MSG_GET_VALUE_NOT_FOUND = "No record found for key '%s'";
const char* Config::MSG_SET_VALUE = "Set value for key '%s' with value '%s'";
const char* Config::MSG_WRITE = "Write config to file";

Config::Config() {

};

Config::~Config() {

};

void Config::load() {
    string line;

    cout << string(PREFIX) + string(MSG_READ_CONFIG_PATH) + string(CONFIG_PATH) << endl;
    ifstream infile(CONFIG_PATH);

    cout << string(PREFIX) + string(MSG_START) << endl;
    while (getline(infile, line))
    {
        cout << string(PREFIX) + string(MSG_READ_LINE) + line << endl;
        istringstream iss(line);
        vector<string> tokens{istream_iterator<string>{iss},
                              istream_iterator<string>{}};

        string value = "";
        for(unsigned int i = 1; i < tokens.size(); i++) {
            value = value + " " + tokens[i];
        }

        configValues[tokens[0]] = value;
    }

    cout << string(PREFIX) + string(MSG_END) << endl;
};

string Config::get(string key) {
    if ( configValues.find(key) == configValues.end() ) {
        cout << string(PREFIX) + string_format(MSG_GET_VALUE_NOT_FOUND, key.c_str()) << endl;
        throw MSG_GET_VALUE_NOT_FOUND;
    }
    cout << string(PREFIX) + string_format(MSG_GET_VALUE, key.c_str(), configValues[key].c_str()) << endl;
    return configValues[key];
}

void Config::set(string key, string value) {
    cout << string(PREFIX) + string_format(MSG_SET_VALUE, key.c_str(), value.c_str()) << endl;
    configValues[key] = value;
}


void Config::write() {
        cout << string(PREFIX) + string(MSG_WRITE) << endl;
        ofstream oupfile;
        oupfile.open (CONFIG_PATH);
        for (map<string, string>::iterator it = configValues.begin(); it != configValues.end(); ++it)
        {
            oupfile << it->first + " " + it->second << endl;
        }

        oupfile.close();
}
