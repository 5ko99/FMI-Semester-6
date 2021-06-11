#include <iostream>
#include "Vehicle/vehicle.h"
#include "Person/person.h"
#include "Commands/file_commands.h"
#include "DataContainer/data_container.h"

int main(int argc, char* argv[])
{

    if(argc > 2)
    {
        std::cout << "Invalid input!";
        return 0;
    }


    bool end = false;
    DataContainer data;

    //get info from file
    try
    {
        data.read(argv[1]);
    }
    catch(const std::invalid_argument& err)
    {
        std::cout << err.what() << std::endl;
    }

    std::string command;

    while (true)
    {
        std::cout << "Comannds: PERSON, VEHICLE, ACQUIRE, RELEASE, REMOVE, SAVE, SHOW, END" << std::endl
                  << std::endl
                  << "------------------------------------------------" << std::endl;

        //get command
        try
        {
            std::cout << "Enter command: ";
            std::getline(std::cin, command);

            if (command == "END")
            {
                return 0;
            }

            //initiate command
            FileCommands::initiateCommand(command, data);
        }
        catch (const std::invalid_argument &err)
        {
            std::cout << err.what() << std::endl;
        }

        command.clear();
    }
}
