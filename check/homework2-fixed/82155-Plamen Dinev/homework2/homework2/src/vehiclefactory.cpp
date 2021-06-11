/*
 * vehiclefactory.cpp
 *
 *  Created on: 23.05.2021 Рі.
 *      Author: plamen
 */

#include "vehiclefactory.h"

#include <exception>
#include <stdexcept>
#include <cassert>

vehicle_factory& vehicle_factory::get_instance()
{
	static vehicle_factory    instance; // Guaranteed to be destroyed.
										// Instantiated on first use.
	return instance;
}

vehicle_factory::~vehicle_factory()
{
	for(const auto &it : this->all_vehicles)
	{
		delete it;
	}
}

Vehicle* vehicle_factory::create_vehicle(Registration reg, std::string desc)
{
	Vehicle tv(reg, desc);
	auto it = this->all_vehicles.find(&tv);
	if(it != this->all_vehicles.end())
	{
		throw std::invalid_argument("Car with the same registration already exists");
	}
	Vehicle *v = new Vehicle(reg, std::move(desc));
	try
	{
		this->all_vehicles.insert(v);
	} catch (...)
	{
		delete v;
		throw;
	}
	return v;
}

Vehicle* vehicle_factory::get(Registration r) const
{
	Vehicle tv(r, std::string(""));
	auto it = this->all_vehicles.find(&tv);
	if(it == this->all_vehicles.end())
	{
		throw std::invalid_argument("Car with this registration does not exist");
	}
	return *it;
}

void vehicle_factory::remove(Vehicle* v)
{
	assert(v != nullptr);
	auto it = this->all_vehicles.find(v);
	if(it == this->all_vehicles.end())
	{
		throw std::invalid_argument("This car does not exist");
	}
	assert(v == *it);
	this->all_vehicles.erase(it); // this should not throw
	delete v;
}

void vehicle_factory::remove(Registration r)
{
	Vehicle tv(r, std::string(""));
	auto it = this->all_vehicles.find(&tv);
	if(it == this->all_vehicles.end())
	{
		throw std::invalid_argument("Car with this registration does not exist");
	}
	Vehicle *v = *it;
	this->all_vehicles.erase(it); // this should not throw
	delete v;
}
