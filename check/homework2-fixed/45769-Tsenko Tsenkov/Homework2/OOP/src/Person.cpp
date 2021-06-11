#include "../include/Vehicle.hpp"

using std::string;

Person::Person(std::string Name, unsigned int Id) : Name{Name}, Id{validateId(Id)}
{
}

unsigned int Person::validateId(unsigned int id)
{
    return checkUniqueness(id);
}

void Person::addCar(Vehicle *vehicle)
{
    if (vehicle != nullptr)
    {
        vehicle->setOwner(this);
        vehicles.push_back(vehicle);
    }
    else
    {
        throw std::runtime_error("Null pointer passed for vehicle");
    }
}

std::vector<Vehicle *> Person::getCars()
{
    return vehicles;
}

std::vector<Vehicle *> Person::getCarsRead() const
{
    return vehicles;
}

unsigned int Person::getId() const
{
    return Id;
}

std::string Person::getName() const
{
    return Name;
}

bool Person::operator == (const Person& other)
{
    return (other.getId() == Id);
}
