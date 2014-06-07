#include "contactBook.h"

string contactBook::configFile = "C:\\Users\\BarT\\Desktop\\stud\\tin\\projekt\\config.txt";

unsigned contactBook::configTimeout = 120;


contactBook* contactBook::instance = NULL;

contactBook* contactBook::Instance(){
    if(instance == NULL)
        instance = new contactBook;
    return instance;
}

contactBook::contactBook(){
    loadFile();
}

void contactBook::loadFile(){
    ifstream file;
    file.open(configFile.c_str());
    if(!file.good())
        return;
    while(!file.eof()){
        bool lineOK = true;
        string line;
        string token[3] = {};
        std::getline(file, line);
        std::istringstream sline(line);
        for(int i = 0; i < 3; ++i){
            std::getline(sline, token[i], ' ');
            if(token[i].empty())
                lineOK = false;
        }
        if(!lineOK)
            continue;
        contact tmpContact;
        tmpContact.ip = token[0];
        tmpContact.name = token[1];
        tmpContact.receiving = (token[2].find_first_of("r") != string::npos);
        tmpContact.sending = (token[2].find_first_of("s") != string::npos);
        if(!tmpContact.receiving && !tmpContact.sending)
            continue;
        tmpContact.timeout = configTimeout;
        contactMap.insert(std::pair<string, contact>(tmpContact.name, tmpContact));
    }
    file.close();
}

bool contactBook::addContact(string name, string ip, bool sending, bool receiving){
    if(!sending && !receiving)
        return false;
    if(name.empty() || ip.empty())
        return false;
    //TODO validate IP
    contact tmpContact;
    tmpContact.ip = ip;
    tmpContact.name = name;
    tmpContact.sending = sending;
    tmpContact.receiving = receiving;
    contactMap.insert(std::pair<string, contact>(tmpContact.name, tmpContact));
    return true;
}

bool contactBook::delContact(string name){
    unsigned n = contactMap.erase(name);
    return n > 0;
}

bool contactBook::setTimeout(string name, unsigned timeout){
    map<string, contact>::iterator it = contactMap.find(name);
    if(it == contactMap.end())
        return false;
    it->second.timeout = timeout;
    return true;
}

string contactBook::getIP(string name){
    map<string, contact>::iterator it = contactMap.find(name);
    if(it == contactMap.end())
        return "";
    return it->second.ip;
}

bool contactBook::getSending(string name){
    map<string, contact>::iterator it = contactMap.find(name);
    if(it == contactMap.end())
        return false;
    return it->second.sending;
}

bool contactBook::getReceiving(string name){
    map<string, contact>::iterator it = contactMap.find(name);
    if(it == contactMap.end())
        return false;
    return it->second.receiving;
}

unsigned contactBook::getTimeout(string name){
    map<string, contact>::iterator it = contactMap.find(name);
    if(it == contactMap.end())
        return 0;
    return it->second.timeout;
}

void contactBook::print(){
    cout<<"Kontakty: \n";
    for(map<string, contact>::iterator it = contactMap.begin(); it != contactMap.end(); ++it){
        cout<<it->second.name
            <<" - "<<it->second.ip
            <<", wysylanie: "<<(it->second.sending ? "tak" : "nie")
            <<", odbieranie: "<<(it->second.receiving ? "tak" : "nie")
            <<", czas oczekiwania: "<<it->second.timeout
            <<"\n";
    }
    cout<<"\n";
}

