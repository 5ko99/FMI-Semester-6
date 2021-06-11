#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Verify.hpp"

class Registration
{
private:
    std::string registration;

public:
    Registration(std::string reg);
    std::string getReg() const; 
};



#endif
