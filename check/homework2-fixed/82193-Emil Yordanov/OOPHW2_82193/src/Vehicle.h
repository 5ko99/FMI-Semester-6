#ifndef VEHICLE_H
#define VEHICLE_H

#include<string>
#include<iostream>
#include<regex>
#include"main.h"
class Person;
class Vehicle : public Object{
    private:
        std::string vehicleRegistration;
        std::string vehicleDescription;
        Person* vehicleOwner;
    public:
        Vehicle(const std::string registration, const std::string description, Person* owner);
        Vehicle(const std::string registration, const std::string description);
        ~Vehicle();
        Person* SetOwner(Person* newOwner);
        Person* RemoveOwner();
        std::string ToString();
        bool operator ==(const Vehicle& other) const;
};

#endif
