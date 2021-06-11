#pragma once
#include "vehicle.h"
#include <vector>
#include <string>
#include <fstream>

class System
{
public:
    System();
    void addVehicle(const Vehicle& vehicle);
    void addPerson(const Person& person);
    void setOwner(Vehicle& vehicle, Person& owner);
    void setFile(const std::string& filePath);
    void removePersonById(unsigned int id);
    void removeVehicleById(const Registration& registrationNumber);
    void saveData();
    void showOwners() const;
    void showVehicles() const;

    int getPersonById(unsigned int id) const;
    int getVehicleById(const Registration& registrationNumber) const;
    std::string getFile() const;
    Person& personAt(size_t index);
    Vehicle& vehicleAt(size_t index);
private:
    std::vector<Vehicle> vehicles;
    std::vector<Person> owners;
    std::string filePath;
};
