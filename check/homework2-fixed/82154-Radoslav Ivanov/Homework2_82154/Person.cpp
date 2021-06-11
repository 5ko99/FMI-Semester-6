#include "Person.h"
#include <iostream>
using std::size_t;

Person::Person (const std::string& name, const unsigned int id) : name(name), id (id) {}

Person::Person (const Person& other)
{
    copyFrom(other);
}

Person& Person::operator=(const Person& other)
{
    if (this != &other){
        copyFrom(other);
    }
    return *this;
}

void Person::copyFrom (const Person& other)
{
    this->name = other.name;
    this->id = other.id;
    for (size_t i=0; i<other.vehicles.size(); ++i){
        this->vehicles.push_back(other.vehicles[i]);
    }
}

unsigned Person::getId() const { return id; }

std::string Person::getName() const { return name; }

size_t Person::getCountOfVehs () const { return vehicles.size(); }

//Validation of pos is not necessary for the use of the method in this program
Vehicle* Person::getOwnedVehicle(unsigned pos)
{
    return vehicles[pos];
}

void Person::addVehicle(Vehicle& newVehicle)
{
    if (findVehicle(newVehicle.getRegistration()) != vehicles.size()){
        throw std::logic_error("This person already owns this vehicle!");
    }
    vehicles.push_back(&newVehicle);
} 

void Person::releaseVehicle (const Registration& reg)
{
    size_t index = findVehicle(reg);
    if (index == vehicles.size()){
        throw std::invalid_argument("This person does not own this vehicle!"); 
    }
    vehicles.erase(vehicles.begin() + index);
}

void Person::releaseVehicleWithoutCheck(const Registration& reg) 
{
    size_t index = findVehicle(reg);
    vehicles.erase(vehicles.begin() + index);
}

void Person::releaseAllVehicles()
{
    for (size_t i=0; i<vehicles.size(); ++i){
        vehicles[i]->releaseOwnerWithoutCheck();
    }
    vehicles.clear();
}

bool Person::hasAnyVehicles() const
{
    return (vehicles.size());
}

void Person::printInfo () const
{
    std::cout << "#Name: " << name << std::endl;
    std::cout << "#ID: " << id << std::endl;
    std::cout << "#Owned vehicles: " << std::endl;
    size_t i=0; 
    for (i; i<vehicles.size(); ++i){
        std::cout << i+1 << ") " << vehicles[i]->getRegistration() << " - "
                  << vehicles[i]->getDescript() << std::endl;  
    }
    if (i == 0){
        std::cout << "*No vehicles to be shown!*" << std::endl;
    }
}

//returns the position of the vehicle with registration = reg
//if there is no such vehicle returns vehicles.size()
size_t Person::findVehicle(const Registration& reg)
{
    for (size_t i=0; i<vehicles.size(); ++i){
        if (vehicles[i]->getRegistration() == reg){
            return i;
        }
    }
    return vehicles.size();
}
