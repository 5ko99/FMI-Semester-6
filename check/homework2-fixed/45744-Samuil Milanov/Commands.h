#ifndef OOP_COMMANDS_H
#define OOP_COMMANDS_H
#endif //OOP_COMMANDS_H

#include "Person.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

class Vehicle;
class Person;

bool IsValidReg(const std::string& other);
std::string UpperToLower(std::string& command);
void CreateVehicle(std::vector<Vehicle>& arr, const std::string& descr, const Registration& registr);
void CreatePerson(std::vector<Person>& arr, const unsigned int& id, const std::string& name);
void ACQUIRE(const std::string& reg, unsigned int id,  std::vector<Person>& arr1, std::vector<Vehicle>& arr2);
void RELEASE(const std::string& reg, unsigned int id,  std::vector<Person>& arr1, std::vector<Vehicle>& arr2);
void REMOVEVeh(std::string reg, std::vector<Vehicle>& arr2, std::vector<Person>& arr1);
void RemovePerson(unsigned int id,  std::vector<Person>& arr1, std::vector<Vehicle>& arr2);
void SAVE(std::string path, std::vector<Person>& arr1, std::vector<Vehicle>& arr2);
void SHOWPeople(std::vector<Person>& arr1);
void SHOWVehicles(std::vector<Vehicle>& arr2);
void SHOWVPersonWithVehicle(unsigned int id,  std::vector<Person>& arr1);
void SHOWVehicleWithPerson(std::string reg,  std::vector<Vehicle>& arr2);
void LoadFromFile(std::string path, std::vector<Person>& arr1, std::vector<Vehicle>& arr2);
int RegOrId(const std::string& command);
