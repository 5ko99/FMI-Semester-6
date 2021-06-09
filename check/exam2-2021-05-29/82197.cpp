// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Любен Георгиев Георгиев
// ФН: 82197
// Специалност: КН
// Курс: първи
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//
//




// YOU NEED Database.txt
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

/*Напишете клас command, който представя команда.

Класът трябва да има подходящ конструктор, в който да получава символен низ -- текстът на командата.
Вътрешно класът трябва да разбие низа на части -- името на командата и нейните аргументи.
Класът да има функция std::size_t size() const, която връща броя на аргументите.
Класът да предефинира operator[] така, че с него да могат да се извличат частите на командата. 
Операторът ще получава стойност от тип std::size_t. 
Тази стойност указва индекса на дума в командата (т.е. 0 - името на командата, 1 - първият ѝ аргумент и т.н.).

*/

class Command
{
private:
    std::vector<std::string> storage;

public:
    Command(std::string cmnd)
    {
        size_t i = 0;
        size_t j = 0;
        while (i < cmnd.size())
        {
            if (i < cmnd.size() && cmnd[i] != ' ') {
                std::string tempStr = "";
                while (i < cmnd.size() && cmnd[i] != ' ')
                {
                    tempStr.push_back(cmnd.at(i));
                    ++i;
                }  
                ++j;
                storage.push_back(tempStr);
            }
            else {
                ++i;
            }
            
        }
        
    }

    size_t size() const
    {
        if (storage.size()) {
            return storage.size() - 1;
        }
        return 0;
    }

    std::string& operator[](size_t index)
    {
        return storage[index];
    }

};



class Editor
{
private:
    std::string path;
    size_t m_size = 0;
    std::fstream file;
    bool isOpen = false;
    
public:
    Editor(std::string path)
        : path(path)
    {
        open();
    }

    ~Editor()
    {
        if (isOpen) {
            file.close();
        }
    }

    void open()
    {
        file.open(path, std::ios::binary | std::ios::in | std::ios::out);
        if (!file) {
            throw "Error while opening file!\n";
        }
        isOpen = true;

        size();        
    }

    void close()
    {
        file.close();
    }

    size_t size()
    {
        if (isOpen) {
            file.seekg(0, std::ios::end);
            m_size = file.tellg();
            file.seekg(0, std::ios::beg);
            m_size -= file.tellg();

            return m_size;
        }
        return 0;
    }


    void edit(std::size_t offset, std::uint8_t value)
    {
        if (isOpen) {
            if (offset > size()) {
                throw std::invalid_argument("Too big offset\n");
            }
            file.seekp(offset, std::ios::beg);
            file.write((char*)&value, sizeof(value));
        }
        else {
            std::cout << "File is not open\n";
        }
    }

    std::ostream& display(std::ostream& out, std::size_t offset, std::size_t limit)
    {
        if (isOpen) {
            if (offset > size()) {
                throw std::invalid_argument("Too big offset\n");
            }
            file.seekg(offset, std::ios::beg);

            uint8_t buffer = 0;
            size_t i = m_size - offset;

            while (i != 0) {
                file.read((char*)&buffer, sizeof(buffer));
                out << std::hex << (int)buffer << ' ';
                
                i--;
            }
        }
        else {
            std::cout << "File is not open\n";
        }

        return out;
    }
};

/*
Напишете клас processor, който изпълнява команди.

Класът да има предикат is_valid, която получава обект от тип command и връща true или false, 
в зависимост дали командата е коректна или в нея има грешка.
Класът да има функция execute, която получава команда и я изпълнява.

Класът да не изпълнява командите директно, нито да работи директно с файла, а вместо това да работи с обект от класа editor.
Класът трябва да прихваща възможни изключения хвърлени от editor и когато е нужно да извежда съобщение за грешка.
*/

class Processor
{
private:
    Editor e;

public:
    Processor(std::string path)
        : e(path)
    {
    }

    bool is_valid(Command& cmnd)
    {
        if (cmnd[0] == "EXIT" || cmnd[0] == "SIZE") return true;

        if (cmnd[0] == "EDIT" || cmnd[0] == "SHOW") {
            return cmnd.size() == 2;
        }

        return false;
    }

    void execute(Command& cmnd)
    {
        if (!is_valid(cmnd)) return;

        if (cmnd[0] == "EXIT") {
            ;
        }
        else if (cmnd[0] == "SIZE") {
            std::cout << e.size();
        }
        else if (cmnd[0] == "EDIT") {
            e.edit(atoi(cmnd[1].c_str()), atoi(cmnd[2].c_str()));
        }
        else {
            e.display(std::cout, atoi(cmnd[1].c_str()), atoi(cmnd[2].c_str()));
        }
    }



};

int main()
{
    std::string path("Database.txt");
    Processor p(path);
    
    // std::string s("EDIT 0 255");
    // Command cmnd(s);

    // p.execute(cmnd);

    // s = "SHOW 0 1";
    // Command cmnd1(s);

    // p.execute(cmnd1);

    while (true) {
        std::string cmndStr1;
        std::cin >> cmndStr1;
        std::string cmndStr2;
        std::cin >> cmndStr2;
        std::string cmndStr3;
        std::cin >> cmndStr3;
        std::string cmndStr;
        cmndStr = cmndStr1 + cmndStr2 + cmndStr3;
        Command cmnd(cmndStr);

        p.execute(cmnd);

        if (cmnd[0] == "EXIT") {
            break;
        }
    }


	return 0;
}