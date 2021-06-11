#ifndef HOMEWORK_2_PERSON_H
#define HOMEWORK_2_PERSON_H


#include "VehicleCollection.h"
#include "../Headers/Registration.h"
#include "Vehicle.h"

#include <string>
#include <vector>

class Vehicle;

class Person {
private:
    friend class Vehicle;

    std::string m_name;
    unsigned int m_id;
    std::vector<Vehicle *> m_vehicles;

    void validate(const std::string &name, unsigned int id);

    int findVehicleIndex(const Registration &vehicleId) const;

public:
    Person(const std::string &name, const unsigned int id);

    void addVehicle(Vehicle &vehicle);

    void releaseVehicle(const Registration &vehicleId);


    /// Prints information about vehicles that the current person owns
    void showVehiclesDetails();

    const std::string &getName() const;

    unsigned int getId() const;

    const Vehicle *getVehicle(int pos) const;

    std::size_t getVehiclesCount() const;

    //    friend void Vehicle::setOwner(const Person &owner);

    friend std::ostream &operator<<(std::ostream &out, const Person &person);
};


#endif //HOMEWORK_2_PERSON_H
