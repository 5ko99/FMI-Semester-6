#ifndef PERSON_H
#define PERSON_H

class Vehicle;

#ifndef VEHICLE_H
#include "Vehicle.h"
#endif

#include <vector>


class Person {

private:
    string name;

    unsigned int uniqueID;

    std::vector<Vehicle*> vehicles;

    friend class Vehicle;

public:
    //Person();

    ~Person() = default;

    Person(const string& newPerson, unsigned int idPerson);

    unsigned int getID() const;

    string getName() const;

    size_t getOwnedVehNum() const {
	    return vehicles.size();
    }

    bool doIPossessVehicles() const ; // If the Person owns vehicles

    int vehiclePositionStorage(const Vehicle& newVehicle) const; // Check if the vehicles is owned by this Person
// const string& regNumber
    // void addVehicle(Vehicle& newVehicle);   // Acquire a vehicle

    void addVehicle(Vehicle& newVehicle);   // Acquire a vehicle

    void removeVehicle(const string& regNumber); // Remove a vehicle    // Remove a vehicle

    void removeAllOwnedVehicles();  // Remove the pointers from the vector

    void printOwnedCars() const;

    void printCommand(std::ostream& out) const; // Printing the person and its information ready for the file save

    Person operator=(const Person newPerson);

    bool operator==(const Person& otherPerson) const;

    friend std::ostream& operator<<(std::ostream& out, const Person newPerson);
};

#endif
