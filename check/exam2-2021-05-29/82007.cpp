// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Теодор Кехайов
// ФН: 82007
// Специалност: Компютърни науки
// Курс: 2ри
// Административна група: 1ва
// Ден, в който се явявате на контролното: 29.05.2021г
// Начален час на контролното: 09:03
// Кой компилатор използвате: gcc
//


#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>




class Command
{
    std::string name;
    std::size_t commandSize=0;
    std::string* parts;

public:
    Command(const char* command): name(command)
    {
        std::string temp;
        for(int i=0;i<strlen(name.c_str());i++)
        {
            if(command[i]==' ' && i>0 || command[i+1]=='\0')
            {
                this->commandSize++;
            }
            while(command[i]==' ') i++;
        }

        parts= new std::string[commandSize+1];

        int j=0;
        for(int i=0;i<strlen(name.c_str());i++)
        {
            if(i==strlen(name.c_str()-1))
            {
                parts[j]=std::string(temp);
                std::cout<<parts[j]<<std::endl;
                j++;
                temp.clear();
            }

            if(command[i]==' ' && i>0)
            {
                parts[j]=std::string(temp);
                std::cout<<parts[j]<<std::endl;
                j++;
                temp.clear();
            }
            while(command[i]==' ') i++;

            temp.push_back(command[i]);
        }
    }

    std::size_t comSize() const
    {
        return commandSize;
    }


    std::string operator[](std::size_t pos) const
    {
        if(pos>= commandSize) throw std::invalid_argument("Incorrect position!");

        return parts[pos];
    }

    void print() const
    {
        std::cout<<parts[0]<<std::endl;
    }

    ~Command()
    {
        delete [] parts;
    }
};

class Editor
{
    std::fstream file;
    unsigned long long fileSize;

public:
    Editor(const char* path, std::ios_base::openmode mode):
            file(path,mode | std::ios_base::binary | std::ios_base::ate),
            fileSize(file.tellg())
    {
        atBeginning();
        open();
    }

    Editor& writeNext(std::uint8_t* value)
    {
        this->file.write((const char*)value,sizeof(uint8_t));
        return *this;
    }

    Editor& writeAt(unsigned long long pos, std::uint8_t* value)
    {
        if(pos>fileSize) throw std::invalid_argument("pos bigger than the file size");
        if(pos==fileSize) this->fileSize++;

        this->file.seekp(pos*sizeof(uint8_t),std::ios_base::beg);
        writeNext(value);
        return this->file? *this: throw std::runtime_error("error while writing");
    }

    void atBeginning()
    {
        file.seekg(0,std::ios_base::beg);
    }

    void open()
    {
        if(!file) throw std::runtime_error("error with opening!");
    }

    void close()
    {
        file.close();
    }

    std::size_t size() const
    {
        return fileSize;
    }

    void edit(std::size_t offset, std::uint8_t value)
    {
        if(offset > this->fileSize) throw std::invalid_argument("offset > fileSize");

        writeAt(offset,&value);
    }

    void display(std::ostream& out, std::size_t offset, std::size_t limit) const
    {
        std::size_t i=offset;
        std::size_t counter=0;
        while(i>fileSize || counter* sizeof(uint8_t)>=limit)
        {
            
        }
    }
};


class Processor: public Command, public Editor
{
public:
    bool isValid(Command command) const
    {
        if(command.comSize()<2) return false;
        return true;
    }

    void execute(Command command)
    {
        if(command[0]=="SIZE")
        {
            std::cout<<size();
        }
        if(command[0]=="EDIT")
        {

        }
    }


};


int main()
{


    return 0;
}