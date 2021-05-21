//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Ивайло Атанасов
// ФН: 45763
// Специалност: Информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 15 май
// Начален час на контролното: 9:00
// Кой компилатор използвате: Clang
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <fstream>

enum MessageType{
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Message{
private:
    const MessageType type{};
    const std::string description{};
    std::string enumToStr(MessageType tp){
        switch (tp){
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            case CRITICAL: return "CRITICAL";
        }
    }
public:
    Message(MessageType type, std::string desc):type(type), description(desc){}
    void printToStream(std::ostream str){
        str<<type<<": "<<description;
    }
    const MessageType& getType(){
        return type;
    }
    
    friend void operator <<(std::ostream& str, Message& msg);
    
};

void operator<<(std::ostream& str,Message& msg){
    str<<msg.enumToStr(msg.type)<<": "<<msg.description;
}



class Logger{
private:
    std::ofstream file;
    static int infoCount;
    static int warnCount;
    static int errrCount;
    static int critCount;
public:
    static int getCount(MessageType type){
        switch (type){
            case INFO: return infoCount;
            case WARNING: return warnCount;
            case ERROR: return errrCount;
            case CRITICAL: return critCount;
        }
    }
    Logger(std::string path){
        file.open("test.txt", std::ios::app);
    }
    ~Logger(){
        file.close();
    }
       
    friend void operator <<(Logger& log, Message& msg);
};
void operator<<(Logger& log, Message& msg){
    log.file<<msg;
    log.file<<"\n";
}




class Configuration{
private:
    std::ifstream file;
    Logger logger;
public:
    static void readConfig(){
        
    }
};



int main(int argc, char** argv){
    std::string confPath;
    if(argc==1){
        confPath = "config.txt";
    } else {
        confPath = argv[2];
    }
    
    
    Message msg1(INFO, "inf1");
    Message msg2(WARNING, "war1");
    Message msg3(WARNING, "war2");
    Message msg4(ERROR, "err1");
    
    
    //std::cout<<msg;
    
    Logger lg("asd.txt");
    lg<<msg1;
    lg<<msg2;
    lg<<msg3;
    lg<<msg4;
    
    //lg<<msg1<<msg2;
    
    
    return 0;
}
