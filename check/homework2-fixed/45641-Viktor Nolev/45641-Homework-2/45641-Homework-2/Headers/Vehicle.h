#ifndef HOMEWORK_2_VEHICLE_H
#define HOMEWORK_2_VEHICLE_H


#include "../Headers/Registration.h"
//#include "../Headers/Person.h"

#include <string>

class Person;

class Vehicle {
private:
    friend class Person;

    Registration m_registration;
    std::string m_description;
    Person *m_owner;

    void setOwner(Person &owner);

public:
    Vehicle(const Registration &registration, const std::string &description);

    const Registration &getRegistration() const;

    const std::string &getDescription() const;

    const Person *getOwner() const;

    friend std::ostream &operator<<(std::ostream &out, const Vehicle &vehicle);

//    friend void Person::addVehicle(const Vehicle &vehicle);
};


#endif //HOMEWORK_2_VEHICLE_H
