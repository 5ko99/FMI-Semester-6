#pragma once

#include <iostream>
#include <string>

class Registration{

    std::string city;
    std::string nomer;
    std::string letters;

    public:

    Registration(std::string reg);
    Registration();

    std::string getcity();
    std::string getnomer();
    std::string getletters();

    std::string& getReg();



};
