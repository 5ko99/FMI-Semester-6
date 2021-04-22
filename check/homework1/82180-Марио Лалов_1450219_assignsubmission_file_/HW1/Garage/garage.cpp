#include "garage.h"
#include <iostream>
#include <cstring>
#include <cassert>

Garage::Garage(std::size_t in_capacity)
{
    //set capacity
    capacity = in_capacity;
    spaces_taken = 0;

    //allocate memory
    try
    {
        vehicles = new Vehicle *[capacity];

        //set all vehicle pointers to nullptr
        for (int i = 0; i < capacity; i++)
        {
            vehicles[i] = nullptr;
        }
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << '\n';
        vehicles = nullptr;
    }
}

Garage::Garage(const Garage &other)
{
    //copy capacity
    capacity = other.capacity;
    spaces_taken = other.spaces_taken;

    //allocate memory
    try
    {
        vehicles = new Vehicle *[capacity];

        //copy vehicle pointers
        for (int i = 0; i < capacity; i++)
        {
            vehicles[i] = other.vehicles[i];
        }
    }
    catch (const std::bad_alloc &err)
    {
        std::cout << "Error: " << err.what() << '\n';
        vehicles = nullptr;
    }
}

Garage &Garage::operator=(const Garage &other)
{
    if (this != &other)
    {
        //create new vehicles array and copy pointers
        try
        {
            Vehicle **new_vehicles = new Vehicle *[other.capacity];
    
            for (int i = 0; i < capacity; i++)
            {
                new_vehicles[i] = other.vehicles[i];
            }

            //delete old vehicles
            delete[] this->vehicles;

            //assign the new values
            this->vehicles = new_vehicles;
            this->capacity = other.capacity;
            this->spaces_taken = other.spaces_taken;
        }
        catch (const std::bad_alloc &err)
        {
            std::cout << "Error: " << err.what() << '\n';
        }
    }

    return *this;
}

void Garage::insert(Vehicle &v)
{
    //check if insertion is possible
    if (v.getSpaces() + spaces_taken > capacity)
    {
        throw std::invalid_argument("Garage full!!!");
    }
    else
    {
        for (int i = 0; i < capacity; i++)
        {
            //find empty space
            if (vehicles[i] == nullptr)
            {
                //add vehicle reference
                vehicles[i] = &v;
                spaces_taken += v.getSpaces();

                return;
            }
        }
    }
}

void Garage::erase(const char *registration)
{
    //search for vehicle
    for (int i = 0; i < capacity; i++)
    {
        if (vehicles[i] == nullptr)
        {
            continue;
        }

        if (strcmp(vehicles[i]->getRegistration(), registration) == 0)
        {
            //remove vehichle
            spaces_taken -= vehicles[i]->getSpaces();
            vehicles[i] = nullptr;
        }
    }
}

Vehicle &Garage::at(std::size_t pos)
{
    //get element at position if possible
    if (pos >= capacity || vehicles[pos] == nullptr)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return *vehicles[pos];
    }
}

const Vehicle &Garage::at(std::size_t pos) const
{
    //get element at position if possible for constants
    if (pos >= capacity || vehicles[pos] == nullptr)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return *vehicles[pos];
    }
}

Vehicle &Garage::operator[](std::size_t pos)
{
    //get element at position pos
    assert(pos < capacity);

    return *vehicles[pos];
}

const Vehicle &Garage::operator[](std::size_t pos) const
{
    //get element at position pos for constants
    assert(pos < capacity);

    return *vehicles[pos];
}

bool Garage::empty() const
{
    //check if empty
    return (spaces_taken == 0);
}

std::size_t Garage::size() const
{
    std::size_t cnt = 0;

    //count vehicles in garage
    for (int i = 0; i < capacity; i++)
    {
        if (vehicles[i] != nullptr)
        {
            cnt++;
        }
    }

    return cnt;
}

void Garage::clear()
{
    //remove all vehicles
    spaces_taken = 0;

    for (int i = 0; i < capacity; i++)
    {
        vehicles[i] = nullptr;
    }
}

const Vehicle *Garage::find(const char *registration) const
{
    //search for vehicle in array
    for (int i = 0; i < capacity; i++)
    {
        if (vehicles[i] == nullptr)
        {
            continue;
        }

        if (strcmp(vehicles[i]->getRegistration(), registration) == 0)
        {
            return vehicles[i];
        }
    }

    return nullptr;
}

void Garage::print() const
{
    //print vehicles in garage
    int cnt = 0;

    for (int i = 0; i < capacity; i++)
    {
        if (vehicles[i] == nullptr)
        {
            cnt++;
            continue;
        }

        std::cout << "-----------------------------\n";
        std::cout << "Vehicle " << i - cnt << " : \n";
        vehicles[i]->print();
    }
}

Garage::~Garage()
{
    //set all vehicles to nullptr
    for (int i = 0; i < capacity; i++)
    {
        vehicles[i] = nullptr;
    }
}