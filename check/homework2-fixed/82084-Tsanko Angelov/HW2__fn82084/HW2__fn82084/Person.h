#pragma once
#ifndef __Person__HH
#define __Person__HH

#include<iostream>
#include<exception>
#include<string>
#include<vector>
#include "Vehicle.h"

class Vehicle;

class Person
{
    private:
    std::string name;
    unsigned int unique_id;
    std::vector<std::string> own_vehicles;

    void copy(const Person& other);
    void clean();

    public:
    Person();
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();
    Person(const std::string _name, const unsigned int _unique_id);
    Person(const std::string _name, const unsigned int _unique_id, const std::vector<std::string> _own_vehicles);
    std::vector<std::string> getVehicles() const;
    std::string getName() const;
    unsigned int getID() const;
    void insertVehicle(const Vehicle& add);
    void eraseVehicle(const Vehicle& erase);

    size_t getOwnedVehiclesCount() const;
    std::string getElement(size_t pos);

};

#endif
