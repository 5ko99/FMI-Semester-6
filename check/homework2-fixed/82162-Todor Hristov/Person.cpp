#include "Person.h"

Person::Person() {}

Person::Person(const std::string &name, unsigned int id):name(name), id(id) {

}

Person::Person(const Person &other) {
    name = other.name;
    id = other.id;
    for (int i = 0; i < other.vehicles.size(); ++i) {
        vehicles.push_back(other.vehicles.at(i));
    }
}

Person &Person::operator=(const Person &other) {
    if (this != &other){
        name = other.name;
        id = other.id;
        for (int i = 0; i < other.vehicles.size(); ++i) {
            vehicles.push_back(other.vehicles.at(i));
        }
    }
    return *this;
}

Person::~Person() {}

void Person::AddVehicle(Vehicle &vehicle) {
    bool IsThereSuchVehicle = false;
    for (int i = 0; i < vehicles.size(); ++i) {
        if(vehicles.at(i) == vehicle){
            IsThereSuchVehicle = true;
        }
    }
    if (!IsThereSuchVehicle){
        vehicles.push_back(vehicle);
        vehicle.setOwner(this);
    } else {
        throw std::invalid_argument("there is existing vehicle with this registration");
    }
}

void Person::RemoveVehicle(Vehicle &vehicle) {
    bool IsThereSuchVehicle = false;
    for (int i = 0; i < vehicles.size(); ++i) {
        if(vehicles.at(i) == vehicle){
            vehicles.erase(vehicles.begin()+i);
            vehicle.clearOwner();
            IsThereSuchVehicle = true;
        }
    }
    if (!IsThereSuchVehicle){
        throw std::invalid_argument("there is existing vehicle with this registration");
    }
}

bool Person::operator==(const Person &other) {
    if(id == other.id){
        return true;
    }
    return false;
}

unsigned int Person::getId() const {
    return id;
}

void Person::RemoveAllVehicles() {
    for (int i = vehicles.size(); i >= 0; i--){
        RemoveVehicle(vehicles[i]);
    }
}

void Person::Print() const {
    std::cout << name << " " << id << std::endl;
}

void Person::PrintAllVehicles() const {
    for (int i = 0; i < vehicles.size(); ++i) {
        vehicles[i].printRegistration();
        std::cout << " ";
        vehicles[i].printDescription();
        std::cout << std::endl;
    }
}

std::string Person::getName() const {
    return name;
}
