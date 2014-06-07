#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>


using std::string;
using std::ifstream;
using std::map;
using std::cout;

class contactBook{
public:
    static contactBook* Instance();
    bool addContact(string name, string ip, bool sending, bool receiving);
    bool delContact(string name);
    bool setTimeout(string name, unsigned timeout);
    string getIP(string name);
    bool getSending(string name);
    bool getReceiving(string name);
    unsigned getTimeout(string name);
    void print();

private:
    contactBook();
    void loadFile();

    class contact{
    public:
        string name;
        string ip;
        unsigned timeout;
        bool sending;
        bool receiving;
    };

    static contactBook *instance;
    map<string, contact> contactMap;
    static string configFile;
    static unsigned configTimeout;
};

