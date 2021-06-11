#pragma once

#include "registration.h"

class Person;

class Vehicle
{
    private:
    Registration uniqueRegistration; 
    std::string description; 
    int ownerID; 

    void copy(const Vehicle& other);

    public:
    Vehicle(const Registration reg, const std::string descr);
    Vehicle(const Registration reg, const std::string descr, unsigned ownerID);
    Vehicle(const Vehicle& other);

    Registration getRegistration() const; 
    std::string getDescription() const; 
    int getOwnerID() const; 
    bool isThereAnOwner() const; 

    void insertOwner(const Person& person); 
    void eraseOwner();  

    Vehicle& operator=(const Vehicle& vehicle); 

    ~Vehicle(); 
};
