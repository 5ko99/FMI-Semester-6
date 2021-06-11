#ifndef VEHICLE_H
#define VEHICLE_H

#include "Registration.hpp"

//class Person; //as it is more effective to store the owners id, as a way to find the owner, this declaration is not needed anymore
// class Organizer;

class Vehicle : public Registration
{
private:
    std::string description;
    unsigned int ownerId = 0; 
    
public:
    Vehicle(Registration registration, std::string description); 
    Vehicle(std::string registration, std::string description);
    Vehicle(const Vehicle& other);

    void addOwner(unsigned int owner);
    void removeOwner();

    std::string getDescription() const;
    unsigned int getOwnerId() const; //can be used to find the owner; better than passing a pointer, as this way the class stays encapsulated
};


#endif
