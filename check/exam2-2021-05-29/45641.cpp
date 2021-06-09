// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Виктор Николаев Нолев
// ФН: 45641
// Специалност: Информатика
// Курс: 2.
// Административна група: 1.
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Command {
public:
    Command(std::string &input) {
        extract(input);
    }

    std::size_t size() const {
        return m_arguments.size();
    }

    // TODO Do we need to return obj or string
    std::string &operator[](std::size_t pos) {
        return m_arguments[pos];
    }

    const std::string &getCommandText() const {
        return m_command;
    }

private:
    std::string m_command{" "};
    std::vector<std::string> m_arguments{};

    /// Extracts the command and it's arguments (if there are any)
    void extract(std::string &input) {
        std::size_t commandLength = input.length();
        // Keeps the chars of current command/argument
//        std::vector<char> current;
        int nextPos = 0;
        int argumentPos = 0;
        for (int i = 0; i < commandLength; ++i) {
//            current.push_back(input[i]);
            if (input[i] == ' ') {
                if (m_command == " ") {
                    m_command = input.substr(0, i - 1);
                    nextPos = i + 1;
                } else {
                    m_arguments[argumentPos++] = input.substr(nextPos, i - 1);
                }
            }
        }
    }
};


class Preprocessor {
public:

    bool is_valid(const Command &command) {
        // TODO Consider moving commands in enum class or vector
        const std::string commandText = command.getCommandText();
        if (commandText != "EXIT"
            || commandText != "SIZE"
            || commandText != "EDIT"
            || commandText != "SHOW") {
            return false;
        }
        return true;
    }

    void execute(const Command &command) {
        try {

        } catch (std::exception &ex) {

        }
    }
};

class Editor {
public:
    Editor() = default;
    Editor(const std::string &filePath) {
        open(filePath);
        m_fileSize = getFileSize();
    }

    void open(const std::string &filePath) {
        // Open the binary file for I/O
        m_file.open(filePath, std::ios::binary | std::ios::in | std::ios::out);
        if (!m_file) {
            throw std::runtime_error("Cannot open file: " + filePath);
        }
    }

    void close() {
        m_file.close();
    }

    void edit(std::size_t offset, std::uint8_t value) {
        // Move put pointer to the desired position for writing - offset
//        seekp(offset);
        if (m_file.eof()) {
            // Cannot write data in file on position that is outside of the file!
            throw std::invalid_argument("Invalid offset for edit! Position is outside of the file");
        }
        // If there is char* or std::string
        // first we have to write the len of the char*/string
        // then we can write len count of bytes - this will be the text of char*/string
        m_file.write(reinterpret_cast<const char *>(&value), sizeof(value));

    }

    void display(std::ostream &out, std::size_t offset, std::size_t limit) {
        // Move get pointer and read from desired postion - offset
//        seekg(offset);
        if (m_file.eof()) {
            throw std::invalid_argument("Invalid offset for display! Position is outside of the file");
        }

        for (int bytesCount = 0; bytesCount < limit; ++bytesCount) {
            // Keep readed value in variable here
            std::uint8_t value = 0;
            // If there is char* or std::string
            // first we have to read the len of the char*/string
            // then we can read len count of bytes - this will be the text of char*/string
            m_file.read(reinterpret_cast<char*>(&value), sizeof(value));

            // Now put the value that was read in the stream
            // NOTE: Refer to the desired output formatting
            out << value;
            // Does it work as expected in binary files?
            if (m_file.eof()) {
                break;
            }
        }
    }

    // Even without explicitly including destructor for Editor that closes the file
    // The file will be automatically closed by the compiler when Editor obj reach out of scope
private:
    std::fstream m_file{};
    std::size_t m_fileSize{};

    std::size_t getFileSize() const {
        // Make sure that file is opened correctly
        if (!m_file.is_open()) {
            throw std::runtime_error("Cannot get file size - file is not opened correctly!");
        }
        // Move get pointer to the end of the file and return file size
//        return seekg(0, std::ios::end);
    }
};

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Please, enter file path as command line argument!\n";
        return -1; // Not very good practice here :)
    }

    Editor editor;
    try {
        editor.open(argv[1]);
    } catch (std::runtime_error& ex) {
        std::cout << ex.what() << '\n';
    }

    // Input is from file - not from console ofc :)
//    std::string input;
//    std::getline(std::cin, input);

    // Put it in separate function in Preprocessor class for better encapsulation and OOP
//    Command command(input);
//    Preprocessor preprocessor;
//    if (!preprocessor.is_valid(command)) {
//        std::cout << "Command is invalid!\n";
//    }
//
//    preprocessor.execute(command);
    return 0;
}