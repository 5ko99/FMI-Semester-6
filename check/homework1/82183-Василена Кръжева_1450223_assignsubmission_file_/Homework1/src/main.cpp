#include <iostream>
#include <cstring>
#include "../include/vehicleallocator.hpp"
#include "../include/vehicle.hpp"
#include "../include/garage.hpp"
#include "../include/menu.hpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int garageCapacity;

    cout<< separator <<"Enter the garage capacity: ";
    cin>> garageCapacity;

    if(!cin)    //if the input is invalid we quit the program
    {
        cin.clear();
        cin.ignore();
        cout<<"Invalid input!\n";
        return 0;
    }
    else if(garageCapacity <= 0)
    {
        cout<<"Invalid capacity!\n";
        return 0;
    }

    VehicleAllocator vehicles(garageCapacity);

    cout<<"Garage created!\n";  //inform the user that the operation was successful

    bool finish = false;
    int choice;

    while (!finish)
    {
        printMenu();

        cout<<"Choose an option, enter anything else to quit: ";
        cin>>choice;

        if(!cin)
        {
            cin.clear();
            cin.ignore();
            cout<<"Invalid input!\n";
            return 0;
        }

        finish = findFunc(vehicles, choice);
    }
    
    return 0;
}