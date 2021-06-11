#include "databasemanager.hpp"

#include <stdexcept>

DatabaseManager::~DatabaseManager() {
    for (Person *p : m_people) {
        delete p;
    }

    for (Vehicle *v : m_vehicles) {
        delete v;
    }
}

void DatabaseManager::add_person(unsigned int id, const std::string &name) {
    if (get_person(id) != nullptr)
        throw std::runtime_error("Error: Person with that id already exists");

    m_people.push_back(new Person(id, name));
}

void DatabaseManager::add_vehicle(const std::string &reg, const std::string &desc) {
    if (get_vehicle(reg) != nullptr)
        throw std::runtime_error("Error: Vehicle with that registration already exists");

    m_vehicles.push_back(new Vehicle(reg, desc));
}

void DatabaseManager::acquire(unsigned int id, const std::string &reg) {
    if (get_vehicle(reg) == nullptr || get_person(id) == nullptr)
        throw std::runtime_error("Error: Invalid identifier provided");

    get_vehicle(reg)->set_owner(get_person(id));
}

void DatabaseManager::release(unsigned int id, const std::string &reg) {
    if (get_vehicle(reg) == nullptr || get_person(id) == nullptr)
        throw std::runtime_error("Error: Invalid identifier provided");

    get_vehicle(reg)->set_owner(nullptr);
}

void DatabaseManager::remove_person(unsigned int id) {
    for (auto it = m_people.begin(); it != m_people.end(); it++) {
        if ((*it)->uid() == id) {
            (*it)->clear_vehicles();
            delete *it;
            m_people.erase(it);
            break;
        }
    }
}

void DatabaseManager::remove_vehicle(const std::string &reg) {
    for (auto it = m_vehicles.begin(); it != m_vehicles.end(); it++) {
        if ((*it)->registration() == reg) {
            (*it)->set_owner(nullptr);
            delete *it;
            m_vehicles.erase(it);
            break;
        }
    }
}

Person *DatabaseManager::get_person(unsigned int id) {
    for (Person *p : m_people) {
        if (p->uid() == id) return p;
    }

    return nullptr;
}

const Person *DatabaseManager::get_person(unsigned int id) const {
    for (Person *p : m_people) {
        if (p->uid() == id) return p;
    }

    return nullptr;
}

Vehicle *DatabaseManager::get_vehicle(const std::string &reg) {
    for (Vehicle *v : m_vehicles) {
        if (v->registration() == reg) return v;
    }

    return nullptr;
}

const Vehicle *DatabaseManager::get_vehicle(const std::string &reg) const {
    for (Vehicle *v : m_vehicles) {
        if (v->registration() == reg) return v;
    }

    return nullptr;
}

std::vector<Person*> DatabaseManager::get_people() const {
    return m_people;
}

std::vector<Vehicle*> DatabaseManager::get_vehicles() const {
    return m_vehicles;
}
