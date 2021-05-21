
//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
//Контролно по ООП - практикум
//
// Име: Боян Веселинов Павлов
// ФН: 82027
// Специалност: КН
// Курс: 1
// Административна група:3
// Ден, в който се явявате на контролното: 15.05
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::string;
// using namespace std;

#ifndef _MY_EXCEPTIONS_
#define _MY_EXCEPTIONS_

class myERROR : public std::exception
{
public:
    const char *what() const throw()
    {
        "Error has occured";
    }
};

class myWARNING : public std::exception
{
public:
    const char *what() const throw()
    {
        "Warning!";
    }
};

class myCRITICAL_ERROR : public std::exception
{
public:
    const char *what() const throw()
    {
        "Critical error has occured";
    }
};
#endif //_MY_EXCEPTIONS_

//======================================================
#ifndef _MESSAGE_
#define _MESSAGE_

enum TypeOfMessage
{
    info,
    warning,
    error,
    critical_error
};

class Message
{
private:
    const string m_describtion;
    const int m_typeOfMessage;

public:
    //TODO
    Message(string given_message, int typeOfM);

    ostream &operator<<(const ostream &obj);
    string typeOfMessage();
    void menu();

    string getDescribtion() const;
    int getTypeOfMessage() const;
};

#endif // _MESSAGE_

Message::Message(string given_message, int typeOfM)
    : m_typeOfMessage(typeOfM), m_describtion(given_message)
{
    menu();
}

ostream &Message::operator<<(const ostream &obj)
{
    string typeOfMessage1 = typeOfMessage();
    obj << typeOfMessage1;
    obj << m_describtion << endl;
}

string Message::typeOfMessage()
{
    switch (m_typeOfMessage)
    {
    case info:
        return "INFO: ";
        break;
    case warning:
        return "WARNING: ";
        break;
    case error:
        return "ERROR: ";
        break;
    case critical_error:
        return "CRITICAL: ";
        break;

    default:
        cout << "something went wrong";
        break;
    }
}

void Message::menu()
{
    switch (m_typeOfMessage)
    {
    case info:
        break;
    case warning:
        throw myWARNING();
        break;
    case error:
        throw myERROR();
        break;
    case critical_error:
        throw myCRITICAL_ERROR();
        break;

    default:
        cout << "something went wrong";
        break;
    }
}

string Message::getDescribtion() const
{
    return m_describtion;
}

int Message::getTypeOfMessage() const
{
    return m_typeOfMessage;
}

//======================================================
#ifndef _LOGGER_
#define _LOGGER_

class Logger
{
private:
    Message myMessage;
    string fileName;
    Logger loadFromFile(string fileName);
    void saveInFile(string fileName);
    bool ifElementExist(string fileName, string element);

public:
    Logger(Message givenMessage, string given_fileName);
    //void countMessages(string fileName);
    int countInfo();
    int countWarnings();
    int countErrors();
    int countCritical();

    ostream &operator<<(const ostream &obj);
};
#endif //_LOGGER_

Logger::Logger(Message givenMessage, string given_fileName)
    : fileName(given_fileName), myMessage(givenMessage)
{
}

Logger Logger::loadFromFile(string fileName)
{
    ifstream log(fileName);
    if (log.is_open())
    {
        log >> myMessage >> endl;
    }
    log.close();
}

ostream &Logger::operator<<(const ostream &obj)
{
}

// int Logger::countMessages(string fileName)
// {
//     ifstream in(fileName, std::ios::in);
//     int counter = 0;
//     string temp;
//     while (!in.eof())
//     {
//         in >> temp;
//         counter++;
//     }
//     return counter;
// }

int Logger::countInfo()
{
    ifstream in(fileName, std::ios::in);
    int counter = 0;
    string temp;
    string info = "INFO";
    while (!in.eof())
    {
        in >> temp;
        if (info == temp)
        {
            counter++;
        }
    }
    return counter;
}

int Logger::countWarnings()
{
    ifstream in(fileName, std::ios::in);
    int counter = 0;
    string temp;
    string error = "ERROR";
    while (!in.eof())
    {
        in >> temp;
        if (error == temp)
        {
            counter++;
        }
    }
    return counter;
}

int Logger::countErrors()
{
    ifstream in(fileName, std::ios::in);
    int counter = 0;
    string temp;
    string warning = "WARNING";
    while (!in.eof())
    {
        in >> temp;
        if (warning == temp)
        {
            counter++;
        }
    }
    return counter;
}

int Logger::countCritical()
{
    ifstream in(fileName, std::ios::in);
    int counter = 0;
    string temp;
    string critical = "CRITICAL";
    while (!in.eof())
    {
        in >> temp;
        if (critical == temp)
        {
            counter++;
        }
    }
    return counter;
}

bool Logger::ifElementExist(string fileName, string element)
{
    ifstream in(fileName, std::ios::in);
    string temp;
    while (!in.eof())
    {
        in >> temp;
        if (element == temp)
        {
            return true;
        }
    }
    return false;
}

void Logger::saveInFile(string fileName)
{
    ofstream log(fileName, std::ios::out | std::ios::app);
    if (log.is_open())
    {
        log << myMessage.typeOfMessage();
        log << myMessage.getDescribtion() << endl;
    }

    log.close();
}

//======================================================
#ifndef _CONFIGURATION
#define _CONFIGURATION

class Configuration
{
private:
    Logger log;
    string fileName;

public:
    //TODO
    //create a static variable
    //intitialize the static variable;

    static Configuration instance();
    Configuration();
    Configuration(const Configuration &) = delete;
    Configuration &operator=(const Configuration &) = delete;
};

#endif //_CONFIGURATION

Configuration::Configuration(/* args */)
{
}
Configuration Configuration::instance()
{
    // static Configuration instance1;
}

//======================================================

int main()
{
    //fstream log("logFile.txt");
    Message t("test-info", 1);
    cout << t;

    return 0;
}