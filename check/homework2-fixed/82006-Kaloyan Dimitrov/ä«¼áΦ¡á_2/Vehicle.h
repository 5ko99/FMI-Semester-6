#ifndef DOMASHNA_2_OOP_2021_VEHICLE_H
#define DOMASHNA_2_OOP_2021_VEHICLE_H

#include "Person.h"
#include "Registration.h"
class Person;
class Vehicle {
private:
    Registration reg;
    std::string description;
    Person* owner;
public:
//    Vehicle();
    Vehicle(const Registration& reg,const std::string& description);
    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);
    ~Vehicle();
    void set_owner(Person* person);
    Person* get_owner()const;
    const Registration& get_reg()const;
    const std::string& get_description()const;
    friend void swap(Vehicle& first,Vehicle& second);
};
static std::vector<Vehicle*> allVehicles;

#endif //DOMASHNA_2_OOP_2021_VEHICLE_H
