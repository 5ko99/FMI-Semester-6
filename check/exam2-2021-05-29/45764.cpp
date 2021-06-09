//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Валентин Димитров
// ФН: 45764
// Специалност: Информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

class command
{
    char *name;
    char *arguments[2];
    std::size_t cnt;
public:
    command(const char *text)
    {
        std::size_t len = strlen(text);
        std::size_t i = 0;
        for(; i < len; i++)
        {
            if(text[i] == ' ')break;
        }
        name = new char[i + 1];
        for(int j = 0; j < i; j++)
            name[j] = text[j];
        name[i] = '\0';
        cnt = 0;
        if(i < len)
        {
            int temp = 0;
            for(i++; i < len; i++)
            {
                if(text[i] == ' ')break;
                temp++;
            }
            arguments[0] = new char[temp + 1];
            for(int j = 0, k = i - temp; j < temp; j++, k++)
                {
                    arguments[0][j] = text[k];
                }
            arguments[0][temp] = '\0';
            ++i;
            arguments[1] = new char[len - i + 1];
            for(int j = 0, k = i; j < len - i; j++, k++)
            {
                arguments[1][j] = text[k];
            }
            arguments[1][len - i] = '\0';
            cnt = 2;
        }

    }
    ~command()
    {
        delete[] name;
        if(cnt)
        {
            delete[] arguments[0];
            delete[] arguments[1];
        }
    }
    std::size_t size()const
    {
        return cnt;
    }
    char *operator[](std::size_t index)
    {
        if(!index)return name;
        return arguments[index - 1];
    }
};

class processor
{

public:
    bool is_valid(command c)const
    {
        if(strcmp(c[0], "EXIT") != 0)
            if(strcmp(c[0], "SIZE") != 0)
                if(strcmp(c[0], "SHOW") != 0)
                    if(strcmp(c[0], "EDIT") != 0)
                        return false;
        if(!strcmp(c[0], "SHOW"))return c.size() == 2? true : false;
        if(!strcmp(c[0], "EDIT"))return c.size() == 2? true : false;
        return true;
    }
    void execute(command c)const
    {

    }
};

class editor
{
    std::fstream file;
    std::size_t size;
public:
    editor()
    {
        size = 0;
    }
    editor(const char *path): file(path, std::ios_base::binary | std::ios_base::in | std::ios_base::out | std::ios_base::ate)
    {
        size = file.tellg();
        rewind();
    }
    void rewind()
    {
        file.seekg(0, std::ios_base::beg);
    }
    void open(const char * path)
    {
        file.open(path, std::ios_base::binary | std::ios_base::in | std::ios_base::out | std::ios_base::ate);
        size = file.tellg();
        rewind();
    }
    void close()
    {
        file.close();
    }
    std::size_t getSize()const
    {
        return size;
    }
    void edit(std::size_t offset, std::uint8_t value)
    {
        if(!file)return;
        if(offset > size)
        {
            throw std::invalid_argument("Possition out of file");
            return;
        }

        file.seekp(offset, std::ios_base::beg);
        file.write((char *) &value, sizeof(uint8_t));
        rewind();
    }
    void display(std::ostream& out, std::size_t offset, std::size_t limit)
    {
        if(!file)return;
        if(offset > size)
        {
            throw std::invalid_argument("Position out of file");
            return;
        }

        file.seekg(offset, std::ios_base::beg);
        uint8_t byte;
        std::size_t counter = 0;
        for(std::size_t i = 0; i + offset < size; i++)
        {
            if(i == limit)break;
            file.read((char*) &byte, sizeof(byte));
            counter++;
            std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte << " ";
            if(counter & 16)
            {
                std::cout << std::endl;
                counter = 0;
            }
        }
    }
    void write100()
    {
        if(!file)std::cout << "No file open" << std::endl;
        for(uint8_t i = 1; i <= 100; i++)
        {
            file.write((char*) &i, sizeof(uint8_t));
        }
    }
};
int main(int argc, char **argv)
{

	return 0;
}
