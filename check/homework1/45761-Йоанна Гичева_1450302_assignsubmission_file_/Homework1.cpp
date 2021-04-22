#include <iostream>
#include <string>
#include <vector>

#include "Vehicle.hpp";
#include "Garage.hpp";
#include "MyString.hpp";


void displayCommands();
void createGarage();
void createVehicle();
void addVehicleToGarage();
void removeVehicleFromGarage();
void commandControlller(char* input);
void printGarage();
void printRegisteredVehicles();
void clearGarage();
bool canCreateVehicle();
void addVehicleToList(Vehicle& vehicle);
bool strcmp(char* a, char* b);
bool strcmp(const char* a, char* b);

unsigned int vehiclesProgramCapacity = 1024;
unsigned int vehiclesCounter = 0;
std::vector<Vehicle> vehicles;
Garage* garage;

int main()
{
    std::cout << "Hi and welcome to YOJI's garage!\n";
    std::cout << "For list of commands press H!\n";

    char* input = new char[32];
    std::cin >> input;

    while (!strcmp(input, (char*)"EXIT")) {
        commandControlller(input);
        std::cin >> input;
    }

    std::cout << "You just exited from your garage! Re-run the program to start over!\n";
    std::cout << "###########################################################################\n";

    return 0;
}

void commandControlller(char* input) {
    if (strcmp(input, (char*)"H")) {
        displayCommands();
    }
    else if (strcmp(input, (char*)"create-vehicle")){
        createVehicle();
    }
    else if (strcmp(input, (char*)"create-garage")) {
        createGarage();
    }
    else if (strcmp(input, (char*)"add-to-garage")) {
        addVehicleToGarage();
    }
    else if (strcmp(input, (char*)"clear-garage")) {
        clearGarage();
    }
    else if (strcmp(input, (char*)"remove-vehicle")) {
        removeVehicleFromGarage();
    }
    else if (strcmp(input, (char*)"print-garage")) {
        printGarage();
    }
    else {
        std::cout << "There is no such command!\n";
    }
}
void printGarage() {
    if (garage == nullptr) {
        std::cout << "You still don't have a garage but you can create one!\n";
        std::cout << "####################################################\n";

        return;
    }
    garage->print();
}

void clearGarage() {
    if (garage->empty()) {
        std::cout << "Your garage is already cleared!";
        std::cout << "##############################\n";

        return;
    }

    garage->clear();
    std::cout << "Your garage was cleared successfully!";
    std::cout << "#####################################\n";

}

void removeVehicleFromGarage() {
    char* registration = new char[32];
    std::cout << "Available registration numbers: \n";
    printRegisteredVehicles();
    std::cout << "Choose Registration: ";
    std::cin >> registration;
    
    garage->erase(registration);
    std::cout << "Vehicle was removed successfully!" << std::endl;
    std::cout << "################################\n";

}

void addVehicleToGarage() {
    if (garage == nullptr) {
        std::cout << "You still don't have a garage but you can create one!\n";
        std::cout << "####################################################\n";
        return;
    }
    if (vehicles.size() == 0) {
        std::cout << "There are no vehicles to add! Please, create one!\n";
        std::cout << "#################################################\n";
        return;
    }

    char* registration = new char[32];
    std::cout << "Available registration numbers: \n";
    printRegisteredVehicles();
    std::cout << "Choose Registration: ";
    std::cin >> registration;

    Vehicle* vehicle = &vehicles[0];
    bool found = false;
    for (int i = 0; i < vehiclesCounter; i++) {
        const char* reg = vehicles[i].registration();
        if (strcmp(reg, registration)) {
            vehicle = &vehicles[i];
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "No such vehicle!" << std::endl;
        std::cout << "#################\n";

    }
    else if (garage == nullptr) {
        std::cout << "You still don't have a garage!" << std::endl;
        std::cout << "##############################\n";

    }
    else {
        try {
            garage->insert(*vehicle);
            std::cout << "Vehicle was added successfully!" << std::endl;
            std::cout << "##############################\n";
        }
        catch (const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
            std::cout << "####################\n";
        }
    }
}

void printRegisteredVehicles() {
    for (int i = 0; i < vehiclesCounter; i++) {
        Vehicle* veh = &vehicles[i];
        std::cout << "#" << vehicles[i].registration() << std::endl;
    }
}
void createVehicle() {
    char* registration = new char[32];
    char* description = new char[32];
    std::size_t space;

    if (!canCreateVehicle()) {
        std::cout << "You cannot create anymore vehicles!\n";
        return;
    }
    std::cout << "Let's create a new vehicle!\n";

    std::cout << "Registration: ";
    std::cin >> registration;
    std::cout << "Description: ";
    std::cin >> description;
    std::cout << "Space: ";
    std::cin >> space;

    Vehicle vehicle = Vehicle(registration, description, space);
    addVehicleToList(vehicle);

    std::cout << "You created a vehicle successfully!\n";
    std::cout << "###################################\n";
}

void createGarage() {
    std::size_t size;

    if (garage != nullptr) {
        std::cout << "You already have a garage!\n";
        return;
    }
    std::cout << "Let's create your garage!\n";

    std::cout << "Size: ";
    std::cin >> size;

    garage = new Garage(size);

    std::cout << "Congratulation!You just created your garage!\n";
    std::cout << "############################################\n";
}

void displayCommands() {
    std::cout << "# Commands helplist #" << std::endl;
    std::cout << "# create-vehicle" << std::endl;
    std::cout << "# create-garage" << std::endl;
    std::cout << "# add-togarage" << std::endl;
    std::cout << "# clear-garage" << std::endl;
    std::cout << "# remove-vehicle" << std::endl;
    std::cout << "# print-garage" << std::endl;
    std::cout << "###################################\n";

}

void addVehicleToList(Vehicle& vehicle) {
    vehicles.push_back(vehicle);
    vehiclesCounter++;
}

bool canCreateVehicle() {
    if (vehiclesProgramCapacity - 1 == 0) {
        return false;
    }

    return true;
}

bool strcmp(char* firstArr, char* secondArr)
{
    int firstLen = strlen(firstArr);
    int secondLen = strlen(secondArr);
    if (firstLen != secondLen) return false;
    for (secondLen = 0; secondLen < firstLen; secondLen++)
    {
        if (toupper(firstArr[secondLen]) != toupper(secondArr[secondLen])){
            return false;
        }
    }
    return true;
}

bool strcmp(const char* a, char* b)
{
    int la = strlen(a);
    int lb = strlen(b);
    if (la != lb) return false;
    for (lb = 0; lb < la; lb++)
    {
        if (toupper(a[lb]) != toupper(b[lb])) {
            return false;
        }
    }
    return true;
}