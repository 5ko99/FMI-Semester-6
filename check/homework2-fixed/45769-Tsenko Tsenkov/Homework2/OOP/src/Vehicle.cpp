#include "../include/Vehicle.hpp"

using std::string;

Vehicle::Vehicle(const string &regNum, string description) : registration{Registration(regNum)}, description{description}, owner{nullptr}
{
}

void Vehicle::setOwner(Person *newOwner)
{
    if (owner != nullptr)
    {
        int vecSize = owner->getCars().size();
        for (int i = 0; i < vecSize; ++i)
        {
            if (owner->getCars()[i] == this)
            {
                owner->getCars().erase(owner->getCars().begin() + i);
                break;
            }
        }
    }
    owner = newOwner;
}

Person *Vehicle::getOwner() const
{
    return owner;
}

std::string Vehicle::getNum() const
{
    return registration.getRegistration();
}

std::string Vehicle::getDescription() const
{
    return description;
}
