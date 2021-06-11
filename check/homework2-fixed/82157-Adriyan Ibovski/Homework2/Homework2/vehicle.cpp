#include "Vehicle.h"

Vehicle::Vehicle(const Registration &reg, const string &desc, Person *owner) : m_reg(reg), m_desc(desc), m_owner(owner) {
}


Vehicle::Vehicle(Vehicle &&other) noexcept: m_reg(other.m_reg), m_desc(other.m_desc), m_owner(other.m_owner) {
    other.m_owner = nullptr;
}

Vehicle &Vehicle::operator=(const Vehicle &other) {
    if(this == &other){
        return *this;
    }
    this->m_reg = other.m_reg;
    this->m_desc = other.m_desc;
    this->m_owner = other.m_owner;
    return *this;
}

Vehicle &Vehicle::operator=(Vehicle &&other) noexcept {
    this->m_reg = other.m_reg;
    this->m_desc = std::move(other.m_desc);
    this->m_owner = other.m_owner;
    other.m_owner = nullptr;

    return *this;
}

Registration Vehicle::getReg() const {
    return m_reg;
}

void Vehicle::setOwner(Person *owner) {
    m_owner = owner;
}

Person *Vehicle::getOwner() const {
    return m_owner;
}

string Vehicle::getDesc() const {
    return m_desc;
}
