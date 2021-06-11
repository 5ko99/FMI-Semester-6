#pragma once

#include <string>
#include <vector>

class Vehicle;

class Person
{
public:
    Person(std::string Name, unsigned int Id);
    void addCar(Vehicle *vehicle);

    std::vector<Vehicle *> getCarsRead() const;
    unsigned int getId() const;
    std::string getName() const;

    bool operator == (const Person& other);

private:
    const std::string Name;
    const unsigned int Id;
    std::vector<Vehicle *> vehicles;
    unsigned int validateId(unsigned int id);
    std::vector<Vehicle *> getCars();

    friend class Vehicle;
};
