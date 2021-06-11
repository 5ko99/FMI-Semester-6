#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
//#include "vehicle.h"

using std::vector;
using std::string;

class Vehicle;

class Person
{
private:
    string name;    //!< stores the name of the person

    /**
     * Stores the ID of the person.
     * 
     * Used type unsigned long instead of unsigned int, because the function converting string(or const char*)
     * to unsigned integer returns a value of type unsigned long
     */
    unsigned long ID;
    vector<Vehicle*> vehicles; //!< stores the vehicles the person owns

    /**
     * Friend function release
     * @see void Vehicle::release();
     */
    //friend void Vehicle::release();

    /**
     * Friend function setOwner
     * @see void Vehicle::setOwner();
     */
    //friend void Vehicle::setOwner(Person* person);

public:

    ///Constructor for creating a Person object with initial values
    Person(string name, unsigned long ID);

    ///Destructor releases all vehicles
    ~Person();

    ///Returns the stored name
    const char* getName() const;

    //Returns the stored ID
    unsigned long getID() const;

    /**
     * @param i the index of the vehicle
     * @return Returns the ID of the vehicle with index i in vehicles
     */
    const char* getVehicleID(size_t i) const;
    const char* getVehicleDescription(size_t i) const;

    ///Returns the current count of owned vehicles
    int vehiclesCount();

    ///The person acquires a new vehicle
    void addVehicle(Vehicle* veh);

    ///The person releases the vehicle
    void removeVehicle(Vehicle* veh);

    ///Releases all vehicles
    void freeVehicles();
};

#endif
