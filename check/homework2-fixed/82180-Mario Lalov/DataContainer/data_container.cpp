#include "data_container.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cassert>
#include "../Commands/file_commands.h"

void DataContainer::write(std::string path) const
{
    //open file for writing
    std::ofstream stream(path);

    if (!stream.is_open())
    {
        throw std::invalid_argument("File problem occured");
    }

    //set type of data and size
    char tag = 'p';
    stream << tag << std::endl;
    stream << peopleList.size() << std::endl;

    //write people list
    for (std::size_t i = 0; i < peopleList.size(); i++)
    {
        stream << peopleList[i]->getId() << std::endl;
        stream << peopleList[i]->getName() << std::endl;
    }

    //set type of data and size
    tag = 'v';
    stream << tag << std::endl;
    stream << vehiclesList.size() << std::endl;

    //write vehicle list
    for (std::size_t i = 0; i < vehiclesList.size(); i++)
    {
        stream << vehiclesList[i]->getRegistration() << std::endl;
        stream << vehiclesList[i]->getDescription() << std::endl;

        //set owner id as 0 if vehicle isn't owned
        if (vehiclesList[i]->getOwner())
        {
            stream << vehiclesList[i]->getOwner()->getId() << std::endl;
        }
        else
        {
            stream << 0 << std::endl;
        }
    }

    //close file
    stream.close();
}

void DataContainer::read(std::string path)
{
    //open file for reading
    std::ifstream stream(path);

    if (!stream.is_open())
    {
        throw std::invalid_argument("File problem occured");
    }

    std::string tag;
    std::string size;
    std::size_t p_size;
    std::size_t v_size;

    //get type tag
    std::getline(stream, tag);
    assert(tag == "p");

    //get size
    std::getline(stream, size);
    p_size = std::stoi(size);

    std::string name;
    std::string id;

    //get people
    for (std::size_t i = 0; i < p_size; i++)
    {
        std::getline(stream, id);
        std::getline(stream, name);

        Person *person = new Person(std::stoi(id), name);
        peopleList.push_back(person);
    }

    //get type tag
    std::getline(stream, tag);
    assert(tag == "v");

    //get size
    std::getline(stream, size);
    v_size = std::stoi(size);

    std::string registration;
    std::string description;
    unsigned int owner_id;

    //get vehicles
    for (std::size_t i = 0; i < v_size; i++)
    {
        std::getline(stream, registration);
        std::getline(stream, description);
        std::getline(stream, id);
        owner_id = std::stoi(id);

        Vehicle *vehicle = new Vehicle(registration, description);
        vehiclesList.push_back(vehicle);

        //set owner if vehicle is owned
        if (owner_id != 0)
        {
            peopleList[getPersonIndex(owner_id, peopleList)]->addVehicle(vehicle);
        }
    }

    stream.close();
}

void DataContainer::printVehicles() const
{
    for (std::size_t i = 0; i < vehiclesList.size(); i++)
    {
        std::cout << "Vehicle " << i + 1 << ":" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << *vehiclesList[i] << std::endl;
    }
}

void DataContainer::printPeople() const
{
    for (std::size_t i = 0; i < peopleList.size(); i++)
    {
        std::cout << "Person " << i + 1 << ":" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << *peopleList[i] << std::endl;
    }
}

DataContainer::~DataContainer()
{
    //delete all dynamicly created objects
    for (std::size_t i = 0; i < peopleList.size(); i++)
    {
        delete peopleList[i];
    }

    for (std::size_t i = 0; i < vehiclesList.size(); i++)
    {
        delete vehiclesList[i];
    }
}
