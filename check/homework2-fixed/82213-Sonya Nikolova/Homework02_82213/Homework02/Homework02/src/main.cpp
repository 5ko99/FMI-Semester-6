#include <iostream>
#include <fstream>
#include <string>

#include "Registration.h"
#include "Person.h"
#include "Database.h"
#include "Commands.h"

int main(int argc, char **argv)
{
    const std::string USAGE_MSG = "Usage: ./Homework02 <database file>";
    if (argc > 2)
    {
        std::cerr << USAGE_MSG << "\n";
        return 1;
    }

    DataBase database;
    CommandProcessor cmdProcessor(database);

    if (argc == 2)
    {
        const std::string &inFileName = argv[1];
        std::ifstream inFile(inFileName);
        if (!inFile.is_open())
        {
            std::cerr << "Couldn't open file " << inFileName << "\n";
        }
        else
        {
            cmdProcessor.loadDataBase(inFile, &std::cerr);
        }
    }

    // Interactive mode
    cmdProcessor.printMenu(std::cout);
    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            cmdProcessor.printMenu(std::cout);
            cmdProcessor.processCommand(line);
            std::cout << "Command OK\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Command FAILED: " << e.what() << '\n';
        }
    }
    
    return 0;
}
