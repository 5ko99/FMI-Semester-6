#ifndef Person_H
#define Person_H

#include "Person.hpp"

Person::Person()
{
}

Person::Person(const Person &other) : name{other.name}, identificationNumber{other.identificationNumber}
{

    for (Vehicle *curr : other.cars)
    {
        this->cars.push_back(curr);
    }
}

Person::~Person()
{
    for (auto curr : cars)
    {
        delete curr;
    }
}

Person &Person::operator=(const Person &other)
{
    if (this != &other)
    {
        this->name = other.name;
        this->identificationNumber = other.identificationNumber;

        for (Vehicle *curr : other.cars)
        {
            this->cars.push_back(curr);
        }
    }
}

void Person::addVehicle(const Vehicle *newVehicle)
{
    if (newVehicle != nullptr)
    {
        cars.push_back(newVehicle);
    }
}

void Person::releaseVehicle(const std::string &numberPlate)
{
    for (auto curr : cars)
    {
        if (curr.getNumberPlate().compare(numberPlate) == 0)
        {
            curr.removeOwner();
            cars.erase(curr);
        }
    }
}

bool Person::hasCars() const
{
    return !this->cars.empty();
}

void releaseAllVehicles()
{
    for (curr : cars)
    {
        curr->removeOwner();
        delete current;
    }

    while (!cars.empty())
    {
        cars.pop_back();
    }
}

void Person::serialize(std::ofstream file)
{
    std::string result = "PERSON " + name + " " + identificationNumber + "\n";
    file << result;

    for (auto curr : cars)
    {
        result = "ACQUIRE " + this->identificationNumber + " " + curr->getNumberPlate + "\n";

        file << result;
    }
}

#endif
