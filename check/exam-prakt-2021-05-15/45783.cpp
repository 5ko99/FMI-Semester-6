//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Веселин Христов Пенев
// ФН: 45783
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 15
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

enum Type{
    info,
    warning,
    error,
    critical
};

class Message{

private:
    const Type messageType;
    const std::string description;

public:



    Message() = delete;

    Message(Type type, const char* description)
        :description(description), messageType(type){
    }

    Message(Message& m)
        :description(m.description), messageType(m.messageType){
    }

    friend std::ostream& operator<<(std::ostream& out, Message& m){

        if(m.messageType == info){
            out << "INFO";
        }
        if(m.messageType == warning){
            out << "WARNING";
        }
        if(m.messageType == error){
            out << "ERROR";
        }
        if(m.messageType == critical){
            out << "CRITICAL";
        }

        out << ": " << m.description;

        out << std::endl;

        return out;
    }


};

/*std::ostream Message::operator<<(std::ostream out){
     out << type << description;
}*/

class Logger{

private:
    std::size_t allocated;
    std::size_t count;
    Message** logs;

public:

    Logger(){
        allocated = 4;
        count = 0;
        logs = new Message*[allocated];
    }

    Logger(size_t count){
        allocated = count;
        this->count = count;
        logs = new Message*[allocated];
    }

    void extendLogs(size_t newSize){
        allocated = newSize;
        delete[] logs;
        try{
            logs = new Message*[allocated];
        }catch(std::bad_alloc& e){
            std::cerr << "memory allocation problem";
        }
    }

    void addMessage(Message& m){
        if(count + 1 >= allocated){
            extendLogs(allocated*2);
        }
        logs[count++] = new Message(m);
    }

    friend Logger& operator<<(Logger& log, Message& m){
        log.addMessage(m);
        return log;
    }

    Message* operator[](std::size_t pos){
        if(pos >= count) return nullptr;
        return logs[pos];
    }

    Logger operator=(Logger& logger){
        count = logger.count;
        allocated = logger.allocated;
        logs = new Message*[allocated];
        for(std::size_t i = 0; i < count; i++){
            logs[i] = new Message(*logger[i]);
        }
    }

};


class Configuration{

private:
    const char* filename;
    Logger logger;

public:

    Configuration() = delete;

    Configuration(const char* filename, Logger logger)
        :filename(filename)
    {
        //Logger = logger;
    }


    void addMessage(Message& m){
        logger << m;
    }

};

int main()
{

    std::string configFileName;

    getline(std::cin, configFileName);

    if(strlen(configFileName.c_str()) == 0){
        configFileName = "config.txt";
    }

    Logger log;
    Configuration config(configFileName.c_str(), log);


    std::size_t messageCount;
    std::cin >> messageCount;
    std::cin.ignore();       // ignores next empty line so it does not get counted as a message
    for(std::size_t i = 0; i < messageCount; i++){

        std::string input;
        getline(std::cin, input);

        Message m(info, input.c_str());

        config.addMessage(m);

    }


	return 0;
}
