
//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Александър Костадинов
// ФН: 82198
// Специалност: КН
// Курс: първи
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9.00
// Кой компилатор използвате: GCC

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return char(int(c) - 32);
    }

    return c;
}

class Command
{
public:
    std::string command;
    std::string command_specification1;
    std::string command_specification2;

public:
    Command(std::string com)
    {
        try
        {
            size_t i = 0;
            while (com[i] == ' ' && i < com.size())
            {
                     i++;
            }

            while (com[i] != ' ' && i < com.size())
            {
                command.push_back(to_upper(com[i]));

                i++;
            }
            std::cout << command << "\n";
            if (command != "EXIT" && command != "EDIT" && command != "SIZE" && command != "SHOW")
            {
                throw std::invalid_argument("");
            }

            while (com[i] == ' ')
            {
                i++;
            }

            while (com[i] != ' ' && i < com.size())
            {
                command_specification1.push_back(com[i]);
                i++;
            }
            std::cout << command_specification1 << "\n";

            if (!command_specification1.empty())
            {
                int test = std::stoi(command_specification1);
            }

            while (com[i] == ' ' && i < com.size())
            {
                i++;
            }

            while (com[i] != ' ' && i < com.size())
            {
                command_specification2.push_back(com[i]);
                i++;
            }

            std::cout << command_specification2 << "\n";

            if (!command_specification2.empty())
            {
                int test = std::stoi(command_specification2);
            }
        }
        catch (std::invalid_argument)
        {
            std::cerr << "Invalid command!" << '\n';
        }
        catch (...)
        {
            std::cerr << "Wrong input!"
                      << "\n";
        }
    }

    Command(const Command &other)
    {
        this->command = other.command;
        this->command_specification1 = other.command_specification1;
        this->command_specification2 = other.command_specification2;
    }

    const size_t size() const
    {
        if (!command_specification1.empty() && !command_specification2.empty())
        {
            return 3;
        }
        else if (!command_specification1.empty())
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    std::string operator[](size_t index)
    {
        if (index == 0)
        {
            return this->command;
        }
        else if (index == 1)
        {
            return this->command_specification1;
        }
        else if (index == 2)
        {
            return this->command_specification2;
        }
        else
        {
            throw std::out_of_range("Invalid index!\n");
        }
    }
};

class Editor
{
private:
    std::string file_name;
    std::fstream file;
    size_t size;

public:
    Editor()
    {
    }
    Editor(std::string file_name)
    {
        this->file_name = file_name;
        file.open(file_name, std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Error with file opening!\n");
        }
    }

    void open(std::string file_name)
    {
        this->file_name = file_name;
        file.open(this->file_name, std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Error with file opening!\n");
        }

        file.seekp(0, std::ios::end);
        size = file.tellp();
        std::cout << size << "\n";
    }

    void close()
    {
        if (!file.good())
        {
            file.clear();
        }

        file.close();
    }

    const size_t size_of_file() const
    {
        return this->size;
    }

    void edit(size_t offset, std::uint8_t value)
    {
        if (offset > size)
        {
            throw std::invalid_argument("offset cannot be bigger than the file size!\n");
        }

        file.seekp(offset, std::ios::beg);
        file.write((char *)&value, sizeof(value));

        if (!file.good())
        {
            std::cout << "Fail!\n";
        }
        else
        {
            std::cout << "OK\n";
        }

        file.seekp(0, std::ios::end);
        size = file.tellp();
    }

    void display(std::ostream &out, size_t offset, size_t limit)
    {
        file.close();
        file.open(file_name, std::ios::in | std::ios::binary);
        file.seekg(offset, std::ios::beg);
        if (offset > size)
        {
            throw std::invalid_argument("offset cannot be bigger than the file size!\n");
        }
        uint8_t x;
        while (offset < limit)
        {
            // x = file.read((char*)&x, sizeof(x));
        }
    }
};

class Processor
{
private:
    Command command;
    Editor editor;

public:
    Processor(Command com) : command(com)
    {
    }

    void execute()
    {
        if (command.command == "EXIT")
        {
            editor.close();
            return;
        }
        else if (command.command == "SHOW")
        {
            // editor.display()
        }
        else if (command.command == "EDIT")
        {
            editor.edit(std::stoi(command.command_specification1), std::stoi(command.command_specification2));
        }
        else if (command.command == "SIZE")
        {
            std::cout << editor.size_of_file() << "\n";
        }
        else
        {
            throw std::invalid_argument("Invalid command!\n");
        }
    }

private:
    bool is_valid() const
    {
        if (command.command == "EXIT" && command.command == "EDIT" && command.command == "SIZE" && command.command == "SHOW")
        {
            return true;
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    if (argv[1])
    {
        Editor edit(argv[1]);
        while (true)
        {
            std::string com;
            std::getline(std::cin, com);
            Command command(com);
            Processor process(com);
            process.execute();

        }
    }
    else
    {
        throw std::invalid_argument("No file or bad file!\n");
    }

    return 0;
}