#ifndef HW_2_PERSON_H
#define HW_2_PERSON_H

#pragma once
#include <string>
#include <vector>

class Vehicle;

class Person{
private:
    unsigned int id;
    std::string name;
    std::vector<Vehicle*> vehicles;

    void setId(unsigned int id);

public:
    explicit Person(const std::string& name, unsigned int id);

    void addVehicle(Vehicle* vhcl);

    const std::string &getName() const;

    unsigned int getId() const;

    void removeVehicle(Vehicle* vehicle);

    const std::vector<Vehicle*> &getVehicles() const;

    static bool idExists(unsigned int id, std::vector<Person*>* vect);
    static Person* findById(unsigned int id, std::vector<Person*>* vect);

    friend std::ostream& operator<<(std::ostream& out,const Person& person);

    bool operator==(const Person &rhs) const;

    bool operator!=(const Person &rhs) const;

    void printCars();

};

#endif
