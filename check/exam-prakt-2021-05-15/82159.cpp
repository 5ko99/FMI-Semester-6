// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Йордан Даниелов Йорданов
// ФН:82159
// Специалност: Компютърни науки
// Курс: I-ви
// Административна група: 2-ра
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

enum class MessageType {
    // UNDEFINED = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    CRITICAL = 4
};

class Message {
private:
    const MessageType type;
    const std::string description;

public:
    Message(const MessageType &type, const std::string &description) : type(type),
                                                                       description(std::move(description)) {}

public:
    MessageType getType() const {
        return this->type;
    }

    std::string getDescription() const {
        return this->description;
    }

public:
    friend std::ostream &operator<<(std::ostream &os, const Message &message) {
        switch (message.type) {
            case MessageType::INFO:
                os << "INFO: ";
                break;
            case MessageType::WARNING:
                os << "WARNING: ";
                break;
            case MessageType::ERROR:
                os << "ERROR: ";
                break;
            case MessageType::CRITICAL:
                os << "CRITICAL: ";
                break;
        }

        os << message.description;

        return os;
    }
};

class Logger {
private:
    std::ofstream osFile;
    static int infoCount;
    static int warningCount;
    static int errorCount;
    static int criticalCount;

public:
    Logger(std::string path) {
        osFile.open(path, std::ios::app);

//        infoCount = 0;
//        warningCount = 0;
//        errorCount = 0;
//        criticalCount = 0;
    }

    Logger(const Logger &logger) = delete;

    ~Logger() {
        if (this->osFile.is_open())
            this->osFile.close();
    }

public:
    static int getInfoCount() {
        return infoCount;
    }

    static int getWarningCount() {
        return warningCount;
    }

    static int getErrorCount() {
        return errorCount;
    }

    static int getCriticalCount() {
        return criticalCount;
    }

private:
    static void increaseMessageCount(const MessageType &messageType) {
        switch (messageType) {
            case MessageType::INFO:
                infoCount++;
                break;
            case MessageType::WARNING:
                warningCount++;
                break;
            case MessageType::ERROR:
                errorCount++;
                break;
            case MessageType::CRITICAL:
                criticalCount++;
                break;
        }
    }

public:
    Logger &operator=(const Logger &logger) = delete;

    std::ofstream &operator<<(const Message &message) {
        if (!this->osFile.is_open()) {
            throw std::invalid_argument("File didn't open!");
        }

        this->osFile << message << endl;

        //Logger::increaseMessageCount(message.getType());

        return this->osFile;
    }
};


int main() {
    std::ifstream configFile("config.txt");

    std::string path;
    configFile >> path;

    configFile.close();

    try {
        Logger logger(path);

        int num, messageType;
        std::string description;

        cout << "Enter number of messages: " << endl;
        cin >> num;

        cout << "Enter message parameters in format message_type(number: 1-4) message(text)" << endl;
        for (int i = 0; i < num; ++i) {
            cin >> messageType;
            getline(cin, description);

            while (messageType < 1 || messageType > 4) {
                cout << "Wrong input! Try again: " << endl;

                cin >> messageType;
                getline(cin, description);

            }


            Message message((MessageType) messageType, description);

            logger << message;
        }
    }
    catch (std::invalid_argument &exc) {
        cout << exc.what() << endl;
        return -1;
    }


    return 0;
}