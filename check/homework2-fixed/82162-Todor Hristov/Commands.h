#pragma once
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
#include <string>
#include <cstring>
#include <algorithm>
class Commands {
    std::vector<Vehicle> listOfAllVehicles;
    std::vector<Person> listOfAllPeople;
    bool IsItRegisration(const std::string what);
public:
    Commands();
    Commands(std::vector<Vehicle> allVehicles, std::vector<Person> allPersons);
    void Command(std::string& command);
    void AddVehicle (const Vehicle& vehicle);
    void AddPerson(const Person& person);
    void Acquire (unsigned int id, const Registration& registration);
    void Release (unsigned int id, const Registration& registration);
    void RemoveVehicle (const Registration& registration);
    void RemovePerson (unsigned int id);
    void Save (const std::string& path);
    void ShowAllPeople()const;
    void ShowAllVehicles()const;
    void ShowACar (const Registration& registration)const;
    void ShowAPerson (unsigned int id);

};
