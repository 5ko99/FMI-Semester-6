#include "Person.h"
#include "Vehicle.h"

std::vector<Person> Person::instancesOfPerson = {};


unsigned int Person::getOwnerID() const
{
    return owner_id;
}

std::string Person::getName() const
{
    return name;
}

std::size_t Person::ownedVehiclesCount()
{
    return owned_cars.size();
}

void Person::addVehicle(Vehicle* newVehicle)
{
    if(newVehicle)
    {
        newVehicle->setOwner(this);
    }
}

void Person::releaseVehicle(Vehicle* newVehicle)
{
    if(newVehicle)
    {
        newVehicle->setOwner(nullptr);
    }
}


Person::Person(std::string name,unsigned int id)
: name(std::move(name)),owner_id(id)
{}

Person* Person::findPerson(unsigned int id)
{
    std::size_t size = instancesOfPerson.size();
    for(std::size_t i = 0;i < size;++i)
    {
        if(id == instancesOfPerson[i].getOwnerID())
        {
            return &instancesOfPerson[i];
        }
    }
    return nullptr;
}

void Person::removePerson(Person* person)
{
    std::size_t size = instancesOfPerson.size();
    for(std::size_t i = 0;i < size;++i)
    {
        if(person->getOwnerID() == instancesOfPerson[i].getOwnerID())
        {
           instancesOfPerson[i] = instancesOfPerson[size-1];
           instancesOfPerson.pop_back();
           break;
        }
    }
}

void Person::releaseAllOwnedVehicles()
{
    std::size_t size = owned_cars.size();
    for(std::size_t i = 0;i < size;++i)
    {
        this->releaseVehicle(owned_cars[i]);
    }
}

const Vehicle* Person::vehicleAt(std::size_t pos) const
{
    if(pos < owned_cars.size())
    {
        return owned_cars[pos];
    }
    return nullptr;
}
