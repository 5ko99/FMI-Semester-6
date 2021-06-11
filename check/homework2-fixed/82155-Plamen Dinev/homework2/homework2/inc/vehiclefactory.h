/*
 * vehiclefactory.h
 *
 *  Created on: 23.05.2021 Рі.
 *      Author: plamen
 */

#ifndef SRC_VEHICLEFACTORY_H_
#define SRC_VEHICLEFACTORY_H_

#include "vehicle.h"

#include <unordered_set>

class vehicle_factory
{
	//singleton stuff
public:

	static vehicle_factory& get_instance();

private:
	vehicle_factory() = default;
	~vehicle_factory();

public:

	vehicle_factory(const vehicle_factory&) = delete;
	vehicle_factory(vehicle_factory&&) = delete;
	void operator=(const vehicle_factory&)  = delete;
	void operator=(vehicle_factory&&) = delete;

	//real implementation

private:

	// we store Vehicles in heap, because unordered_set
	// iterrator invalidation might mess the addresses
	// if Vehicles were stored in the unordered_set directly
	std::unordered_set<Vehicle*,
					   Vehicle::hash_registration_only,
					   Vehicle::cmp_equal_registration_only
					   > all_vehicles;

public:

	inline const std::unordered_set<Vehicle*,
	   Vehicle::hash_registration_only,
	   Vehicle::cmp_equal_registration_only>& get_all() const noexcept
	{ return this->all_vehicles; }

	Vehicle* create_vehicle(Registration reg, std::string desc);

	Vehicle* get(Registration r) const;
	void remove(Vehicle* v);
	void remove(Registration r);

};

#endif /* SRC_VEHICLEFACTORY_H_ */
