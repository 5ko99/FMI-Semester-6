#include <stdexcept>
#include <iostream>
#include "../Headers/Person.h"
#include "../Headers/VehicleCollection.h"

Person::Person(const std::string &name, const unsigned int id) {
    validate(name, id);
    m_name = name;
    m_id = id;
}


void Person::validate(const std::string &name, const unsigned int id) {
    size_t emptySpacePosition = name.find(' ');
    // If there is no empty space that separates first name from last name...
    if (emptySpacePosition == std::string::npos) {
        throw std::invalid_argument("Person's name must contains first name and last name!");
    }
    if (id == 0) {
        throw std::invalid_argument("Person's id cannot be 0!");
    }

}

void Person::addVehicle(Vehicle &vehicle) {
    vehicle.setOwner(*this);
    m_vehicles.push_back(&vehicle);

}

void Person::releaseVehicle(const Registration &vehicleId) {
    int vehicleIndex = findVehicleIndex(vehicleId);

    if (vehicleIndex == -1) {
        throw std::invalid_argument("Invalid vehicle id! There is no vehicle with that id!");
    }

    // First set the Vehicle's owner to nullptr
    m_vehicles[vehicleIndex]->m_owner = nullptr;;

    // Then remove that vehicle from the vector of vehicles that this person owns
    // Note that we do NOT delete permanently this Vehicle object
    // Vehicle object continues to live in VehicleCollection without having owner now
    m_vehicles.erase(m_vehicles.begin() + vehicleIndex);
}


int Person::findVehicleIndex(const Registration &vehicleId) const {
    size_t vehiclesCount = m_vehicles.size();
    for (int i = 0; i < vehiclesCount; ++i) {
        if (m_vehicles[i]->m_registration == vehicleId) {
            return i;
        }
    }
    return -1;
}

void Person::showVehiclesDetails() {
    size_t vehiclesCount = m_vehicles.size();
    if (vehiclesCount == 0) {
        std::cout << "There are no vehicles here...\n";
    }

    for (int i = 0; i < vehiclesCount; ++i) {
        std::cout << *m_vehicles[i] << '\n';
/*        std::cout << "Registration ID: " << m_vehicles[i]->m_registration
                  << "\t Description: " << m_vehicles[i]->m_description
                  << "\n";*/
    }
}

const std::string &Person::getName() const {
    return m_name;
}

unsigned int Person::getId() const {
    return m_id;
}


const Vehicle *Person::getVehicle(int pos) const {
    return m_vehicles[pos];
}

std::size_t Person::getVehiclesCount() const {
    return m_vehicles.size();
}

std::ostream &operator<<(std::ostream &out, const Person &person) {
//    out << "Name: " << person.m_name << " ID: " << person.m_id  <<  '\n';
    out << "\"" << person.m_name << "\"" << " " << person.m_id;
//    out << person.m_name << " " << person.m_id;
    return out;
}
