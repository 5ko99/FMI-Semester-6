#include <stdexcept>
#include "../Headers/Vehicle.h"

Vehicle::Vehicle(const Registration &registration, const std::string &description) {
    m_registration = registration;
    m_description = description;
    m_owner = nullptr;
}

const Registration &Vehicle::getRegistration() const {
    return m_registration;
}

const std::string &Vehicle::getDescription() const {
    return m_description;
}

const Person *Vehicle::getOwner() const {
    return m_owner;
}

void Vehicle::setOwner(Person &owner) {
    if (m_owner != nullptr) {
        throw std::logic_error("Before setting new owner make sure the previous owner is properly removed!");
    }
    m_owner = &owner;
}

std::ostream &operator<<(std::ostream &out, const Vehicle &vehicle) {
    // We cannot put these strings directly between << <here> <<
    // Using std::string is such an expensive workaround :)
    std::string empty = " ";
    out << vehicle.m_registration << empty << vehicle.m_description;
    return out;
}


