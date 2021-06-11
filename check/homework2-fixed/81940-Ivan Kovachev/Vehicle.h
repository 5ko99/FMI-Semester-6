#pragma once
#include "Registration.h"
#include "Person.h"

class Vehicle
{
private:
    Registration reg;
    std::string description;
    unsigned int personId ;
public:
    Vehicle(Registration reg, std::string descrtiption);


    void setOwner(unsigned int persId);

    Registration& getReg() ;
    unsigned int getPersonId() ;
    std::string getDescription() ;
    friend std::ostream& operator<<(std::ostream& out, const Vehicle& arg);

    void setPersonId(const unsigned int personId);

    /// Person <-> Vehicle relationship Vehicle shte byde shefa

};
