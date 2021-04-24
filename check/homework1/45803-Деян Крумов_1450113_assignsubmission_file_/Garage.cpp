#include "Garage.h"

Garage::Garage(std::size_t size)
{
    try
    {
        this->data = new Vehicle *[size] { nullptr, };
        this->capacity = size;
        this->occupied = 0;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Failed to initialize class" << e.what() << '\n';
        throw e;
    }
}

void Garage::copyFrom(const Garage &other)
{
    if (this != &other)
    {
        try
        {
            this->data = new Vehicle *[other.capacity];
            for (std::size_t i = 0; i < other.occupied; i++)
            {
                this->data[i] = other.data[i];
            }
            this->capacity = other.capacity;
            this->occupied = other.occupied;
        }
        catch (const std::bad_alloc &e)
        {
            std::cerr << "Failed to copy " << e.what() << '\n';
            throw e;
        }
    }
}

Garage::Garage(const Garage &other)
{
    this->copyFrom(other);
}

Garage &Garage::operator=(const Garage &other)
{
    delete[] this->data;
    this->copyFrom(other);
    return *this;
}

void Garage::insert(Vehicle &v)
{
    size_t availableSpots = this->capacity - this->occupied;
    if ((this->occupied == this->capacity) || v.space() > availableSpots)
        throw std::length_error("The capacity of the array is exceeded");

    for (std::size_t i = 0; i < this->occupied; i++)
    {
        if (strcmp(this->data[i]->registration(), v.registration()) == 0)
        {
            throw std::invalid_argument("This registry number already exists");
        }
    }

    for (std::size_t i = this->occupied; i < this->capacity; i++)
    {
        for (std::size_t j = 0; j < v.space(); j++)
        {
            this->data[i + j] = &v;
        }
        break;
    }

    this->occupied += v.space();
}

void Garage::erase(const char *registration)
{
    for (std::size_t i = 0; i < this->occupied; i++)
    {
        if (strcmp(this->data[i]->registration(), registration) == 0)
        {
            this->data[i] = this->data[this->occupied - 1];
            this->occupied--;
            i--; // Test the same item again
        }
    }
}

const Vehicle &Garage::at(std::size_t pos) const
{
    if (pos >= this->occupied || pos < 0)
    {
        throw std::out_of_range("You're trying to access invalid position, bud");
    }
    else
    {
        return *this->data[pos];
    }
}

const Vehicle &Garage::operator[](std::size_t pos) const
{
    assert(pos < this->occupied);
    return *this->data[pos];
}

bool Garage::empty() const
{
    if (this->occupied > 0)
    {
        return false;
    }

    return true;
}

std::size_t Garage::size() const
{
    return this->occupied;
}

void Garage::clear()
{
    for (std::size_t i = 0; i < this->occupied; i++)
    {
        this->data[i] = nullptr;
    }
    this->occupied = 0;
}

const Vehicle *Garage::find(const char *registration) const
{
    for (std::size_t i = 0; i < this->occupied; i++)
    {
        if (strcmp(this->data[i]->registration(), registration) == 0)
        {
            return this->data[i];
        }
    }

    return nullptr;
}

Garage::~Garage()
{
    delete[] data;
}