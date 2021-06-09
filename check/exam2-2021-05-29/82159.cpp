// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Йордан Йорданов
// ФН: 82159
// Специалност: Компютърни науки
// Курс: I-ви
// Административна група: 2-ра
// Ден, в който се явявате на контролното: 29.05.21
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class command {
private:
    std::vector<std::string> commands;
public:
    command() = default;

    command(const std::string &command) {
        this->split(command);
    };

public:
    size_t size() const {
        return this->commands.size();
    }

public:
    std::string &operator[](size_t index) {
        return this->commands[index];
    }

    const std::string &operator[](size_t index) const {
        return this->commands[index];
    }

private:
    void split(const std::string &command) {
        size_t currIndex = 0;
        size_t lastIndex = 0;
        size_t commandSize = command.size();

//        while (currIndex != std::string::npos) {
        while (lastIndex < commandSize) {
            while (command[lastIndex] == ' ') {
                lastIndex++;
            }

            if (lastIndex >= commandSize) {
                break;
            }

            currIndex = command.find(' ', lastIndex + 1);

            if (currIndex == std::string::npos) {
                currIndex = commandSize;
            }

            this->commands.push_back(command.substr(lastIndex, currIndex - lastIndex));

            lastIndex = currIndex;
        }
    }
};

class editor {
private:
    std::fstream file;
    size_t m_size;

public:
    editor() = default;

    editor(const std::string &path) {
        this->open(path);
    }

public:
    size_t size() const {
        return this->m_size;
    }

public:
    void open(const std::string &path) {
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

            if (!this->file) {
                throw std::runtime_error("File couldn't open!");
            }

            this->m_size = this->getFileSize(this->file);
        }
    }

    void close() {
        if (this->file.is_open()) {
            this->file.close();
        }
    }

    void edit(size_t offset, std::uint8_t value) {
        if (offset > this->m_size) {
            throw std::invalid_argument("Error: file size is ");
        }

        this->file.seekp(offset, std::ios::beg);
        this->file.write((const char *) &value, sizeof(std::uint8_t));
    }

    std::ostream &display(std::ostream &out, std::size_t offset, std::size_t limit) {
        if (offset > this->m_size) {
            throw std::invalid_argument("Error: file size is ");
        }

        if (limit > this->m_size) {
            limit = this->m_size - offset;
        }

        size_t counter = 1;
        uint8_t *arr = new std::uint8_t[limit];
        this->file.read((char *) arr, sizeof(std::uint8_t) * limit);

        out << std::setfill('0') << std::setw(8) << std::hex << offset << ' ';

        for (int i = offset; i < offset + limit; ++i) {
            if (counter % 16 == 0) {
                out << std::setfill('0') << std::setw(2) << std::hex << arr[counter] << '\n';
                out << std::setfill('0') << std::setw(8) << std::hex << offset + (counter / 16) << ' ';
            } else {
                out << std::setfill('0') << std::setw(2) << std::hex << arr[counter] << ' ';
            }

            counter++;
        }

        delete[] arr;

        out << '\n';

        return out;
    }

private:
    size_t getFileSize(std::fstream &file) {
        size_t currPos = file.tellg();
        size_t fileSize;

        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(currPos, std::ios::beg);

        return fileSize;
    }
};

class processor {
private:
    editor m_editor;
public:
    processor(const std::string &path) {
        m_editor = editor(path);
    }

public:
    void execute(const command &m_command) {
        if (!isValid(m_command)) {
            throw std::invalid_argument("Wrong command!");
        }

        if (m_command[0] == "SIZE") {
            std::cout << this->m_editor.size() << " byte(s)" << std::endl;
        } else if (m_command[0] == "EDIT") {
            try {
                this->m_editor.edit(std::stoi(m_command[1]), std::stoi(m_command[2]));
                std::cout << "OK!" << std::endl;
            } catch (std::invalid_argument &exc) {
                std::cout << exc.what() << this->m_editor.size() << "!" << std::endl;
            }
        } else if (m_command[0] == "SHOW") {
            try {
                this->m_editor.display(std::cout, std::stoi(m_command[1]), std::stoi(m_command[2]));

            } catch (std::invalid_argument &exc) {
                std::cout << exc.what() << this->m_editor.size() << "!" << std::endl;
            }
        } else if (m_command[0] == "EXIT") {
            this->m_editor.close();
        }
    }

private:
    bool isValid(const command &command) {
        bool shortCommand = command[0] == "SIZE" || command[0] == "EXIT";
        bool longCommand = command[0] == "EDIT" || command[0] == "SHOW";

        if (!shortCommand && !longCommand) {
            return false;
        }

        if (shortCommand && command.size() != 1) {
            return false;
        }

        if (longCommand && command.size() != 3) {
            return false;
        }

        return true;
    }
};

int main(int argc, char **argv) {
    std::string input;
    command inputCommand;

    // std::cout << inputCommand[0];

    if (argc != 2) {
        std::cout << "Invalid number of parameters" << std::endl;
        return 1;
    }

    try {
        processor m_processor(argv[1]);

        do {
            getline(std::cin, input);
            inputCommand = command(input);
            try {
                m_processor.execute(inputCommand);
            } catch (std::invalid_argument &exc) {
                std::cout << exc.what() << std::endl;
            }
        } while (input != "EXIT");
    } catch (std::runtime_error &exc) {
        std::cout << exc.what() << std::endl;
    }

    return 0;
}