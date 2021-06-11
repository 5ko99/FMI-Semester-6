#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include<iostream>
#include<string>
#include<vector>
#include<exception>
#include"main.h"

class VehicleManager{
    private:
        std::vector<Vehicle*> vehicles;
    public:
        VehicleManager();
        ~VehicleManager();
        bool AddVehicle(Vehicle* vehicleToAdd);
        bool RemoveVehicle(std::string vehicleRegistration);
        Vehicle* GetVehicleByRegistration(std::string vehicleRegistration);
        std::vector<Vehicle*> GetAll();
};

#endif
