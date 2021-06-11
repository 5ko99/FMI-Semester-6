#include <iostream>
#include "Person.h"
#include "Vehicle.h"

const std::string &Person::getName() const {
    return name;
}

unsigned int Person::getID() const {
    return ID;
}

const std::vector<Vehicle*>& Person::getOwnedVehicles() const {
    return ownedVehicles;
}

void Person::addVehicleOwnership(Vehicle* vehicle) {
    //validating the choice of the vehicle and if it is incorrect - throws an exception
    if(!vehicle) {
        throw std::invalid_argument("No valid vehicle has been chosen!");
    }

    //sets the vector with the owned vehicles
    if(vehicle->getOwner()) {
        ownedVehicles.push_back(vehicle);
        vehicle->setOwnership(this);
    } else {
        ownedVehicles.push_back(vehicle);
        vehicle->setOwnership(this);
    }
}

void Person::removeVehicleOwnership(Vehicle* vehicle) {
    //validating the choice of the vehicle and if it is incorrect - throws an exception
    if(!vehicle) {
        throw std::invalid_argument("No valid vehicle has been chosen!");
    }
    
    for (std::size_t i = 0; i < ownedVehicles.size(); i++) {
        if (ownedVehicles[i] == vehicle) {
            //if the vehicle has been detected,
            ownedVehicles[i]->setOwnership(nullptr); //the vehicle is not owned by anyone anymore - ownership set to nullptr
            ownedVehicles.erase(ownedVehicles.begin()+i); //the vehicle is erased from the list of owned vehicles
        }
    }
}

std::ostream& operator<<(std::ostream &out, const Person &person) {
    out<<"Person: "<<person.ID<<", Name: "<<person.name<<", Owned vehicles: "<<person.ownedVehicles.size()<<std::endl;

    if(person.ownedVehicles.size() > 0) {
        for(std::size_t i = 0; i < person.ownedVehicles.size(); i++) {
            out<<person.ownedVehicles.at(i)->getDescription()<<std::endl;
        }
    }

    return out;
}
