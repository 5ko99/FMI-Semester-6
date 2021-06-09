//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име:Боян Павлов
// ФН:82027
// Специалност: КН
// Курс:1
// Административна група:3
// Ден, в който се явявате на контролното:29.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::vector;

#ifndef _EXCEPTIONS_
#define _EXCEPTIONS_
class FileCouldntOpen : std::exception
{
public:
    const char *what() const throw()
    {
        return "File couldn't open\n";
    }
};

#endif _EXCEPTIONS_

#ifndef _COMMAND_
#define _COMMAND_

class Command
{
private:
    string command;
    int numberOfArg;
    string substr;

public:
    static vector<string> list_commands;
    Command(string input) : command(input)
    {
        int counter = 0;
        char space = ' ';
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == space)
            {
                counter++;
            }
        }
        counter++;
        numberOfArg = counter;
    }

    std::size_t size() const
    {
        return numberOfArg;
    }

    string &operator[](std::size_t argument_index)
    {
        substr = command;

        int counter = 0;
        char space = ' ';
        int possition = -1;
        for (int i = 0; i < command.size(); i++)
        {
            if (command[i] == space)
            {
                counter++;
                // substr.erase(i-1, i);
                if (counter == argument_index)
                {
                    possition = i;
                    substr.erase(0, possition);
                }
            }
        }
        if (substr[0] == space)
        {
            substr.erase(0, 1);
        }

        int endOfSubstr = 0;
        for (int i = 0; i < substr.size(); i++)
        {
            if (substr[i] == space)
            {
                endOfSubstr = substr.size() - i;
                substr.erase(0 + i, endOfSubstr);
            }
        }
        return substr;
    }
};

vector<string> Command::list_commands =
    {"EXIT",
     "SIZE",
     "EDIT",  //EDIT <offset> <byte>
     "SHOW"}; //SHOW <offset><limit>}

const int numberOfArg[] = {
    0, //EXIT
    0, //SIZE
    2, //EDIT
    2  //SHOW
};

enum Commands
{
    EXIT,
    SIZE,
    EDIT,
    SHOW
};

#endif // _COMMAND_

#ifndef _EDITOR_
#define _EDITOR_

class Editor
{
private:
    string given_path;
    fstream file;
    std::size_t size;

public:
    Editor(string path)
    {
        open(path);
        file.seekp(0, std::ios_base::end);
        size = file.tellp();
    }

    ~Editor()
    {
        close();
    }

    void open(string path)
    {
        file.open(path, std::ios::binary | std::ios::in);
        if (!(file.is_open()))
        {
            throw FileCouldntOpen();
        }
        given_path = path;
    }
    void close()
    {
        file.close();
    }
    std::size_t size() const
    {
        return size;
    }
    void edit(std::size_t offset, std::uint8_t value)
    {
        file.open(given_path, std::ios::binary | std::ios::out);
        if (!file.is_open())
        {
            throw FileCouldntOpen();
        }

        if (offset >= size)
        {
            throw std::invalid_argument("Out of bounds");
        }
        else
        {
            file.seekg(0, offset);
            file.write((char *)&value, sizeof(value));
        }
    }

    void display(std::ostream &out, std::size_t offset, std::size_t limit)
    {
        if (offset >= size)
        {
            throw std::invalid_argument("Out of bounds");
        }
    }
};

#endif // _EDITOR_

#ifndef _PROCESSOR_
#define _PROCESSOR_

class Processor
{
private:
    // Processor() = default;
    string m_path;
    Editor &m_edit;

public:
    // static Processor &getInstance()
    // {
    //     static Processor instance;
    //     return instance;
    // }

    // Processor(const Processor &) = delete;
    // Processor &operator=(const Processor &) = delete;

    Processor(string given_path)
    {
        Editor edit(given_path);
        m_edit = edit;
    }

    bool is_valid(Command &givenCommand)
    {
        // check if command is valid
        for (int i = 0; i < Command::list_commands.size(); i++)
        {
            if (givenCommand[0] == Command::list_commands[i] && (givenCommand.size() - 1) == numberOfArg[i])
            {
                return true;
            }
        }
        return false;
    }

    void execute(Command &givenCommand)
    {

        int possition = 0;
        for (int i = 0; i < Command::list_commands.size(); i++)
        {
            if (givenCommand[0] == Command::list_commands[i] && (givenCommand.size() - 1) == numberOfArg[i])
            {
                possition = i;
            }
        }

        switch (possition)
        {
        case EXIT:
            cout << "You are exiting the program\n";
            break;
        case SIZE:
            cout << edit.size() << " byte(s)";
            break;
        case EXIT:
            cout << "You are exiting the program\n";
            break;
        case EXIT:
            cout << "You are exiting the program\n";
            break;

        default:
            break;
        }
        // try
        // {
        //     /* code */
        // }
        // catch(const FileCouldntOpen& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }

        //TODO
    }
};

#endif // _PROCESSOR_

int main(int argc, char const *argv[])
{
    // string command = "SHOW world bye";
    // Command c(command);
    // string co1 = c[0];
    // string co2 = c[1];
    // string co3 = c[2];

    // // std::cout << co1;
    // // std::cout << co2;
    // // std::cout << co3;
    // // cout << c.size();

    // Processor &p = Processor::getInstance();
    // cout << p.is_valid(c);

    return 0;
}
