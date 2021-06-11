#include "person.hpp"

#include <iostream>
#include <sstream>

Person::Person(unsigned int uid, const std::string &name)
    : m_uid{uid}, m_name{name} {}

unsigned int Person::uid() const { return m_uid; }

std::string Person::name() const { return m_name; }

std::vector<Vehicle *> Person::vehicles() const { return m_vehicles; }

std::size_t Person::vehicles_count() const { return m_vehicles.size(); }

std::string Person::to_string() const {
    std::stringstream ss;

    ss << "Id: " << m_uid << "\n"
       << "Name: " << m_name << "\n"
       << "Owned vehicles: ";

    if (m_vehicles.empty()) {
        ss << "None\n";
        return ss.str();
    } else {
        ss << m_vehicles.size() << "\n";
    }

    for (Vehicle *v : m_vehicles) {
        ss << v->to_string();
    }

    return ss.str();
}

void Person::clear_vehicles() {
    for (Vehicle *v : m_vehicles) {
        v->set_owner(nullptr);
    }
}

void Person::add_vehicle(Vehicle *v) {
    m_vehicles.push_back(v);
}

void Person::remove_vehicle(Vehicle *v) {
    for (auto it = m_vehicles.begin(); it != m_vehicles.end(); it++) {
        if ((*it)->registration() == v->registration()) {
            m_vehicles.erase(it);
            break;
        }
    }
}
