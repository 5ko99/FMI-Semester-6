//
// Created by Yani Drenchev on 6.05.21.
//
#include "../Headers/Person.h"

Person::Person(const std::string &name, const unsigned int id) : name(name), id(id) {
}

unsigned int Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

std::vector<Registration> Person::getVehicles() const {
    return vehicles;
}

bool Person::operator==(const Person &oth) const {
    return id == oth.id;
}

bool Person::addVehicle(const Registration &reg) {
    for (auto & vehicle : vehicles) {
        if (vehicle == reg){
            std::cout << "Duplicated car this person owns this car \n";
            return false;
        }
    }
    try {
        vehicles.push_back(reg);
        return true;
    }catch (std::bad_alloc &exx){
        std::cout << "Not enough space";
        return false;
    }
}

void Person::print() const {
    std::cout << "Printing person \n";
    std::cout << "id: " << id << "\n";
    std::cout << "Name: " << name << "\n";
}

bool Person::removeVehicle(const Registration &reg) {
    for (int i = 0; i < vehicles.size(); ++i) {
        if (vehicles[i] == reg){
            vehicles.erase(vehicles.begin() + i);
            return true;
        }
    }
    return false;
}
