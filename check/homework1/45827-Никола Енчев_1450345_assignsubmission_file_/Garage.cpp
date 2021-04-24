#include "Garage.h"
#include <iostream>
#include <cassert>
#include <cstring>
Garage::Garage(size_t size)
{
	this->capacity = size;
	this->vehicleCount = 0;
	this->vehicles = nullptr;
	this->spaceTaken = 0;
}

Garage::Garage(const Garage& other)
{
	this->capacity = other.capacity;
	this->vehicleCount = other.vehicleCount;
	this->spaceTaken = other.spaceTaken;

	Vehicle** buffer = new Vehicle * [other.vehicleCount]{ nullptr };

	for (size_t i = 0; i < other.vehicleCount; i++)
	{
		buffer[i] = other.vehicles[i];
	}

	this->vehicles = buffer;
	buffer = nullptr;
}

Garage::~Garage()
{
	this->capacity = 0;
	this->spaceTaken = 0;

	for (size_t i = 0; i < this->vehicleCount; i++)
	{
		this->vehicles[i] = nullptr;
	}
	delete this->vehicles;

	this->vehicleCount = 0;
}

Garage& Garage::operator=(const Garage& rhs)
{
	this->capacity = rhs.capacity;
	this->vehicleCount = rhs.vehicleCount;

	Vehicle** buffer = new Vehicle * [rhs.vehicleCount]{ nullptr };

	for (size_t i = 0; i < rhs.vehicleCount; i++)
	{
		buffer[i] = rhs.vehicles[i];
	}

	this->vehicles = buffer;
	buffer = nullptr;
	return *this;
}

void Garage::insert(Vehicle& v)
{
	// TODO : check the capacity

	if (v.getSpace() > (capacity - spaceTaken))
	{
		throw std::out_of_range("No more space!\n");
	}
	if (this->find(v.getRegistration()) != nullptr)
	{
		throw std::out_of_range("That vehicle is already in the garage!");
	}

	Vehicle** buffer = new Vehicle * [vehicleCount + 1]{ nullptr };

	for (size_t i = 0; i < vehicleCount; i++)
	{
		buffer[i] = vehicles[i];
	}
	buffer[vehicleCount] = &v;

	for (size_t i = 0; i < this->vehicleCount; i++)
	{
		this->vehicles[i] = nullptr;
	}
	delete this->vehicles;

	this->vehicles = buffer;
	buffer = nullptr;

	this->vehicleCount++;
	this->spaceTaken = this->spaceTaken + v.getSpace();
}

void Garage::erase(const char* registration)
{
	if (this->find(registration) != nullptr)
	{
		Vehicle** buffer = new Vehicle * [vehicleCount - 1]{ nullptr };
		size_t bufferIdex = 0;

		for (size_t i = 0; i < this->vehicleCount; i++)
		{
			if (strcmp(this->vehicles[i]->getRegistration(), registration) == 0)
			{
				this->spaceTaken -= this->vehicles[i]->getSpace();
				continue;
			}
			buffer[bufferIdex] = this->vehicles[i];
			bufferIdex++;
		}

		for (size_t i = 0; i < this->vehicleCount; i++)
		{
			this->vehicles[i] = nullptr;
		}

		this->vehicles = buffer;
		buffer = nullptr;

		this->vehicleCount--;
	}
}

const Vehicle& Garage::at(size_t pos) const
{
	if (pos >= 0 & pos < vehicleCount)
	{
		return *this->vehicles[pos];
	}
	else
	{
		throw std::out_of_range("That element does not exist");
	}
}

const Vehicle& Garage::operator[](size_t pos) const
{
	
	assert(pos < vehicleCount);
		return *this->vehicles[pos];	
}

bool Garage::empty() const
{
	if (vehicleCount > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

size_t Garage::size() const
{
	return vehicleCount;
}

void Garage::clear()
{
	if (vehicles)
	{
		for (size_t i = 0; i < this->vehicleCount; i++)
		{
			this->vehicles[i] = nullptr;
		}
		delete this->vehicles;

		this->vehicles = nullptr;
	}
	this->spaceTaken = 0;
	this->vehicleCount = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
	for (int i = 0; i < this->vehicleCount; i++)
	{
		if (strcmp(this->vehicles[i]->getRegistration(), registration) == 0)
		{
			return this->vehicles[i];
		}
	}
	return nullptr;
}
