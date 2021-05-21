//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Кристиян Даскалов
// ФН: 45759
// Специалност: Информатика
// Курс: първи
// Административна група: 2-ра
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
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
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>


enum Mess{
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Message{
    Mess type{};
    std::string description{};

public:
    Message() = default;
    Message(const Mess& _type, const std::string& _des):type{_type}, description{_des}{}

    friend std::ostream& operator<<(std::ostream& os,const Message& message){
        switch(message.type){
            case 0: os<<"INFO: ";
                    break;
            case 1: os<<"WARNING: ";
                    break;
            case 2: os<<"ERROR: ";
                    break;
            case 3: os<<"CRITICAL: ";
                    break;
        }

        os<<message.description;
        return os;
    }
    Mess get_type() const
    {
        return type;
    }

};

class Logger{


    static unsigned count_info_logs;
    static unsigned count_warning_logs;
    static unsigned count_error_logs;
    static unsigned count_critical_logs;

public:
    friend std::fstream& operator<<(std::fstream& file,const Message& message){
        file<<message<<"\n";
        switch(message.get_type()){
            case 0: count_info_logs++;
                    break;
            case 1: count_warning_logs;
                    break;
            case 2: count_error_logs;
                    break;
            case 3: count_critical_logs;
                    break;
        }

        return file;
    }
    unsigned get_info_count() const
    {
        return count_info_logs;
    }
    unsigned get_warning_count() const
    {
        return count_warning_logs;
    }
    unsigned get_error_count() const
    {
        return count_error_logs;
    }
    unsigned get_critical_count() const
    {
        return count_critical_logs;
    }


};

unsigned Logger::count_info_logs = 0;
unsigned Logger::count_warning_logs = 0;
unsigned Logger::count_error_logs = 0;
unsigned Logger::count_critical_logs = 0;

//class Configuration
//{
//    std::ofstream config("log.txt");
//    if(!config.is_open()){
//        std::cout<<"Config file opening error!\n";
//    }
//    Logger log{};
//
//    Configuration() = default;
//public:
//    Configuration& myConfiguration;
//
//
//};


int main()
{
    Message first(CRITICAL, "Cannot open input file");
    std::cout<<first;

	return 0;
}
