#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
#include <iostream>
class Vehicle;
class Person
{
    friend Vehicle;
    std::string name;
    unsigned int id;
    std::vector<Vehicle*> vehiclesOwned;
public:
    Person(const char* name, unsigned int id);
    void acquire(Vehicle* newVehicle);
    void release(Vehicle* toBeRemoved);
    void releaseAll();
    unsigned int getId() const;
    const char* getName() const;
    std::size_t numberOfVehiclesOwned() const;
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};


#endif
