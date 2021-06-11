#pragma once

#include "registration.h"
#include "person.h"
#include "vehicle.h"

void getAllArguments(std::string command, std::string& first, std::string& second, std::string& third);
std::string getSingleArgument(std::string& command); 
size_t getEmptyRowNumber(std::string fileName); 


class Data
{
    private:
    std::vector<Person> people;
    std::vector<Vehicle> vehicles;

    void copy(const Data& wanted);
    void clear();

    bool isItId(std::string str);
    bool isItChar(std::string str);

    int findVehicle(std::string regNumber);
    int findPerson(int id);

    public:
    Data();
    Data(const Data& other);
    Data(std::string fileName);

    static std::vector<Person> readPeople(std::string fileName);
    static Person readPerson(std::string line); 
    static std::vector<Vehicle> readVehicles(std::string fileName); 
    static Vehicle readVehicle(std::string line);

    void addVehicle(const Registration &reg, const std::string &desc); 
    void addPerson(const std::string &name, unsigned int id); 
    void release(unsigned int id, const Registration &reg);
    void acquire(unsigned int id, const Registration &reg);
    void remove(const std::string &what); 
    void show(std::string &what);
    void saveToFile(std::string &fileName);

    Person getPersonAt(unsigned int index);
    Vehicle getVehicleAt(unsigned int index);

    size_t getPeopleSize() const;
    size_t getVehicleSize() const; 

    Data& operator=(const Data& other);

    ~Data();

};
