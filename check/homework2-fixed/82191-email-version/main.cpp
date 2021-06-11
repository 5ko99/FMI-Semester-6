#include "Interpreter.h"

#include <iostream>

int main (int argc, char** argv)
{
    Database db;
    if (argc > 1)
    {
        std::string filepath;
        filepath = argv[1];

        try {
            db = Database(filepath);
            std::cout << "Database loaded from: " << filepath << std::endl;
        }
        catch (const std::exception& ex) {
            std::cout << "Error:" << ex.what() << std::endl;
        }
    } else
        std::cout << "Using an empty database." << std::endl;
    
    Interpreter interpreter(db);
    Interpreter::ShowHelp();
    std::string line;
    while (std::getline(std::cin, line))
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
