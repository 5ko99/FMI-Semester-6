#include"vehicle.h"
#include"registration.h"
#include"person.h"
#include<iostream>



Vehicle::Vehicle(const Registration& id, std::string description) : id(id), description(description)
{}

std::string Vehicle::getDescription() const {
    return description;
}

std::string Vehicle::getRegistration() const {
    return id.getRegistration();
}

Person* Vehicle::getPerson() {

    if(person == nullptr) {
        throw "This vehicle has no owner!";
    }

    return person; 
}

void Vehicle::addPerson(Person* owner) {
    person = owner;
}

void Vehicle::releaseOwner() {
    person = nullptr;
}

bool Vehicle::isItHasNoOwner() const {
    return (person == nullptr);
}

void Vehicle::printVehicle() const {

    std::cout << "Registration of the vehicle: " << id.getRegistration() << std::endl;
    std::cout << "Description of the vehicle: " << description << std::endl;

    if(person == nullptr) {
        std::cout << "Owner - No" << std::endl;
        return;
    }

    std::cout<< "Owner - Yes" << std::endl;

}
