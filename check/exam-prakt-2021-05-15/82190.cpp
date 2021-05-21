// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Михаил Сашков
// ФН: 82190
// Специалност: Компютърни науки
// Курс: I
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.21г.
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>


enum Type {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Message {
private:
    Type type;
    std::string description;

public:
    Message(Type type, std::string description);
    friend std::ostream& operator <<(std::ostream& out, const Message& message);
    Type getType() const;
    std::string getDescription() const;

};

class Logger {
private:
    static unsigned int countForINFO;
    static unsigned int countForWARNING;
    static unsigned int countForERROR;
    static unsigned int countForCRITICAL;
    int info = 0;
    int warning = 0;
    int error = 0;
    int critical = 0;
    
public:
    Logger();
    friend void operator <<(const Logger& log, const Message& message);
    void count() const;

};

unsigned int Logger::countForINFO = 0;
unsigned int Logger::countForWARNING = 0;
unsigned int Logger::countForERROR = 0;
unsigned int Logger::countForCRITICAL = 0;


Logger::Logger() {

    info = countForINFO;
    warning = countForWARNING;
    error = countForERROR;
    critical = countForCRITICAL;

}

void Logger::count() const {

    std::cout << "INFO: " << info << std::endl;
    std::cout << "WARNING: " << warning << std::endl;
    std::cout << "ERROR: " << error << std::endl;
    std::cout << "CRITICAL: " << critical << std::endl;

}


void operator <<(const Logger& log, const Message& message) {

    std::ofstream file("log.txt", std::ios::app);

    if(message.getType() == 0){
        Logger::countForINFO++;
        file << "INFO: ";
    }

    if(message.getType() == 1) {
        Logger::countForWARNING++;
        file << "WARNING: ";
    }

    if(message.getType() == 2) {
        Logger::countForERROR++;
        file << "ERROR: ";
    }

    if(message.getType() == 3) {
        Logger::countForCRITICAL++;
        file << "CRITICAL: ";
    }


    file << message.getDescription() << std::endl;

    file.close();
}


Message::Message(Type type, std::string description) : type(type), description(description)
{}

std::ostream& operator <<(std::ostream& out, const Message& message) {

    
    if(message.type == 0) {
        std::cout << "INFO: ";
    }

    if(message.type == 1) {
        std::cout << "WARNING: ";
    }

    if(message.type == 2) {
        std::cout << "ERROR: ";
    }

    if(message.type == 3) {
        std::cout << "CRITICAL: ";
    }

    out << message.description;
    std::cout << std::endl;

    return out;

}

Type Message::getType() const {
    return type;
}

std::string Message::getDescription() const {
    return description;
}

int main() {

    Message message(INFO, "Something went wrong!");
    Message message1(WARNING, "SOmething");
    Logger log;

    log << message;
    std::cout << message;
    log.count();


	return 0;
}