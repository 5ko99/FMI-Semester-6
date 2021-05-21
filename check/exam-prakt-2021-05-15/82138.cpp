//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Ралица Юлианова Андреева
// ФН: 82138
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//
#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

enum Type {
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
    COUNT
};

class Message {
public:
    const Type type;
    const std::string description;
    Message(Type tp,const std::string& desc): type(tp), description(desc) {}
    Message(const Message& other) = delete;
    Message& operator=(const Message& other) = delete;
    friend std::ostream& operator<<(std::ostream& os,const Message& m);
    std::string getType() const
    {
        switch(type)
        {
            case INFO:
                return "INFO";
                break;
            case WARNING:
                return "WARNING";
                break;
            case ERROR:
                return "ERROR";
                break;
            case CRITICAL:
                return "CRITICAL";
                break;
            case COUNT:
                return "";
        }
    }
};
std::ostream& operator<<(std::ostream& os,const Message& m)
{
    os << m.getType() << ": " << m.description;
    return os;
}

class Logger{
    std::fstream file;
    std::string fileName;
    static int cnt[COUNT];
public:
    Logger(const std::string& fileName): fileName(fileName) {}
    Logger& operator<<(const Message& m)
    {
        file.open(fileName,std::fstream::out | std::fstream::app);
        if(!file){
            throw std::exception();
        }
        //cnt[m.type]++;
        file << m << '\n';
        file.close();
        return *this;
    }
};
class Configuration{
    std::string fileName;
    Logger log;
public:

};
int main()
{
    //Message m1(INFO,"asdfasdf"),m2(WARNING,"ddddd");
    //Logger log("out.txt");
    //log << m1 << m2;
    return 0;
}
