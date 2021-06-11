#pragma once 

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

class Registration
{
    private:
    std::string registration; 

    void copy(const Registration& other); 

    public:
    Registration();
    Registration(std::string reg);
    Registration(const Registration& other); 

    static bool validation(std::string reg); 
    size_t getSize() const; 
    std::string getString() const; 

    Registration& operator=(const Registration& other);

    ~Registration(); 
};
