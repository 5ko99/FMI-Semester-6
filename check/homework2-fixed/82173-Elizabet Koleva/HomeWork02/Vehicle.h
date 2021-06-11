#ifndef VEHICLE_H
#define VEHICLE_H

class Person;

#include "Registration.h"
#include "Person.h"


class Vehicle {

private:
    Registration regNumber;
    
    string carDescription;

    Person* owner = nullptr;

public:
    // Vehicle();

    ~Vehicle() = default;

    Vehicle(const Registration& registrationN, const string& carDescript);

    string getDescr() const;

    string getRegistrationNumb() const;

    // Person getOwner();

    bool isOwned() const; // Is the vehicle owned

    Person* getOwner() const; // Access the owner

    void setOwner(Person& otherOwner); // Pretty much set the owner

    void removeOwner(); // Remove the owner

    void printCommand(std::ostream& out) const; // Printing in the file for save

    void printEverything(std::ostream& out) const; // Printing the owner and the car info

    // TODO: will see if I use them 2 below

    bool operator==(const Registration& registrationNumbr) const ;

    bool operator==(const string& registrationNumbr) const ;

    bool operator==(const Vehicle& otherVehicle) const ;

    friend std::ostream& operator<<(std::ostream& out, const Vehicle& newVehcile);
};

#endif

