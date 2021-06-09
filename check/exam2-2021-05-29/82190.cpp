// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Михаил Гинчев Сашков
// ФН: 82190
// Специалност: Компютърни науки
// Курс: I
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021г.
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <iomanip>

class Command {
private:
    std::string command;
    std::vector<std::string> container;

public:
    Command(std::string command);
    Command();
    std::size_t size() const;
    std::string& operator [](std::size_t pos);

};

class Editor : public Command {
private:
    std::fstream file;
    std::size_t fileSize;
    std::string path;
    void rewind();

public:
    Editor(std::string path);    
    void open(std::string path);
    void close();
    std::size_t size() const;
    void edit(std::size_t offset, std::uint8_t value);
    void display(std::ostream& out, std::size_t offset, std::size_t limit);
    ~Editor();

};

class Processor {
private:
    bool is_valid(Command& command);

public:
    bool execute(Editor& editor, Command& command);

};

Command::Command() {
    command = "";
}

Command::Command(std::string command) {

    if(command.compare("EXIT") == 0) {
        container.push_back(command);
    }

    else if(command.compare("SIZE") == 0) {
        container.push_back(command);
    }

    else if(command.compare("EDIT") == 0 || command.compare("SHOW") == 0) {

        std::string arguments = command.substr(command.find(" ") + 1);
        std::string firstArgument = arguments.substr(0, arguments.find(" "));
        std::string secondArgument = arguments.substr(arguments.find(" ") + 1);
        std::string commandPart = command.substr(0, command.find(" "));

        container.push_back(commandPart);
        container.push_back(firstArgument);
        container.push_back(secondArgument);

    }

    else {
        container.push_back(command);
    }

    this->command = command;

}

std::size_t Command::size() const {
    return container.size() - 1;
}

std::string& Command::operator[](std::size_t pos) {

    assert(pos < 0 || pos >= container.size());

    return container[pos];

}

bool Processor::is_valid(Command& command) {

    if(!((command[0].compare("EXIT") == 0 || command[0].compare("SIZE") == 0) && command.size() == 0) ||
          ((command[0].compare("EDIT") == 0 || command[0].compare("SHOW") == 0) && command.size() == 2) ) {

            return false;

    }

    if(command[0].compare("EDIT") == 0 || command[0].compare("SHOW") == 0) {

        if(!(stoi(command[1]) && stoi(command[2]))) {
            return false;
        }

    }

    return true;

}

bool Processor::execute(Editor& editor, Command& command) {

    if(is_valid(command)) {

        try {

            if(command[0].compare("EXIT") == 0) {
                return false;
            }

            else if(command[0].compare("SIZE") == 0) {
                std::cout << editor.size() << std::endl;
            }

            else if(command[0].compare("EDIT") == 0) {
                editor.edit(stoi(command[1]), stoi(command[2]));
            }

            else if(command[0].compare("SHOW") == 0) {
                editor.display(std::cout, stoi(command[1]), stoi(command[2]));
            }

            return true;
        }
        catch(std::runtime_error& ex) {
            std::cout << ex.what() << std::endl;
        }
        catch(std::invalid_argument& ex) {
            std::cout << ex.what() << std::endl;
        }


    } 

    else {
        return false;
    }   

}

Editor::Editor(std::string path) {

    file.open(path, std::ios_base::binary | std::ios_base::ate);
    fileSize = file.tellg();
    rewind();

    if(!file.is_open()) {
        throw std::runtime_error("The did not open");
    }

    if(fileSize % sizeof(std::uint8_t)) {
        throw std::runtime_error("The content is incorrect");
    }

    fileSize /= sizeof(std::uint8_t);
    
    

    this->path = path;

}

void Editor::rewind() {
    file.seekg(0, std::ios_base::beg);
}

void Editor::open(std::string path) {

    file.open(path, std::ios_base::binary | std::ios_base::ate);
    if(!file.is_open()) {
        throw std::runtime_error("The did not open");
    }
    fileSize = file.tellg();
    rewind();

    this->path = path;

}

void Editor::close() {
    file.close();
    fileSize = 0;
}

Editor::~Editor() {
    file.close();
}

std::size_t Editor::size() const {
    return fileSize;
}

void Editor::edit(std::size_t offset, std::uint8_t value) {

    if(offset > fileSize) {
        throw std::invalid_argument("The offset is bigger than the file size");
    }

    if(offset == fileSize) {
        fileSize++;
    }

    file.seekp(offset*sizeof(value), std::ios_base::beg);
    file.write((const char*)&value, sizeof(value));

}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit) {

    if(offset >= fileSize) {
        throw std::invalid_argument("Incorrect file size");
    }

    std::uint8_t value;

    file.seekg(offset, std::ios_base::beg);
    int counter = 0;
    while(counter < limit || file.eof()) {

        file.read((char*)&value, sizeof(value));
        out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)value;
        counter++;
    }

}

int main(int argc, char** argv) {

    std::string command;
    bool exit = true;
    std::string commandPart;
    Processor processor = Processor();

   try { 
        if(argc != 2) {
            throw std::runtime_error("Incorrect arguments");
        }

        std::cout << "Insert your command with upper letters." << std::endl;

        while(exit) {

            getline(std::cin, command);
            Command commands(command);
            Editor editor(argv[1]);
            exit = processor.execute(editor, commands);

        }


    
    }
    catch(std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }

	return 0;
}