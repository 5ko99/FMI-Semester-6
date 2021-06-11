#pragma once
#include <vector>
#include "person.h"
#include "vehicle.h"

class Allocator { // Singleton

    static Allocator* instance;

    std::vector<Person> people; // Stores people
    std::vector<Vehicle> vehicles; // Stores vehicles
    std::size_t sizePeople;
    std::size_t sizeVehicles;

    bool isValidPerson(unsigned id); // Checks wether a person with the same id exists
    bool isValidVehicle(const Registration& licensePlate); // Checks if a vehicle with the same license plate exists

    Allocator(); 
public:

    static Allocator* getInstance();

    void addPerson(std::string name, unsigned id); // Adds a person
    void addVehicle(const Registration& licensePlate, std::string description); // adds a vehicle
    void removePerson(unsigned id); // removes a perosn
    void removeVehicle(const Registration& licensPlate); // removes a vehicle

    void acquire(unsigned id, const Registration& licensePlate); // makes a vehicle owned
    void release(unsigned id, const Registration& licensePlate); // frees a vehicle

    void printPeople(); // prints people only
    void printVehicles();   // print vehicles only
    void printById(unsigned id); // prints all vehicles related to this id 
    void printByLicensePlate(const Registration& licensePlate); // prints the owner of this vehicle
    
    // Accessors
    std::size_t getPeopleSize(); 
    std::size_t getVehiclesSize();
    std::vector<Person> getPeople();
    std::vector<Vehicle> getVehicles();

    ~Allocator(); 
};
