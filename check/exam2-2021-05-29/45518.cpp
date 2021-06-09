//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Яни Дренчев
// ФН: 45518
// Специалност: Информатика
// Курс: 2 (прекъснал)
// Административна група: -
// Ден, в който се явявате на контролното:
// Начален час на контролното: 9:00
// Кой компилатор използвате: Clang
//
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum class CommandType {
    SIZE,
    SHOW,
    EDIT,
    EXIT,
    NIL,
};

class Command {
private:
    std::vector<std::string> arguments;

    CommandType commandType;

    CommandType readCommandType(const std::string &cmd);

    std::vector<std::string> readArguments(unsigned int index, const std::string &cmd);

public:
    Command(const std::string &);

    std::size_t size() const;

    std::string operator[](std::size_t) const;

    CommandType getCommandType() const;
};

CommandType Command::readCommandType(const std::string &cmd) {

    std::string cmdType;
    for (char i : cmd) {
        if (i == ' ') {
            break;
        }
        cmdType.push_back(toupper(i));
    }
    if (cmdType == "EXIT") {
        return CommandType::EXIT;
    }
    if (cmdType == "SHOW") {
        return CommandType::SHOW;
    }
    if (cmdType == "EDIT") {
        return CommandType::EDIT;
    }
    if (cmdType == "SIZE") {
        return CommandType::SIZE;
    }
    return CommandType::NIL;
}

Command::Command(const std::string &cmd) {
    commandType = readCommandType(cmd);

    unsigned int index = 0;
    for (std::string::size_type i = index; i < cmd.size(); ++i) {
        if (cmd[i] == ' ') {
            index++;
            break;
        }
        index++;
    }
    arguments = readArguments(index, cmd);
}

std::vector<std::string> Command::readArguments(unsigned int index, const std::string &cmd) {
    std::string argument;
    std::vector<std::string> argumentVec;
    for (unsigned int i = index; i < cmd.size(); ++i) {
        if (cmd[i] == ' ') {
            argumentVec.push_back(argument);
            argument.clear();
            continue;
        }
        argument.push_back(cmd[i]);
    }
    argumentVec.push_back(argument);
    return argumentVec;
}

std::size_t Command::size() const {
    return arguments.size();
}

std::string Command::operator[](std::size_t index) const {
    assert(arguments.size() > index);
    return arguments[index];
}

CommandType Command::getCommandType() const {
    return commandType;
}

class Editor {
private:
    std::fstream file;
    std::size_t fileSize;
public:
    Editor(const std::string &fileName);

    bool open(const std::string &fileName);

    bool close();

    ~Editor();

    std::size_t size() const;

    bool edit(std::size_t offset, std::uint8_t value);

    void display(std::ostream &out, std::size_t offset, std::size_t limit);
};

bool Editor::open(const std::string &fileName) {
    std::ifstream testFile;
    testFile.open(fileName, std::ios::binary | std::ios::out | std::ios::in);
    if (!testFile.is_open()) {
        throw (std::invalid_argument("Invalid Filename"));
    }
    file.open(fileName);
    return true;
}

bool Editor::close() {
    if (file.is_open()) {
        file.close();
        return true;
    }
    std::cout << "No file is opened \n";
    return false;
}

Editor::Editor(const std::string &_fileName) {
    try {
        open(_fileName);
    } catch (std::invalid_argument &ex) {
        std::cout << "File Could not be opened \n";
    }
//    Изпуснал съм лекцията :)
    file.seekg(file.eof());
    fileSize = 0 + file.tellg();
}

Editor::~Editor() {
    close();
}

std::size_t Editor::size() const {
    return fileSize;
}

bool Editor::edit(std::size_t offset, std::uint8_t value) {
    if (offset > fileSize) {
        throw (std::invalid_argument("Invalid position in file \n"));
    }
    file.seekp(file.beg + offset);
    file << value;
    return true;
}

void Editor::display(std::ostream &out, std::size_t offset, std::size_t limit) {
    if (offset > fileSize) {
        throw (std::invalid_argument("Invalid position in file \n"));
    }
    file.seekg(file.beg + offset);
    size_t limitTester = 0;
    while (file.eof()) {
        if (limitTester > limit) {
            return;
        }
        out << file.get();
    }
}

class Processor {
private:
    Editor *editor;

public:
    Processor(const std::string &file) {
        editor = new Editor(file);
    }

    ~Processor() = default;

    Processor &operator=(const Processor &processor) = delete;

    Processor(const Processor &oth) = delete;

    bool is_valid(const Command &cmd) const;

    bool execute(const Command &cmd);
};

bool Processor::is_valid(const Command &cmd) const {
    switch (cmd.getCommandType()) {
        case CommandType::EXIT:
            if (cmd.size() == 0) {
                return true;
            }
            break;
        case CommandType::SHOW:
            try {
                std::stoi(cmd[0]);
                std::stoi(cmd[1]);
            }
            catch (std::invalid_argument &exx) {
                std::cout << "Invalid arguments must be numeric\n";
                return false;
            }
            if (cmd.size() == 2) {
                return true;
            }
            break;
        case CommandType::EDIT:
            try {
                std::stoi(cmd[0]);
                std::stoi(cmd[1]);
            }
            catch (std::invalid_argument &exx) {
                std::cout << "Invalid arguments must be numeric\n";
                return false;
            }
            if (cmd.size() == 2) {
                return true;
            }
            break;
        case CommandType::SIZE:
            if (cmd.size() == 0) {
                return true;
            }
            break;
        case CommandType::NIL:
            return false;
    }
    return false;
}

bool Processor::execute(const Command &cmd) {
    if (!is_valid(cmd)) {
        std::cout << "Invalid Command please try again\n";
    }
    switch (cmd.getCommandType()) {
        case CommandType::EXIT:
            return true;
        case CommandType::SHOW:
            try {
                editor->display(std::cout, std::stoi(cmd[0]), std::stoi(cmd[1]));
            } catch (std::invalid_argument &ex) {
                std::cout << "Invalid position in file \n";
                return false;
            }
            break;
        case CommandType::EDIT:
            try {
                editor->edit(std::stoi(cmd[0]), std::stoi(cmd[1]));
                std::cout << "OK \n";
            } catch (std::invalid_argument &ex) {
                std::cout << "Command not executed\n";
            }
        case CommandType::SIZE:
            std::cout << editor->size() << "\n";
            break;
        case CommandType::NIL:
            return false;
    }
    return true;
}


int main(int argc, char *argv[]) {
    std::string fileName;
    if (argc < 2) {
        std::cout << "No file name provided \n";
        return 0;
    } else {
        fileName = argv[1];
    }
    std::fstream testFile(fileName);
    if (!testFile.is_open()) {
        std::cout << "Could not open file \n";
    }
    Processor proc(fileName);
    std::string cmd;
    std::getline(std::cin, cmd);
    while (true) {
        if (cmd == "EXIT") {
            return 1;
        }
        bool isCommandValid = proc.execute(cmd);
        while (!isCommandValid) {
            std::cin >> cmd;
            isCommandValid = proc.execute(cmd);
        }
    }
}