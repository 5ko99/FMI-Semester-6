#pragma once

#include "Vehicle.h"
#include "Person.h"

class Container {
    std::vector<Vehicle*> vehicleContainer;
    std::vector<Person*> personContainer;

public:
    Container() = default;
    ~Container();

    size_t findVehicle(const Vehicle& vehicle) const;
    size_t findVehicle(const char* registration) const;
    size_t findPerson(const Person& person) const;
    size_t findPerson(unsigned id) const;

    void addVehicle(const std::string& registration, const std::string& description);
    void removeVehicle(Vehicle* vehicle);
    void removeVehicle(const char* registration);

    void addPerson(const std::string& name, unsigned id);
    void removePerson(Person* person);
    void removePerson(unsigned id);

    Vehicle& getVehicle(size_t idx);
    const Vehicle& getVehicle(size_t idx) const;
    Person& getPerson(size_t idx);
    const Person& getPerson(size_t idx) const;

    void printVehicles() const;
    void printPeople() const;
    void saveToFile(const std::string& path);
    void loadFromFile(const char* path);
};
