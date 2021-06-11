#ifndef Person_H
#define Person_H

#include <iostream>
#include <string>
#include <vector>
#include "../Vehicle/Vehicle.hpp"

class Person
{

public:
    Person();
    Person(const Person &);
    ~Person();

    Person &operator=(const Person &);

    void addVehicle(const Vehicle *);
    void releaseVehicle(const std::string &);

    int getPersonName(const std::string &) const;
    void setPersonName(const std::string &);

    int getIdentificationNumber() const;
    int getCarsNameOwns() const;
    void setIdentificationNumber(const unsigned int &);
    bool hasCars() const;
    void releaseAllVehicles();
    void serialize(std::ofstream);

private:
    std::string name;
    int identificationNumber;
    //static unsigned int numberOfPeopleCreated;
    std::vector<Vehicle *> cars;
};

#include "Person.cpp"
#endif
