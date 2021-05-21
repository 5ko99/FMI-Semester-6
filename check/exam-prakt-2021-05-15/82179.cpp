// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: I
// ФН:82179
// Специалност: кн 
// Курс:1
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include<fstream>

enum MessageType
{
    info,
    warning,
    error,
    criticalError
};

class Message
{
private:
    MessageType messageType;
    std::string description;
public:
    Message(MessageType messageType, std::string description)
    {
        this->messageType = messageType;
        this->description = description;
    }

    friend std::ostream& operator<<(std::ostream& os, const Message& m)
    {
        if(m.messageType == MessageType::criticalError)
        {
            std::cout << "CRITICAL ERROR" << ": " << m.description;
        }
        else
        {
            std::cout << m.messageType << ": " << m.description;
        }
    }

    MessageType getMessageType()
    {
        return messageType;
    }
};

class Logger
{
private:
    static std::ofstream outfile;
    static std::string currentLoggingFile;
    static unsigned int infoMessagesCount;
    static unsigned int wariningMessagesCount;
    static unsigned int errorMessagesCount;
    static unsigned int criticalErrorMessagesCount;

public:
    void openLoggingFile(std::string fileLocation)
    {
        //outfile.open(fileLocation);
    }
    friend std::ostream& operator<<(std::ostream &out, Message message)
    {
        out << message <<std::endl;

        MessageType messageType = message.getMessageType();
        switch (messageType)
        {
        case MessageType::info:
            ++infoMessagesCount;
            break;

        case MessageType::warning:
            ++wariningMessagesCount;
            break;

        case MessageType::error:
            ++errorMessagesCount;
            break;

        case MessageType::criticalError:
            ++criticalErrorMessagesCount;
            break;
        default:
            break;
        }
    }
    unsigned int getInfoMessagesCount()
    {
        return infoMessagesCount;
    }
    unsigned int getWariningMessagesCount()
    {
        return wariningMessagesCount;
    }
    unsigned int getErrorMessagesCount()
    {
        return errorMessagesCount;
    }
    unsigned int getCriticalErrorMessagesCount()
    {
        return criticalErrorMessagesCount;
    }
};

class Configuration
{
private:
    std::ifstream ifile;
    std::string configurationFilePath = "config.txt";
    std::string loggerFilePath;
    Logger logger;

public:
    void setPath(std::string path)
    {
        if (!path.empty() && path != "" )
        {
            configurationFilePath = path;
        }
        
        ifile.open(configurationFilePath);
        ifile >> loggerFilePath;

        logger.openLoggingFile(loggerFilePath);
    }
};

int main()
{
    std::string path;
    Configuration configuration;
    std::string command;
    std::string commandArgument;
    MessageType mType;

    std::cout << "If you want to work with the default configuration file press enter without type anything" << std::endl;
    std::cout << "Configuration File: ";
    std::cin >> path;

    try
    {
        configuration.setPath(path);
    }
    catch(const std::exception& e)
    {
        std::cout<<"the configuration cannot be proceed";
        return 1;
    }

    std::cout << "you can add messages until you type end as command";
    std::cin >> command >> commandArgument;

    while (command != "end")
    {
        
    }
    

    return 0;
}