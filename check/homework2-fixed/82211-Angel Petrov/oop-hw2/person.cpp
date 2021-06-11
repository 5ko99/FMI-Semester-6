#include <iostream>
#include "person.h"
#include "vehicle.h"
// for operator= and copy constr
void Person::copy(const Person& other) {

    name = other.name;
    id = other.id;
    numOwnedVehicles = other.numOwnedVehicles;

    for (size_t i = 0; i < numOwnedVehicles; ++i) {
        ownedVehicles.emplace_back(other.ownedVehicles[i]);
    }
}

Person::Person() {
    
    name = "N/A";
    id = 0;
    numOwnedVehicles = 0;
}

Person::Person(std::string name, unsigned id) {

    this->name = name;
    this->id = id;
    numOwnedVehicles = 0;
}

Person::Person(const Person& other) {

    copy(other);
}

Person Person::operator=(const Person& other) {

    if (this != &other) {
        copy(other);
    }

    return *this;
}

//accesors
unsigned Person::getID() const {

    return id;
}

std::vector<Vehicle*> Person::getVehicles() const{
    
    return ownedVehicles;
}

std::size_t Person::getNumberOfVehiclesOwned() {

    return numOwnedVehicles;
}

// adds a vehicle
void Person::addVehicle(Vehicle& other) {

    ownedVehicles.emplace_back(&other);
    ++numOwnedVehicles;
}

// releases a vehicle
void Person::releaseVehicle(const Registration& licensePlate) {

    for (size_t i = 0; i < numOwnedVehicles; ++i) {
        if(ownedVehicles[i]->getLicensePlate() == licensePlate) {
            ownedVehicles.erase(ownedVehicles.begin() + i);
            --numOwnedVehicles;
            break;
        }
    }
}

// prints all vehicles owned
void Person::printVehicles() {

    for (size_t i = 0; i < numOwnedVehicles; ++i) {
        std::cout << (*ownedVehicles[i]);
    }
}

std::ostream& operator<<(std::ostream& out, const Person& person) {

    out << person.name << ", " << person.id << ";\n";

    return out;
}
