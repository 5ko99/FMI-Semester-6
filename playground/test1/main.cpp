#include <iostream>
#include "VehicleList.h"

int main() {
    size_t size;
    std::cout << "Enter list size: ";
    std::cin >> size;
    std::cin.ignore(); // flush the new line

    VehicleList vl(size);

    for (size_t i = 0; i < size; ++i) {
        char regnum[9];
        char description[100];

        std::cout << "\nEnter the data for vehicle " << i << ":\n";

        std::cout << "  registration: ";
        std::cin.getline(regnum, 9);
        std::cout << "  description: ";
        std::cin.getline(description, 100);

        try {
            vl.insert(regnum, description);
        }
        catch (...) {
            std::cout << "You entered invalid data! Try again.\n";
            --i;
        }
    }

    std::cout << "\nThe list is created and contains " << vl.size() << " vehicle(s)\n";

    char regnum[9];
    std::cout << "\nEnter a registration number to search for:";
    std::cin.getline(regnum, 9);

    std::cout << (vl.find(regnum) ? "Vehicle exists\n" : "Vehicle DOES NOT exist\n");
    return 0;
}