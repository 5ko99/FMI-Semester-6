#include "Commands.h"

#include <iostream>
#include <fstream>

int main()
{
    Commands startup;
    std::cout << "Do you want to continue your progress from a file? (y/n): ";
    char key;
    std::cin >> key;
    bool answer;
    key == 'Y' || key == 'y' ? answer = true : answer = false;

    std::cin.ignore();

    if(answer) {

        std::string fileName;
        std::cout << "Enter the name of the file: ";
        getline(std::cin, fileName);

        bool canContinue = true;
        std::ifstream progress {fileName};
        if(!progress) {
            std::cout << fileName << " could not be opened!\n";
            canContinue = false;
        }

        if(canContinue) {
            while(progress) {
                std::getline(progress, startup.command);
                std::getline(progress, startup.argument1);
                std::getline(progress, startup.argument2);

                startup.CommandCentre();
            }

            std::cout << "Progress loaded!\n";
        }
    }

    std::cout << "To exit the program - enter EXIT as a command.\n";

    while(true) {
        std::cout << "Enter command: ";
        getline(std::cin, startup.command);
        std::cout << "Enter argument 1(if needed, if not leave it empty): ";
        getline(std::cin, startup.argument1);
        std::cout << "Enter argument 2(if needed, if not leave it empty): ";
        getline(std::cin, startup.argument2);

        startup.CommandCentre();

        if(startup.exit)
            break;
    }
}
