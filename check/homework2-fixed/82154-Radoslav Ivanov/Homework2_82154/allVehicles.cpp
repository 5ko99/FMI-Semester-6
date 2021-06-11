#include "allVehicles.h"
#include <iostream>

AllVehicles::~AllVehicles()
{
    for (size_t i=0; i<allVehicles.size(); ++i){
        delete allVehicles[i];
    }
    allVehicles.clear();
}

//Validation of pos is not necessary for the use of the method in this program
Vehicle* AllVehicles::operator[](unsigned int pos)
{
    return allVehicles[pos];
}

size_t AllVehicles::getCount() const 
{ 
    return allVehicles.size();
}

Vehicle*& AllVehicles::getVehicle(const Registration& reg)
{
    for (size_t i=0; i<allVehicles.size(); ++i){
        if (allVehicles[i]->getRegistration() == reg){
            return allVehicles[i];
        }
    }
    throw std::invalid_argument("Vehicle not found!");
}

void AllVehicles::addVehicle (Vehicle& newVehicle)
{
    try {
        Vehicle* found = getVehicle(newVehicle.getRegistration());  
        //if getVehicle throws, it means there is no vehicle with
        //this registration. In the current situation this is what we 
        //are looking for 
    } catch (std::invalid_argument& e){
        Vehicle* newVeh = new Vehicle(newVehicle);
        allVehicles.push_back(newVeh);
        return;
    }
    throw std::invalid_argument("There is already a vehicle with this registration!");
}

void AllVehicles::removeVehicle (const Registration& reg)
{
    Vehicle** found = &getVehicle(reg); //cannot throw because of the implementation of the command REMOVE
    (**found).releaseOwner(); 
    delete (*found);
    std::swap(*found, allVehicles.back());
    allVehicles.pop_back();
    //Using double pointer, std::swap and pop_back() instead of making an additional
    //method which finds the index in the vector of vehicle* and using erase() 
}


void AllVehicles::addOwnerToVehicle (const Registration& reg, Person& owner)
{
    getVehicle(reg)->addOwner(owner);
}


void AllVehicles::releaseOwnerFromVehicle (const Registration& reg)
{
    getVehicle(reg)->releaseOwner();
}


void AllVehicles::showInfo (const Registration& reg)
{
    getVehicle(reg)->printInfo();
}


void AllVehicles::showAllInfo () const
{
    size_t i=0;
    std::cout << "\n";
    for (i; i<allVehicles.size(); ++i){
        allVehicles[i]->printInfo();
        std::cout << "\n";
    }
    if (i == 0){
        std::cout << "No vehicles registered yet!\n" << std::endl;
    }
}
