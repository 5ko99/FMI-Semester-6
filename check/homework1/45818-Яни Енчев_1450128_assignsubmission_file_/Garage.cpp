#include "Garage.h"
#include <iostream>

Garage::Garage(std::size_t size)
	:capacity(size), capacityLeft(size), numberVehicles(0), vehiclesBuffer(0)
{
	this->vehicles = nullptr;
}

Garage::~Garage()
{
	this->dataClear();
}

void Garage::insert(Vehicle& v)
{
	if (v.space() > this->capacityLeft)
		throw std::length_error("Not enough space for the given vehicle!!");

	if (!this->validRegistationNumber(v))
		throw std::invalid_argument("A vehicle with this registration number is already in the garage!!");

	if (this->vehiclesBuffer > this->numberVehicles)
	{
		this->vehicles[numberVehicles] = &v;
		(this->numberVehicles)++;
		this->capacityLeft -= v.space();
		return;
	}

	Vehicle** temp = new Vehicle * [this->numberVehicles + 1];

	for (size_t i = 0; i < this->numberVehicles; i++)
		temp[i] = this->vehicles[i];

	temp[this->numberVehicles] = &v;

	this->dataClear();
	this->vehicles = temp;
	(this->numberVehicles)++;
	(this->vehiclesBuffer)++;
	this->capacityLeft -= v.space();	
}

// returns if there is already a car in the garade with the same registration number
bool Garage::validRegistationNumber(const Vehicle& v) const
{
	for (std::size_t i = 0; i < this->numberVehicles; i++)
	{
		if (strcmp(v.registration(),this->vehicles[i]->registration()) == 0) 
			return false;
	}
		

	return true;
}

//swaps the vehicle in position - position with the last positioned vehicle
bool Garage::swapVehicles(const Vehicle& toSwap)
{
	if (this->vehicles == nullptr)
		return 0;

	size_t position = this->numberVehicles + 1;
	for (size_t i = 0; i < this->numberVehicles; i++)
	{
		if (this->vehicles[i] == &toSwap)
		{
			position = i;
			break;
		}
	}

	if (position == this->numberVehicles + 1)
		return 0; // no such position has been found

	if (position == this->numberVehicles - 1)
		return 1; // has been found and it is the last

	Vehicle* temp;
	temp = this->vehicles[position];
	this->vehicles[position] = this->vehicles[this->numberVehicles - 1];
	this->vehicles[this->numberVehicles - 1] = temp;

	return 1;
}

// deletes the allocated data data, but doesn't change the other characteristics of the garage;
// useful in the insert function where we want to clear the data, but not change 
// the other characteristics 
// only used in the 'insert' function and in the destructor
void Garage::dataClear()
{
	for (size_t i = 0; i < this->numberVehicles; i++)
		this->vehicles[i] = nullptr; // taking it away from the vehicle;
	delete[] this->vehicles;
	this->vehicles = nullptr;
}


void Garage::clear()
{
	this->dataClear();
	this->numberVehicles = 0;
	this->capacityLeft = this->capacity;
	this->vehiclesBuffer = 0;
}

void Garage::erase(const char* registration)
{
	if(!this->swapVehicles(*find(registration)))
		return;
	this->capacityLeft += this->vehicles[this->numberVehicles - 1]->space();
	(this->numberVehicles)--;
	this->vehicles[this->numberVehicles - 1] = nullptr;
}

const Vehicle& Garage::at(std::size_t pos) const
{
	if (pos >= this->numberVehicles)
		throw std::out_of_range("The vehicle you're trying to access is out of range");

	return *(this->vehicles[pos]);
}

const Vehicle& Garage::operator[](std::size_t pos) const
{
	assert(pos < this->numberVehicles);

	return *(this->vehicles[pos]);
}

bool Garage::empty() const
{
	if(this->numberVehicles == 0) // tuka ne stava kakto vuv MyString da gledam dali e nullptr 
		//zashtoto ne poddurjam tochen razmer
		return true;

	return false;
}

std::size_t Garage::size() const
{
	return this->numberVehicles;
}

const Vehicle* Garage::find(const char* registration) const
{
	for (size_t i = 0; i < this->numberVehicles; i++)
		if (strcmp(this->vehicles[i]->registration(), registration) == 0)
			return this->vehicles[i];

	return nullptr;
}

void printGarage(Garage& toPrint)
{
	size_t size = toPrint.size();
	for (size_t i = 0; i < size; i++)
	{
		std::cout << toPrint[i].description() << " : " << toPrint[i].registration();
		std::cout << " : " << toPrint[i].space() << std::endl;
	}
}

//used in main
void clear(Vehicle** arr, size_t sz)
{
	for (size_t i = 0; i < sz; i++)
		delete arr[i];

	delete[] arr;
}
