#pragma once
#include <iostream>
#include <string>
#include <vector>

class Vehicle;

class Person {

    std::string name;
    unsigned int owner_id;
    std::vector<Vehicle*> owned_cars;

public:

     unsigned int getOwnerID() const;
     std::string getName() const;
     void addVehicle(Vehicle* newVehicle);
     void releaseVehicle(Vehicle* newVehicle);
     void releaseAllOwnedVehicles();
     explicit Person(std::string name,unsigned int id);
     static Person* findPerson(unsigned int id);
     std::size_t ownedVehiclesCount();
     static void removePerson(Person* person);
     const Vehicle* vehicleAt(std::size_t pos) const;

    static std::vector<Person> instancesOfPerson;

    friend class Vehicle;
};


