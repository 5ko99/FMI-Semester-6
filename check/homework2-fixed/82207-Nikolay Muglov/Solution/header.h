#include <vector>
#include <string>
#include "Registration.h"
class Vehicle;
class Person
{
    std::string m_name;
    unsigned int m_id;
    std::vector<Vehicle *> m_vehicles;

public:
    Person(std::string name, unsigned int id);
    unsigned int getID() const;
    std::string getName();
    void addVehicle(const Vehicle &v);
    void removeVehicle(const Vehicle &v);
    std::size_t cntVehicles() const;
    Vehicle &operator[](std::size_t pos) const;
};
class Vehicle
{
    Registration m_reg;
    std::string m_description;
    Person *m_owner;

public:
    Vehicle(Registration reg, std::string description);
    Registration registration() const;
    std::string description() const;
    void setOwner(Person *owner);
    Person &owner() const;
};
