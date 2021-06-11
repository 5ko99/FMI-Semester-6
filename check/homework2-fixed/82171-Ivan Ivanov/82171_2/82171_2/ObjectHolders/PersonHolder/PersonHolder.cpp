#include "PersonHolder.h"
#include "../VehicleHolder/VehicleHolder.h"
#include <iostream>

PersonHolder::PersonHolder() {
    ;
}

PersonHolder* PersonHolder::operator*() {
    return this;
}

std::size_t PersonHolder::getIndexByID(unsigned int id) {
    for(std::size_t i = 0; i < this->people.size(); ++i) {
        if (id == this->people.at(i).getID()) {
            return i;
        }
    }
    throw PersonException("Could not find a person with the given ID.");
}

const std::vector<Person> PersonHolder::getAllPeople() const {
    return this->people;
}

void PersonHolder::add(Person person) {
    for(std::size_t i = 0; i < this->people.size(); ++i) {
        if (person.getID() == this->people.at(i).getID()) {
            throw PersonException("Person with this ID already added.");
        }
    }
    this->people.push_back(person);
}

void PersonHolder::removeByID(unsigned int id) {
    this->people.erase(people.begin() + getIndexByID(id));
}

Person* PersonHolder::getByID(unsigned int id) {
    return *(this->people.at(getIndexByID(id)));
}

void PersonHolder::printPersonsVehiclesAt(std::size_t index) {
    VehiclePtr* ownedVehicles = this->people.at(index).getVehicles();

    for (std::size_t i = 0; i < this->people.at(index).getVehiclesCount(); ++i) {
        std::cout << "Vehicle " << i + 1 << ":\n" << *ownedVehicles[i] << "\n";
        std::cout << std::endl;
    }

    delete[] ownedVehicles;
}

void PersonHolder::printPersonAt(std::size_t i) {
    std::cout << this->people.at(i);
    std::cout << std::endl;
}

void PersonHolder::printAll() {
    std::cout << "People:\n";

    for(std::size_t i = 0; i < people.size(); ++i) {
        std::cout << "Person " << i + 1 << ":\n";
        this->printPersonAt(i);
    }

}

void PersonHolder::printDetailed(unsigned int id) {
    std::size_t indexPerson = getIndexByID(id);
    this->printPersonAt(indexPerson);
    this->printPersonsVehiclesAt(indexPerson);
}
