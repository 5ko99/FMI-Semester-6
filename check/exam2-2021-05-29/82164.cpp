// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Иван Цветанов Стефанов
// ФН: 82164
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <stdexcept>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cstdint>
#include <iomanip>

void copy(std::string& dest,std::string src,std::size_t pos,std::size_t len)
{
    for(std::size_t i = pos;i < len;++i)
    {
        dest[i] = src[i];
    }
}

class command {
protected:
    std::vector<std::string> arguments = {};
    void tokenize(std::string arg);
public:

    explicit command(std::string commandText)
    {
        tokenize(std::move(commandText));
    }
    std::size_t size() const
    {
        return arguments.size();
    }
    std::string operator[](std::size_t pos) const
    {
        if(pos < size())
        {
            return arguments[pos];
        }
        throw std::out_of_range("There is no such element");
    }

    friend class processor;
};

void command::tokenize(std::string arg)
{
    std::size_t index = 0;
    std::string temp;
    for(std::size_t i = 0;i < arg.size();++i)
    {
        if(arg[i] == ' ' || arg[i] == '\t')
        {
            if(index < i)
            {
                copy(temp, arg, index, i - index);
                arguments.push_back(temp);
            }
            index = i;
        }
    }
}

class editor;

class processor {

protected:
    editor* owner;
    bool endProgram = false;
public:
    explicit processor(editor* owner)
            : owner(owner)
    {}
    bool is_valid(const command& arg)
    {
        if(arg.size() == 1)
        {
            if(strcmp(arg[0].c_str(),"EXIT") == 0) return true;
            else if(strcmp(arg[0].c_str(),"SIZE") == 0) return true;
            else return false;
        }
        else if(arg.size() == 3)
        {
            if(strcmp(arg[0].c_str(),"EDIT") == 0) return true;
            else if(strcmp(arg[0].c_str(),"SHOW") == 0) return true;
            else return false;
        }
        else return false;
    }
    virtual void execute(const command& arg) = 0;
};

class editor : public processor {

    std::fstream* file = nullptr;
    std::size_t filesize;
    void getSize()
    {
        if(file->good())
        {
            file->seekg(0,std::ios_base::end);
            filesize = file->tellg();
        }
    }
    void rewind()
    {
        if(file)
        {
            file->seekg(0,std::ios_base::beg);
            file->seekp(0,std::ios_base::beg);
        }
    }
public:
    explicit editor(const std::string& path)
    : processor(this),file(new std::fstream(path,std::ios_base::binary | std::ios_base::ate))
    {
        getSize();
    }
    std::size_t size() const
    {
        return filesize;
    }
    bool programEnd() const
    {
        return this->endProgram;
    }
    void edit(std::size_t offset, std::uint8_t value)
    {
        if(file)
        {
            if(offset >= filesize)
            {
                throw std::invalid_argument("Invalid position!");
            }
            file->seekp(offset,std::ios_base::beg);
            file->write((const char*)&value,sizeof(uint8_t));
        }
    }
    void display(std::ostream& out,std::size_t offset, std::size_t limit)
    {
        if(offset >= filesize)
        {
            throw std::invalid_argument("Invalid position!");
        }
        file->seekg(offset,std::ios_base::beg);
        std::size_t bytes_count = 0;
        uint8_t temp;
        while(bytes_count < limit && file)
        {
            file->read((char*)&temp,sizeof(uint8_t));
            ++bytes_count;

            if(bytes_count % 16 == 1)
            {
                std::uint32_t data = (std::uint32_t)file->tellg();
                out<<std::setfill('0')<<std::setw(8)<<std::hex<<data;
            }

            out<<std::hex
               <<std::setfill('0')
               <<std::setw(2)
               <<(unsigned int)temp;

              (bytes_count % 16) ? out<<' ' : out<<'\n';
        }

    }
    void open(const std::string& path)
    {
       if(file)
       {
           file->close();
           delete file;
       }
       file = new std::fstream(path,std::ios_base::binary | std::ios_base::ate);
       getSize();
    }

    void close()
    {
        if(file)
        {
            file->close();
            filesize = 0;
        }
    }
    ~editor()
    {
        close();
        delete file;
        file = nullptr;
    }

    void execute(const command& arg) override
    {
        if(arg.size() == 1)
        {
            if(strcmp(arg[0].c_str(),"EXIT") == 0)
            {
                this->endProgram = true;
            }
            else if(strcmp(arg[0].c_str(),"SIZE") == 0)
            {
                std::cout<<size()<<" byte(s)"<<std::endl;
            }
            else;
        }
        else if(arg.size() == 3)
        {
            if(strcmp(arg[0].c_str(),"EDIT") == 0)
            {
                std::size_t offset = stoull(arg[1]);
                std::uint8_t byte = (std::uint8_t)stoi(arg[2]);
                edit(offset,byte);
            }
            else if(strcmp(arg[0].c_str(),"SHOW") == 0)
            {
                std::size_t offset = stoull(arg[1]);
                std::size_t limit = stoull(arg[2]);
                display(std::cout,offset,limit);
            }
            else;
        }
    }
};

int main(int argc,char** argv)
try
{
    if(argc == 2)
    {
        editor FileManager(argv[1]);
        std::string userInput;
        while(!FileManager.programEnd())
        {
            std::cout<<'>';
            std::cin>>userInput;
            command process(userInput);
            FileManager.execute(process);
        }
    }
    else
    {
        throw std::invalid_argument("Wrong usage! Program takes 1 argument: file path");
    }
	return 0;
}
catch(const std::exception& e)
{
    std::cout<<e.what()<<std::endl;
    return 1;
}