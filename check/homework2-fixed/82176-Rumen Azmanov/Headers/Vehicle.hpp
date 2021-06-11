#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "..\Headers\Registration.hpp"

class Person;

class Vehicle {
   private:
    Registration registrationVehicle;
    std::string descriptionVehicle;
    Person *ownerVehicle = nullptr;

   public:
    //! Vehicle constructor
    Vehicle(const char regNumberInput[9], std::string descriptionVehicleInput);

    Registration getRegistration();
    std::string getDescription();
    Person *getOwner();

    void acquireVehicle(Person *ownerVehicleInput);
    void freeVehicle();

    //! Vehicle destructor
    ~Vehicle();
};

#endif
