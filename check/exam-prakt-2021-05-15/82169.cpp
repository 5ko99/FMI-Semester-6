// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Кристиян Георгиев
// ФН: 82169
// Специалност: Компютърни науки
// Курс: I
// Административна група: II
// Ден, в който се явявате на контролното: 15.05
// Начален час на контролното: 8:45
// Кой компилатор използвате: <mingw-win10-gcc>
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

class Message{
private:
    std::string type;
    std::string description;

public:
    Message(){
        
        enum type{
            Info, Warning, Error, Critical error
        };
        std::cout<<"enter the description:"<<"\n";
        std::cin>>description;
    }
    ~Message(){
        
    };

    Message operator<<{
        std::cout<<type;
        std::cout<<description;
    };


};

Class Logger(){
private:
    unsigned short messagesInfo[3];

public:
    Message operator<<(Message m){
        std::ofstream logfile("logfile.txt", std::ios::app);
        
        logfile.open();
        if(!logfile.is_open()){
            std::cout<<"file can't be opened for writing"<<std::endl;
            return -1;
        }
        
        while(m.type){
            logfile << m.type;
        }
        while(m.description){
            logfile << m.description;
        }

        if(m.type == "Warning"){
            messagesInfo[0]++;
        }
        if(m.type == "Error"){
            messagesInfo[1]++;
        }
        if(m.type == "Critical Error"){
            messagesInfo[2]++;
        }
        if(logfile.good()){
            std::cout<<"log file works fine"<<std::endl;
        }
        logfile.close();
    ]
    Message ErrorsSoFarCount(){
        
        std::cout<<"Warnings ="<<messagesInfo[0];
        std::cout<<"Errors ="<<messagesInfo[1];
        std::cout<<"Critical Errors ="<<messagesInfo[2];
    }

}

Class Configuration{
private:
    std::string file;
    Logger obj;
public:
    
}





int main()
{

	return 0;
}