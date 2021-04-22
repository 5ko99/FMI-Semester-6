#include <iostream>
#include <limits>
#include "garagesystem.h"

using std::cout;
using std::cin;
using std::endl;

GarageSystem::GarageSystem(size_t cap) : capacity(cap), garage(cap), allVehicles(cap) {}

void GarageSystem::printGarage () const 
{
    if (garage.size() == 1){
        cout << "There is 1 vehicle in the garage:\n";
    }
    else if (garage.empty()){
        cout << "There are no vehicles in the garage!" << endl;
    }
    else {
        cout << "There are " << garage.size() << " vehicles in the garage:\n";
    }

    for (size_t i=0; i<garage.size(); i++){
        cout << i+1 << ") " << garage[i].registration() << " - " << garage[i].description()
             << " - " << "Size: " << garage[i].space() << endl; 
    }
}

void GarageSystem::printOptions () const
{
    cout << "\nSelect what you want to do:" << endl;
    cout << "1) Add new vehicle to the garage" << endl;
    cout << "2) Remove a vehicle from the garage" << endl;
    cout << "3) Print info about the vehicles from the garage" << endl;
    cout << "4) Check if a vehicle is in the garage" << endl;
    cout << "0) Quit the system" << endl;
}

void GarageSystem::insertNewVehicle()
{
    cout << "Enter the vehicle's info!\n" << "Registration number: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char reg[51];
    cin.getline(reg, 51);
    cout << "Description: ";
    char descr[101];
    cin.getline(descr, 101);
    cout << "Required Space: ";
    size_t space;   
    cin >> space;
    if (space == 0){
        std::cerr << "Invalid vehicle's size" << endl;
        return;
    }
    Vehicle newVehicle(reg, descr, space);
    allVehicles.addVehicle(newVehicle);
    try {
        garage.insert(allVehicles.getLastAdded());
    } catch (const char* e){
        std::cerr << e << endl; 
    }
    
}

void GarageSystem::removeVehicle()
{
    cout << "Enter the registration number of the vehicle: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char reg[51];
    cin.getline(reg, 51);
    garage.erase(reg);
}

void GarageSystem::checkVehicle() const
{
    cout << "Enter the registration of the vehicle: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char reg[51];
    cin.getline(reg, 51);
    if (garage.find(reg)){
        cout << "The vehicle is in the garage!" << endl;
    }
    else {
        cout << "The vehicle is NOT in the garage!" << endl;
    }
}

void GarageSystem::runSystem()
{
    bool ready = false;
    do {
        printOptions();
        int choice;
        cin >> choice;
        if (choice == 1){
            insertNewVehicle();
        }  
        else if (choice == 2){
            removeVehicle();
        }
        else if (choice == 3){
            printGarage();
        }
        else if (choice == 4){
            checkVehicle();
        }
        else if (choice == 0){
            ready = true;
        }
        else {
            cout << "Invalid command!" << endl;
        }
    } while (!ready);
}