#include "Person.h"
#include "Vehicle.h"
#include <stdexcept>

bool Person::isLetter(char a)
{
    return ('a' <= a && a <= 'z') ||
           ('A' <= a && a <= 'Z') ||
           (a == ' ');
}

Person::Person(std::string name, unsigned int id)
        : name(std::move(name)), id(id)
{
    size_t len = this->name.length();
    for (size_t i = 0; i < len; ++i)
        if (!isLetter(this->name[i]))
            throw std::invalid_argument("Person: invalid name");
}

void Person::addVehicle(Vehicle& vehicle)
{
    vehicle.setOwner(*this); // Checks if vehicle is already owned.
    try {
        owned_vehicles.push_back(&vehicle);
    } catch (std::exception&) {
        vehicle.removeOwner();
        throw std::invalid_argument("Vehicle not added, error occurred.");
    }
}

size_t Person::findVehicle(const Vehicle& vehicle) const
{
    size_t size = owned_vehicles.size();
    for (size_t i = 0; i < size; ++i)
        if (owned_vehicles[i]->getRegistration() == vehicle.getRegistration())
            return i;
    throw std::invalid_argument("Vehicle not found");
}

void Person::removeVehicle(Vehicle& vehicle)
{
    size_t vehicle_idx = findVehicle(vehicle); //If not found exception is thrown
    vehicle.removeOwner();
    owned_vehicles[vehicle_idx] = owned_vehicles.back();
    owned_vehicles.pop_back();
}

unsigned Person::getID() const
{ return id; }

std::ostream& operator<<(std::ostream& os, const Person& person)
{
    size_t size = person.owned_vehicles.size();
    os << "--------------------------\n"
       << "Name: " << person.name << '\n'
       << "ID: " << person.id << '\n'
       << "Vehicles: ";
    if (size == 0)
        os << "No vehicles owned." << '\n';
    else {
        for (size_t i = 0; i < size; ++i)
            os << '\n' << i << ":\nRegistration: " << person.owned_vehicles[i]->getRegistration() << '\n'
               << "Description: " << person.owned_vehicles[i]->getDescription();
    }
    os << "\n--------------------------";
    return os;
}

const std::string& Person::getName() const
{ return name; }

Person::~Person()
{
    size_t size = owned_vehicles.size();
    for (size_t i = 0; i < size; ++i)
        owned_vehicles[i]->removeOwner();
}

const std::vector<Vehicle*>& Person::getOwnedVehicles() const
{
    return owned_vehicles;
}
