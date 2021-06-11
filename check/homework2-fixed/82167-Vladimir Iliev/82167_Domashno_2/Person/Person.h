#pragma once

#include <string>
#include <vector>

class Vehicle;

class Person {
    const std::string name;
    std::vector<Vehicle*> owned_vehicles;
    const unsigned id;

private:
    bool isLetter(char a);
    size_t findVehicle(const Vehicle& vehicle) const;

public:
    Person() = delete;
    Person(std::string name, unsigned id);
    ~Person();

    void addVehicle(Vehicle& vehicle);
    void removeVehicle(Vehicle& vehicle);

    const std::string& getName() const;
    unsigned getID() const;
    const std::vector<Vehicle*>& getOwnedVehicles() const;

    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};
