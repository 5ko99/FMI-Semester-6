#ifndef DATA_H
#define DATA_H
#include <vector>
#include "Person.h"
#include "Vehicle.h"

//Makes use of Singleton Design Pattern

class Data
{
    std::vector<Person*> people;
    std::vector<Vehicle*> vehicles;
    Data();
public:
//-----------------Deleted copy ctor and copy assignment------------------
    Data(const Data& rhs)=delete;
    Data& operator=(const Data& rhs)=delete;
//----------------------Method to create an instance----------------------
    static Data& getInstance();
//--------------------------Database operations---------------------------
    Person*  newPerson (const char* name, unsigned int id);
    Vehicle* newVehicle(const char* registration, const char* description);
    Person*  findPerson(unsigned int id) const;
    Vehicle* findVehicle(const char* registration) const;
    void acquire(const char* who, const char* what);
    void release(const char* who, const char* what);
    void removePerson (unsigned int id);
    void removeVehicle(const char* registration);
    void remove(const char* what);
    std::size_t numberOfVehicles() const;
    std::size_t numberOfPeople() const;
//-------------------------File/Stream operations-------------------------
    void save(std::ofstream& oFile) const;
    void showVehicles() const;
    void showPeople() const;
    void showVehicle(const char* registration) const;
    void showPerson(unsigned int id) const;
    void show(const char* what) const;
//-------------------------------Destructor-------------------------------
    ~Data();
//------Static member functions for determining the type of a string------
    static bool isStringId(const char* str);
    static bool isStringRegistration(const char* str);
};


#endif
