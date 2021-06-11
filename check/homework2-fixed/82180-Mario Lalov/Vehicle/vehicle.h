#ifndef VEHICLE_H
#define VEHICLE_H
#include "../Person/person.h"
#include <vector>

class Person;

class Vehicle
{
    static std::vector<std::string> usedRegistrations;

private:
    std::string registration;
    std::string description;
    Person *owner;

public:
    Vehicle(std::string in_registration, std::string in_description);
    const std::string getRegistration() const;
    const std::string getDescription() const;
    Person *getOwner() const;
    void setOwner(Person *in_owner);
    bool checkIfOwned() const;
    void removeOwner();//set owner as nullptr
    friend std::ostream &operator<<(std::ostream &stream, const Vehicle &vehicle);
    ~Vehicle();
};

//helpers
bool validateRegistration(std::string input);

#endif
