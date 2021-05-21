// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Валери Добрев
// ФН:45807
// Специалност: Информатика
// Курс:1
// Административна група:5
// Ден, в който се явявате на контролното: 15/5/2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <iostream>
#include<fstream>
#include <string>

using std::string;
using std::fstream;




enum TYPE{INFO,WARNING, ERROR,CRITICAL};


class StringHelpers{



public:
    StringHelpers()=delete;
    StringHelpers(const StringHelpers& str) = delete;
    StringHelpers& operator=(const StringHelpers& other) = delete;

    static char* getFirstWord(const char* line){
        if(!line) return nullptr;
        size_t len = strlen(line);
        char* res = new char[len + 1];
        for(unsigned int i = 0; i <= len; i++){
            if(line[i] == ' '){
                res[i] = '\0';
                break;
            }
            res[i]=line[i];
        }

        return res;
    } 
    static char* getSecondWord(const char* line){
        if(!line) return nullptr;
        
        size_t res_index;
        while(*line != ' ') line++;

        size_t len =strlen(line);
        char* res = new char[len + 1];
        for(unsigned i=0; i<=len; i++) res[i] = line[i];

        return res;
    }

    static TYPE getMsgType(const char* line){
        char* res = getFirstWord(line);
        if(strcmp(res,"INFO")==0) {
            delete [] res;
            return TYPE::INFO;
        }
        if(strcmp(res,"WARNING")==0){
            delete [] res;
            return TYPE::WARNING;
        }
        if(strcmp(res,"ERROR")==0){
            delete [] res;
            return TYPE::ERROR;
        }
        
        delete [] res;
        return TYPE::CRITICAL;
        
    }
    
};

class Message{
    const TYPE msg_type;
    const string description;

public:
    Message(const TYPE msg_type, const string description): msg_type(msg_type), description(description){
    }
    
    Message(const Message& other) =delete;
    Message& operator= (const Message& other) = delete;

    friend std::ostream& operator << ( std::ostream& os, Message& msg){
        switch(msg.msg_type) {
            case 0: os<<"INFO";break;
            case 1: os<<"WARNING";break;
            case 2: os<<"ERROR";break;
            case 3: os<<"CRITICAL";break;
        }
        os<<" "<<msg.description;
        return os;
    }
    string getDescription() const { return description; }
};

class Logger{
    static int count[4];
    fstream os;
public:

    Logger(const string& path){
        os.open(path, std::ios::out | std::ios::in | std::ios::app);
        if(!os.is_open()) throw std::runtime_error("Error when reading the file!");
        string line; 
        
        while(getline(os,line)) {
            count[StringHelpers::getMsgType(line.c_str())]++;
        }
        
        // os.close();
        // if(!os.good()) throw std::runtime_error("Error!");

        // os.open(path, std::ios::app);

    }

    ~Logger(){
        os.close();
    }

    static int getNumberOfInfos(){
        return count[0];
    }
    static int getNumberOfWarnings(){
        return count[1];
    }
    static int getNumberOfErrors(){
        return count[2];
    }
    static int getNumberOfCriticals(){
        return count[3];
    }

    Logger& operator<<(Message& msg){
        os << msg;
        return *this;
    }
};
int Logger::count[] = {0,0,0,0};

class Configuration{
    string file;
    Logger log;

    Configuration(string path) : file(path), log(path){
    }
public:
    static Configuration* getInstance(string path){
        static Configuration instance(path);
        return &instance;
    }

    void logMsg(Message& msg){
        log<<msg;
    }

};

int main(int argc, char* argv[])
{
    
    string path("config.txt");
    if(argc==2){
        path = argv[1];
    }
    
    Configuration* config;
    try{
        config = Configuration::getInstance(path);
    }catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
        return -1;
    }
    
    string line("");
    while(line != "exit"){
        getline(std::cin, line);
        char* desc = StringHelpers::getSecondWord(line.c_str());
        Message msg(StringHelpers::getMsgType(line.c_str()), string(desc));
        config->logMsg(msg);
    }
    
	return 0;
}