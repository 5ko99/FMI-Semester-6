//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Иван Славов Ковачев
// ФН: 81940
// Специалност: Компютърни науки
// Курс: Трети
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
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
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//// mov f1 f2 f3 this[2] -> f2 this.size_t -> 4
class command
{
    std::string cmd;
public:
    command(std::string cmd): cmd(cmd) {}
    std::size_t size() const
    {
        size_t res = mySplit(cmd).size();
        return res;
    }
    std::string& operator[](std::size_t index)
    {
        return mySplit(cmd)[index];
    }
    command& operator=(const command& arg)
    {
        if(this != &arg)
        {
            cmd = arg.cmd;
        }
        return *this;
    }
    std::string getCommand() const
    {
        return cmd;
    }
    static std::vector<std::string> mySplit(const std::string& Line)
    {
        std::string tmpWord;
        std::vector<std::string> vectResult;
        for(size_t i = 0; i < Line.size(); i++ )
        {
            if(Line[i] != ' ')
            {
                tmpWord += Line[i];
            }
            else
            {
                vectResult.push_back(tmpWord);
                tmpWord.erase();
            }
        }
        return vectResult;
    }
    friend bool operator==(const command& lhs, const command& rhs)
    {
        return lhs.cmd == rhs.cmd ;
    }
};

class editor
{
    std::size_t m_size;
public:
    editor(const char* filePath)
    {
        openFile(filePath);
    }
    std::ofstream& openFile(const char* filePath)
    {
        std::ofstream File(filePath, std::ios_base::binary);
        if(!File)
        {
            std::cerr<< "File failed to open!\n";
        }
        return File;
    }
    std::size_t _size()
    {
        return m_size;
    }
};

class processor:public command
{
public:

    bool is_valid(command& cmd)
    {
        if(cmd[0].size() != 4)
        {
            return false;
        }
        if(cmd[0] == "EXIT")
        {
            return true;
        }
        else if(cmd[0] == "SIZE")
        {
            return true;
        }
        else if(cmd[0] == "EDIT" && cmd.size() == 3 )
        {
            return true;
        }
        else if(cmd[0] == "SHOW" && cmd.size() == 3 )
        {
            return true;
        }
        else return false;
    }
    void execute(command& cmd)
    {
        //if(cmd[0] == "SHOW") showMethod(cmd);
        //else if (cmd[0] == "EDIT") editMethod(cmd);
        //else if (cmd[0] == "EXIT") exit(cmd);
        //else if(cmd[0] == "SIZE") _size();
    }
};
int main(int argc, char** argv)
{
    /// arg[1]
    editor ed(argv[1]);
    while(true)
    {
        std::string input = "mov f1 f2 f3";
        command a(input);
        std::vector<std::string> vectCmds = command::mySplit(a.getCommand());
        //processor(vectCmds);
    }
    return 0;
}
