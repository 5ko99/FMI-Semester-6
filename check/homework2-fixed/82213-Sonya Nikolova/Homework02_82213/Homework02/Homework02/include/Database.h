#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Person.h"
#include "Registration.h"
#include "Vehicle.h"

class DataBase
{
private:
    std::vector<Person *> people;
    std::vector<Vehicle *> vehicles;

    //helper functions

    /**
     * @brief Finds a person with the given ID in the database
     * @param id: The ID to find
     * @return: Pointer to Person in people with given ID, or nullptr if not found
     */
    Person *findPerson(const unsigned int id);

    /**
     * @brief Finds a vehicle by registration in the database
     * @param reg: The registration to find
     * @return: Pointer to Vehicle in vehicles with given reg, or nullptr if not found
     */
    Vehicle *findVehicle(const Registration &reg);

    bool doesPersonExist(const unsigned int id);
    bool doesVehicleExist(const Registration &registration);

public:
    DataBase();
    ~DataBase();

    /**
     * @brief Adds a person with the given ID and name in the database
     * @param name: The name of the person
     * @param id: The ID of the person
     */
    void addPerson(const std::string &name, const unsigned int id);

    /**
     * @brief Adds a vehicle with the given registration and description in the database
     * @param registration: The registration of the vehicle
     * @param desciption: The description of the vehicle
     */
    void addVehicle(const Registration &registration, const std::string &description);

    /**
     * @brief Assigns a vehicle with given registration to the person with the given ID
     * @param owner_id: The ID of the person
     * @param registration: The registration of the vehicle
     */
    void assignVehicleToPerson(const unsigned int owner_id, const Registration &registration);

    /**
     * @brief Releases a vehicle with given registration from the person with the given ID
     * @param owner_id: The ID of the person
     * @param registration: The registration of the vehicle
     */
    void releaseVehicleFromPerson(const unsigned int owner_id, const Registration &registration);

    /**
     * @brief Prints the information about the person with the given ID
     * @param id: The ID of the person
     */
    void printPerson(const unsigned id);

    /**
     * @brief Prints the information about the vehicle with the given registration
     * @param registration: The registration of the vehicle
     */
    void printVehicle(const Registration &registration);

    /**
     * @brief Saves the information about the database in a file
     * @param path: The rpath of the file in which the database will be saved
     */
    void saveDataBase(std::string path); 

    /**
     * @brief Removes the vehicle with the given registration from the database
     * @param registration: The registration of the vehicle
     */
    void removeVehicle(const Registration &registration); 

    /**
     * @brief Removes the person with the given ID from the database
     * @param id: The ID of the person
     */
    void removePerson(const unsigned id); 
    

    const Vehicle * getVehicle(const Registration & reg);

    const Person * getPerson(const unsigned id);

    std::vector<Registration> getAllVehicleRegistrations() const;
    
    std::vector<unsigned int> getAllPeopleIds() const;
};
#endif
