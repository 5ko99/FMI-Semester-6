#pragma once

#include <vector>
#include <string>

class Vehicle;

class Person
{
    private:
    std::string name; 
    unsigned int id; 
    std::vector<std::string> vehicles; 

    void copy(const Person& other); 

    public: 
    Person(const std::string name, const unsigned int id);
    Person(const std::string name, const unsigned int id, const std::vector<std::string> vehicles);
    Person(const Person& other);

    void insertVehicle(const Vehicle& add);
    void eraseVehicle(const Vehicle& erase);

    size_t getOwnedVehiclesCount() const;
    std::string getName() const; 
    unsigned int getId() const;
    std::string getElement(size_t pos);

    Person& operator=(const Person& person);

    ~Person();

};
