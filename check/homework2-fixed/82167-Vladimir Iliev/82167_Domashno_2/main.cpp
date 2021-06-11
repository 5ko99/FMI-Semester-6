#include <iostream>

#include "Commands.h"

int main(int argc, char* argv[])
{
    Container storage;

    if (argc == 2) {
        try {
            storage.loadFromFile(argv[1]);
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << '\n';
        }
    } else if (argc > 2) {
        std::cerr << "Program started with too many arguments.\n";
        return 2;
    }

    bool exit = false;
    while (!exit) {
        std::cout << "Enter command:\n";
        std::string str;
        std::getline(std::cin, str, '\n');

        try {
            Command cmd(str.c_str());
            exit = cmd.execute(storage);
            std::cout << "\nCommand executed successfully\n";
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << '\n';
        } catch (std::out_of_range& e) {
            std::cerr << e.what() << std::endl;
        } catch (std::bad_alloc& e) {
            std::cerr << e.what() << std::endl;
            return 2;
        }
    }

    return 0;
}
