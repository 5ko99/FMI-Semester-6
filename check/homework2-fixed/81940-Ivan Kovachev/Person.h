#pragma once
#include <iostream>
#include "Registration.h"
#include <vector>

//class Vehicle;

class Person
{
    std::string name;
    unsigned int id;
    std::vector<Registration> carRegs;
public:
    Person();
    Person(std::string name, unsigned int id);

    void setOwnedVehicles();
    void p_addVehicle( Registration& newReg );

    std::string getName();
    std::vector<Registration>& getCarRegs();
    unsigned int getId();

    void setName(const std::string name);
    void setId(const unsigned int id);

    friend std::ostream& operator<<(std::ostream os,  Person& arg);
};
