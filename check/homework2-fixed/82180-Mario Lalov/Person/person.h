#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
#include "../Vehicle/vehicle.h"

class Vehicle;

class Person
{
    static std::vector<unsigned int> usedId;

private:
    unsigned int id;
    std::string name;
    std::vector<Vehicle *> ownedVehicles;
    unsigned int numberOfVehicles;

public:
    Person(unsigned int in_id, std::string in_name);
    const unsigned int getId() const;
    const std::string getName() const;
    const std::vector<Vehicle *> getOwnedVehicles() const;
    void addVehicle(Vehicle *newVehicle);
    const Vehicle* getVehicleByRegistration(std::string in_registration) const;
    std::size_t getVehicleIndex(std::string in_registration) const;//get index in owned vehicles
    void disownVehicle(std::string in_registration);//remove vehicle from woned vehicles
    friend std::ostream& operator<<(std::ostream & stream, const Person& person);
    ~Person();
};

#endif
