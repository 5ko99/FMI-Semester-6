#include <iostream>
#include "Vehicle.h"

Vehicle::Vehicle(const Registration *registration, const std::string &desc) : registration(*registration) {
    description = desc;
    owner = nullptr;
}

const Registration &Vehicle::getRegistration() const {
    return registration;
}

const std::string &Vehicle::getDescription() const {
    return description;
}

const Person *Vehicle::getOwner() const {
    return owner;
}

void Vehicle::setOwner(Person *value) {
    if(value == nullptr){
        throw std::invalid_argument("Person must be valid!");
    }
    this->owner = value;
}

Vehicle *Vehicle::findById(const std::string &id, std::vector<Vehicle *>* vect) {
    if(vect == nullptr){
        throw std::invalid_argument("Null argument!");
    }

    std::size_t len = vect->size();
    for (int i = 0; i < len; ++i) {
        if ((*vect)[i]->registration.getRegistrationNumber() == id) {
            return (*vect)[i];
        }
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &out, const Vehicle &vhcl) {
    out << "------------\nRegistration: " <<
    vhcl.registration.getRegistrationNumber() << "\n" <<
    "Descrition: " <<
    vhcl.description << std::endl;

    return out;
}

void Vehicle::removeOwner() {
    if (this->owner) {
        this->owner->removeVehicle(this);
        this->owner = nullptr;
    }
}

