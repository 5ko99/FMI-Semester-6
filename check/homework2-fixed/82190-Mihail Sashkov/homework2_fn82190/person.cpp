#include"person.h"
#include"vehicle.h"
#include<vector>
#include<iostream>


Person::Person(std::string name, unsigned int id) : name(name), id(id)
{}

Person::Person(const Person& other) {

    name = other.name;
    id = other.id;
    vehicles = other.vehicles;

}

Person& Person::operator =(const Person& other) {

    if(this != &other) {

        name = other.name;
        id = other.id;
        vehicles = other.vehicles;

    }

    return *this;

}

std::string Person::getName() const {
    return name;
}

unsigned int Person::getId() const {
    return id;
}

void Person::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

void Person::releaseVehicle(std::string id) {

    for(int i = 0; i < vehicles.size(); i++) {

        if(vehicles[i]->getRegistration().compare(id) == 0) {
            vehicles.erase(vehicles.begin() + i);
        }
        
    }

}

bool Person::isHeHasNoVehicles() const {
    return vehicles.empty();
}

std::vector<Vehicle*>& Person::getVehicles() {
    return vehicles;
}

void Person::printPerson() const {

    std::cout << "Name: " << name << std::endl;
    std::cout << "ID: " << id << std::endl;

}

void Person::printTheVehicles() const {

    try {

        if(vehicles.empty()) {
            throw "The person with this id has no vehicles!";
        }

        for(int i = 0; i < vehicles.size(); i++) {

            vehicles[i]->printVehicle();
            std::cout << std::endl;

        }

    }
    catch(const char* str) {
        std::cout << str << std::endl;
    }

}
