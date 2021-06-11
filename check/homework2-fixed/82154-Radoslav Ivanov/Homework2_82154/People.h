#pragma once
#include "Person.h"

class People {

private:
    std::vector <Person*> people;

public:
    People () = default;
    People (const People&) = delete;
    People& operator=(const People&) = delete;
    ~People();

    Person* operator[](unsigned pos); 
    Person*& getPerson (unsigned id);
    size_t getCount() const;
    void addPerson(Person& newPerson);
    void removePerson(unsigned id);
    void addVehicleToPerson (Vehicle& newVehicle, unsigned id);
    void releaseVehicleFromPerson (const Registration& reg, unsigned id);
    void showInfo(unsigned id);
    void showAllInfo() const;
};
