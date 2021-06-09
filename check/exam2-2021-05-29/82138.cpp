//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име:Ралица Юлианова Андреева
// ФН:82138
// Специалност:КН
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//
#include <cstddef>
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

class Command{
    std::string arguments[3];
    std::size_t cntArg;
    static std::string commands[];
    static std::size_t cntCommands;
public:
    Command(const std::string& line){
        cntArg = 0;
        std::size_t ind = 0;
        std::size_t lineLen = line.size();
        readArg(0,line,ind,lineLen);
        clearWhitespace(line,ind,lineLen);
        if(!findCommand(arguments[0]))throw std::invalid_argument("Unknown command");
        readArg(1,line,ind,lineLen);
        clearWhitespace(line,ind,lineLen);
        readArg(2,line,ind,lineLen);
    }
    std::size_t size() const
    {
        return cntArg;
    }
    std::string operator[](std::size_t ind) const
    {
        assert(ind < cntArg);
        return arguments[ind];
    }
private:
    void clearWhitespace(const std::string& line,std::size_t& ind,std::size_t lineLen)
    {
        while(ind < lineLen && line[ind] == ' ')
            ++ind;
    }
    void readArg(std::size_t numArg,const std::string& line,std::size_t& ind,std::size_t lineLen)
    {
        arguments[numArg] = "";
        while(ind < lineLen && line[ind] != ' ')
            arguments[numArg] += line[ind++];
        if(arguments[numArg] != "")++cntArg;
    }
    bool findCommand(const std::string& s)
    {
        for(std::size_t i = 0; i < cntCommands; i++)
        {
            if(commands[i] == s)return 1;
        }
        return 0;
    }
};
std::string Command::commands[] = {"EXIT","SIZE","SHOW","EDIT"};
std::size_t Command::cntCommands = sizeof(commands)/sizeof(std::string);


class Editor{
    std::fstream file;
    std::size_t fileSize;
public:
    Editor(const std::string& filePath){
        file.open(filePath,std::fstream::in | std::fstream::binary);
        if(!file){
            throw std::invalid_argument("Can't open file");
        }
    }
    ~Editor(){
        file.close();
    }
    void open(const std::string& filePath){
        file.open(filePath,std::fstream::in | std::fstream::binary);
        if(!file){
            throw std::invalid_argument("Can't open file");
        }
    }
    void close()
    {
        file.close();
    }
    std::size_t size() const
    {
        return fileSize;
    }

};
class Processor{

public:
    void execute(const Editor& e,const Command& c)
    {

    }
private:
};
int main()
{

	return 0;
}
