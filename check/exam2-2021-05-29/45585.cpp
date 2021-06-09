//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Елеонора Емилова Цекова
// ФН: 45585
// Специалност: Информатика
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//


#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class command{
    std::string text;
    std::string nameOfCommand;
    std::string arguments;
public:
    command(std::string _text){
        text=_text;
    }
    string setName(string _nameOfCommand){
        nameOfCommand=_nameOfCommand;
    }
    void devide(){
        int count=0;
        for(int i=0;i<sizeof(text);i++){
            if(text!=" "){
               nameOfCommand=text;
            }
            else{
                arguments=text;
            }
        }
    }
    std::size_t size() const{
        return sizeof(arguments);
    }
    std::size_t operator[](const std::size_t index){
        int count=0;
        std::string newText;
        for(int i=0;i<sizeof(text);i++){
            if(text!=" "){
                newText[i]=text[i];
                count++;
            }
        }
        for(int i=0;i<count;i++){
            if(index==newText[i]){
                return i;
            }
        }
    }
};


class editor{
public:
    void open(){
        std::ifstream op("myFile.txt", std::ios::in|std::ios::binary);
        if(!op.is_open()){
            std::cerr<<"The file could not be opened"<<std::endl;
            return;
        }

    }
    void close(){
        std::ifstream op("myFile.txt", std::ios::in|std::ios::binary);
        if(!op.is_open()){
            std::cerr<<"The file could not be opened"<<std::endl;
            return;
        }
        op.close();
    }
    editor(std::ifstream op){
        if(!op.is_open()){
            std::cerr<<"The file could not be opened"<<std::endl;
            return;
        }
    }
    void edit(std::size_t offset, std::uint8_t value){
        std::ifstream op("myFile.txt", std::ios::in|std::ios::binary);
        if(!op.is_open()){
            std::cerr<<"The file could not be opened"<<std::endl;
            return;
        }
        while(op){
            if(op.eof()){
                throw std::invalid_argument;
            }
        }
    }
};

class processor: public command,public editor{
    public:
        bool is_valid(command& com){
            std::string n;
            setName(n);
            if(n==com){
                return true;
            }
            else return false;

        }
        size_t execute(command& com){
            return com;
        }
};

int main()
{

	return 0;
}
