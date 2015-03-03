Compile :
```sh
g++ -std=c++11 -pthread -Wall src/*.cpp -o dh15-webservert
```
Run : 
```sh
./dh15-webservert
```
Use config file
```cpp
//init config file
Config config;
//Load config from file
config.load();

//Get value by key
config.get("webroot");

//Exception thrown when key not found
try {
    config.get("no found key");
}catch (const char* msg) {
    cout << msg << endl;
}

//Set new or replace config  value
config.set("webroot", "/var/test");
config.get("webroot");

//Write changes to config file
config.write();
```