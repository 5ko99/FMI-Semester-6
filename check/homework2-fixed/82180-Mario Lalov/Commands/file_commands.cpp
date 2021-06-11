#include "file_commands.h"
#include <iostream>

bool isNumber(std::string input) //checks if string is number
{
    //check for each char
    for (int i = 0; i < input.size(); i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }

    return true;
}

int getType(std::string input) //finds what the input type is
{
    if (validateRegistration(input))
    {
        return VEHICLE;
    }
    else if (isNumber(input))
    {
        return PERSON;
    }
    else if (input == "VEHICLES")
    {
        return VEHICLES_COM;
    }
    else if (input == "PEOPLE")
    {
        return PEOPLE_COM;
    }
    else
    {
        throw std::invalid_argument("Invalid argument");
    }
}

void toUpper(std::string &input) //make whole string to upper
{
    for (std::size_t i = 0; i < input.length(); i++)
    {
        input[i] = std::toupper(input[i]);
    }
}

std::size_t getPersonIndex(unsigned int id, std::vector<Person *> &list)
{
    for (std::size_t i = 0; i < list.size(); i++)
    {
        if (id == list[i]->getId())
        {
            return i;
        }
    }

    throw std::invalid_argument("No such person");
}

std::size_t getVehicleIndex(std::string registration, std::vector<Vehicle *> &list)
{
    for (std::size_t i = 0; i < list.size(); i++)
    {
        if (registration == list[i]->getRegistration())
        {
            return i;
        }
    }

    throw std::invalid_argument("No such vehicle");
}

void FileCommands::createVehicle(std::vector<Vehicle *> &list, std::string registration, std::string description)
{
    Vehicle *newVehicle = new Vehicle(registration, description);

    list.push_back(newVehicle);
}

void FileCommands::createPerson(std::vector<Person *> &list, std::string name, unsigned int id)
{
    Person *newPerson = new Person(id, name);

    list.push_back(newPerson);
}

void FileCommands::acquire(std::string owner_id, std::string vehicle_id, std::vector<Person *> &peopleList, std::vector<Vehicle *> &vehicleList)
{
    //find vehicle and person
    std::size_t p_index = getPersonIndex(std::stoi(owner_id), peopleList);
    std::size_t v_index = getVehicleIndex(vehicle_id, vehicleList);

    //release if owned
    if (vehicleList[v_index]->checkIfOwned())
    {
        release(std::to_string(vehicleList[v_index]->getOwner()->getId()), vehicleList[v_index]->getRegistration(), peopleList);
    }

    //acquire
    peopleList[p_index]->addVehicle(vehicleList[v_index]);
}

void FileCommands::release(std::string owner_id, std::string vehicle_id, std::vector<Person *> &peopleList)
{
    //find person
    std::size_t index = getPersonIndex(std::stoi(owner_id), peopleList);

    //remove vehicle
    peopleList[index]->disownVehicle(vehicle_id);
}

void FileCommands::remove(std::string input, std::vector<Vehicle *> &vehicleList, std::vector<Person *> &peopleList)
{
    //get type of input
    if (getType(input) & VEHICLE)
    {
        //find vehicle
        std::size_t index = getVehicleIndex(input, vehicleList);

        //disown if vehicle has owner
        if (vehicleList[index]->getOwner())
        {
            char symbl;
            std::cout << "Are you sure you want to remove this vehicle (Y/N):";
            std::cin >> symbl;

            if (symbl == 'y' || symbl == 'Y')
            {
                //remove vehicle from owner
                vehicleList[index]->getOwner()->disownVehicle(input);
            }
            else //terminate process
            {
                return;
            }
        }

        //delete the dynamically allocated vehicle
        delete vehicleList[index];

        vehicleList.erase(vehicleList.begin() + index);
    }
    else
    {
        //find person
        std::size_t index = getPersonIndex(std::stoi(input), peopleList);

        //disown all owned vehicles
        for (std::size_t i = 0; i < peopleList[index]->getOwnedVehicles().size(); i++)
        {
            peopleList[index]->getOwnedVehicles()[i]->removeOwner();
        }

        //delete the dynamically allocated person
        delete peopleList[index];

        peopleList.erase(peopleList.begin() + index);
    }
}

void FileCommands::save(std::string input, DataContainer &data)
{
    //write info in file
    data.write(input);
}

void FileCommands::show(std::string input, DataContainer &data)
{
    //output depending on type
    if (getType(input) & VEHICLES_COM)
    {
        data.printVehicles();
    }
    else if (getType(input) & PEOPLE_COM)
    {
        data.printPeople();
    }
    else if (getType(input) & PERSON)
    {
        std::size_t index = getPersonIndex(std::stoi(input), data.peopleList);
        std::cout << *data.peopleList[index] << std::endl;
    }
    else
    {
        std::size_t index = getVehicleIndex(input, data.vehiclesList);
        std::cout << *data.vehiclesList[index] << std::endl;
    }
}

void FileCommands::initiateCommand(std::string fullCommand, DataContainer &data)
{
    std::string command;
    std::string param;
    std::vector<std::string> params;

    std::size_t endPos;
    std::size_t startPos;

    //get command
    endPos = fullCommand.find(' ');
    command = fullCommand.substr(0, endPos);

    //make command in upper case
    toUpper(command);

    //get parameters
    while (endPos < fullCommand.length())
    {
        while (fullCommand[endPos + 1] == ' ')
        {
            endPos++;
        }

        startPos = endPos + 1;

        if (fullCommand[startPos] == '"')
        {
            startPos += 1;
            endPos = fullCommand.find('"', startPos);

            param = fullCommand.substr(startPos, endPos - startPos);

            endPos++;
        }
        else
        {
            endPos = fullCommand.find(' ', startPos);

            param = fullCommand.substr(startPos, endPos - startPos);
        }

        params.push_back(param);
    }

    //initiate command
    if (command == "PERSON")
    {
        if (params.size() != 2)
        {
            throw std::invalid_argument("Invalid parameters for PERSON!");
        }

        createPerson(data.peopleList, params[0], std::stoi(params[1]));
    }
    else if (command == "VEHICLE")
    {
        if (params.size() != 2)
        {
            throw std::invalid_argument("Invalid parameters for VEHICLE!");
        }

        createVehicle(data.vehiclesList, params[0], params[1]);
    }
    else if (command == "ACQUIRE")
    {
        if (params.size() != 2)
        {
            throw std::invalid_argument("Invalid parameters for ACQUIRE!");
        }

        acquire(params[0], params[1], data.peopleList, data.vehiclesList);
    }
    else if (command == "RELEASE")
    {
        if (params.size() != 2)
        {
            throw std::invalid_argument("Invalid parameters for RELEASE!");
        }

        release(params[0], params[1], data.peopleList);
    }
    else if (command == "REMOVE")
    {
        if (params.size() != 1)
        {
            throw std::invalid_argument("Invalid parameters for REMOVE!");
        }

        remove(params[0], data.vehiclesList, data.peopleList);
    }
    else if (command == "SAVE")
    {
        if (params.size() != 1)
        {
            throw std::invalid_argument("Invalid parameters for SAVE!");
        }

        save(params[0], data);
    }
    else if (command == "SHOW")
    {
        if (params.size() != 1)
        {
            throw std::invalid_argument("Invalid parameters for SHOW!");
        }

        show(params[0], data);
    }
    else
    {
        throw std::invalid_argument("Invalid command");
    }
}
