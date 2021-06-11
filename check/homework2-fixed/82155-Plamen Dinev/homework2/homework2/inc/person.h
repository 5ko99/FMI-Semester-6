/*
 * person.h
 *
 *  Created on: 22.05.2021 Рі.
 *      Author: plamen
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include "vehicle.h"

#include <unordered_set>

//class Vehicle; // could not come up with a better solution
//static inline bool Vehicle::cmp_equal_registration_only (const Vehicle &a, const Vehicle &b); // this does not compile
//static inline std::size_t Vehicle::hash_registration_only (const Vehicle &a);
//bool vehicle_cmp_equal_registration_only (const Vehicle &a, const Vehicle &b) noexcept; //this compiles only with friend function
//std::size_t vehicle_hash_registration_only (const Vehicle &a) noexcept;

// cannot forward declare inner class of a forward delcared class
// so declare it as an outter
// class Vehicle::hash_vehicle_registration_only;
//class hash_vehicle_registration_only;
//class vehicle_cmp_equal_registration_only;

// The inability of C++ to work with cross referenced headers is almost impossible
// to understand. How is that even possible? How C++ can be that much of an sh*ty language?!

class Person
{
private:

	const unsigned int id;
	const std::string name;

	std::unordered_set<Vehicle*,
					   Vehicle::hash_registration_only,
					   Vehicle::cmp_equal_registration_only
					   > owned_vehicles;

	void _add_owned_vehicle(Vehicle *v);
	void _remove_owned_vehicle(Vehicle *v) noexcept;

	// private constructor, allowed creation only from person_factory
	inline Person(unsigned int _id, std::string _name)
	    : id(_id), name(std::move(_name))
	{ }

	~Person() noexcept;

public:

	// disable copy
	Person(const Person&) = delete;
	Person& operator= (const Person&) = delete;

	// disable move
	Person(Person&&) = delete;
	Person& operator= (Person&&) = delete; // immutable

	void remove_vehicle(Vehicle* removed_vehicle) noexcept;
	void add_vehicle(Vehicle* new_vehicle);

	inline unsigned int get_id() const noexcept
	{ return this->id; }
	inline const std::string& get_name() const noexcept
	{ return this->name; }
	inline const std::unordered_set<Vehicle*,
	   Vehicle::hash_registration_only,
	   Vehicle::cmp_equal_registration_only
	   >&
	get_owned_vehicles() const noexcept
	{ return this->owned_vehicles; }

	struct cmp_equal_id_only
	{
		bool operator()(const Person &a, const Person &b) const noexcept;
		bool operator()(const Person *a, const Person *b) const noexcept;
	};

	struct hash_id_only
	{
		std::size_t operator()(const Person &v) const noexcept;
		std::size_t operator()(const Person *v) const noexcept;
	};

	friend class Vehicle; // could not come up with a better solution
	friend class person_factory;
};

#endif /* SRC_PERSON_H_ */
