#include <iostream>
#include "Person.h"
#include "Vehicle.h"

Person::Person(const std::string &name, unsigned int id) : name(name) {
    setId(id);
}

void Person::addVehicle(Vehicle *vhcl) {

    if(!vhcl){
        throw std::invalid_argument("Vehicle can't be nullptr!");
    }

    if (vhcl->getOwner()) {
        if (vhcl->getOwner()->id != this->id) {
            vehicles.push_back(vhcl);
            vhcl->setOwner(this);
        }
    } else {
        vehicles.push_back(vhcl);
        vhcl->setOwner(this);
    }

}

const std::string &Person::getName() const {
    return name;
}

const std::vector<Vehicle *> &Person::getVehicles() const {
    return vehicles;
}

void Person::printCars() {
    int size = this->vehicles.size();

    for (int i = 0; i < size; ++i) {
        std::cout << (*vehicles[i]);
    }
}

void Person::removeVehicle(Vehicle *vehicle) {

    if(vehicle == nullptr){
        throw std::invalid_argument("Vehicle is not valid!");
    }

    int len = vehicles.size();

    for (int i = 0; i < len; ++i) {
        if (this->vehicles[i] == vehicle) {
            this->vehicles[i]->setOwner(nullptr);
            this->vehicles.erase(this->vehicles.begin() + i);
        }
    }

}

bool Person::idExists(unsigned int id, std::vector<Person *> *vect) {
    if(vect == nullptr){
        throw std::invalid_argument("Vector must be not null!");
    }

    int len = vect->size();

    for (int i = 0; i < len; ++i) {
        if ((*vect)[i]->id == id) { return true; }
    }

    return false;
}

std::ostream &operator<<(std::ostream &out, const Person &person) {

    if(&person == nullptr){
        throw std::invalid_argument("Vector can't be nullptr!");
    }

    std::size_t len = person.vehicles.size();
    out << "------------\nId: " << person.id << " \nName: " << person.name << "\nCars: " << person.vehicles.size();

    return out;
}

Person *Person::findById(unsigned int id, std::vector<Person *> *vect) {
    if(!vect){
        throw std::invalid_argument("Vector can't be nullptr!");
    }

    std::size_t len = vect->size();
    for (int i = 0; i < len; ++i) {
        if ((*vect)[i]->id == id) { return (*vect)[i]; }
    }

    return nullptr;
}

unsigned int Person::getId() const {
    return id;
}

void Person::setId(unsigned int id) {
    if (id < 0) {
        throw std::invalid_argument("Id can't be lower than 0!");
    } else {
        this->id = id;
    }
}

bool Person::operator==(const Person &rhs) const {
    return id == rhs.id;
}

bool Person::operator!=(const Person &rhs) const {
    return !(rhs == *this);
}


