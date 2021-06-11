#include <iostream>
#include "Person.h"

std::vector<Person*> Person::people;

Person::Person(std::string newName, unsigned int newId)
{
    unsigned int vehiclesSize = people.size();
    for (size_t i = 0; i < vehiclesSize; i++)
    {
        if (people[i]->getId() == newId) {
            std::cout << "A person with id " << newId << " already exists" << std::endl;
            return;
        }
    }
    name = newName;
    id = newId;
    people.push_back(this);
}

Person::Person()
{
    
}

unsigned int Person::getId()
{
    return id;
}

Person& Person::operator=(const Person& other)
{
    if (this != &other) {
        copy(other);
    }
    return *this;
}

Person::~Person()
{
}

std::vector<Vehicle*> Person::getVehiclesOwned()
{
    return vehiclesOwned;
}

Person* Person::getPersonById(int id)
{
    unsigned int peopleSize = people.size();
    for (size_t i = 0; i < peopleSize; i++)
    {
        if (people[i]->id == id){
            return people[i];
        }
    }
    return nullptr;
}

std::string Person::getName()
{
    return name;
}

void Person::copy(const Person& other)
{
    name = other.name;
    id = other.id;
    vehiclesOwned = other.vehiclesOwned;
}

void Person::removePerson(int id)
{
    unsigned int peopleSize = people.size();
    for (size_t i = 0; i < peopleSize; i++) {
        if (people[i]->id == id) {
            people.erase(people.begin() + i);
        }
    }
}



void Person::removeOwnedVehicle(unsigned int index)
{
        vehiclesOwned.erase(vehiclesOwned.begin() + index);
}

void Person::addVehicle(Vehicle *other)
{
    vehiclesOwned.push_back(other);
}

