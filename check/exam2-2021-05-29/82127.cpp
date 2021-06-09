//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Димитър Кръстинов Ангелов
// ФН: 82127
// Специалност: Компютъри науки
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: MinG
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
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class comand{

    char* cm;
public:
    comand(char* str){
         strcpy(this->cm,str);
     }

     std::size_t size() const{

         std::size_t br=0;
         bool f=1;

         for(int i=0;i<sizeof(this->cm);i++){
            if(cm[i]==' '){
                f=1;
            }
            else{
                if(f==1){
                    br++;
                    f=0;
                }

            }
         }

     return br;
     }

     char* operator[](std::size_t t){
        char* s;
        if(t>=this->size()){
            throw std::invalid_argument("Invalid argument");
        }

        std::size_t br=0;
         bool f=1;

         for(int i=0;i<sizeof(this->cm);i++){
            if(cm[i]==' '){
                f=1;
            }
            else{
                if(f==1){
                    br++;
                    if(t==br-1){
                        int j=0;
                        while(cm[i]!=' '&&cm[i]!='\0'){
                             s[j]=cm[i];
                        j++;
                        }
                        break;
                    }
                    f=0;
                }

            }
         }

         return s;


    }
};

class editor:public comand{



};

class processor:public comand{
    bool is_valid(){
    if(this->cm[0]=="EDIT"||this->cm[0]=="SHOW"||this->cm[0]=="SIZE"){
        return true;
    }
    else{
        return false;
    }
    }

    void execute(){
        editor e(this->cm[0]);
        if(this->cm[0]=="EDIT"){
        e.EDIT();
    }
    if(this->cm[0]=="SHOW"){
        e.SHOW();
    }
    if(this->cm[0]=="SIZE"){
        e.SIZE();
    }

    }
};

int main(int argc,char** argv)
{
    try{
    char* f=argv[1];
    editor f;
    }
    catch{std::cout<<"Invalid argument. Program terminated"<<"\n"; return 0;}

    char* c;
        std::cin.getline(c);
    while(c!="EXIT"){
        std::cin.getline(c);
    comand com(c);
    processor p(com);
    }


	return 0;
}
