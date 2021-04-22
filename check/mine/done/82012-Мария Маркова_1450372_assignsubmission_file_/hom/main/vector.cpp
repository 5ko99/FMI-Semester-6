

#include <cassert>
#include <iostream>
#include <stdexcept>
#include "vector.h"

Vector::Vector ()
{
    vehicles = nullptr; 
    size = 0;
}




Vector::Vector (size_t initial_size)
{
    vehicles = new Vehicle*[initial_size];
    size = initial_size;
}


Vector::Vector (const Vector& other) 
{
    vehicles = new Vehicle*[other.size];
    for (size_t i = 0; i < other.size; ++i)
    {
        this->vehicles[i] = other.vehicles[i];
    }
    this->size = other.size;
}



void Vector::to_end (Vehicle& x)
{
    
    Vehicle **bigger_buffer = new Vehicle*[size + 1];
    for (size_t i = 0; i < size; i++)
    {
        bigger_buffer[i] = vehicles[i];
    }   
    bigger_buffer[size] = &x;
    ++size;
    delete [] vehicles; 
    vehicles = bigger_buffer;
}







void Vector::resize(size_t new_size)
{
    assert (new_size > size);

    Vehicle** new_buffer = new Vehicle*[new_size]; //default constr
    for (size_t i = 0; i < size; ++i)
    {
        new_buffer[i] = vehicles[i];
    }

    delete [] vehicles;
    size = new_size;
    vehicles = new_buffer;
}



Vehicle& Vector::operator [] (size_t i) 
{

    assert( i >= 0 && i <= size);
    return *vehicles[i]; 
}

Vehicle Vector::operator [] (size_t i) const
{
    if (i >= size)
    {
        throw std::out_of_range("too big index!");
    }
    return *vehicles[i]; 
}

Vector& Vector::operator = (const Vector& other)
{
    if (this != &other)
    {
        delete [] vehicles;
        this->vehicles = new Vehicle*[other.size];
        for (size_t i = 0; i < other.size; ++i)
        {
            this->vehicles[i] = other.vehicles[i];
        }
        this->size = other.size;
    } 
    return *this;
}

Vector::~Vector ()
{
    //std::cout << "I am being deleted\n";
    delete [] vehicles;
}

size_t Vector::length () const
{
    return size;
}

bool Vector::operator != (const Vector& other) const
{
    return !(*this == other);
}

bool Vector::operator == (const Vector& other) const
{
    if (this->size != other.size)
        return false;
    
    for (size_t i = 0; i < size; ++i)
    {
        if (vehicles[i] != other.vehicles[i])
            return false;
    }
    return true;
}



std::ostream& operator << (std::ostream& stream, const Vector& v)
{
    for (size_t i = 0; i < v.length(); ++i)  
        stream << v[i].registration() << ' ' << v[i].description() << " "
               << v[i].space() << std::endl;
    return stream;
}



