//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Диана Венциславова Маркова
// ФН: 82140
// Специалност: Компютърни науки
// Курс: 1(първи)
// Административна група: 1(първа)
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>


class command
{
    std::string name;
    std::vector<std::string> arguments;
public:
    command(const char* str)
    {
        skipwhitespace(str);
        std::string temp;
        while(*str && !iswhitespace(*str))
            temp.push_back(*str++);
        if(!temp.empty()) name = temp;
        skipwhitespace(str);
        temp.clear();
        //std::cout<<name<<std::endl;
        while(*str)
        {
            //std::cout<<"here"<<std::endl;
            std::string temp;
            while(*str && !iswhitespace(*str)) temp.push_back(*str++);
            if(!temp.empty()) arguments.push_back(temp);
            skipwhitespace(str);
        }
    }
    std::size_t size() const
    {
        return arguments.size();
    }

    std::string& operator[](std::size_t pos)
    {
        if(pos==0) return name;
        return arguments[pos-1];
    }

    const std::string& operator[](std::size_t pos) const
    {
        if(pos==0) return name;
        return arguments[pos-1];
    }
private:
    static bool iswhitespace(char ch)
    {
        return ch==' '||ch=='\t';
    }
    static void skipwhitespace(const char*& str)
    {
        while(*str&&iswhitespace(*str)) ++str;
    }
};
bool isValid(const command& c)
{
    if(c[0]=="EXIT")
    {
        if(c.size()==0) return true;
    }
    else if(c[0]=="SIZE")
    {
        if(c.size()==0) return true;
    }
    else if(c[0]=="EDIT")
    {
        if(c.size()==2) return true;
    }
    else if(c[0]=="SHOW")
    {
        if(c.size()==2) return true;
    }
    else throw std::invalid_argument("Unknown command");
    return false;
}
class editor
{
    //for objects of type fstream seekp == seekg && tellp == tellg
    std::fstream file;
    bool isopen = false;
    std::size_t filesize;
public:
    editor(const char* path,
           std::ios_base::openmode mode=std::ios_base::ate|std::ios_base::in|std::ios_base::out)
    {
        open(path, mode);
    }
    void open(const char* path,
              std::ios_base::openmode mode=std::ios_base::ate|std::ios_base::in|std::ios_base::out)
    {
        if(isopen) file.close();
        file.open(path, mode);
        if(!file) throw std::runtime_error("could not open file"+std::string(path));
        isopen = true;
        filesize = file.tellp();
        rewind();
        if(!file) throw std::runtime_error("could not open file"+std::string(path));
        if(filesize%2!=0) throw std::runtime_error("bad file content");
    }
    void close()
    {
        if(isopen) file.close();
        else throw std::runtime_error("no file is open");
    }
    void rewind()
    {
        file.seekp(0, std::ios_base::beg);
    }
    void edit(std::size_t offset, std::uint8_t value)
    {
        if(offset>filesize) throw std::invalid_argument("pos is out of file");
        file.seekp(offset, std::ios_base::beg);
        file.write((const char*)&value, sizeof(value));
        if(!file) throw std::runtime_error("writing failed");
    }
    std::size_t size() const
    {
        return filesize;
    }
    void display(std::ostream& out, std::size_t offset, std::size_t limit)
    {
        if(offset>size()) throw std::invalid_argument("pos is out of file");
        file.seekg(offset, std::ios_base::beg);
        if(!file) throw std::runtime_error("reading failed");
        if(limit>offset) limit = offset;
        std::uint8_t reader;
        std::size_t cnt=0;
        while(file.tellg()<=limit && file.read((char*)&reader, sizeof(uint8_t)))
        {
            ++cnt;
            out << std::setfill('0') << std::setw(2) << std::hex << reader;
            if(cnt==16) out<<'\n';
        }
    }
    ~editor()
    {
        if(isopen) close();
    }
};


class processor: public editor
{
public:
    processor(const char* path,
           std::ios_base::openmode mode=std::ios_base::ate|std::ios_base::in|std::ios_base::out):
               editor(path, mode)
    {}
    void execute(const command& c)
    {
        if(!is_valid(c)) throw std::invalid_argument("Invalid command");
        if(c[0]=="EXIT")
        {
            close();
        }
        else if(c[0]=="SIZE")
        {
            std::cout<<size()<<std::endl;
        }
        else if(c[0]=="EDIT")
        {
            edit(std::atoi(c[1].c_str()), std::atoi(c[2].c_str()));
        }
        else if(c[0]=="SHOW")
        {
            edit(std::atoi(c[1].c_str()), std::atoi(c[2].c_str()));
        }
    }
private:
    static bool is_valid(const command& c)
    {
        if(c[0]=="EXIT")
        {
            if(c.size()==0) return true;
        }
        else if(c[0]=="SIZE")
        {
            if(c.size()==0) return true;
        }
        else if(c[0]=="EDIT")
        {
            if(c.size()==2) return true;
        }
        else if(c[0]=="SHOW")
        {
            if(c.size()==2) return true;
        }
        return false;
    }
};

int main(int argc, char** argv) try
{
    //for(std::size_t i=0; i<(a.size()); ++i) std::cout<<a[i]<<std::endl;
    //a processor is technically an editor
    if(argc!=2) {
        throw std::invalid_argument("Usage: "+std::string(argv[0])+"<input filename>");
    }
    processor p(argcv[1]);
    std::string line;
    while(std::getline(std::cin, getline))
    {
        command c;
        c(line.c_str());
        p.execute(c);
    }

	return 0;
}
catch(const std::exception& e)
{
    std::cerr<<e.what()<<'\n';
    return 1;
}
