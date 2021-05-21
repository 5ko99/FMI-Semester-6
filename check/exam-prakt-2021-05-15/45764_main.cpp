//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Валентин Димитров
// ФН: 45764
// Специалност: Информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum messType
{
    info,
    warning,
    error,
    critical
};

class Message
{
    messType type;
    string description;
public:
    Message(messType newType, string newDescription)
    {
        type = newType;
        description = newDescription;
    }
    void operator<<(ostream a)
    {
        switch(type)
        {
            case 0: {a << "INFO: " << description << endl; break;}
            case 1: {a << "WARNING: " << description << endl; break;}
            case 2: {a << "ERROR: " << description << endl; break;}
            case 3: {a << "CRITICAL: " << description << endl; break;}
        }
    }
    messType getType()const
    {
        return type;
    }
};

class Logger
{
    string file;
    size_t counter[4];
public:
    Logger()
    {
        for(int i = 0; i < 4; i++)counter[i] = 0;
    }
    Logger(string newFile)
    {
        file = newFile;
        for(int i = 0; i < 4; i++)counter[i] = 0;
    }
    void editLogger(string newFile)
    {
        file = newFile;
    }
    void operator<<(Message &a)
    {
        ofstream log(file);
        if(log.is_open())
        {
            counter[a.getType()]++;
            log << a << endl;
            log.close();
        }
    }
    size_t getInfos()const
    {
        return counter[0];
    }
    size_t getWarnings()const
    {
        return counter[1];
    }
    size_t getErrors()const
    {
        return counter[2];
    }
    size_t getCriticals()const
    {
        return counter[3];
    }

};

class Configuration
{
    string path;
    Logger log;
public:
    Configuration(string newPath)
    {
        log.editLogger(newPath);
    }
    void operator<<(Message &a)
    {
        log << a;
    }
};

int main()
{
    Configuration config("config.txt");
    string newMessage;
    size_t newType;
    while(true)
    {
        cin >> newType >> newMessage;
        if(newMessage == "exit")break;
        Message a(messType(newType), newMessage);
        config << a;
    }
	return 0;
}

