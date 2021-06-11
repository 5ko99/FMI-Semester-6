#include "Interpreter.h"

#include <iostream>

int main (int argc, char** argv)
{
    std::string filepath;
    if (argc > 1)
        filepath = argv[1];
    
    Database* db;
    try {
        db = new Database(filepath);
        std::cout << "Database loaded from: " << filepath << std::endl;
    } catch(const std::exception& ex) {
        std::cout << "Error:" << ex.what() << std::endl;
        return 0;
    }
    Interpreter interpreter(*db);
    Interpreter::ShowHelp();
    std::string line;
    while (std::getline(std::cin >> std::ws, line))
    {
        if (line.empty())
            continue;
        try {
            interpreter.Process(line);
        } catch(const std::exception& ex) {
            std::cout << "Error: " << (std::string(ex.what()) == "stoi" ? "Invlaid arguments" : ex.what()) << std::endl;
        }
    }
    return 0;
}
