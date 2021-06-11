#include "../Headers/Person.h"

#include <stdexcept>


Person::Person(const std::string &name, unsigned int id) : name(std::move(name)), id(id) {
}

Person::Person(const Person &object) {
    this->id = object.id;
    this->name = object.name;
    this->vehicles = object.vehicles;
}

unsigned int Person::getId() const {
    return this->id;
}

const std::string &Person::getName() const {
    return this->name;
}

std::vector<Vehicle *> &Person::getVehicles() {
    return this->vehicles;
}


void Person::addVehicle(Vehicle &vehicle) {
    this->vehicles.push_back(&vehicle);
}

void Person::removeVehicle(Vehicle &vehicle) {
    int pos = findVehiclePos(vehicle);

    if (pos == -1) {
        throw std::invalid_argument("Invalid vehicle!");
    }

    this->vehicles.erase(this->vehicles.begin() + pos);
}

int Person::findVehiclePos(const Vehicle &vehicle) const {
    for (int i = 0; i < this->vehicles.size(); ++i) {
        if (this->vehicles[i] == &vehicle) {
            return i;
        }
    }

    return -1;
}

Person &Person::operator=(const Person &object) {
    if (this != &object) {
        this->id = object.id;
        this->name = object.name;
        this->vehicles = object.vehicles;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << "Person with: " << std::endl;
    os << " Name: " << person.name << std::endl;
    os << " Id: " << person.id << std::endl;

    if (person.vehicles.empty()) {
        os << " Vehicles: none" << std::endl;
    }

    for (int i = 0; i < person.vehicles.size(); ++i) {
        os << " Vehicle " << i + 1 << ": " << person.vehicles[i]->getRegistration() << std::endl;
    }

    return os;
}

