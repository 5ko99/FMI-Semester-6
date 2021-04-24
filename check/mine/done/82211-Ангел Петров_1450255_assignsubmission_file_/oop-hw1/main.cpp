#include <iostream>
#include <cstring>
#include "myString.h"
#include "vehicle.h"
#include "garage.h"
#include "vehicleAllocator.h"
#include "utils.h"


int main() {
    size_t size;
    std::cout << "Enter garage capacity: ";
    std::cin >> size;

    VehicleAllocator vehicleContainer(size);

    Garage myGarage(size);
    int option;

    do {
        menu();
        std::cin >> option;

        if (option == 1) {

            addVehicle(myGarage, vehicleContainer);
        } 
        else if (option == 2) {
            
            removeVehicle(myGarage, vehicleContainer);
        } 
        else if (option == 3) {
            printGarage(myGarage);
        }
        else if (!option) {
            break;
        }
        else {
            std::cout << "Invalid command!\n";
        }

    } while(option);

    return 0;
}