#ifndef PERSON
#define PERSON

#include <string>
#include <vector>
#include "Vehicle.hpp"
#include <algorithm>

class Vehicle;

class Person
{
    std::string name;
    unsigned int id;

    std::vector<Vehicle*> vehicles;

    friend std::ostream& operator<<(std::ostream& out, Person const& p);

public:

    Person(std::string name,  unsigned int id);

    const Vehicle& addVehicle(Vehicle* v);

    void removeVehicle(Vehicle* const v);

    void removeVehicle(const Registration& r);

    const std::string getName() const;

    unsigned int getId() const;

    void printVehicles() const;

    void clear();

    size_t getVehiclesCount() const;

    bool has(Registration& v) const;

};

#endif
