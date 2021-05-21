//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Теодор Тодоров Карушков
// ФН: 82204
// Специалност: КН
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 15.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

enum type
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL
    //UNKNOWN
};

class Message
{
private:
    int messageType = 0;
    std::string description;

    void copy(const Message &other);

public:
    Message();
    Message(int type, std::string description);
    Message(const Message &other);

    Message &operator=(const Message &other);
    friend std::ostream &operator<<(std::ostream &out, const Message &other);
};

void Message::copy(const Message &other)
{
    messageType = other.messageType;
    description = other.description;
}

Message::Message()
{
    messageType = 0;
    description = nullptr;
}

Message::Message(int type, std::string description)
{
    /*switch (type)
    {
    case 1:
        messageType = INFO;
        break;
    case 2:
        messageType = WARNING;
        break;
    case 3:
        messageType = ERROR;
        break;
    case 4:
        messageType = CRITICAL;
        break;

    default:
        messageType = UNKNOWN;
        break;
    }*/
    messageType = type;
    this->description = description;
}

Message::Message(const Message &other)
{
    copy(other);
}

Message &Message::operator=(const Message &other)
{
    if (this != &other)
    {
        copy(other);
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Message &other)
{
    switch (other.messageType)
    {
    case 1:
        out << "INFO";
        break;
    case 2:
        out << "WARNING";
        break;
    case 3:
        out << "ERROR";
        break;
    case 4:
        out << "CRITICAL";
        break;
    default:
        out << "UNKNOWN";
        break;
    }

    out << ": " << other.description << std::endl;

    return out;
}

class Logger
{
private:
    Message *myMessage;
    static int counter;
    int size;

    void copy(const Logger &other);

public:
    Logger();
    Logger(Message *myMessage, int size);

    Logger &operator=(const Logger &other);
    friend std::ostream &operator<<(std::string fileName, const Logger &other);
};

int Logger::counter = 0;

void Logger::copy(const Logger &other)
{
    myMessage = other.myMessage;
    size = other.size;
}

Logger::Logger()
{
    size = 0;
}

Logger(Message *myMessage, int size)
{
    this->myMessage = myMessage;
    size = ++counter;
}

Logger &Logger::operator=(const Logger &other)
{
    if (this != &other)
    {
        copy(other);
    }

    return *this;
}

std::ostream &operator<<(std::string fileName, const Logger &other)
{
    std::ofstream fileToWrite(fileName.c_str(), std::ios::app);

    if (!fileToWrite)
    {
        std::cerr << "Error while opening the file\n";
        exit(0);
    }

    fileToWrite << size;
    for (int i = 0; i < size; ++i)
    {
        switch (other.myMessage[i]->messageType)
        {
        case 1:
            fileToWrite << "INFO";
            break;
        case 2:
            fileToWrite << "WARNING";
            break;
        case 3:
            fileToWrite << "ERROR";
            break;
        case 4:
            fileToWrite << "CRITICAL";
            break;
        default:
            fileToWrite << "UNKNOWN";
            break;
        }
        fileToWrite << " " << other.myMessage[i]->description << std::endl;
    }

    fileToWrite.close();
}

class Configuration
{
private:
    static Configuration *instance = 0;
    std::string file;
    Logger myLog;

public:
    Configuration(std::string file, Logger myLog);
};

Configuration::Configuration(std::string file, Logger myLog)
{
    this->file = file;
    this->myLog = myLog;
}

int main()
{
    std::cout << "Enter the number of messages: ";

    int n;
    cin >> n;

    try
    {
        Message *messageArray;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::string type;
    std::string description;

    for (int i = 0; i < n; ++i)
    {
        cout << "Type of Message #" << i << ": ";
        cin >> type;
        cout << "Description of Message #" << i << ": ";
        cin >> description;

        messageArray[i] = new Message((int)type, description);
    }

    std::string file = "config.txt";

    Logger myLog;
    for (int i = 0; i < n; ++i)
    {
        myLog << messageArray[i];
    }

    Config myConfig(file, myLog);

    delete[] messageArray;

    return 0;
}