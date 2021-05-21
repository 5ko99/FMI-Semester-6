//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Румен Георгиев Азманов
// ФН: 82176
// Специалност: Компютърни науки
// Курс: Първи 1
// Административна група: Трета 3
// Ден, в който се явявате на контролното: 15.05.2021г.
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//
// #define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

// using namespace std;

enum TypeMessage {
    EMPTY = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

class Message {
   private:
    TypeMessage type;
    std::string description;

   public:
    Message(TypeMessage typeInput, std::string descriptionInput) : type(typeInput) {
        description.assign(descriptionInput.c_str());
    }

    void operator<<(std::fstream& file) {
        switch (type) {
            case INFO:
                file << "INFO: ";
                break;
            case WARNING:
                file << "WARNING: ";
                break;
            case ERROR:
                file << "ERROR: ";
                break;
            case CRITICAL:
                file << "CRITICAL: ";
                break;
            default:
                break;
        }
        file << description.c_str() << std::endl;
    }

    ~Message() {
    }
};

class Logger {
   private:
    std::string pathToSave;
    static unsigned int counterInfo;
    static unsigned int counterWarning;
    static unsigned int counterError;
    static unsigned int counterCritical;

   public:
    unsigned int getInfo() {
        return counterInfo;
    }
    unsigned int getWarning() {
        return counterWarning;
    }
    unsigned int getError() {
        return counterError;
    }
    unsigned int getCritical() {
        return counterCritical;
    }
    void setLoggerPath(std::string path) {
        pathToSave.assign(path);
    }
    void operator<<(Message m) {
        std::fstream append;
        append.open(pathToSave.c_str(), std::ios::app);
        m.operator<<(append);
        append.close();
    }
};

unsigned int Logger::counterInfo = 0;
unsigned int Logger::counterWarning = 0;
unsigned int Logger::counterError = 0;
unsigned int Logger::counterCritical = 0;

class Configuration {
   private:
    static bool isSingleton;
    std::string filePathToLog;
    Logger loggerObject;

   public:
    Configuration(std::string filePath) {
        if (isSingleton == false) {
            std::fstream readerFromWhere(filePath.c_str(), std::ios::in | std::ios::out);
            std::getline(readerFromWhere, filePathToLog);
            if (filePathToLog.empty() == true) {
                filePathToLog.assign("config.txt");
            }
            readerFromWhere.close();
            if (!(filePathToLog.c_str()[filePathToLog.length() - 4] == '.' &&
                  filePathToLog.c_str()[filePathToLog.length() - 3] == 't' &&
                  filePathToLog.c_str()[filePathToLog.length() - 2] == 'x' &&
                  filePathToLog.c_str()[filePathToLog.length() - 1] == 't')) {
                throw std::invalid_argument("Not a text file!");
            }
            loggerObject.setLoggerPath(filePathToLog);
            isSingleton = true;
        } else {
            throw std::invalid_argument("Already existing singleton");
        }
    }

    void writelog() {
        TypeMessage typeInput = EMPTY;
        int typeIn = 0;
        std::string descriptionInput;
        do {
            std::cout << "type:";
            std::cin >> typeIn;
            typeInput = (TypeMessage)typeIn;
        } while (!(typeIn == 1 || typeIn == 2 || typeIn == 3 || typeIn == 4));
        std::cout << "description:";
        std::cin >> descriptionInput;
        Message m(typeInput, descriptionInput);
        loggerObject << m;
    }
};

bool Configuration::isSingleton = false;

int main(int argc, char* argv[]) {
    try {
        Configuration myconfiguration(argv[1]);
        char yesno = 'Y';
        while (true) {
            std::cout << "Input log? (Y/N) ";
            std::cin >> yesno;
            if (yesno == 'Y' || yesno == 'y') {
                myconfiguration.writelog();
            } else
                break;
        }
    } catch (std::invalid_argument& e) {
        std::cout << e.what();
    }

    return 0;
}