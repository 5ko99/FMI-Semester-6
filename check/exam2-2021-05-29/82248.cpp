//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Мартин Йорданов
// ФН: 82248
// Специалност: KН
// Курс: 1
// Административна група:
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
class Command {
    std::vector<std::string> args;
    std::string cmd;
public:
    Command(std::string cmdLine) {
        
        auto stream = std::stringstream(cmdLine);
        stream >> cmd;
        std::string buf;
        while (!stream.eof())
            stream >> buf;
            args.push_back(buf);
    }

    std::size_t size() const {
        return args.size();
    }

    std::string operator[](std::size_t index) {
            if (!index)
                return cmd;
            else
                return args.at(index - 1);
    }
};

class Editor {
    std::fstream file;
    std::size_t fileSize;
    std::string filePath;
public:
    Editor() {}
    
    Editor(std::string path) {
        filePath = path;
        if (path.size())
            open();        
    }

    Editor(Editor &other) {
        filePath = other.filePath;        
        other.close();
        open();
        fileSize = other.fileSize;
    }

    Editor &operator=(Editor &other) {
        filePath = other.filePath;        
        other.close();
        open();
        fileSize = other.fileSize;
        return *this;
    }

    ~Editor() {
        file.close();
    }

    void open() {
        file.open(filePath, std::ios_base::binary);
        if (file.failbit) 
            throw std::runtime_error("Failed to open file");
        
        while (!file.eof())
            file.read(NULL, 1);

        fileSize = file.tellg();
        file.seekg(0);
    }

    size_t size() {
        return fileSize;
    }

    void close() {
        file.close();
    }
    
    void edit(std::size_t offset, std::uint8_t value) {
        if (offset >= fileSize)
            throw std::invalid_argument("Out of range offset");

        file.seekp(offset);
        file.write((char *)&value, 1);
    }

    void display(std::ostream& out, std::size_t offset, std::size_t limit) {
        if (offset >= fileSize)
            throw std::invalid_argument("Out of range offset");

        char value;
        file.seekg(offset);
        for(int i = 0; file.tellg() < limit + offset && !file.eof(); ++i){
            file.read(&value, 1);
            if (i % 16 == 0)
                out << std::endl << std::setfill('0') << std::setw(2) << file.tellg();
            out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)value;
        }

    }
};

class Processor {
    Editor &editor;
    std::ostream &_out;

public:
    Processor(Editor &e, std::ostream &out) : editor(e),  _out(out) {}

    bool is_valid(Command com) {
        return com.size() > 0;
    }

    int execute(Command com) {
        is_valid(com);
        std::string cmdName = com[0];
        if (!cmdName.compare("EXIT"))
        {
            editor.close();
            return 1;
        } else if (!cmdName.compare("EDIT")) {
            if (com.size() < 2)
                throw std::invalid_argument("Not enough arguments");
            std::size_t offset = atoi(com[1].c_str());
            std::size_t value = atoi(com[2].c_str());
            try
            {
                editor.edit(offset, value);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return 1;
            }
            
            _out << "OK!" << std::endl;

        } else if (!cmdName.compare("SIZE")) {
            _out << editor.size() << " byte(s)";
        } else if (!cmdName.compare("SHOW")) {
            if (com.size() < 2)
                throw std::invalid_argument("Not enough arguments");
            std::size_t offset = atoi(com[1].c_str());
            std::size_t limit = atoi(com[2].c_str());
            editor.display(_out, offset, limit);
        } else {
            throw std::invalid_argument("No such command");
        }
        return 0;
    }
};
int main(int argc, char const *argv[])
{
    if (argc < 2)
        return 1;
    try
    {
        Editor editor(argv[1]);
        std::string commandStr;
        Processor proc(editor, std::cout);
        while (true)
        {
            std::cin >> commandStr;
            Command cmd(commandStr);
            proc.execute(cmd);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    

    return 0;
}