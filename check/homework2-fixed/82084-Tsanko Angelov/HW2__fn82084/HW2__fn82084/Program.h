#pragma once
#ifndef __Program__HH
#define __Program__HH

#include<iostream>
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"


std::string getCommand(std::string& command);
void getAllArguments(std::string command, std::string& first, std::string& second, std::string& third);
size_t getEmptyRowNumber(std::string file_name);

class Program
{
    private:
    std::vector<Person> people;
    std::vector<Vehicle> vehicles;

    void copy(const Program& other);
    void clean();

    bool isItID(const std::string str);
    bool isItReg(const std::string str);
    bool isItWord(const std::string str);

    public:
    Program();
    Program(const Program& other);
    Program& operator=(const Program& other);
    ~Program();
    Program(std::string fileName);

    static std::vector<Person> readPeople(std::string fileName);
    static Person readPerson(std::string line); 
    static std::vector<Vehicle> readVehicles(std::string fileName); 
    static Vehicle readVehicle(std::string line);

    void addVehicle(const Registration &registration, const std::string &description); 
    void addPerson(const std::string &name, const unsigned int id); 
    void release(const unsigned int id, const Registration &registration);
    void acquire(const unsigned int id, const Registration &reg);
    void remove(const std::string what); 
    void show(std::string what);
    void saveToFile(std::string fileName);

    size_t getPeopleSize() const;
    size_t getVehicleSize() const; 
    
};

#endif
