// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Виктор Николаев Нолев
// ФН: 45641
// Специалност: Информатика
// Курс: 2.
// Административна група: 1.
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

// Here we can add last element in enum that would hold the total number of types :)
const unsigned TYPES_COUNT = 4;
enum Type {
    INFO, WARNING, ERROR, CRITICAL
};

class Message {
private:
    Type m_type;
    std::string m_description;
public:
    Message(Type type, std::string &description);

    friend std::ostream &operator<<(std::ostream &out, const Message &message);

};

Message::Message(Type type, std::string &description)
        : m_type(type), m_description(description) {
    m_type = type;
}

std::ostream &operator<<(std::ostream &out, const Message &message) {
    switch (message.m_type) {
        case INFO:
            out << "INFO: " << message.m_description;
            break;
        case WARNING:
            out << "WARNING: " << message.m_description;
            break;
        case ERROR:
            out << "ERROR: " << message.m_description;
            break;
        case CRITICAL:
            out << "CRITICAL ERROR: " << message.m_description;
            break;
        default:
            out << "UNKNOWN: " << message.m_description;
            break;
    }
    return out;
}


class Logger {
private:
    // Another approach is to keep message here in collection
    // Appending each message in file is done by accessing each message by index in collection

    static std::fstream m_file;

    static std::string m_fileName;
    // Counts each message type - each position corresponds to message type
    static unsigned countEach[TYPES_COUNT];


public:
    Logger(const std::string &fileName);

    void openFile();

    void closeFile();

    friend std::istream &operator>>(Logger &logger, Message &message);

//    friend std::ostream &operator<<(std::ostream &out, const Logger &logger);

    friend Logger &operator<<(Logger &logger, const Message &message) {
        m_file << message;
        return logger;
    }

};

/*std::ostream &operator<<(std::ostream &out, const Logger &message) {


    return out;
}*/


/*
std::istream &operator>>(std::istream &in, Logger &logger) {


    return in;
}*/

Logger::Logger(const std::string &fileName) {
    m_fileName = fileName;
    // TODO Check for errors
}

void Logger::openFile() {
    m_file.open("..\\" + m_fileName, std::ios::out | std::ios::in | std::ios::app);
    if (!m_file) {
        throw std::invalid_argument("Cannot open file: " + m_fileName);
    }
    std::cout << "File: " + m_fileName + " is opened for read and write operations\n";
}

void Logger::closeFile() {
    m_file.close();
    std::cout << "File: " + m_fileName + " is now closed!";
}


class Configuration {
public:
    Configuration() = default;

    Configuration(const Configuration &other) = delete;

    Configuration &operator=(const Configuration &other) = delete;

//    Configuration(Logger& logger, std::string& file);

    static Configuration &getInstance() {
        static Configuration configuration;
        return configuration;
    }

private:
    Logger m_logger;
    std::string m_file;

    ~Configuration();

};

int main() {

    Message m(Type::INFO, "Information in this message");
    Message n(Type::CRITICAL, "Cannot open input file");

    Logger log("log.txt");
    log.openFile(); // Check for errors

    log << m << n;

    log.closeFile();
    return 0;
}

