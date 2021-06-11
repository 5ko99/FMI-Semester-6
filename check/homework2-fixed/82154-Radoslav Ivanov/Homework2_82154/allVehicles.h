#pragma once
#include "Vehicle.h"
#include "Person.h"

class AllVehicles {

private:
    std::vector <Vehicle*> allVehicles;

public:
    AllVehicles () = default;
    AllVehicles (const AllVehicles&) = delete;
    AllVehicles& operator=(const AllVehicles&) = delete;
    ~AllVehicles();

    Vehicle* operator[](unsigned int pos);
    Vehicle*& getVehicle(const Registration& reg);
    size_t getCount() const;
    void addVehicle (Vehicle& newVehicle);
    void removeVehicle (const Registration& reg);
    void addOwnerToVehicle (const Registration& reg, Person& per);
    void releaseOwnerFromVehicle (const Registration& reg);
    void showInfo (const Registration& reg);
    void showAllInfo () const;
};
