#ifndef __DATABASE_HH__
#define __DATABASE_HH__

#include <iostream>
#include <string>
#include <algorithm>
#include "Registration.h"
#include "Vehicle.h"

//the class supporting the data base of the registration numbers, vehicles and people
class DataBase {
    std::vector<Registration*> registrations;
    std::vector<Vehicle*> vehicles;
    std::vector<Person*> people;

    void toUpperCase(std::string& command); //a helping method for making commands capitalized
    void removeWhiteSpaces(std::string& command); //a helping method for removing white spaces in a command
    bool confirmDeleting(); //a helping method for the decision of the user to remove something
    void countArguments(const std::vector<std::string>& arguments, std::size_t neededCount); //a method for checking if the arguments are the correct amount
    void vehicleCommand(const std::vector<std::string>& arguments); //the VEHICLE command
    void personCommand(const std::vector<std::string>& arguments); //the PERSON command
    void acquireCommand(const std::vector<std::string>& arguments); //the ACQUIRE command
    void releaseCommand(const std::vector<std::string>& arguments); //the RELEASE command
    void removeCommand(const std::vector<std::string>& arguments); //the REMOVE command
    void saveCommand(const std::vector<std::string>& arguments); //the SAVE command
    void showCommand(const std::vector<std::string>& arguments); //the SHOW command

    //helping methods for the SHOW command
    void showPerson(unsigned searchedID) const;
    void showPeople() const;
    void showVehicle(const std::string& searchedID) const;
    void showVehicles() const;

    //helping methods for the REMOVE command
    void removeVehicle(Vehicle* vehicleToDelete);
    void removePerson(Person* personToDelete);
    
    void executeCommand(std::vector<std::string>& arguments);

    public:
    //a constructor which takes the data and creates the database
    DataBase (std::vector<Registration*>& otherRegistrations, std::vector<Vehicle*>& otherVehicles, 
              std::vector<Person*>& otherPeople): registrations(otherRegistrations), vehicles(otherVehicles),
                                                  people(otherPeople) {}
    ~DataBase(); //a destructor

    static bool IDExists(unsigned int searchedID, std::vector<Person*> people);
    static bool isValid(const char* otherRegistration) {
        return otherRegistration != nullptr;
    }

    static Person* findPersonID(unsigned int searchedID, std::vector<Person*> people);
    static Vehicle* findVehicleID(const std::string& searchedID, std::vector<Vehicle*> vehicles);

    void run(std::string commandPrompt); //a method that runs the database
    
};

#endif
