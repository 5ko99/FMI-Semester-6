#include "Vehicle.h"

Vehicle::Vehicle() {}

Vehicle::Vehicle(const Registration &registration, const std::string &description):
registration(registration), description(description){

}

Vehicle::Vehicle(const Vehicle &other) {
    registration = other.registration;
    description = other.description;
    if (other.owner){
        owner = other.owner;
    }
}

Vehicle &Vehicle::operator=(const Vehicle &other) {
    if (this != &other) {
        registration = other.registration;
        description = other.description;
        if (other.owner) {
            owner = other.owner;
        }
    }
    return *this;
}

Vehicle::~Vehicle() {}

std::string Vehicle::getDescription() {
    return description;
}

void Vehicle::printDescription() const{
    std::cout << description;
}

void Vehicle::clearOwner() {
    owner = nullptr;
}

void Vehicle::setOwner(Person *newOwner) {
    owner = newOwner;
}

Registration Vehicle::getRegistration() const{
    return registration;
}

void Vehicle::printRegistration() const{
    registration.print();
}

bool Vehicle::operator==(const Vehicle &other) {
    if (registration.getRegistration() == other.registration.getRegistration()){
        return true;
    }
    return false;
}

Person* Vehicle::getOwner() const{
    return owner;
}

