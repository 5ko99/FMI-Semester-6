#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <cstddef>
#include <vector>
#include <iostream>

using std::vector;
using std::string;

class Vehicle;

class Person {
    string name;
    static size_t nextId;
    size_t id;
    vector<const Vehicle*> vehicles;

    public:
        Person(const string& name);
        Person(const char* name);
        Person(const string& name, vector<const Vehicle*> vehicles);
        Person(const char* name, vector<const Vehicle*> vehicles);
        Person(const Person& rhs);
        Person& operator=(const Person& rhs);
        bool operator==(const Person& rhs);

        void addVehicle(const Vehicle* v);
        void removeVehicle(const Vehicle* v);
        const char* getName() const;
        size_t getId() const;
        size_t getNumberOfVehicles() const;
        void printDetailedInformation(std::ostream& out) const;
        
        friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

#endif /* PERSON_H */
