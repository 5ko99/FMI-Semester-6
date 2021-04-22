#include <iostream>
#include <cstring>
#include "../include/vehicleallocator.hpp"
#include "../include/mystring.hpp"

using std::cin;
using std::cout;
using std::endl;

const size_t DEFAULT_SIZE = 10;

int VehicleAllocator::find(const char* registration) const
{
    for (size_t i = 0; i < count; i++)
    {
        if(strcmp((*vehicles[i]).registration(), registration) == 0)
        {
            return i;
        }
    }

    return -1;
}


//we don't know how many vehicles the user will create
//so we have a function to extend the array
void VehicleAllocator::extend()
{
    size_t newSize = (size + 1) * 2; //size + 1 in case DEFAULT_SIZE is set to 0

    Vehicle ** tmp = new Vehicle*[newSize];

    for (size_t i = 0; i < count; i++)
    {
        tmp[i] = vehicles[i];
    }

    delete[] vehicles;
    vehicles = tmp;
    size = newSize;
}

VehicleAllocator::VehicleAllocator(size_t size) : count(0), size(DEFAULT_SIZE)
{
    garage = new Garage(size);
    vehicles = new Vehicle*[this->size];
}

VehicleAllocator::VehicleAllocator(Garage& garage) : count(0), size(DEFAULT_SIZE), garage(&garage)
{
    vehicles = new Vehicle*[size];
}

VehicleAllocator::~VehicleAllocator()
{
    for (size_t i = 0; i < count; i++)
    {
        delete vehicles[i];//calling vehicle constructor
    }
    delete[] vehicles;
    delete garage;
}

const Vehicle& VehicleAllocator::allocate(const char* registration, const char* description, std::size_t space)
{
    if(find(registration) > -1)
    {
        throw std::invalid_argument("Vehicle with this registration number already exists!\n");
    }

    if(count >= size)   //count shouldn't be more than size but for extra safety we are including the case
    {
        extend();
    }

    Vehicle* veh = new Vehicle(registration, description, space);
    vehicles[count++] = veh;
    return *veh;
}


//can print both vehicles in garage and all vehicles
void VehicleAllocator::print(bool inVehicles)
{
    size_t size = garage->size();
    if(inVehicles) size = count;

    for (size_t i = 0; i < size; i++)
    {
        cout<<' '<< i + 1 <<") ";
        if(inVehicles) 
        {
            printVehicle(vehicles[i]); 
        }
        else 
        {
            printVehicle(&(*garage)[i]);
        }
    }
    cout<<endl;
}

void VehicleAllocator::add(size_t num)
{
    if(num >= 0 && num < count)
    {
        garage->insert(*vehicles[num]);
        
    }
    else
    {
        throw std::out_of_range("The number of the vehicle is invalid!\n");
    }
}

void VehicleAllocator::remove(size_t num)
{
    try
    {
        garage->erase(garage->at(num).registration());
    }
    catch(const std::out_of_range& e)
    {
        cout << e.what() << '\n';
    }
    
}

const Vehicle& VehicleAllocator::operator[](size_t pos) const
{
    return *vehicles[pos];
}

void VehicleAllocator::printVehicle(const Vehicle* v) const
{
    cout<< v->registration() << ", " << v->description() 
        <<", " << v->space() << endl;
}