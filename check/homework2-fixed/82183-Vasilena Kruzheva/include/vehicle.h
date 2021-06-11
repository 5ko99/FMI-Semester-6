#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include "../include/person.h"
#include "../include/registration.h"

using std::string;

class Vehicle
{
private:
    Registration registration; //!< stores vehicle's registration
    string description; //!< stores vehicle's description
    Person* owner;  //!< stores a pointer to the owner of the vehicle(nullptr if there's no owner)

    friend void Person::addVehicle(Vehicle* veh);
    friend void Person::removeVehicle(Vehicle* veh);

public:
    ///Constructor copying the values of another vehicle
    Vehicle(const Vehicle& other);

    ///Constructor taking initial values and setting owner to nullptr
    Vehicle(const char* reg, string description);

    ///Constructor taking initial values
    Vehicle(const char* reg, string description, Person* owner);

    ///Vehicle is used in vectors and the operator= is required
    Vehicle& operator=(const Vehicle& other);

    ///Returns true if the vehicle has owner and false otherwise
    bool hasOwner();

    ///Returns the value of owner
    const Person* getOwner();

    ///Returns vehicle's description
    const char* getDescription();

    ///Returns vehicle's registration
    const char* getRegistration();

    ///Releases the vehicle
    void release();

    ///Sets the owner to person
    void setOwner(Person* person);
};

#endif
