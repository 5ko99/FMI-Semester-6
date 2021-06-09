//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име:Яни Божанов Янков
// ФН:45806
// Специалност:Информатика
// Курс:първи
// Административна група:5
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното:9:00
// Кой компилатор използвате: <GCC>
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
#include <exception>
#include <vector>
using namespace std;

class Command
{
private:
    string command;
    vector<string> arguments;

    size_t GetBegining(const char *cmd)
    {
        size_t start = 0;
        for (size_t i = 0; i < strlen(cmd); i++)
        {
            if (cmd[i] == ' ')
            {
                ++start;
            }
            else
            {
                break;
            }
        }
        return start;
    }
    // string& GetString(const char* cmd)
    // {
    //     string word;
    // }
public:
    Command(const char *cmd)
    {
        size_t lenght = strlen(cmd);
        size_t index = GetBegining(cmd);
        for (size_t i = index; i < lenght && cmd[i] != ' '; i++)
        {
            command.push_back(cmd[i]);
            ++index;
        }

        for (size_t j = index; j < lenght;)
        {
            string argument = "";
            for (size_t i = index; i < lenght; i++)
            {
                if ((cmd[i] == ' ') && (argument.size() > 0))
                {
                    break;
                }
                if (cmd[i] != ' ')
                {
                    argument.push_back(cmd[i]);
                    index++;
                }
            }
            arguments.push_back(argument);
            j += (argument.size());
        }
    }

    size_t size() const
    {
        return arguments.size();
    }

    string &operator[](size_t i)
    {
        if (i >= this->size() + 1)
        {
            //throw exception("Please enter valid index");
        }
        if (i == 0)
        {
            return this->command;
        }
        else
        {
            return this->arguments[i];
        }
    }

    void print() const
    {
        cout << command << endl;
        for (size_t i = 0; i < this->size(); i++)
        {
            cout << arguments[i] << endl;
        }
    }

    const string &GetCommand() const
    {
        return command;
    }
    ~Command()
    {
    }
};

class Processor
{
private:
public:
    Processor()
    {
    }
    bool is_valid(Command &cmd)
    {
        if ((cmd.GetCommand() == "EXIT") ||
            (cmd.GetCommand() == "SIZE") ||
            (cmd.GetCommand() == "EDIT") ||
            (cmd.GetCommand() == "SHOW"))
        {
            return true;
        }
        return false;
    }
    void execute()
    {
    }
};

class Editor
{
private:
    size_t size;
    ifstream file;

public:
    Editor(const char *path)
    {
        open(path);
    }

    void open(const char *path)
    {
        file.open(path, ios::app, ios::binary);
        if (!file.is_open())
        {
            file.close();
            throw exception("File couldn't open");
        }
        file.seekg(0, ios_base::beg);
        size = file.gcount();
    }
    void close()
    {
        if (!file.is_open())
        {
            throw exception("This file hasn't been opened");
        }
        file.close();
        return;
    }
    size_t GetSize() const
    {
        return size;
    }
};

int main()
{
    // size_t i;
    // string a;
    // getline(cin, a);
    // cin >> i;
    // Command c(a.c_str());
    // // c.print();
    // cout << c[i] << endl;

    return 0;
}