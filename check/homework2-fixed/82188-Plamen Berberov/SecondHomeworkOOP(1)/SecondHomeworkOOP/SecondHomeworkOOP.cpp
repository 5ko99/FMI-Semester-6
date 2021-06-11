// SecondHomeworkOOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "CommandHelper.h"
#include "Person.h"

void splitString(const std::string& str, const char delim,
    std::vector<std::string>& out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

int main(int argc, char** argv)
{
    std::fstream file;
    if (argc > 1)
    {
        try 
        {
            file.open(argv[1], std::ios::in | std::ios::out);
        }
        catch (...)
        {
            std::cerr << "File could not be opened! Terminating program!";
            return -1;
        }

        if (file.is_open())
        {
            while (file.good())
            {
                std::string buffer;
                std::getline(file, buffer);
                std::vector<std::string> args;
                splitString(buffer, ' ', args);

                std::string command = args[0];
                args.erase(args.begin());

                try
                {
                    CommandHelper::executeCommand(command, args);
                }
                catch (...)
                {
                    std::cerr << "Something went wrong with the execution of the command! Try again!" << std::endl;
                }
            }
        }
    }

    std::string buffer;
    while (true)
    {
        std::getline( std::cin, buffer);
        std::vector<std::string> args;
        splitString(buffer, ' ', args);

        std::string command = args[0];
        args.erase(args.begin());

        try 
        {
            CommandHelper::executeCommand(command, args);
        }
        catch (...)
        {
            break;
            std::cerr << "Something went wrong with the execution of the command!" << std::endl;
        }
    }

    CommandHelper::deallocateMemory();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
