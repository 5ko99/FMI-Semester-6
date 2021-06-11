/*
 * Vehicle.cpp
 *
 *  Created on: 21.05.2021 Рі.
 *      Author: plamen
 */

#include "vehicle.h"
#include "person.h"

#include <functional>
#include <cassert>

void Vehicle::remove_owner() noexcept
{
	if(this->owner == nullptr)
	{
		return;
	}
	this->owner->_remove_owned_vehicle(this);
	// if and only if the previous operation succeeds then
	this->owner = nullptr;
}

void Vehicle::set_onwer(Person *new_owner)
{
	assert(new_owner != nullptr);
	if(this->owner == new_owner)
	{
		return; //already an owner
	}
	new_owner->_add_owned_vehicle(this); // exception safety
	// if and only if the previous operation succeeds then
	remove_owner();
	this->owner = new_owner;
}

//bool vehicle_cmp_equal_registration_only (const Vehicle &a, const Vehicle &b) noexcept
//{ return a.registration == b.registration; }

//std::size_t vehicle_hash_registration_only (const Vehicle &a) noexcept
//{ return std::hash<Registration>()(a.registration); }

bool Vehicle::cmp_equal_registration_only::operator()(const Vehicle &a, const Vehicle &b) const noexcept
{
	return a.registration == b.registration;
}

bool Vehicle::cmp_equal_registration_only::operator()(const Vehicle *a, const Vehicle *b) const noexcept
{
	return a->registration == b->registration;
}

std::size_t Vehicle::hash_registration_only::operator()(const Vehicle &v) const noexcept
{
	return std::hash<Registration>()(v.registration);
}

std::size_t Vehicle::hash_registration_only::operator()(const Vehicle *v) const noexcept
{
	return std::hash<Registration>()(v->registration);
}
