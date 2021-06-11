#include "Headers/CommandParser.h"

#include <fstream>

int main(int argc, char **argv) {
    CommandParser commandParser;
    std::string temp;

    if (argc == 2) {
        std::ifstream isFile(argv[1]);

        if (isFile.is_open()) {
            while (getline(isFile, temp)) {
                commandParser.parseCommand(temp);
            }
            isFile.close();
        } else {
            std::cout << "File couldn't open!" << std::endl;
        }
    }

    do {
        getline(std::cin, temp);
        commandParser.parseCommand(temp);
    } while (temp != "end");

    return 0;
}
