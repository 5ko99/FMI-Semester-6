#include <iostream>

#include "Garage.hpp"
#include "MyString.hpp"
#include "Vehicle.hpp"

void garageManager() {
    std::cout << "GARAGE MANAGER\n";
    const int maxStringSize = 128;
    std::size_t inputGarageSize;
    // For the solution of the task is used a dynamic array vehicles
    std::size_t sizeOfStorage = 0;
    Vehicle **vehicles = nullptr;
    char menuInput = ' ';

    std::cout << "Input garage size:";
    std::cin >> inputGarageSize;
    Garage garage1(inputGarageSize);

    do {
        std::cout << "MENU\n";
        std::cout << "Add a vehicle: V\n";
        std::cout << "Remove a vehicle: R\n";
        std::cout << "Printgarage: P\n";
        std::cout << "Exit: E\n";
        std::cin >> menuInput;
        switch (menuInput) {
            case 'V':
            case 'v': {
                //! Data input from user
                char holderR[maxStringSize];
                char holderD[maxStringSize];
                size_t size;
                char *registration;
                char *description;
                try {
                    registration = new char[strlen(holderR)];
                    description = new char[strlen(holderD)];
                } catch (std::bad_alloc &e) {
                    delete[] registration;
                    delete[] description;
                    throw;
                }

                std::cout << "Car registration: ";
                std::cin >> holderR;
                strcpy(registration, holderR);

                std::cout << "Car description: ";
                std::cin.ignore();
                std::cin.getline(holderD, maxStringSize);
                strcpy(description, holderD);

                std::cout << "Car size: ";
                std::cin >> size;

                //! The new vehicle is stored in the array
                Vehicle **newVehicles;
                try {
                    newVehicles = new Vehicle *[sizeOfStorage + 1];
                } catch (std::bad_alloc &e) {
                    delete[] registration;
                    delete[] description;
                    throw;
                }
                for (int i = 0; i < sizeOfStorage; ++i) {
                    newVehicles[i] = vehicles[i];
                }
                delete[] vehicles;

                ++sizeOfStorage;

                try {
                    vehicles = new Vehicle *[sizeOfStorage];
                } catch (std::bad_alloc &e) {
                    delete[] registration;
                    delete[] description;
                    delete[] newVehicles;
                    delete[] vehicles;
                    throw;
                }
                for (int i = 0; i < sizeOfStorage - 1; ++i) {
                    vehicles[i] = newVehicles[i];
                }
                delete[] newVehicles;

                Vehicle *v;
                try {
                    v = new Vehicle(registration, description, size);
                } catch (std::bad_alloc &e) {
                    delete[] registration;
                    delete[] description;
                    delete[] newVehicles;
                    delete[] vehicles;
                    throw;
                }
                vehicles[sizeOfStorage - 1] = v;

                garage1.insert(*vehicles[sizeOfStorage - 1]);
            } break;

            case 'R':
            case 'r': {
                char holderR[maxStringSize];
                std::cout << "Remove car by registration: ";
                std::cin >> holderR;
                char *registration;
                try {
                    registration = new char[strlen(holderR)];
                } catch (std::bad_alloc &e) {
                    throw;
                }
                strcpy(registration, holderR);
                garage1.erase(registration);
            } break;

            case 'P':
            case 'p': {
                for (size_t i = 1; i <= garage1.size(); ++i) {
                    std::cout << "Car at position " << i << "\n";
                    std::cout << "Registration: " << garage1[i].registration()
                              << "\n";
                    std::cout << "Description: " << garage1[i].description()
                              << "\n";
                    std::cout << "Space: " << garage1[i].space() << "\n";
                }
            } break;

            default:
                break;
        }
    } while (menuInput != 'E' && menuInput != 'e');
    delete[] vehicles;
}