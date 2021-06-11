#ifndef DOMASHNA_2_OOP_2021_PERSON_H
#define DOMASHNA_2_OOP_2021_PERSON_H
#include <vector>
#include <exception>
//#include "Vehicle.h"
//#include "Registration.h"
#include<string>
class Vehicle;
class Person {
private:
    std::string name;
    unsigned int egn;
//    Vehicle** vehicles;
    std::vector<Vehicle*> vehicles;
public:
    Person();
    Person(const std::string& name,const unsigned int egn);
    Person(const Person& other);
    Person& operator=(const Person& other);
    ~Person();

    void add_vehicle(Vehicle* v);
    const std::string& get_name()const;
    const unsigned int& get_egn()const;
    const int& vehicles_size()const;
    Vehicle* vehicle_pos(const int& pos);
    void remove_vehicle(const std::string& reg);
    void remove_vehicle();

    void print_vehicles()const;

    friend void swap(Person& first,Person& second);
};

static std::vector<Person*>allPersons;

#endif //DOMASHNA_2_OOP_2021_PERSON_H
