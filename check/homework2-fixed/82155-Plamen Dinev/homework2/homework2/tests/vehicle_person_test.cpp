/*
 * vehicle_person_test.cpp
 *
 *  Created on: 24.05.2021 Рі.
 *      Author: plamen
 */

#include <catch2/catch.hpp>

#include <exception>
#include <stdexcept>

#include "registration.h"
#include "vehicle.h"
#include "vehiclefactory.h"

#include "person.h"
#include "personfactory.h"

TEST_CASE("General test")
{
	Vehicle *v1 = vehicle_factory::get_instance().create_vehicle(Registration("AB1112CD"), "Lada");
	REQUIRE(v1 != nullptr); REQUIRE(v1->get_owner() == nullptr);
	Vehicle *v2 = vehicle_factory::get_instance().create_vehicle(Registration("C1112CD"), "Lada2");
	REQUIRE(v2 != nullptr); REQUIRE(v2->get_owner() == nullptr);
	REQUIRE_THROWS_AS(vehicle_factory::get_instance().create_vehicle(Registration("AB1112CDQE"), "Lada3"), std::invalid_argument);
	REQUIRE_THROWS_AS(vehicle_factory::get_instance().create_vehicle(Registration("AB1112CD"), "Lada4"), std::invalid_argument);

	Person *p1 = person_factory::get_instance().create_person(0, "Paco");
	REQUIRE(p1 != nullptr); REQUIRE(p1->get_owned_vehicles().empty());
	Person *p2 = person_factory::get_instance().create_person(1, "Go60");
	REQUIRE(p2 != nullptr); REQUIRE(p2->get_owned_vehicles().empty());
	REQUIRE_THROWS_AS(person_factory::get_instance().create_person(1, "Paco3"), std::invalid_argument);

	v1->set_onwer(p1);
	REQUIRE(v1->get_owner() == p1); REQUIRE(p1->get_owned_vehicles().size() == 1);
	v1->remove_owner();
	REQUIRE(v1->get_owner() == nullptr); REQUIRE(p1->get_owned_vehicles().empty());

	p1->add_vehicle(v1);
	REQUIRE(v1->get_owner() == p1); REQUIRE(p1->get_owned_vehicles().size() == 1);
	p1->remove_vehicle(v1);
	REQUIRE(v1->get_owner() == nullptr); REQUIRE(p1->get_owned_vehicles().empty());

	v1->set_onwer(p1);
	REQUIRE(v1->get_owner() == p1); REQUIRE(p1->get_owned_vehicles().size() == 1);
	p1->remove_vehicle(v1);
	REQUIRE(v1->get_owner() == nullptr); REQUIRE(p1->get_owned_vehicles().empty());

	p1->add_vehicle(v1);
	REQUIRE(v1->get_owner() == p1); REQUIRE(p1->get_owned_vehicles().size() == 1);
	v1->remove_owner();
	REQUIRE(v1->get_owner() == nullptr); REQUIRE(p1->get_owned_vehicles().empty());


	v1->set_onwer(p2);
	REQUIRE(v1->get_owner() == p2); REQUIRE(p2->get_owned_vehicles().size() == 1);
	p1->add_vehicle(v1);
	REQUIRE(v1->get_owner() == p1); REQUIRE(p1->get_owned_vehicles().size() == 1);
	REQUIRE(p2->get_owned_vehicles().empty());
}

TEST_CASE("Search and remove")
{
	Vehicle *v1 = vehicle_factory::get_instance().create_vehicle(Registration("ZX1112CD"), "Vigula1");
	Vehicle *v2 = vehicle_factory::get_instance().create_vehicle(Registration("Q1112CD"), "Vigula2");

	Person *p1 = person_factory::get_instance().create_person(100, "Paco2");
	Person *p2 = person_factory::get_instance().create_person(101, "Go602");

	v1->set_onwer(p1);
	p1->add_vehicle(v1);

	Vehicle *vtmp;
	vtmp = vehicle_factory::get_instance().get(v1->get_registration());
	REQUIRE(vtmp == v1);
	vtmp = vehicle_factory::get_instance().get(v2->get_registration());
	REQUIRE(vtmp == v2);

	vehicle_factory::get_instance().remove(v1->get_registration());
	vehicle_factory::get_instance().remove(v2);

	REQUIRE(p1->get_owned_vehicles().empty());
	REQUIRE(p2->get_owned_vehicles().empty());

	Person *ptmp;
	ptmp = person_factory::get_instance().get(p1->get_id());
	REQUIRE(ptmp == p1);
	ptmp = person_factory::get_instance().get(p2->get_id());
	REQUIRE(ptmp == p2);

	person_factory::get_instance().remove(p1->get_id());
	person_factory::get_instance().remove(p2);
}


