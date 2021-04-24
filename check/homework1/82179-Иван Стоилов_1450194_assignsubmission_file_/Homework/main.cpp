#include"Vehicle/vehicle.hpp"
#include"Garage/garage.hpp"
#include"VehicleAllocator/vehicleAllocator.hpp"
#include<iostream>
#include<limits> 
using std::istream;

#define MAX_STRING 80

void printMenu();
const char *getInput();
void printAllCars(const Garage& garage);

int main ()
{
    VehicleAllocator allocator;
    std::size_t garageCapacity;
    int input = 0;

    std::cout << "CREATING GARAGE:" << '\n' << "GARAGE CAPACITY: ";
    std::cin >> garageCapacity;

    Garage garage(garageCapacity);

    printMenu();

    while (input != 4)
    {
        std::cin >> input;
        if (input == 1)
        {
            std::cout << "type the registration: ";
            const char *registration = getInput();

            std::cout << "type the description: ";
            const char* description = getInput();

            std::cout << "type the space it gets: ";
            std::size_t space;
            std::cin >> space;

            Vehicle *vehicle = allocator.allocate(registration, description, space);

            garage.insert(*vehicle);
        }
        else if (input == 2)
        {
            const char *registration = getInput();

            garage.erase(registration);
        }
        else if (input == 3)
        {
            printAllCars(garage);
        }
        else if (input == 4)
        {
            allocator.~VehicleAllocator();
            garage.~Garage();

            return 0;
        }
        else
        {
            std::cout << "your input was incorrect!" << '\n';
        }
    }
    
}

void printMenu()
{
    std::cout << "for creating and then adding a vehicle in the garage type: 1" << std::endl;
    std::cout << "for removing a existing vehicle from the garage type: 2" << std::endl;
    std::cout << "to print all vehicles type: 3" << std::endl;
    std::cout << "to exit the program type: 4" << std::endl;
}

const char* getInput()
{
    char input[MAX_STRING];
    std::cin >> input;

    char *pointer = input;

    return pointer;
}

void printAllCars(const Garage& garage)
{
    for (std::size_t counter = 0; counter < garage.size(); ++counter)
    {
        MyString registration = garage[counter].registration();
        std::cout << registration.size();
        for (int i = 0; i < registration.size(); i++)
        {
            std::cout << registration[i];
        }
        
        std::cout << std::endl;

     

        /*const char *description = garage[counter].description();
        while (description[i] !='\0')
        {
            std::cout << description;

            ++i;
        }
        std::cout << std::endl;*/
        

        std::cout << "it takes " << garage[counter].space() << " parking lots" << std::endl;
    }
    
}