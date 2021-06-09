//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Румен Георгиев Азманов
// ФН: 82176
// Специалност: Компютърни науки
// Курс: Първи 1
// Административна група: Трета 3
// Ден, в който се явявате на контролното: 29.05.2021г.
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

enum CommandType {
    EXIT = 0,
    SIZE = 1,
    EDIT = 2,
    SHOW = 3
};

class command {
   private:
    std::string commandLine;
    std::string commandName;
    std::string commandArg1;
    std::string commandArg2;
    std::size_t sizeOfArguments;

   public:
    command(const char* commandInput) {
        commandName.assign(" ");
        commandArg1.assign(" ");
        commandArg2.assign(" ");

        commandLine.assign(commandInput);
        int copyindex = 0;
        int pasteindex = 0;
        while (copyindex < commandLine.size() && commandLine.at(copyindex) != ' ') {
            commandName.push_back(commandLine.at(copyindex));
            ++copyindex;
        }
        ++copyindex;
        while (copyindex < commandLine.size() && commandLine.at(copyindex) != ' ') {
            commandArg1.push_back(commandLine.at(copyindex));
            ++copyindex;
        }
        ++copyindex;
        while (copyindex < commandLine.size() && commandLine.at(copyindex) != ' ') {
            commandArg2.push_back(commandLine.at(copyindex));
            ++copyindex;
        }
        commandName.push_back('\0');
        commandArg1.push_back('\0');
        commandArg2.push_back('\0');
    }

    std::size_t size() {
        sizeOfArguments = 0;
        if (std::strcmp(commandName.c_str(), " ") != 0) {
            ++sizeOfArguments;
            if (std::strcmp(commandArg1.c_str(), " ") != 0) {
                ++sizeOfArguments;
            }
            if (std::strcmp(commandArg2.c_str(), " ") != 0) {
                ++sizeOfArguments;
            }
        }
        return sizeOfArguments;
    }

    std::string operator[](std::size_t index) {
        switch (index) {
            case 0:
                return commandName;
                break;
            case 1:
                return commandArg1;
                break;
            case 2:
                return commandArg2;
                break;
            default:
                break;
        }
        return "";
    }
};

class editor {
   private:
    std::size_t filesize;
    std::fstream myfile;
    std::size_t sizeoffile;

   public:
    editor(const char* filepath) {
        open(filepath);
    }

    void open(const char* filepath) {
        myfile.open(filepath, std::ios::in | std::ios::out | std::ios::binary);
        if (!myfile) {
            throw std::invalid_argument("Invalid file");
        }
    }

    void close() {
        myfile.close();
    }

    std::size_t size() {
        myfile.seekg(myfile.end);
        return myfile.tellg();
    }

    void edit(std::size_t offset, std::uint8_t value) {
        if (offset > filesize) {
            throw std::invalid_argument("Invalid argument");
        }

        myfile.seekp(offset, myfile.beg);
        myfile.write((char*)&value, sizeof(uint8_t));

        std::cout << "ОК" << '\n';
    }

    void display(std::ostream& out, std::size_t offset, std::size_t limit) {
        if (offset > filesize) {
            throw std::invalid_argument("Invalid argument");
        }
        uint8_t reader;
        while (!myfile.eof() || myfile.tellg() < limit) {
            myfile.read((char*)&reader, sizeof(uint8_t));
        }
        out << reader;
    }

    ~editor() {
        myfile.close();
    }
};

class processor {
   private:
   public:
    bool is_valid(command commandType) {
        if (commandTypeDetermine(commandType) < 0 || commandTypeDetermine(commandType) > 3) {
            return false;
        }
        for (int i = 0; i < commandType[1].size(); ++i) {
            if (commandType[1].at(i) < '0' || commandType[1].at(i) > '9') {
                return false;
            }
        }
        for (int i = 0; i < commandType[2].size(); ++i) {
            if (commandType[2].at(i) < '0' || commandType[2].at(i) > '9') {
                return false;
            }
        }
    }

    int commandTypeDetermine(command mycommand) {
        int type = -1;
        if (std::strcmp(mycommand[0].c_str(), " EXIT") == 0) type = EXIT;
        if (std::strcmp(mycommand[0].c_str(), " SIZE") == 0) type = SIZE;
        if (std::strcmp(mycommand[0].c_str(), " EDIT") == 0) type = EDIT;
        if (std::strcmp(mycommand[0].c_str(), " SHOW") == 0) type = SHOW;
        return type;
    }

    int execute(command mycommand, editor& myeditor) {
        int type = commandTypeDetermine(mycommand);
        try {
            switch (type) {
                case EXIT:
                    return -1;
                    break;
                case SIZE:
                    std::cout << myeditor.size();
                    break;
                case EDIT:
                    // std::size_t offset = 0;
                    // for (int i = 0; i < mycommand[1].size(); ++i) {
                    //     offset *= 10;
                    //     offset += mycommand[1].at(i) - '0';
                    // }
                    myeditor.edit(std::atoi(mycommand[1].c_str()), std::atoi(mycommand[2].c_str()));
                    break;
                case SHOW:
                    myeditor.display(std::cout, std::atoi(mycommand[1].c_str()), std::atoi(mycommand[2].c_str()));
                    break;
                default:
                    break;
            }
        } catch (std::invalid_argument& e) {
            std::cout << e.what();
        }

        return 0;
    }
};

int main(int argv, char* argc[]) {
    editor my_editor(argc[1]);
    processor myprocessor;

    std::string commandinput;
    char commandinput2[30];
    int exit = 0;
    while (exit == 0) {
        std::cout << '>';
        std::cin >> commandinput2;
        commandinput.assign(commandinput2);
        command mycommand(commandinput.c_str());
        exit = myprocessor.execute(mycommand, my_editor);
    }

    return 0;
}