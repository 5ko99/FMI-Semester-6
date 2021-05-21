//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Диана Венциславова Маркова
// ФН: 82140
// Специалност: КН
// Курс: Първи
// Административна група: 1
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstddef>

enum Type
{
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Message
{
    Type type;
    std::string description;
public:
    Message(Type t, const char* descrpt): description(descrpt)
    {
        if(t<INFO||t>CRITICAL) throw std::invalid_argument("Invalid value for type");
        type=t;
    }
    Type getType() const{return type;}

    friend std::ostream& operator<<(std::ostream& os, const Message& m)
    {
        switch(m.type)
        {
            case INFO: os<<"INFO: "; break;
            case WARNING: os<<"WARNING: "; break;
            case ERROR: os<<"ERROR: "; break;
            case CRITICAL: os<<"CRITICAL: "; break;
        }
        return os<<" "<<m.description;
    }
};

class Logger
{
    static inline std::size_t infoCnt=0;
    static inline std::size_t warningCnt=0;
    static inline std::size_t errorCnt=0;
    static inline std::size_t criticalCnt=0;
    std::ofstream oFile;
public:
    Logger(){};
    Logger(const char* path):oFile(path, std::ios::app|std::ios::out)
    {
        if(!oFile.is_open()) throw std::runtime_error("Failed to open file");
    }
    Logger& operator<<(const Message& m)
    {
        if(oFile.is_open())
        {
            oFile<<m<<std::endl;
            switch(m.getType())
            {
                case INFO: ++infoCnt; break;
                case WARNING: ++warningCnt; break;
                case ERROR: ++errorCnt; break;
                case CRITICAL: ++criticalCnt; break;
            }
            return *this;
        }
        else throw std::runtime_error("No file opened to log anything");
    }
    void setPath(const char* newPath)
    {
        if(oFile.is_open()) oFile.close();
        oFile.open(newPath, std::ios::app|std::ios::out);
        if(!oFile.is_open()) throw std::runtime_error("Failed to open path file");
    }
    static std::size_t getInfoCnt() {return infoCnt;}
    static std::size_t getWarningCnt() {return warningCnt;}
    static std::size_t getErrorCnt() {return errorCnt;}
    static std::size_t getCriticalCnt() {return criticalCnt;}
    ~Logger(){oFile.close();}

};

class Configuration
{
    std::ifstream cFile;
    Logger l;
    Configuration(const char* confPath): cFile(confPath)
    {
        if(!cFile.is_open()) throw std::runtime_error("Failed to open configuration file");
        std::string logPath;
        if(!cFile.eof()) cFile>>logPath;
        if(cFile.is_open()) cFile.close();
        l.setPath(logPath.c_str());
    }
public:
    Configuration(const Configuration& other)=delete;
    Configuration& operator=(const Configuration& other)=delete;
    static Configuration& getInstance(const char* cPath)
    {
        static Configuration c(cPath);
        return c;
    }
};

int main(int argc, char** argv)
{
    if(argc<2)
    {
        try{Configuration& conf= Configuration::getInstance("config.txt");}
        catch(const std::runtime_error& re) {std::cerr<<re.what()<<'\n'; return 2;}
        catch(const std::invalid_argument& ia){std::cerr<<ia.what()<<'\n'; return 2;}
        catch(...) {std::cerr<<"Some error occurred.\n"; return 2;}
    }
    else if(argc==2)
    {
        try{Configuration& conf=Configuration::getInstance(argv[1]);}
        catch(const std::runtime_error& re) {std::cerr<<re.what()<<'\n'; return 2;}
        catch(const std::invalid_argument& ia){std::cerr<<ia.what()<<'\n'; return 2;}
        catch(...) {std::cerr<<"Some error occurred.\n"; return 2;}
    }
    //while(true)
    /*
    else {std::cerr<<"Wrong number of arguments.\n"; return 2;}
    Message a(INFO, "some info");
    Message b(ERROR, "some error");
    //std::cout<<a<<std::endl;
    Logger l("data.txt");
    l<<a<<b;
    std::cout<<Logger::getInfoCnt()<<std::endl;
    */
	return 0;
}
