#include"garage.hpp"
#include <cassert>

void dynamicMatrixCopy(Vehicle** destination, Vehicle** source, std::size_t vehiclesCount)
{
    for (int counter = 0; counter < vehiclesCount; ++counter)
    {
        destination[counter] = source[counter];
    }
}

void Garage::allocateDynamicVehicleArray(std::size_t size)
{
    vehicles = nullptr;
    try {
        vehicles = new Vehicle*[size];
    }
    catch (std::bad_alloc e) {
        std::cerr << "Memory fault!" << std::endl;
        throw;
    } 
}

Garage::Garage(std::size_t size)
{
    capacity = size;
    allocateDynamicVehicleArray(size);
    occupiedLots = 0;
    vehiclesCount = 0;
}

Garage& Garage::operator=(const Garage &source)
{
    capacity = source.capacity;
    occupiedLots = source.occupiedLots;

    for (std::size_t counter = 0; counter < size(); ++counter)
    {
        vehicles[counter] = nullptr;    
    }

    delete[] vehicles;

    allocateDynamicVehicleArray(source.capacity);

    dynamicMatrixCopy(vehicles, source.vehicles, source.vehiclesCount);

    return *this;
}

Garage::~Garage()
{
    for (std::size_t counter = 0; counter < size(); ++counter)
    {
        vehicles[counter] = nullptr;    
    }

    delete[] vehicles;
}

void Garage::insert(Vehicle &v)
{
    bool isValid = true;

    if (occupiedLots + v.space() > capacity)
    {
        isValid = false;

        std::cout << "2" << std::endl;

        throw "there is not enough space for this vehicle";
    }
    
    MyString vehicleToInsertRegistration = v.registration();

    for (std::size_t counter = 0; counter < vehiclesCount; ++counter)
    {
        MyString currentVehicleRegistration = (*vehicles[counter]).registration();

        if (currentVehicleRegistration == vehicleToInsertRegistration)
        {
            throw "the car already has been added into the garage";
           
            isValid = false;
        }
        
    }

    if(isValid)
    {
        vehicles[vehiclesCount] = &v;
        
        occupiedLots += 1;

        vehiclesCount++;
    }
    
}

void Garage::erase(const char *registration)
{

    MyString vehicleToEraseRegistration = registration;

    for (std::size_t counter = 0; counter < vehiclesCount; ++counter)
    {
        MyString currentVehicleRegistration = (*vehicles[counter]).registration();
        
        if (currentVehicleRegistration == vehicleToEraseRegistration)
        {
            occupiedLots -= (*vehicles[counter]).space();

            vehicles[counter] = vehicles[vehiclesCount - 1];
            vehicles[vehiclesCount - 1] = nullptr;

            --vehiclesCount;
        }
        
    }
    
}

const Vehicle& Garage::at(std::size_t pos) const
{
    if(pos > vehiclesCount || pos < 1)
    {
        throw std::out_of_range("there isn't vehicle at this index");
    }
    else
    {
        return *vehicles[pos - 1];
    }
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
    assert(pos >= 0 && pos < vehiclesCount && "this index is out of range");

    return *vehicles[pos];
}

bool Garage::empty() const
{
    if (vehiclesCount == 0)
    {
        return true;
    }

    return false;
}

std::size_t Garage::size() const
{
    return vehiclesCount;
}

void Garage::clear()
{
    for (std::size_t counter = 0; counter < size(); ++counter)
    {
        vehicles[counter] = nullptr;    
    }

    delete[] vehicles;
    occupiedLots = 0;
    vehiclesCount = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
    MyString vehicleToFindRegistration = registration;

    for (std::size_t counter = 0; counter < vehiclesCount; ++counter)
    {
        MyString currentVehicleRegistration = (*vehicles[counter]).registration();
        
        if (currentVehicleRegistration == vehicleToFindRegistration)
        {
            return vehicles[counter];
        }
        
    }

    return nullptr;
}