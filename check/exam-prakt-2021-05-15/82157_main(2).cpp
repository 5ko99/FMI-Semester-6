// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Адриян Ивов Ибовски
// ФН: 82157
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9.00
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum TYPE{
    INFO = 0,
    WARNING,
    ERROR,
    CRITICAL
};

class Message{
private:
    const std::string m_description;
public:
    const TYPE m_type;

    Message(const TYPE type, const std::string& description) : m_type(type), m_description(description){}
    Message(const Message& other) : m_type(other.m_type), m_description(other.m_description){}
    Message& operator=(const Message& other) = delete;
    friend std::ostream& operator<<(std::ostream& out, const Message& obj){
        if(obj.m_type == 0) out<<"INFO";
        if(obj.m_type == 1) out<<"WARNING";
        if(obj.m_type == 2) out<<"ERROR";
        if(obj.m_type == 3) out<<"CRITICAL";
        out<<": "<<obj.m_description;
        return out;
    }
     std::string getType() const{
         if(m_type == 0) return "INFO ";
         if(m_type == 1) return "WARNING ";
         if(m_type == 2) return "ERROR ";
         if(m_type == 3) return "CRITICAL ";
         return "";
    }
     std::string getDesc() const{return m_description;}
};
static int info[4];
class Logger{
private:
    std::ofstream m_log;

public:

    Logger(std::string name){
        m_log.open(name,std::ios::app);
        if(!m_log.is_open()) {
            throw std::exception();
        }
    }

    ~Logger(){
        m_log.close();
    }
    void operator<<(const Message& obj){
        if(m_log.is_open()) {
            m_log << obj.getType() << obj.getDesc()<<std::endl;
            std::cout << obj << std::endl;
            info[obj.m_type]++;
        }
    }
    static void show(){
        std::cout<<"INFO: "<<info[0]<<std::endl;
        std::cout<<"WARNING: "<<info[1]<<std::endl;
        std::cout<<"ERROR: "<<info[2]<<std::endl;
        std::cout<<"CRITICAL: "<<info[3]<<std::endl;
    }
};

class Configuration{
private:
    std::string m_file;
    Logger m_log;
public:
    Configuration(std::string& file, Logger& log) : m_file(file), m_log(file){}
};

int main(int argc, char* args[])
{
    std::string path ="config.txt";
    if(args[1]) path = args[1];
    try {
        Logger log(path);
        Configuration cf(path, log);
        while (true) {
            std::cout<<"TYPE: ";
            int num;
            std::cin >> num;
            if(num < 0 || num >3) {std::cout<<"wrong type"<<std::endl; continue;}
            TYPE t;
            if(num == 0) t = INFO;
            if(num == 1) t= WARNING ;
            if(num == 2) t = ERROR ;
            if(num == 3) t =CRITICAL ;
            std::string desc;
            std::getline(std::cin,desc);
            if (desc == "ex") break;
            Message m(t, desc);
            log << m;
            log.show();
        }
    }
    catch (std::exception& e){
        std::cout<<"Could not open the file"<<std::endl;
        return 0;
    }
	return 0;
}