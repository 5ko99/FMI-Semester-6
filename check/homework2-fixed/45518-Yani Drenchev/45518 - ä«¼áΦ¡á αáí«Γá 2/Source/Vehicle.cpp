//
// Created by Yani Drenchev on 6.05.21.
//

#include "../Headers/Vehicle.h"

Vehicle::Vehicle(const std::string &reg, const std::string &desc) :description(desc) {
   registration = reg;
   person = 0;
}

Registration Vehicle::getRegistration() const {
    return registration;
}

unsigned int Vehicle::getPerson() const {
    return person;
}

void Vehicle::print() const {
    std::cout << "Vehicle reg number: " << registration.getRegistration() << "\n";
    std::cout << "Vehicle owner: " << person << "\n";
    std::cout << "Vehicle description: " << description << "\n";
}

void Vehicle::setPerson(unsigned int per) {
    person = per;
}

bool Vehicle::operator==(const Vehicle &oth) const {
    if (registration == oth.registration){
        return true;
    }
    return false;
}

