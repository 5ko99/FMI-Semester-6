#include <iostream>
#include <fstream>
#include <string>
#include "CommandProcessor.h"

bool fileIsEmpty(std::string fileName) {
    std::ifstream ifs(fileName, std::ios::ate);

    if (ifs.tellg() == 0)
    {
        return true;
    }

    return false;
}

bool is_file_exist(const char* fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

int main()
{
    std::string fileName;
    std::cout << "Hi, enter file name to start exploring!\n";
    std::cout << "File name: ";
    std::cin >> fileName;

    CommandProcessor commandProcessor = CommandProcessor();
    std::fstream myfile;
    myfile.open(fileName);
    std::string str_obj(fileName);
    char* fileNameArr = &str_obj[0];

    if (is_file_exist(fileNameArr) && !fileIsEmpty(fileName))
    {
        std::string line;
        while (std::getline(myfile, line)) 
        {
            commandProcessor.ProcessCommand(line, true);
        }

        std::cout << "Here is the content in the current database: \n";
        std::cout << "People: \n";
        std::cout << commandProcessor.ProcessCommand("SHOW PEOPLE", false) << std::endl;
        std::cout << "Vehicles \n";
        std::cout << commandProcessor.ProcessCommand("SHOW VEHICLES", false)  << std::endl;

        std::cout << "If you'd like we can create more or do some changes?\n";
        std::cout << "Press H for more information. \n";
    }
    else 
    {
        std::cout << "The database is empty. \n";
        std::cout << "Let's create some content! \n";
        std::cout << "Press H for more information. \n";
    }

    char input[100];
    std::cin.ignore(100, '\n');
    std::cin.getline(input, sizeof(input));

    while (input != "exit") 
    {
        try
        {
            std::cout << commandProcessor.ProcessCommand(input, true);
        }
        catch (const std::exception& ex) 
        {
            std::cerr << "Error occurred: " << ex.what() << std::endl;
        }

        std::cin.ignore(100, '\n');
        std::cin.getline(input, sizeof(input));
    }

    myfile.close();
    commandProcessor.~CommandProcessor();
}
