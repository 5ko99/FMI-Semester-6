/*
 * Vehicle.h
 *
 *  Created on: 21.05.2021 Рі.
 *      Author: plamen
 */

#ifndef SRC_VEHICLE_H_
#define SRC_VEHICLE_H_

#include "registration.h"
//#include "person.h"

#include <cstdint>
#include <cstdlib>
#include <string>

class Person; // could not come up with a better solution
class vehicle_factory;

class Vehicle
{
private:

	const Registration registration;
	const std::string description;
	Person *owner;

	// without making modifications to Person owner
	inline void _set_owner (Person *new_owner) noexcept
	{ this->owner = new_owner; }
	inline void _remove_owner () noexcept
	{ this->owner = nullptr; }

	// private constructor, allowed creation only from vehicle_factory
	inline Vehicle(Registration reg, std::string desc)
	: registration(reg), description(std::move(desc)), owner(nullptr)
	{ }

public:

	// disable copy
	Vehicle(const Vehicle&) = delete;
	Vehicle& operator= (const Vehicle&) = delete;

	// disable move
	Vehicle(Vehicle&&) = delete;
	Vehicle& operator= (Vehicle&&) = delete; // immutable

	void remove_owner() noexcept;
	void set_onwer(Person *new_owner);

	inline Registration get_registration() const noexcept
	{ return this->registration; }
	inline const std::string& get_description() const noexcept
	{ return this->description; }
	inline Person* get_owner() const noexcept
	{ return this->owner; }

	inline bool operator== (const Vehicle &other) const noexcept
	{
		return (this->owner == other.owner) &&
			   (this->registration == other.registration) &&
			   (this->description == other.description);
	}

	struct cmp_equal_registration_only
	{
		bool operator()(const Vehicle &a, const Vehicle &b) const noexcept;
		bool operator()(const Vehicle *a, const Vehicle *b) const noexcept;
	};

	struct hash_registration_only
	{
		std::size_t operator()(const Vehicle &v) const noexcept;
		std::size_t operator()(const Vehicle *v) const noexcept;
	};

	friend class Person; // could not come up with a better solution
	friend class vehicle_factory;

private:
	inline ~Vehicle() noexcept
	{
		remove_owner();
	}
};

#endif /* SRC_VEHICLE_H_ */
