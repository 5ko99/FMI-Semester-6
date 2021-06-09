// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име:Самуил Антонов Миланов
// ФН: 45744
// Специалност: Информатика
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното:  29.05.21
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class command{
    std::vector<std::string> List;
public:
    command(const char* ComAndArg)
    {
        char p;
        int i = 0;
        std::string thing;
        while(i < strlen(ComAndArg)) {
            thing.clear();
            p = ComAndArg[i];
            while (p != ' ') {
                thing.push_back(p);
                i++;
                p = ComAndArg[i];
            }
            this->List.push_back(thing);
            i++;
        }
        this->List.push_back(thing);
    }
    std::size_t size() const
    {
        return this->List.size();
    }
    std::string& operator[](std::size_t pos)
    {
        return this->List.at(pos);
    }
};
class editor
{
    std::size_t size;
    std::fstream File;
public:
    editor(const std::string& path)
    {
        this->File.open(path, std::ios::binary | std::ios::out | std::ios::in);
        if(!File.is_open())
        {
            throw "File couldn't open\n";
        }
        File.seekp(std::ios::end);
        this->size = File.tellp();
    }
    void open (const std::string& path)
    {
        this->File.open(path, std::ios::binary | std::ios::out | std::ios::in);
        if(!File.is_open())
        {
            throw "File couldn't open\n";
        }
        std::string something;
        while(getline(this->File, something))
        {}
        this->size = File.tellp();
    }
    void close()
    {
        this->File.close();
    }
    std::size_t GetSize()
    {
        return this->size;
    }
    void edit(std::size_t offset, std::uint8_t value)
    {
        if(this->size < offset)
        {
            throw  std::invalid_argument("Invalid argument\n ");
        }
        File.write((const char*) &value, offset);
    }
    std::ostream& display(std::ostream& out, std::size_t offset, std::size_t limit)
    {
        if(limit + offset > this->size)
        {
            throw std::invalid_argument("Invalid argument\n ");
        }
        File.seekp(offset);
        std::string displaying;
        File.read((char *)& displaying, limit);
        out << displaying;
        return out;
    }
};

class processor
{
public:
    bool is_Valid (command& command1)
    {
        if(!(strcmp(command1[0].c_str(), "SHOW") !=0
        || strcmp(command1[0].c_str(), "EXIT") !=0
        || strcmp(command1[0].c_str(), "EDIT") !=0
        || strcmp(command1[0].c_str(), "SIZE") !=0))
        {
            return false;
        }
        if(strcmp(command1[0].c_str(), "SHOW") ==0)
        {
            for(int i = 0; i < command1[1].size(); i++)
            if(command1[1].at(i) < '0' || command1[1].at(i) > '9')
            {
                return false;
            }
            for(int i = 0; i < command1[2].size(); i++)
                if(command1[2].at(i) < '0' || command1[2].at(i) > '9')
                {
                    return false;
                }
        }
        if(strcmp(command1[0].c_str(), "EDIT") ==0)
        {
            for(int i = 0; i < command1[1].size(); i++)
                if(command1[1].at(i) < '0' || command1[1].at(i) > '9')
                {
                    return false;
                }
            for(int i = 0; i < command1[2].size(); i++)
                if(command1[2].at(i) < '0' || command1[2].at(i) > '9')
                {
                    return false;
                }
        }
        return true;
    }
    void execute(command& command_new, editor& MainEditor)
    {
        if(!is_Valid(command_new))
        {
            std::cout << "Command is not correct\n";
            return;
        }
        if(strcmp(command_new.operator[](0).c_str(), "SIZE") == 0)
        {
            std::cout << MainEditor.GetSize() << " byte(s)" << std::endl;
        }
        if(strcmp(command_new.operator[](0).c_str(), "EDIT") == 0)
        {
            try {
                std::size_t offset = 0;
                std::size_t byte = 0;
                for (int i = 0; i < command_new.operator[](1).size(); i++) {
                    offset = offset +
                             (command_new.operator[](1).at(i) - '0') * pow(10, command_new.operator[](1).size() - i);
                }
                for (int i = 0; i < command_new.operator[](2).size(); i++) {
                    byte = byte +
                           (command_new.operator[](2).at(i) - '0') * pow(10, command_new.operator[](2).size() - i);
                }
                MainEditor.edit(offset, byte);
                std::cout << "OK\n";
            }
            catch(...)
            {
                std::cout << "Fail\n";
            }
        }
        if(strcmp(command_new.operator[](0).c_str(), "SHOW") == 0)
        {
            try {
                std::size_t offset = 0;
                std::size_t limit = 0;
                for (int i = 0; i < command_new.operator[](1).size(); i++) {
                    offset = offset +
                             (command_new.operator[](1).at(i) - '0') * pow(10, command_new.operator[](1).size() - i);
                }
                for (int i = 0; i < command_new.operator[](2).size(); i++) {
                    limit = limit +
                            (command_new.operator[](2).at(i) - '0') * pow(10, command_new.operator[](2).size() - i);
                }
                MainEditor.display(std::cout, offset, limit);
            }
            catch (...)
            {
                std::cout << "Fail\n";
            }
        }
    }
};

int main()
{
    std::string path;
    std::cin >> path;
    try {
        editor MainEditor(path);
    }
    catch (...)
    {
        std::cout << "File couldn't be opened.\n";
        return 0;
    }
    editor MainEditor(path);
    std::string new_command;

    while(strcmp(new_command.c_str(), "EXIT") != 0) {
        std::cout << "Enter command\n";
        getline(std::cin >> new_command, new_command);
        command command_new(new_command.c_str());
        processor a;
        a.execute(command_new, MainEditor);
    }
    MainEditor.close();
    return 0;
}