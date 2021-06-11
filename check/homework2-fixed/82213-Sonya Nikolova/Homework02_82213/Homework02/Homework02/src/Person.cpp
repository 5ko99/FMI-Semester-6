#include "Person.h"

Person::Person(const std::string &name, const unsigned int id)

{
    this->name = name;
    this->id = id;
}

Person::Person(const Person &other)
{
    this->name = other.name;
    this->id = other.id;
    this->vehicles = other.vehicles;
}

bool Person::operator==(const Person &other) const
{
    return this->id == other.id;
}

Person &Person::operator=(const Person &other)
{
    this->name = other.name;
    this->id = other.id;
    this->vehicles = other.vehicles;

    return *this;
}

std::string Person::getName() const
{
    return this->name;
}

unsigned int Person::getId() const
{
    return this->id;
}

int Person::cntOfVehicles() const
{
    return this->vehicles.size();
}

void Person::addVehicle(Vehicle *vehicle)
{
    //validate that same vehicle is not already owned by person
    const int cntVehicles = this->vehicles.size();
    for (int i = 0; i < cntVehicles; i++)
    {
        if (this->vehicles[i]->getRegistration() == vehicle->getRegistration())
        {
            throw std::invalid_argument("This vehicle is already owned by the person");
        }
    }

    this->vehicles.push_back(vehicle);
}

void Person::removeVehicle(Vehicle *vehicle)
{
    //validate that vehicle is owned by person
    const size_t size = this->vehicles.size();

    for (int i = 0; i < size; i++)
    {
        if (this->vehicles[i]->getRegistration() == vehicle->getRegistration())
        {
            this->vehicles[i] = nullptr;
            this->vehicles.erase(this->vehicles.begin() + i);
            return;
        }
    }
    throw std::invalid_argument("Vehicle is not owned by person");
}

void Person::removeAllVehicles()
{
    const size_t size = this->vehicles.size();

    for (int i = 0; i < size; i++)
    {
        this->vehicles[i] = nullptr;
    }
    this->vehicles.clear();
}

void Person::printOwnedVehicles(std::ostream &stream) const
{
    int cntOfVehicles = this->cntOfVehicles();

    for (int i = 0; i < cntOfVehicles; i++)
    {
        std::cout << " " << this->vehicles[i]->getRegistration().getNumber() << " ";
    }
}
