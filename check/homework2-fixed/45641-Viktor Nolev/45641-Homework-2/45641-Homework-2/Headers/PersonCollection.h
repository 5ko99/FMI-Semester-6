#ifndef HOMEWORK_2_PERSON_COLLECTION_H
#define HOMEWORK_2_PERSON_COLLECTION_H

#include "Person.h"
#include "../Headers/VehicleCollection.h"

#include <vector>

class VehicleCollection;

class PersonCollection {
private:
    std::vector<Person> m_persons;

    int findPersonIndex(unsigned int id) const;

public:
    Person *findPerson(unsigned int id);

    void addPerson(const Person &person);

    void acquireVehicle(unsigned int ownerId,
                        const Registration &vehicleId,
                        VehicleCollection &vehicleCollection);

    void releaseVehicle(unsigned int ownerId, const Registration &vehicleId);

    void removePerson(unsigned int id);

    void showPersonDetails(unsigned int personId);

    unsigned int peopleCount() const;

    Person &operator[](std::size_t pos);

    const Person &operator[](std::size_t pos) const;

    friend std::ostream &operator<<(std::ostream &out, const PersonCollection &personCollection);
};


#endif //HOMEWORK_2_PERSON_COLLECTION_H
