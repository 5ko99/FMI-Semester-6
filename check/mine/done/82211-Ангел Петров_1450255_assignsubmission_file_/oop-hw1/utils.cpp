#include <iostream>
#include <cstring>
#include "myString.h"
#include "vehicle.h"
#include "garage.h"
#include "vehicleAllocator.h"
#include "utils.h"

const size_t MAX_STRING_SIZE = 64;

void menu() {

    std::cout << "Press 1 to add a car.\n";
    std::cout << "Press 2 to remove a car\n";
    std::cout << "Press 3 to print the garage.\n";
    std::cout << "Press 0 to exit.\n";
}

char* getRegistration () {

    char* buffer = new char [MAX_STRING_SIZE];
    
    std::cout << "Enter registration : ";
    std::cin.ignore();
    std::cin.getline(buffer, MAX_STRING_SIZE);
    char* registration = new char [strlen(buffer) + 1];
    strcpy(registration, buffer);
    delete [] buffer;
    
    return registration;
}

char* getDescription() {

    char* buffer = new char [MAX_STRING_SIZE];

    buffer = new char [MAX_STRING_SIZE];
    std::cout << "Enter description : ";
    std::cin.getline(buffer, MAX_STRING_SIZE);
    char* description = new char [strlen(buffer) + 1];
    strcpy(description, buffer);
    delete [] buffer;  

    return description;   
}

size_t getSpace() {

    size_t space;
    std::cout << "Enter space: ";
    std::cin >> space;

    return space;
}

void printGarage(Garage& myGarage) {

    if (myGarage.empty()) {
        std::cout << "Garage is empty.\n";
        return;
    }    

    for (size_t i = 0; i < myGarage.size(); ++i) {

        std::cout << "\nRegistration: " << myGarage[i].getRegistration() << std::endl;
        std::cout << "Description: " << myGarage[i].getDescription() << std::endl;
        std::cout << "Space: " << myGarage[i].getSpace() << std::endl;
    }
    std::cout << std::endl;
}

void addVehicle(Garage& myGarage, VehicleAllocator& vehicleContainer) {

    const char* registration = getRegistration();
    const char* description = getDescription();
    const size_t space = getSpace();

    Vehicle* vehicle = vehicleContainer.allocate(registration, description, space);
    
    myGarage.insert(*vehicle);

    delete [] registration;
    delete [] description;
}

void removeVehicle(Garage& myGarage, VehicleAllocator& vehicleContainer) {

    if (myGarage.empty()) {
        std::cout << "Garage is empty.\n";
        return;
    }

    const char* registration = getRegistration();

    myGarage.erase(registration);
    delete [] registration;
}