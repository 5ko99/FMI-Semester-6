
#include "RegistrationNumber.h"
#include <iostream>


#include "Vehicle.h"
#include "Person.h"

Vehicle::Vehicle(const Registration& reg,const  std::string& description) {
    this->descr = description;
    this->reg = new Registration;
    this->reg[0] = reg;
}

void Vehicle::addPerson(Person &owner) {
    this->owner = &owner;
}

void Vehicle::RemovePerson() {
    this->owner = nullptr;
}

Registration &Vehicle::GetReg()  {
    return this->reg[0];
}

Person *Vehicle::GetPerson() {
    return this->owner;
}

std::string Vehicle::Getdescr() {
    return this->descr;
}

