#include "..\Headers\Person.hpp"

std::vector<unsigned int> Person::identifiers;

//! Person constructor
Person::Person(std::string namePersonInput, unsigned int identifierPersonInput) {
    bool appear = false;
    for (int i = 0; i < identifiers.size(); ++i) {
        if (identifiers[i] == identifierPersonInput) {
            appear = true;
            throw std::invalid_argument("[!] Person with the same identifier already exists!\n");
            break;
        }
    }

    if (appear == false) {
        namePerson.assign(namePersonInput);
        identifierPerson = identifierPersonInput;
        identifiers.push_back(identifierPerson);
    }
}

std::string Person::getName() {
    return namePerson;
}

unsigned int Person::getIdentifier() {
    return identifierPerson;
}

std::vector<Vehicle *> Person::getOwnedVehicles() {
    return ownedVehicles;
}

void Person::acquireVehicleToPerson(Vehicle *vehicle) {
    ownedVehicles.push_back(vehicle);
}

void Person::releaseVehicle(const char regNumberInput[9]) {
    for (size_t l = 0; l < ownedVehicles.size(); ++l) {
        if (std::strcmp(ownedVehicles.at(l)->getRegistration().getRegistration(), regNumberInput) == 0) {
            ownedVehicles.erase(ownedVehicles.begin() + l);
            break;
        }
    }
}

void Person::emptyVehicle() {
    ownedVehicles.clear();
}

//! Person destructor
Person::~Person() {
}
