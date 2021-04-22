#include "Garage.h"

Garage::Garage(std::size_t size)
{
    if (size == 0)
    {
        throw std::invalid_argument("****Size of Garage cannot be 0!****");
    }

    this->capacity = size;
    this->spaceFilled = 0;
    this->vehicles = new Vehicle *[size];

    for (size_t i = 0; i < size; i++)
    {
        vehicles[i] = nullptr;
    }
}

Garage::Garage(const Garage &other)
{
    copy(other);
}

Garage::~Garage()
{
    destroy();
}

Garage &Garage::operator=(const Garage &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }

    return *this;
}

void Garage::insert(Vehicle &vehicle)
{
    try
    {
        if (vehicle.get_space() > this->capacity)
        {
            throw std::length_error("");
        }

        if (!isUnique(vehicle.get_registration()))
        {
            throw std::invalid_argument("");
        }

        Vehicle **new_vehicles = new Vehicle *[spaceFilled + 1];

        for (size_t i = 0; i < spaceFilled; i++)
        {
            new_vehicles[i] = this->vehicles[i];
        }

        new_vehicles[this->spaceFilled] = &vehicle;

        destroy();
        this->vehicles = new_vehicles;
        spaceFilled++;

        //this->vehicles[this->spaceFilled] = &vehicle;
        // this->spaceFilled++;
        this->capacity -= vehicle.get_space();
    }
    catch (std::length_error)
    {
        std::cout << "****The vehicle is too big!****\n";
    }
    catch (std::invalid_argument)
    {
        std::cout << "****Vehicle with the same registration already exists!****\n";
    }
    catch (std::bad_alloc)
    {
        std::cout << "****Insertion failed! The initial garage is returned!****\n";
    }
}

void Garage::erase(const char *registration)
{
    if (size() > 0)
    {
        for (size_t i = 0; i < this->spaceFilled; i++)
        {
            if (MystrcmpareEquality(registration, this->vehicles[i]->get_registration()))
            {
                swap(i, this->spaceFilled - 1, this->vehicles);

                this->capacity += vehicles[spaceFilled - 1]->get_space();
                this->spaceFilled--;
                break;
            }
        }
    }
}

const Vehicle &Garage::at(std::size_t pos) const
{
    if (pos >= this->spaceFilled)
    {
        throw std::out_of_range("****Invalid index****");
    }

    return *(this->vehicles[pos]);
}

const Vehicle &Garage::operator[](std::size_t pos) const
{

#ifdef DEBUG
    assert(pos < size())
#endif

        return *(this->vehicles[pos]);
}

bool Garage::empty() const
{
    return this->spaceFilled == 0;
}

std::size_t Garage::size() const
{
    return this->spaceFilled;
}

void Garage::clear()
{
    for (size_t i = 0; i < this->spaceFilled; i++)
    {
        this->capacity += this->vehicles[i]->get_space();
    }

    this->spaceFilled = 0;
}

Vehicle *Garage::find(const char *registration)
{
    for (size_t i = 0; i < this->spaceFilled; i++)
    {
        if (MystrcmpareEquality(registration, this->vehicles[i]->get_registration()))
        {
            return this->vehicles[i];
        }
    }

    return nullptr;
}

const Vehicle *Garage::find(const char *registration) const
{
    for (size_t i = 0; i < this->spaceFilled; i++)
    {
        if (MystrcmpareEquality(registration, this->vehicles[i]->get_registration()))
        {
            return this->vehicles[i];
        }
    }

    return nullptr;
}

void Garage::print() const
{
    for (size_t i = 0; i < this->spaceFilled; i++)
    {
        std::cout << this->vehicles[i]->get_description() << " " << this->vehicles[i]->get_registration() << "\n";
    }
}

void Garage::copy(const Garage &other)
{
    this->capacity = other.capacity;
    this->spaceFilled = other.spaceFilled;
    this->vehicles = new Vehicle *[other.capacity];

    for (size_t i = 0; i < other.spaceFilled + other.capacity; i++)
    {
        this->vehicles[i] = other.vehicles[i];
    }
}
void Garage::destroy()
{
    if (this->vehicles)
    {
        delete[] this->vehicles;
    }
}
bool Garage::isUnique(const char *string) const
{
    for (size_t i = 0; i < this->spaceFilled; i++)
    {
        if (MystrcmpareEquality(this->vehicles[i]->get_registration(), string))
        {
            return false;
        }
    }

    return true;
}