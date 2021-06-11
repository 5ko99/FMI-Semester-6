/*
 * person.cpp
 *
 *  Created on: 22.05.2021 Рі.
 *      Author: plamen
 */

#include "person.h"
#include "vehicle.h"

#include <cassert>

void Person::_add_owned_vehicle(Vehicle *v)
{
	// private api, so assert that v is not an already owned vehicle
	assert(this->owned_vehicles.find(v) == this->owned_vehicles.end());
	this->owned_vehicles.insert(v);
}

void Person::_remove_owned_vehicle(Vehicle *v) noexcept
{
	// private api, so assert that v is an already owned vehicle
	assert(this->owned_vehicles.find(v) != this->owned_vehicles.end());
	this->owned_vehicles.erase(v);
}

void Person::remove_vehicle(Vehicle* removed_vehicle) noexcept
{
	assert(removed_vehicle != nullptr);
	auto it = this->owned_vehicles.find(removed_vehicle);
	if(it == this->owned_vehicles.end())
	{
		return; // vehicle is already removed
	}
	assert(removed_vehicle->owner == this);
	this->owned_vehicles.erase(it);
	removed_vehicle->_remove_owner();
}

void Person::add_vehicle(Vehicle* new_vehicle)
{
	assert(new_vehicle != nullptr);
	auto it = this->owned_vehicles.find(new_vehicle);
	if(it != this->owned_vehicles.end())
	{
		return; // vehicle is already added
	}
	this->owned_vehicles.insert(new_vehicle);
	// it this succeeds then
	new_vehicle->remove_owner();
	new_vehicle->_set_owner(this);
}

bool Person::cmp_equal_id_only::operator()(const Person &a, const Person &b) const noexcept
{
	return a.id == b.id;
}

bool Person::cmp_equal_id_only::operator()(const Person *a, const Person *b) const noexcept
{
	return a->id == b->id;
}

std::size_t Person::hash_id_only::operator()(const Person &v) const noexcept
{
	return std::hash<unsigned int>()(v.id);
}

std::size_t Person::hash_id_only::operator()(const Person *v) const noexcept
{
	return std::hash<unsigned int>()(v->id);
}

Person::~Person() noexcept
{
	// while a person has vehicles, remove them safely
	while(!this->owned_vehicles.empty())
	{
		remove_vehicle(*(this->owned_vehicles.begin()));
	}
}
