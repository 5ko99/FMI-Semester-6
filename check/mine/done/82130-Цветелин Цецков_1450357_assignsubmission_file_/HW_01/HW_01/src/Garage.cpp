#include "Garage.h"
#include <stdexcept>
#include <cassert>
#include<cstring>

Garage::Garage(std::size_t size)
	: maxSize(size),
	occupiedSize(0),
	nextFreeIndex(0)
{
	vehicles = new Vehicle*[size];
	for (std::size_t i = 0; i < size; i++)
	{
		vehicles[i] = nullptr;
	}
}

Garage::Garage(const Garage & other)
	: maxSize(other.maxSize),
	occupiedSize(other.occupiedSize),
	nextFreeIndex(other.nextFreeIndex)
{
	vehicles = new Vehicle*[other.maxSize];
	for (std::size_t i = 0; i < maxSize; i++)
	{
		vehicles[i] = other.vehicles[i];
	}
}

Garage::~Garage()
{
	delete[] vehicles;
	vehicles = nullptr;
	occupiedSize = 0;
	nextFreeIndex = 0;

	printf("Cleaned the garage\n");
}

Garage & Garage::operator=(const Garage & other)
{
	Vehicle** newBuf = new Vehicle*[other.maxSize];
	for (std::size_t i = 0; i < other.maxSize; i++)
	{
		newBuf[i] = other.vehicles[i];
	}
	delete[] vehicles;
	vehicles = newBuf;
	maxSize = other.maxSize;
	occupiedSize = other.occupiedSize;
	nextFreeIndex = other.nextFreeIndex;
	return *this;
}

void Garage::insert(Vehicle & v)
{
	if (v.size() + occupiedSize > maxSize)
	{
		throw std::length_error("The supplied vehicle does not fit in the free space");
	}
	if (indexOf(v.registration()) != nextFreeIndex)
	{
		throw std::invalid_argument("A vehicle with the supplied registration number is already in the garage");
	}
	this->vehicles[nextFreeIndex] = &v;
	nextFreeIndex++;
	this->occupiedSize = v.size() + occupiedSize;
}

void Garage::erase(const char * registration)
{
	std::size_t indexOfVehicle = indexOf(registration);

	if (indexOfVehicle == nextFreeIndex)
	{
		return;
	}

	const Vehicle* toBeRemoved = vehicles[indexOfVehicle];
	occupiedSize -= toBeRemoved->size();

	nextFreeIndex--;
	vehicles[indexOfVehicle] = vehicles[nextFreeIndex];
	vehicles[nextFreeIndex] = nullptr;
}

const Vehicle & Garage::at(std::size_t pos) const
{
	if (pos >= nextFreeIndex)
	{
		throw std::out_of_range("Requested vehicle at index out of range");
	}
	return *vehicles[pos];
}

const Vehicle & Garage::operator[](std::size_t pos) const
{
	assert(pos < nextFreeIndex);
	return *vehicles[pos];
}

bool Garage::empty() const
{
	return size() == 0;
}

std::size_t Garage::size() const
{
	return nextFreeIndex;
}

void Garage::clear()
{
	for (std::size_t i = 0; i < maxSize; i++)
	{
		vehicles[i] = nullptr;
	}
	occupiedSize = 0;
	nextFreeIndex = 0;
}

const Vehicle * Garage::find(const char * registration) const
{
	return vehicles[indexOf(registration)];
}

std::size_t Garage::indexOf(const char * regNumber) const
{
	if (regNumber == nullptr)
	{
		return nextFreeIndex;
	}
	for (std::size_t i = 0; i < nextFreeIndex; i++)
	{
		if (strcmp(vehicles[i]->registration(), regNumber) == 0)
		{
			return i;
		}
	}

	return nextFreeIndex;
}

std::ostream & operator<<(std::ostream & os, const Garage & garage)
{
	if (garage.size() == 0)
	{
		os << "No vehicles in garage!" << std::endl;
		return os;
	}
	os << "Contents of garage:" << std::endl;
	for (std::size_t i = 0; i < garage.size(); ++i)
	{
		os << "\t- " << i + 1 << " " << garage[i] << std::endl;
	}
	return os;
}
