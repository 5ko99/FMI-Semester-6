//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Християн Ангелов
// ФН: 82099
// Специалност: КН
// Курс: 2
// Административна група: 3
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

class Editor {
    std::fstream file;

    size_t _size();
    void _is_open();
public:
    Editor();
    Editor(std::string path);
    ~Editor();
    void open(std::string path);
    void close();
    size_t size();
    void edit(std::size_t offset, std::uint8_t value);
    void display(std::ostream& out, std::size_t offset, std::size_t limit);
};
class Processor;
class Command {
    std::string command;
    std::vector<std::string> splitedCommand;

    void _split(std::string command) {
        std::string currentWord = "";
        for (size_t i = 0; i < command.size(); i++) {
            if (command[i] == ' ') {
                if (currentWord != "") {
                    splitedCommand.push_back(currentWord);
                }
                currentWord = "";
            } else {
                currentWord += command[i];
            }
        }

        if (currentWord != "") {
            splitedCommand.push_back(currentWord);
        }
    }
public:
    Command(std::string command) {
        this->command = command;
        _split(command);
    }

    size_t size() const {
        return splitedCommand.size();
    }

    std::string operator[] (size_t i) const {
        if (i > size()) {
            throw std::runtime_error("Index out of bounds!");
        }

        return splitedCommand[i];
    }
};

class Processor {
    Editor *editor;

public:
    Processor(Editor* editor): editor(editor) { }

    ~Processor() {
        delete editor;
    }

    bool is_valid(const Command& command) {
        if (command[0] == "SHOW" && command.size() >= 3) {
            return true;
        } else if (command[0] == "SIZE"){
            return true;
        } else if (command[0] == "EXIT") {
            return true;
        } else if (command[0] == "EDIT" && command.size() >= 3) {
            return true;
        }

        return false;
    }

    void execute(const Command& command) {
        try {
            if (!is_valid(command)) {
                throw std::invalid_argument("Invalid command!");
            }

            if (command[0] == "SHOW") {
                editor->display(std::cout, std::stoul(command[1], nullptr, 0), std::stoul(command[2], nullptr, 0));
            } else if (command[0] == "SIZE"){
                std::cout << editor->size() << std::endl;
            } else if (command[0] == "EXIT") {
                editor->close();
                std::cout << "FILE CLOSED!" << std::endl;
            } else if (command[0] == "EDIT") {
                editor->edit(std::stoul(command[1], nullptr, 0), std::stoul(command[2], nullptr, 0));
            }

        } catch (std::exception& error) {
            std::cout << error.what() << std::endl;
        }
    }
};

size_t Editor::_size() {
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    return size;
}

void Editor::_is_open() {
    if (!file.is_open()) {
        throw std::runtime_error("No open file!");
    }
}

Editor::Editor(const std::string path) {
        open(path);
}

Editor::~Editor() {
        close();
}

void Editor::open(const std::string path) {
    file.open(path, std::ios::out | std::ios::app | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("The file could not be open!");
    }
}

void Editor::close() {
    file.close();
}

size_t Editor::size() {
    return _size();
}

void Editor::edit(std::size_t offset, std::uint8_t value) {
    _is_open();

    if (size() <= offset) {
        throw std::invalid_argument("The offset is outside the file bounaries!");
    }

    file.seekp(offset, std::ios::beg);
    file.write((char*)&value, sizeof(value));
    file.seekp(0, std::ios::beg);
}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit) {
    _is_open();

    if (size() <= offset) {
        throw std::invalid_argument("The offset is outside the file bounaries!");
    }

    // Не ми стигна времето
}

Editor::Editor() { }

int main(int argc, const char * argv[]) {
    Editor* editor = new Editor();
    editor->open(argv[2]);
    Processor processor(editor);

    std::string line;
    while (std::getline(std::cin, line)) {
        processor.execute(line);
    }
    return 0;
}
