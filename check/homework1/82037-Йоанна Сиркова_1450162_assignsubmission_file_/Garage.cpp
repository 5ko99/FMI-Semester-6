#include "Vehicle.h"
#include "Garage.h"
#include "MyString.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>

Garage::Garage(std::size_t size)
{
	this->size_buf = size;
	cars = 0;
	free_space = size;
	vehicle = new Vehicle * [size];
}

Garage::~Garage()
{
	delete[] vehicle;
}

void Garage::insert(Vehicle& v)
{
	if (free_space >= v.space())
	{
		for (std::size_t i = 0; i < cars; i++)
			if (vehicle[i]->registration() == v.registration())
				throw std::exception("There is already vehicle with this registration!");
		vehicle[cars] = &v;
		cars++;
		free_space -= v.space();
	}
	else
		throw std::out_of_range("There is no enough space for this vehicle!");
}

void Garage::erase(const char* registration)
{
	for (std::size_t i = 0; i < cars; i++)
		if (vehicle[i]->registration() == registration)
		{
			free_space += vehicle[i]->space();
			vehicle[i] = vehicle[cars - 1];
			vehicle[cars - 1] = nullptr;
			cars--;
		}

}

const Vehicle& Garage::at(std::size_t pos) const
{
	if (pos<0 || pos>cars) throw std::out_of_range("There is no such position!");
	return *vehicle[pos];

}

const Vehicle& Garage::operator[](std::size_t pos) const
{
	assert(pos >= 0 && pos < cars);
	return *vehicle[pos];
}

bool Garage::empty() const
{
	return cars == 0;
}

std::size_t Garage::size() const
{
	std::size_t nz = cars;
	return nz;
}

void Garage::clear()
{

	for (std::size_t i = 0; i < cars; i++)
		delete vehicle[i];

	cars = 0;
	free_space = this->size_buf;

}

const Vehicle* Garage::find(const char* registration) const
{
	for (std::size_t i = 0; i < cars; i++)
		if (vehicle[i]->registration() == registration) return vehicle[i];
	return nullptr;
}