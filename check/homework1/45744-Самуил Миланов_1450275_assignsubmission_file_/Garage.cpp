#pragma once

#include "Garage.h"
#include <cstring>
#include <iostream>

Garage::Garage(size_t size)
{
	this->Capacity = size;
}

void Garage::insert(Vehicle& v)
  {
	if (this->TakenSpaces + v.space() > this->Capacity)
	{
		std::cout << "Car takes too much space bro, try removing another car" << std::endl;
		return;
	}
	for (size_t i = 0; i < this->insertedVehicles; i++)
	{
		if (this->Vehicles[i] != nullptr)
		{
			if (strcmp(this->Vehicles[i]->registration(), v.registration()) == 0)
			{
				return;
			}
		}
	}
	if (this->insertedVehicles == this->MaxNumberOfvehicles) {
		const int NewMax = 2 * MaxNumberOfvehicles;
		Vehicle** poe = new Vehicle * [NewMax];
		for (size_t p = 0; p < MaxNumberOfvehicles; p++)
		{
			poe[p] = this->Vehicles[p];
		}
		this->Vehicles = poe;
		this->MaxNumberOfvehicles *= 2;
	}
	
	this->Vehicles[this->insertedVehicles] = new Vehicle(v.registration(), v.description(), v.space());
	this->TakenSpaces = this->TakenSpaces + v.space();
	this->insertedVehicles++;
	std::cout << "Successfully added car to the garage." << std::endl;

	return;
}

void Garage::erase(const char* registration)
{
	for (size_t i = 0; i < this->insertedVehicles; i++)
	{
		if (this->Vehicles[i] != nullptr)
		{
			if (strcmp(this->Vehicles[i]->registration(), registration) == 0)
			{
				this->TakenSpaces = this->TakenSpaces - this->Vehicles[i]->space();
				this->Vehicles[i] = nullptr;
				std::cout << "Vehicle succesfully removed from the garage." << std::endl;
			}
		}
	}
}

const Vehicle& Garage::at(size_t pos) const
{
    if(this->MaxNumberOfvehicles > pos)
    {
        return *this->Vehicles[pos - 1];

    }
    else throw std::out_of_range("Invalid position");
	
}
const Vehicle& Garage::operator[](size_t pos) const
{
   assert(pos < this->MaxNumberOfvehicles);
   return *this->Vehicles[pos-1];


}

bool Garage::empty() const
{
	if (this->TakenSpaces == 0)
		return true;
	return false;
}

size_t Garage::size() const
{
	
	return this->insertedVehicles;
}

void Garage::clear()
{
	for (size_t i = 0; i < this->MaxNumberOfvehicles; i++)
	{
		this->Vehicles[i] = nullptr;
	}
	this->TakenSpaces = 0;
    this->insertedVehicles = 0;
}

const Vehicle* Garage::find(const char* registration) const
{
	for (size_t i = 0; i < this->MaxNumberOfvehicles; i++)
	{
		if (strcmp(this->Vehicles[i]->registration(), registration) == 0)
		{
			return this->Vehicles[i];
		}
	}
    return nullptr;
	
}

