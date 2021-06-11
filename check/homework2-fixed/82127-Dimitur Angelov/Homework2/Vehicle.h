#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Person.h"

class Vehicle{

    Registration reg;
    std::string descr;
    Person owner;

    public:

    Vehicle(Registration reg,std::string descr, Person owner);
    Vehicle();

    std::string& getRegVehStr();
    Registration& getRegVeh();
    std::string& getDescr();
    Person& getPerVeh();




};

