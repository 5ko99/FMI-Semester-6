
#ifndef VEHICLE
#define VEHICLE

class Person;
#include"registration.h"


class Vehicle {
private:
    Registration id;
    std::string description;
    Person* person = nullptr;

public:
    Vehicle(const Registration& id, std::string description); //constructor for the class vehicle
    std::string getDescription() const;                       //getter for the description
    std::string getRegistration() const;                      //getter for the registration
    Person* getPerson();                                      //getter for the owner of the vehicle
    void addPerson(Person* owner);                            //function which adds an owner for the vehicle
    void releaseOwner();                                      //function which remove the owner of the vehicle
    bool isItHasNoOwner() const;                              //function which check if the vehicle has an owner
    void printVehicle() const;                                //function which print the information about the vehicle

};


#endif
