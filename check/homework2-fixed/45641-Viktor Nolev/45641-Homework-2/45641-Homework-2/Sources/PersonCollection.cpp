#include <stdexcept>
#include <iostream>
#include <cassert>
#include "../Headers/PersonCollection.h"


Person *PersonCollection::findPerson(unsigned int id) {
    // We declare separate variable for count
    // in case if one day std::vector<T>.size() is modified to iterate collection element by element each time :)
    // Better to use some more bytes than do end-to-end iterations for each iteration in for-cycle condition down here
    size_t personsCount = m_persons.size();
    for (int i = 0; i < personsCount; ++i) {
        if (m_persons[i].getId() == id) {
            return &m_persons[i];
        }
    }
    // Person is not in the collection
    return nullptr;
}

int PersonCollection::findPersonIndex(unsigned int id) const {
    // We declare separate variable for count
    // in case if one day std::vector<T>.size() is modified to iterate collection element by element each time :)
    // Better to use some more bytes than do end-to-end iterations for each iteration in for-cycle condition down here
    size_t personsCount = m_persons.size();
    for (int i = 0; i < personsCount; ++i) {
        if (m_persons[i].getId() == id) {
            return i;
        }
    }
    // Person is not in the collection
    return -1;
}

void PersonCollection::addPerson(const Person &person) {
    if (findPerson(person.getId())) {
        throw std::invalid_argument("There is another person with same id in the collection!");
    }
    m_persons.push_back(person);
}

void PersonCollection::acquireVehicle(unsigned int ownerId, const Registration &vehicleId,
                                      VehicleCollection &vehicleCollection) {
    int personIndex = findPersonIndex(ownerId);
    if (personIndex == -1) {
        throw std::invalid_argument("Invalid id for owner! There is no person with entered id!");
    }

    Vehicle *vehicle = vehicleCollection.findVehicle(vehicleId);
    if (!vehicle) {
        throw std::invalid_argument("Invalid id for vehicle! There is no vehicle with entered id!");
    }

    // If vehicle already has an owner - remove the current owner before setting the new owner
    const Person *previousOwner = vehicle->getOwner();
    if (previousOwner != nullptr) {
        releaseVehicle(previousOwner->getId(), vehicleId);
    }

    m_persons[personIndex].addVehicle(*vehicle);
}


void PersonCollection::releaseVehicle(unsigned int ownerId, const Registration &vehicleId) {
    int personIndex = findPersonIndex(ownerId);
    if (personIndex == -1) {
        throw std::invalid_argument("Invalid id for owner! There is no person with entered id!");
    }
    m_persons[personIndex].releaseVehicle(vehicleId);
}

void PersonCollection::removePerson(unsigned int id) {
    int personIndex = findPersonIndex(id);
    if (personIndex == -1) {
        throw std::invalid_argument("Cannot remove person that is not in the collection!");
    }
    // First check his vehicles
    // TODO if person owns vehicles ask for confirmation and set owner of each car to nullptr
    // releaseVehicle().....

    // First we release all vehicles that this person owns - by setting their owner to nullptr
    // Note that we do NOT delete permanently these vehicles
    std::size_t vehiclesCount = m_persons[personIndex].getVehiclesCount();
    for (int i = 0; i < vehiclesCount; ++i) {
        m_persons[personIndex].releaseVehicle(m_persons[personIndex].getVehicle(i)->getRegistration());
    }

    // Then delete permanently this person from PersonCollection
    m_persons.erase(m_persons.begin() + personIndex);
}

void PersonCollection::showPersonDetails(unsigned int personId) {
    int personIndex = findPersonIndex(personId);
    if (personIndex == -1) {
        // Print instead of throwing?
        std::cout << "Invalid person's id! There is no person with entered id!\n";
    }

    std::cout << "~~~~~~~~ Person ~~~~~~~\n"
              << m_persons[personIndex]
              << "\nowns the following vehicles:\n";
    // << m_persons[personIndex] - due to UX reasons we do not use that here :)
    m_persons[personIndex].showVehiclesDetails();
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~\n";
}

unsigned int PersonCollection::peopleCount() const {
    return m_persons.size();
}

Person &PersonCollection::operator[](std::size_t pos) {
    assert(pos < m_persons.size());
    return m_persons[pos];
}

const Person &PersonCollection::operator[](std::size_t pos) const {
    assert(pos < m_persons.size());
    return m_persons[pos];
}

std::ostream &operator<<(std::ostream &out, const PersonCollection &personCollection) {
    size_t personsCount = personCollection.m_persons.size();
    for (size_t i = 0; i < personsCount; ++i) {
        out << personCollection.m_persons[i];
    }
    return out;
}
