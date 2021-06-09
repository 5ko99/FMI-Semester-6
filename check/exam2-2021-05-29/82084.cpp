//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име:Цанко Ангелов
// ФН:82084
// Специалност:Компютърни науки
// Курс:2
// Административна група:4
// Ден, в който се явявате на контролното: 29.05.2021
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
#include <fstream>
#include <iostream>
#include <string>
#include <exception>

class Command
{
    std::string str;
    int word_count;
    std::string command;

    void copy(Command &other)
    {
        str = other.str;
        word_count = other.word_count;
        command = other.command;
    }

    void clean()
    {
        str.clear();
        command.clear();
    }

    public:
    Command()
    {
        str.clear();
        word_count = 0;
        command.clear();
    }

    Command(Command &other)
    {
        copy(other);
    }

    Command &operator=(Command &other)
    {
        if (this != &other)
        {
            clean();
            copy(other);
        }

        return *this;
    }

    ~Command()
    {
        clean();
    }

    Command(std::string _str)
    {
        str = _str;
    }

    int count_word()
    {
        int i = 0;
        while (word_count < 1)
        {
            if (str.at(i) == (char)32 || str.at(i) == str.length())
            {
                word_count++;
                for (int j = 0; j <= i; j++)
                {
                    command.at(j) = str.at(j);
                }
            }
            i++;
        }
        while (i <= str.length())
        {
            if (str.at(i) == (char)32 || str.at(i) == str.length())
            {
                word_count++;
            }
            i++;
        }

        return word_count;
    }

    std::size_t size() const
    {
        return this->word_count - 1;
    }

    std::string operator[](std::size_t size)
    {
        if (size > word_count)
        {
            throw std::invalid_argument("Invalid size");
        }

        int index = word_count - size;

        for (int i = 0; i < str.length(); i++)
        {
            std::string temp;
            int j = 0;
            temp.at(j) = str.at(i);
            if (str.at(i) == (char)32 || str.at(i) == str.length())
            {
                index--;
                if (index == 0)
                {
                    return temp;
                }
                else
                {
                    temp.clear();
                    j = 0;
                }
            }
        }
    }

    std::string getCommand() const
    {
        return this->command;
    }

    std::string getStr() const
    {
        return this->str;
    }

    std::size_t getWord_count() const
    {
        return this->word_count;
    }
};

class Processor
{
public:
    bool is_valid(Command c)
    {
        if (c.getCommand() == "EXIT")
        {
            return true;
        }
        else
        {
            return false;
        }

        if (c.getCommand() == "SIZE")
        {
            return true;
        }
        else
        {
            return false;
        }

        if (c.getCommand() == "EDIT")
        {
            for (int i = 1; i <= c.getWord_count(); i++)
            {
                for (int j = 0; j < c[i].length(); j++)
                {
                    if (c[i].at(j) < 48 || c[i].at(j) > 57)
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        else
        {
            return false;
        }

        if (c.getCommand() == "SHOW")
        {
            for (int i = 1; i <= c.getWord_count(); i++)
            {
                for (int j = 0; j < c[i].length(); j++)
                {
                    if (c[i].at(j) < 48 || c[i].at(j) > 57)
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        else
        {
            return false;
        }

        
    }
};

int main()
{

    return 0;
}