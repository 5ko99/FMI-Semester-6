#include <string>
#include <functional>
#include <iostream>

#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"

    Vehicle::Vehicle()
    {
        registration = nullptr;
        description = "";
    }

    Vehicle::Vehicle(Registration* reg, const std::string descript)
    {
        this->registration = reg;
        this->description = descript;
    }

    Vehicle::Vehicle(const Vehicle& vehicle)
    {
        registration = vehicle.registration;
        description = vehicle.description;
        owner = vehicle.owner;
    }

    Vehicle& Vehicle::operator=(const Vehicle& source)
    {
        if(this == &source)
        {
            return *this;
        }

        registration = source.registration;
        description = source.description;
        owner = source.owner;


        return *this;
    }

    void Vehicle::addOwner(Person &person)
    {
        if(owner.empty())
        {
            owner.push_back(person);

            person.addCar(*this);
        }
        else
        {
            std::cout << "It already has an owner!" << std::endl;
        }

    }

    const std::string Vehicle::getRegistration() const
    {
        return registration->getNumber();
    }

    const std::string Vehicle::getDescription() const
    {
        return description;
    }

    void Vehicle::releaseOwner(Person &person)
    {
        if(!owner.empty())
        {
            person.releaseCar(getRegistration());
            owner.pop_back();
        }
        else
        {
            std::cout << "The car has no owner!" << std::endl;
        }

    }

    bool Vehicle::hasOwner()
    {
        return !owner.empty();
    }

    const unsigned int Vehicle::getOwnerId()
    {
        Person p = owner.front().get();
        return p.getId();
    }

    Vehicle::~Vehicle()
    {

    }
