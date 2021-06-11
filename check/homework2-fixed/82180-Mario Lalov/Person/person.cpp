#include "person.h"
#include <iostream>
#include <algorithm>

std::vector<unsigned int> Person::usedId;

Person::Person(unsigned int in_id, std::string in_name)
{
    //check if id is 0
    if(in_id == 0)
    {
        throw std::invalid_argument("Invalid id");
    }

    //check if id is used
    if (std::find(usedId.begin(), usedId.end(), in_id) != usedId.end())
    {
        throw std::invalid_argument("Invalid id");
    }

    //assign values
    id = in_id;
    name = in_name;
    numberOfVehicles = 0;

    //mark id as used
    usedId.push_back(id);
}

const unsigned int Person::getId() const
{
    return id;
}

const std::string Person::getName() const
{
    return name;
}

const std::vector<Vehicle *> Person::getOwnedVehicles() const
{
    return ownedVehicles;
}

void Person::addVehicle(Vehicle *newVehicle)
{
    if (newVehicle->checkIfOwned())
    {
        throw std::invalid_argument("Vehicle already owned!");
    }

    //set vehicle owner
    newVehicle->setOwner(this);

    //add vehicle to owned list
    ownedVehicles.push_back(newVehicle);

    numberOfVehicles++;
}

const Vehicle *Person::getVehicleByRegistration(std::string in_registration) const
{
    for (int i = 0; i < numberOfVehicles; i++)
    {
        if (ownedVehicles[i]->getRegistration() == in_registration)
        {
            return ownedVehicles[i];
        }
    }

    throw std::invalid_argument("No such vehicle!");
}

std::size_t Person::getVehicleIndex(std::string in_registration) const
{
    for (std::size_t i = 0; i < numberOfVehicles; i++)
    {
        if (ownedVehicles[i]->getRegistration() == in_registration)
        {
            return i;
        }
    }

    throw std::invalid_argument("No such vehicle!");
}

void Person::disownVehicle(std::string in_registration)
{
    std::size_t index = getVehicleIndex(in_registration);

    //remove owner form vehicle 
    ownedVehicles[index]->removeOwner();
    //remove from list
    ownedVehicles.erase(ownedVehicles.begin() + index);
}

std::ostream &operator<<(std::ostream &stream, const Person &person)
{
    stream << "Id: " << person.id << std::endl;
    stream << "Name: " << person.name << std::endl;

    return stream;
}

Person::~Person()
{
    //remove person form used list
    usedId.erase(std::find(usedId.begin(), usedId.end(), id));
}
