#include <iostream>
#include "Commands.h"
#include <fstream>
int main(int argc, char *argv[]) {
    Commands commandPanel;
    std::string command;
    if (argc == 2) {
        std::ifstream file(argv[1]);
        if (file.is_open()) {
            while (getline(file, command)) {
                commandPanel.Command(command);
            }
            file.close();
        } else {
            std::cout << "Cannot open the file";
        }
    }
    while (true){
        std::cout << "please enter a command" << std::endl;
        std::getline(std::cin, command);
        if (command == "close") break;
        try {
            commandPanel.Command(command);
        } catch (std::exception &exception) {
            std::cout << "exception occures with text " << exception.what() << std::endl;
        }

    }

    return 0;
}
