// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Костадин Маринов Нарлиев
// ФН: 81975
// Специалност: Компютърни науки
// Курс: Втори
// Административна група: Втора
// Ден, в който се явявате на контролното: 29.05.2021г.
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class command
{
    public:
    std::string com;
    std::string* arguments;
    size_t arg_count;
    bool valid;

    command()
    {
        arg_count=0;
        valid=true;
    }

    void split(char* input)
    {
        int input_length=0;
        for (int i = 0; input[i]!='\0'; i++)
        {
            input_length++;
        }
        bool com_name_flag=false;
        bool argument_1=false;
        bool argument_2=false;
        for (int i = 0; input[i]!='\0'; i++)
        {
            if(input[i]==' ')
            {
                if(input[i-1]==' ') continue;
                else if(com_name_flag==false) com_name_flag=true;
                else if(argument_1==false) argument_1=true;
                else if(argument_2==false) argument_2=true;
            }
            else
            {
                if(com_name_flag==false) this->com+=input[i];
                else if(argument_1==false)
                {
                    arg_count=1;
                    this->arguments[0]+=input[i];
                }
                else if(argument_2==false)
                {
                    arg_count=2;
                    this->arguments[1]+=input[i];
                }
                else valid=false;
            }
        }
    }

    command(char* input)
    {
        split(input);
    }

    std::size_t size() const
    {
        return this->arg_count;
    }

    void clear()
    {
        for (int i = 0; i < arg_count; i++)
        {
            arguments[i]=nullptr;
        }
        com=nullptr;
        arg_count=0;
    }

    std::string operator[](std::size_t index)
    {
        if(index==0) return this->com;
        if(index==1) return this->arguments[0];
        if(index==2) return this->arguments[1];
    }

    ~command()
    {
        clear();
    }
};

class editor
{
    private:
    size_t file_size;
    public:
    std::ifstream read;
    std::ofstream write;
    bool opened=false;

    editor()
    {
        file_size=0;
        opened=false;
    }

    std::size_t size_find(std::ifstream &r)
    {
        int size=0;
        //...
        return size;
    }

    std::size_t size()
    {
        return this->file_size;
    }

    void open(char* path)
    {
        this->write.open(path);
        this->read.open(path);
        if(!write.is_open()) std::cout << "File has not been opened properly" << std::endl;
        else if(!read.is_open()) std::cout << "File has not been opened properly" << std::endl;
        else
        {
            std::cout << "File has been opened properly!" << std::endl;
            file_size=size_find(read);
            opened=true;
        }
    }

    editor(char* path)
    {
        open(path);
    }

    void edit(std::size_t offset, std::uint8_t value)
    {
        if(opened)
        {
            if(offset>size())
            {
                std::cout << "Invalid argument!" << std::endl;
            }
            else
            {
                write.seekp(offset);
                write << value;
            }
        }
        else std::cout << "No file opened!" << std::endl;
    }

    void close()
    {
        write.close();
        read.close();
        opened=false;
    }

    ~editor()
    {
        close();
    }
};

class processor
{
    public:
    bool is_valid(command Comm)
    {
        if(Comm.valid==false) return false;
        else if(Comm.com!="SHOW" && Comm.com!="SIZE" && Comm.com!="EDIT" && Comm.com!="EXIT") return false;
        else if(Comm.com=="EXIT" && Comm.arg_count>0) return false;
        else if(Comm.com=="SIZE" && Comm.arg_count>0) return false;
        else if(Comm.com=="EDIT" && Comm.arg_count!=2) return false;
        else if(Comm.com=="SHOW" && Comm.arg_count!=2) return false;
        else return true;
    }

    void execute(command Comm, editor Edit)
    {
        if(is_valid(Comm))
        {
            if(Comm.com=="SIZE") std::cout << Edit.size() << " byte(s)" << std::endl;
            else if(Comm.com=="EDIT")
            {
                std::size_t a=0;
                for (int i = 0; i < Comm[1].size(); i++)
                {
                    a+=a*10 + (Comm[1][i]-'0');
                }
                std::size_t b=0;
                for (int i = 0; i < Comm[2].size(); i++)
                {
                    b+=b*10 + (Comm[2][i]-'0');
                }
                Edit.edit(a,b);
            }
        }
    }

};

int main()
{
    char* filename;
    std::cout << "Enter file name:" << std::endl;
    std::cin >> filename;
    char* input;
    command Com;
    editor Edit;
    processor Pro;
    while(true)
    {
        std::cin >> input;
        Com.split(input);
        if(Pro.is_valid(Com))
        {
            if(Com.com=="EXIT")
            {
                Edit.close();
                break;
            }
            else
            {
                Edit.open(filename);
                Pro.execute(Com,Edit);
            }
        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
            Com.clear();
        }
    }
	return 0;
}