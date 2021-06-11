#pragma once
#include <cstring>
#include <iostream>
#include "RegistrationNumber.h"
#include <vector>
#include "Person.h"
class Person;
class Registration;
class Vehicle

{
    Registration* reg;
    std::string descr;
    Person* owner = nullptr;
public:
    Vehicle(const Registration& reg, const std::string& description);
    void addPerson(Person& owner);
    void RemovePerson();
    Registration& GetReg();
    Person* GetPerson();
    std::string Getdescr();
};
