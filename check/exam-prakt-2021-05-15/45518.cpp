// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Яни Дренчев
// ФН: 45518
// Специалност: Информатика
// Курс: прекъснал 2
// Административна група: -
// Ден, в който се явявате на контролното: събота 15.05.21
// Начален час на контролното: 9:00
// Кой компилатор използвате: Clang
//
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum class Type {
    INFO,
    WARNING,
    ERROR,
    CRITICAL_ERROR
};

class Message {
private:
    Type type;
    std::string description;

public:

    Message(Type type1, const std::string &string);

    Type get_type() const {
        return type;
    }

    friend std::ostream &operator<<(std::ostream &ostream, const Message &mes) {
        std::string str;
        switch (mes.type) {
            case Type::INFO:
                str += "INFO: " + mes.description;
                break;
            case Type::WARNING:
                str += "WARNING: " + mes.description;
                break;
            case Type::ERROR:
                str += "ERROR " + mes.description;
                break;
            case Type::CRITICAL_ERROR:
                str += "CRITICAL_ERROR " + mes.description;
                break;
        }
        ostream << str;
        return ostream;
    };

};

Message::Message(Type type1, const std::string &desc) : type(type1), description(desc) {
}

class Logger {
private:
    std::ofstream file;
    static unsigned int infoCounter;
    static unsigned int warningCounter;
    static unsigned int errorCounter;
    static unsigned int criticalCounter;

    void logToFile(Message &mes) {
        switch (mes.get_type()) {
            case Type::INFO:
                infoCounter++;
                break;
            case Type::WARNING:
                warningCounter++;
                break;
            case Type::ERROR:
                errorCounter++;
                break;
            case Type::CRITICAL_ERROR:
                criticalCounter++;
                break;
        }
        file << mes << "\n";
    }

public:

    Logger(const std::string &path) {
        file.open(path);
        if (!file.is_open()) {
            std::cout << "Could not open file";
        }
    }

    ~Logger() {
        file.close();
    }

    static unsigned int get_errors() {
        return errorCounter;
    }

    static unsigned int get_infos() {
        return infoCounter;
    }

    static unsigned int get_warning() {
        return warningCounter;
    }

    static unsigned int get_critical_errors() {
        return criticalCounter;
    }

    friend Logger &operator<<(Logger &logger, Message &message) {
        logger.logToFile(message);
        return logger;
    }
};

unsigned int Logger::criticalCounter = 0;
unsigned int Logger::errorCounter = 0;
unsigned int Logger::warningCounter = 0;
unsigned int Logger::infoCounter = 0;

class Configuration {
private:
    Logger *logger;
    std::string fileName;
public:
    Configuration(const std::string &path) {
        std::ifstream file;
        file.open(path);
        std::string secondPath;
        if (file.is_open()) {
            getline(file, secondPath);
            logger = new Logger(secondPath);
            fileName = path;
        } else {
            throw std::invalid_argument("Could not open file");
        }
    }

    ~Configuration() {
        delete[] logger;
    }

    std::string getPath() const {
        return fileName;
    }
};

std::string getCommand(const std::string &string) {
    std::string cmdString;
    for (std::string::size_type i = 0; i < string.size(); ++i) {
        if (string[i] == ' ')
            return cmdString;
        cmdString += toupper(string[i]);
    }
    return cmdString;
}

std::string getArgument(const std::string &string, int index) {
    std::string cmdString;
    for (std::string::size_type i = index; i < string.size(); ++i) {
        if (string[i] == ' ')
            return cmdString;
        cmdString += toupper(string[i]);
    }
    return cmdString;
}

int main(int argc, char *argv[]) {
    std::string command;
    std::string argument;
    Message *mess;
    Configuration *confing;

    if (argv[0][0] != ' ') {
        try {
            confing = new Configuration("test1.log");
        } catch (std::invalid_argument &exx) {
            std::cout << exx.what();
            return 1;
        }

    } else {
        try {
            confing = new Configuration("test1.log");
        } catch (std::invalid_argument &exx) {
            std::cout << exx.what();
            return 1;
        }
    }

    Logger logger(confing->getPath());

    while (true) {
        getline(std::cin, command);
        std::string commandString = getCommand(command);
        auto index = commandString.length() + 1;
        argument = getArgument(command, index);
        std::cout << commandString << "\n";
        std::cout << argument << "\n";


        if (commandString == "WARNING") {
            mess = new Message(Type::WARNING, argument);
        }
        if (commandString == "ERROR") {
            mess = new Message(Type::ERROR, argument);
        }
        if (commandString == "CRITICAL") {
            mess = new Message(Type::CRITICAL_ERROR, argument);
        }
        if (commandString == "INFO") {
            mess = new Message(Type::INFO, argument);
        }
        if (commandString == "EXIT") {
            break;
        }
//        logger << mess;
        std::cout << *mess << "\n";
    }
    return 0;
}