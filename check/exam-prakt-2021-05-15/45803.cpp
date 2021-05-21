// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Деян Крумов
// ФН:45803
// Специалност:Информатика
// Курс:1-ви
// Административна група:5
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: <тук попълнете часа за вашата група>9:00
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang>Visual c
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
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum type
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Message
{
    public:
    const char* type;
    const std::string description;

    public:
    Message(const enum type, const std::string& description) :type(type),description(description){};

    std::ostream& operator>>(std::ostream& out)
    {
        out <<  '<' << this->type << '>' << '<' << this->description << '>';
        return out;
    }
};

class Logger
{
    std::ofstream file;

    struct count
    {
        std::size_t infoCount;
        std::size_t warningCount;
        std::size_t errorCount;
        std::size_t criticalCount;
    };
    static count countTypes;

    public:

    Logger() = default;

    Logger(const std::string fileName)
    {
        file.open(fileName,std::ios::app);
        if(!file.is_open())
        {
            throw std::exception("Failed to open file");
        }
    }

    void counter(const Message& m)
    {
        if(strcmp(m.type,"INFO") == 0)
        {
            Logger::countTypes.infoCount++;
            return;
        }

        if(strcmp(m.type,"WARNING") == 0)
        {
            Logger::countTypes.warningCount++;
            return;
        }

        if(strcmp(m.type,"ERROR") == 0)
        {
            Logger::countTypes.errorCount++;
            return;
        }

        if(strcmp(m.type,"CRITICAL") == 0)
        {
            Logger::countTypes.infoCount++;
            return;
        }
    }

    Logger& operator<<(const Message& m)
    {
        file << m.type << " ";
        file << m.description << '\n';
        counter(m);
        return *this;
    }

    ~Logger()
    {
        file.close();
    }
};

class Configuration
{
    Logger log;
    std::ifstream configf;

    static Configuration* instance;
    
    Configuration(const std::string& filePath)
    {
        configf.open(filePath);
        if(!configf.is_open())
        {
            throw std::exception("Failed to open file");
        }
        std::string path;
        std::getline(configf,path);

        Logger(path);
    }
    
    public:
    Configuration* getInstance(std::string& filePath)
    {
        if(!instance)
            instance = new Configuration(filePath);
        return instance;
    }

    ~Configuration()
    {
        configf.close();
    }

};

Configuration* Configuration::instance = 0;

type getInput(const char* str)
{
    if(strcmp(str,"INFO") == 0)
        {
            return type::INFO;
        }

        if(strcmp(str,"WARNING") == 0)
        {
            return type::WARNING;
        }

        if(strcmp(str,"ERROR") == 0)
        {
            return type::ERROR;
        }

        if(strcmp(str,"CRITICAL") == 0)
        {
            return type::CRITICAL;
        }
}

int main(unsigned argc,std::string argv)
{
    if(argc == 0)
    {
        std::string str = "config.txt";
        Configuration* config = config->getInstance(str);
    }

    try
    {
        Configuration* config = config->getInstance(argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    bool state = true;
    while(state)
    {
        std::cout <<"<type><message" << std::endl;
        char[10] input;
        std::string input1;
        std::cin >> input;
        std::getline(std::cin,input1);
    }
    
    
	return 0;
}