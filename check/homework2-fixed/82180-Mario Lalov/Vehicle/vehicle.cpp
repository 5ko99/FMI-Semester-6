#include "vehicle.h"
#include <iostream>
#include <algorithm>

std::vector<std::string> Vehicle::usedRegistrations;

bool validateRegistration(std::string input)
{
    if (input.length() == 7)
    {
        bool checkLetters = input[0] >= 'A' && input[0] <= 'Z' && input[5] >= 'A' && input[5] <= 'Z' &&
                            input[6] >= 'A' && input[6] <= 'Z';
        bool checkDigits = isdigit(input[1]) && isdigit(input[2]) && isdigit(input[3]) && isdigit(input[4]);

        return checkLetters && checkDigits;
    }
    else if (input.length() == 8)
    {
        bool checkLetters = input[0] >= 'A' && input[0] <= 'Z' && input[1] >= 'A' && input[1] <= 'Z' &&
                            input[6] >= 'A' && input[6] <= 'Z' && input[7] >= 'A' && input[7] <= 'Z';
        bool checkDigits = isdigit(input[2]) && isdigit(input[3]) && isdigit(input[4]) && isdigit(input[5]);

        return checkLetters && checkDigits;
    }
    else
    {
        return false;
    }
}

Vehicle::Vehicle(std::string in_registration, std::string in_description)
{
    //check if registration is valid
    if (!validateRegistration(in_registration))
    {
        throw std::invalid_argument("Invalid registration");
    }

    //check if registration is used
    if (std::find(usedRegistrations.begin(), usedRegistrations.end(), in_registration) != usedRegistrations.end())
    {
        throw std::invalid_argument("Invalid registration");
    }

    //assign new values
    registration = in_registration;
    description = in_description;
    owner = nullptr;

    //mark that registration is used
    usedRegistrations.push_back(in_registration);
}

const std::string Vehicle::getRegistration() const
{
    return registration;
}

const std::string Vehicle::getDescription() const
{
    return description;
}

Person *Vehicle::getOwner() const
{
    return owner;
}

void Vehicle::setOwner(Person *in_owner)
{
    owner = in_owner;
}

bool Vehicle::checkIfOwned() const
{
    return owner;
}

void Vehicle::removeOwner()
{
    owner = nullptr;
}

std::ostream &operator<<(std::ostream &stream, const Vehicle &vehicle)
{
    stream << "Registration: " << vehicle.registration << std::endl;
    stream << "Description: " << vehicle.description << std::endl;
    stream << "Owned by: " << std::endl;
    
    //output owner if such exists
    if (vehicle.owner)
    {
        stream << "Id: " << vehicle.owner->getId() << std::endl;
        stream << "Name: " << vehicle.owner->getName() << std::endl;
    }

    return stream;
}

Vehicle::~Vehicle()
{
    //remove vehicle from used list
    usedRegistrations.erase(std::find(usedRegistrations.begin(), usedRegistrations.end(), registration));
}
