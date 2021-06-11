#pragma once
#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include "Registration.h"
#include "Vehicle.h"
#include<iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

//class Vehicle;

class VehicleManager {
    vector<Vehicle*> vehicles;
    
    public:      
        void addVehicle(const string& registration,
        const string& description);
        void removeVehicle(const string& registration);
        Vehicle* findVehicle(const string& registration);
        Vehicle* findVehicle(const Registration& registration);
        Vehicle& at(size_t pos);
	    const Vehicle& at(size_t pos) const;
        Vehicle& operator[](size_t pos);
        const Vehicle& operator[](size_t pos) const;
        size_t getNumberOfVehicles() const;
        
        void showAllVehicles(std::ostream& out);
        void showAllVehiclesDetailed(std::ostream& out);


    private:
    	bool registrationAlreadyExist(const string& registration) const;
};

#endif //VEHICLEMANAGER_H
