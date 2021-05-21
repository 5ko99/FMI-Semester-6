// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Любен Георгиев Герогиев
// ФН: 82197
// Специалност: КН
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

enum Type
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL_ERROR
};

class Message
{
private:
    Type type;
    std::string description;

public:
    Message(Type t, std::string d)
        : type(t), description(d)
    {

    }

    Message(const Message &other)
    {
        this->type = other.type;
        this->description = other.description;
    }

    Message& operator=(const Message& other)
    {
        if (this != &other) {
            this->type = other.type;
            this->description = other.description;
        }

        return *this;
    }

    const Type getType() const
    {
        return this->type;
    }

    const std::string getDescription() const
    {
        return this->description;
    }

};

std::ostream& operator<<(std::ostream &out, const Message &msg)
{
    switch (msg.getType())
    {
    case 0:
        return out << "INFO: " << msg.getDescription();
    case 1:
        return out << "WARNING: " << msg.getDescription();
    case 2:
        return out << "ERROR: " << msg.getDescription();
    case 3:
        return out << "CRITICAL: " << msg.getDescription();
    }

    return out;
}

class Logger
{
private:
    std::string path;
    static unsigned msgCounter[4];

public:
    void setPath(std::string p)
    {
        path = p;
    }

    const std::string getPath() const
    {
        return this->path;
    }

    void operator<<(const Message &msg)
    {
        std::ofstream out;
        out.open(this->getPath(), std::ios::app);

        if (!out) throw "Could not open file!";

        out << msg << std::endl;

        out.close();

        ++msgCounter[msg.getType()];
    }

    unsigned getInfoMsgCnt()
    {
        return msgCounter[0];
    }

    unsigned getWarningMsgCnt()
    {
        return msgCounter[1];
    }

    unsigned getErrorMsgCnt()
    {
        return msgCounter[2];
    }

    unsigned getCriticalMsgCnt()
    {
        return msgCounter[3];
    }
};

unsigned Logger::msgCounter[4] = {0, 0, 0, 0};


class Configuration
{
private:
    Configuration()
    {

    }
    ~Configuration()
    {

    }

    std::string path;
    Logger l;

    void setPath(Configuration &config, std::string p)
    {
        config.path = p;
    }

    void setLoggerPath(Configuration &config)
    {
        std::ifstream in;
        in.open(config.getPath());

        if (!in) {
            throw "Could not open file!";
        }

        std::string tempPath;

        std::getline(in, tempPath);

        config.getLogger().setPath(tempPath);

        in.close();
    }


public:
    Configuration(const Configuration &other) = delete;
    Configuration& operator=(const Configuration &other) = delete;

    static Configuration& getInstance(std::string p)
    {
        static Configuration c;
        c.setPath(c, p);

        c.setLoggerPath(c);

        return c;
    }

    std::string getPath()
    {
        return this->path;
    }

    Logger& getLogger()
    {
        return this->l;
    }
};


int main(int argc, char** argv)
{
    if (argc == 1) {
        try
        {
            Configuration::getInstance(argv[0]);
            Logger log = Configuration::getInstance(argv[0]).getLogger();

            std::string descr;
            Type t;
            unsigned type;

            std::cout << "Type 'exit' to exit\n";
            while (descr != "exit") {
                std::cout << "What type msg do you want to write: ";
                std::cin >> type;
                t = (Type)type;
                std::cout << "Write msg: ";
                std::cin >> descr;

                Message m(t, descr);

                log << m;
            }
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        

        
    }
    else {
        try
        {
            Configuration::getInstance("config.txt");
            Logger log = Configuration::getInstance("config.txt").getLogger();

            std::string descr;
            Type t;
            unsigned type;

            std::cout << "Type 'exit' to exit\n";
            while (descr != "exit") {
                std::cout << "What type msg do you want to write: ";
                std::cin >> type;
                t = (Type)type;
                std::cout << "Write msg: ";
                std::cin >> descr;

                Message m(t, descr);

                log << m;
            }
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    




	return 0;
}