#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include "vehicle.h"

using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Manager
{
private:
    vector<Person> people;  //!< vector storing the people
    vector<Vehicle> vehicles; //!< vector storing the vehicles

    /**
     * Finds the index of a person in people
     * 
     * @param personID the id of the person that we want to find
     * @return Returns the index if the person is found
     * @throw invalid_argument if the person wasn't found
     */
    int findPerson(unsigned int personID);
    /**
     * Finds the index of a vehicle in vehicles
     * 
     * @param reg registration of the vehicle we want to find
     * @return Returns the index if the vehicle is found
     * @throw invalid_argument if the vehicle wasn't found
     */
    int findVehicle(const char* reg);

    ///Removes the person with the given ID. Warns the user if the person owns vehicles
    void removePerson(unsigned int ID);
    
    ///Removes the vehicle with the given ID. Warns the user if the vehicle has owner
    void removeVehicle(const char* reg);

    ///throws an invalid_argument error if the index is < 0
    void validateIDIndex(int index);
public:

    ///Converts char array to unsigned long(throws invalid_argument error if the array can't be converted!)
    static unsigned long convertToULong(const char* id);
    
    ///Prints the given message and asks for permission to continue. Returns true if permission is given and false otherwise
    static bool takePermission(const char* message);

    ///Returns the count of vehicles stored in the manager
    unsigned int getVehiclesCount();

    ///Returns the count of the people stored in the manager
    unsigned int getPeopleCount();

    ///Adds vehicle with the given arguments
    void addVehicle(const char* reg, string description);

    ///Adds a person with the given arguments
    void addPerson(string name, unsigned int ID);

    ///The person with personID acquires the vehicle with registration reg
    void aquire(unsigned int personID, const char* reg);

    ///The person with personID releases the vehicle with registration reg
    void release(unsigned int personID, const char* reg);

    ///Removes the object with the given id
    void remove(const char* id);

    ///Saves the info in the file
    void save(const char* path);

    ///Shows the info for the object
    void show(const char* object);
};

#endif
