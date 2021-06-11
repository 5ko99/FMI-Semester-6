#include "Person.hpp"

Person::Person(std::string name, unsigned int id)
{
    this->name = name;
    this->id = id;
}

std::string Person::getName() const
{
    return name;
}

unsigned Person::getId() const
{
    return id;
}

std::size_t Person::numberOfVehicles() const
{
    return vehicles.size();
}

Vehicle* Person::getVehicle(std::size_t pos) const
{
    if(pos<vehicles.size())
    {
        return vehicles[pos];
    }
    else
    {
        throw std::out_of_range("Out of range");
    }
}

bool Person::addVehicle(Vehicle& veh) 
{
    Vehicle* temp = new Vehicle(veh);   //allocating a copy of the vehicle on the heap
    vehicles.push_back(temp);
    if(vehicles.back()->getReg() == veh.getReg())
    {
        temp = nullptr;
        return true;
    }
    else
    {
        delete temp;
        temp = nullptr;
        return false;
    }
}

bool Person::releaseVehicle(Registration registration)
{
    for(std::size_t i = 0; i<vehicles.size(); ++i)
    {
        if(vehicles[i]->getReg() == registration.getReg())
        {
            delete vehicles[i];
            vehicles[i] = nullptr;
            vehicles.erase(vehicles.begin()+i);
            return true; 
        }
    }
    return false;
}

Person::~Person()
{
    for(std::size_t i = 0; i < vehicles.size(); ++i)
    {
        delete vehicles[i];
        vehicles[i] = nullptr;
        std::cout<<"DESTR PERSON\n";
    }
}

Person::Person(const Person& other)
{
    name = other.getName();
    id = other.getId();
    vehicles = other.vehicles;
}
