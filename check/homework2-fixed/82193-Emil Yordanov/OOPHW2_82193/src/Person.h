#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<string>
#include<vector>
#include"main.h"
class Vehicle;
class Person : public Object{
    private:
        std::string personName;
        unsigned int personId;
        std::vector<Vehicle*> personVehicles;
    public:
        Person(const std::string name, const unsigned int id);
        ~Person();
        // Method for adding an owned vehicle to the person's vehicle collection. Returns the added vehicle when execution is successfull.
        Vehicle* AddVehicleToPersonCollection(Vehicle* vehicle);
        Vehicle* RemoveVehicleFromPersonCollection(Vehicle* vehicle);
        bool IsOwner();
        std::string ToString();
        bool operator ==(const Person& other) const;
};

#endif
