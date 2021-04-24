#include "vehicle_list.h"
#include <cstring>

VehicleList::VehicleList()
{
    //set empty values
    vehicles = nullptr;
    size = 0;
}

void VehicleList::push(const char *in_reg_num, const char *in_description, int in_spaces)
{
    //create new dynamic vehicle array and dynamic vehicle
    Vehicle **new_vehicles = nullptr;
    Vehicle *new_vehicle = nullptr;

    try
    {
        new_vehicle = new Vehicle(in_reg_num, in_description, in_spaces);
        new_vehicles = new Vehicle *[size + 1];
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << "/n";

        //if exception is thrown at new_vehicle then no memory will be assigned to new_vehicles
        if (new_vehicle != nullptr)
        {
            //delete only new_vehicle
            delete new_vehicle;
        }

        return;
    }

    //copy info from original array if not empty
    if (vehicles != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            new_vehicles[i] = vehicles[i];
        }

        //delete old vehicles
        delete[] vehicles;
    }

    //assign the new values
    new_vehicles[size] = new_vehicle;
    vehicles = new_vehicles;
    size++;
}

Vehicle &VehicleList::operator[](std::size_t pos) const
{
    //return element at position pos if possible
    if (pos >= size)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return *vehicles[pos];
    }
}

std::size_t VehicleList::getIndex(const char *in_reg_number) const
{
    //get index of vehicle, return -1 if vehicle doesn't exist
    for (int i = 0; i < size; i++)
    {
        if (strcmp(vehicles[i]->getRegistration(), in_reg_number) == 0)
        {
            return i;
        }
    }

    return -1;
}

void VehicleList::remove(const char *in_reg_number)
{
    //delete vehicle if it exists
    std::size_t index = getIndex(in_reg_number);
    if (index == -1)
    {
        std::cout << "No such vehicle";
        return;
    }

    //create new dynamic vehicle array
    Vehicle **new_vehicles = nullptr;

    try
    {
        new_vehicles = new Vehicle *[size - 1];
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << "/n";
        return;
    }

    //copy all elements except the one to be removed
    int cnt = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != index)
        {
            new_vehicles[cnt] = vehicles[i];
            cnt++;
        }
    }

    //delete vehcile
    delete vehicles[index];

    //delete old array
    delete[] vehicles;

    //assign the new values
    vehicles = new_vehicles;
    size--;
}

void VehicleList::print() const
{
    //print all vehicles
    for (int i = 0; i < size; i++)
    {
        std::cout << "Vehicle " << i + 1 << " : ";
        std::cout << "---------------------------------------------------------" << std::endl;
        std::cout << "Registration number: " << vehicles[i]->getRegistration() << std::endl;
        std::cout << "Description: " << vehicles[i]->getDescription() << std::endl;
        std::cout << "Spaces taken: " << vehicles[i]->getSpaces() << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;
    }
}

VehicleList::~VehicleList()
{
    //delete date if such exists
    if (vehicles)
    {
        for (int i = 0; i < size; i++)
        {
            delete vehicles[i];
        }

        delete[] vehicles;
    }
}