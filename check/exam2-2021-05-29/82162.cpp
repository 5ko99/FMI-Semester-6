// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Тодор Христов
// ФН: 82162
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29/05/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> clion
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
using namespace std;
class command{
    string m_command;
    size_t m_numberOfArguments;
    vector <string> m_argumnts;
public:
    command(){}
    command(const string& input): m_command(input){
        string temp = "";
        for (int i = 0; i < m_command.size(); ++i) {
            if(m_command[i] == ' '){
                if (temp != ""){
                    m_argumnts.push_back(temp);
                    m_numberOfArguments++;
                }
                temp = "";
            } else {
                temp+=m_command[i];
            }
        }
    }
    size_t size() const{
        return m_numberOfArguments;
    }
    string& operator[](size_t size){
        return m_argumnts[size];
    }
};


class editor{
    string m_path;
    size_t m_size;
    fstream file;
public:
    editor (const string& path):m_path(path){
        open();
    }
    ~editor (){
        close();
    };
    void open (){
        file = fstream (m_path, ios::ate | ios::binary | ios::in);
        if(!file.is_open())
            throw exception();
        //long cur = file.tellp();
        file.seekp(0, ios::end);
        m_size = file.tellp();
    }
    void close (){
        file.close();
    }
    size_t size () const {
        return m_size;
    }
    void edit(std::size_t offset, std::uint8_t value){
        if (offset > size ()){
            throw invalid_argument("offset out of range");
        }
        file.write((const char *) &value, sizeof (uint8_t) * offset);
        m_size += 1;
    }
    void  display(std::ostream& out, std::size_t offset, std::size_t limit){
        if (offset > size ()){
            throw invalid_argument("offset out of range. Max size is " + m_size);
        }
        uint8_t read;
        long cur = out.tellp();
        out.seekp(0, ios::end);
        for (int i = offset; i < offset + limit && i < size(); ++i){
            file.read((char*) &read, sizeof(uint8_t) * i);
            if (file.good()) {
                out.write((const char *) &read, sizeof (uint8_t) * cur);
            }
        }
    }
};

class processor:editor{
    size_t stringIntoSize_t(const string& str){
        size_t output = 0;
        int multiply = 1;
        for (int i = str.size() - 1; i >= 0; --i){
            if (str[i] >= '0' && str[i] <= '9'){
                output+= (str[i] - '0') * multiply;
                multiply*=10;
            } else {
                throw invalid_argument("you have to input number");
            }
        }
        return output;
    }
public:
    bool is_valid (command com)  const{
        if(com[0] == "EXIT" ||
           com[0] == "SIZE" ||
           (com[0] == "EDIT" && com.size() == 2)||
           (com[0] == "SHOW" && com.size() == 2)){
            return true;
        }
        return false;
    }
    bool execute(command com){
        if (is_valid(com)){
            if(com[0] == "SIZE"){
                cout << size();
                return 1;
            } else if (com[0] == "EXIT"){
                return 0;
            } else if (com[0] == "SHOW"){
                size_t offset = stringIntoSize_t(com[1]);
                uint8_t value = uint8_t(stringIntoSize_t(com[2]));
                try{
                    display(cout, offset, value);
                } catch (exception e) {
                    cout << &e;
                }
                return 1;
            } else if (com[0] == "EDIT"){
                size_t offset = stringIntoSize_t(com[1]);
                uint8_t value = uint8_t(stringIntoSize_t(com[2]));
                try{
                    edit(offset, value);
                } catch (exception e) {
                    cout << &e;
                }
                return 1;
            }
        }
    }
};
int main(int argc, char*argv[])
{
    while(true){
        string nextCommand;
        cin >> nextCommand;
        command newCommand(nextCommand);
        
    }
    return 0;
}