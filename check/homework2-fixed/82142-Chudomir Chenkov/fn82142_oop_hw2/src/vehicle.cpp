#include "vehicle.hpp"
#include "person.hpp"

#include <sstream>

Vehicle::Vehicle(const std::string &reg, const std::string &desc)
    : m_reg{Registration(reg)}, m_desc{desc}, m_owner{nullptr} {}

std::string Vehicle::registration() const { return m_reg.to_string(); }

std::string Vehicle::description() const { return m_desc; }

Person *Vehicle::owner() const { return m_owner; }

std::string Vehicle::to_string() const {
    std::stringstream ss;

    ss << "Registration: " << m_reg.to_string() << "\n"
       << "Description: " << m_desc << "\n";

    if (m_owner != nullptr)
        ss << "Owner: " << m_owner->name() << "(id: " << m_owner->uid() << ")\n";

    return ss.str();
}

void Vehicle::set_owner(Person *owner) {
    if (m_owner != nullptr) m_owner->remove_vehicle(this);
    if (owner != nullptr) owner->add_vehicle(this);

    m_owner = owner;
}
