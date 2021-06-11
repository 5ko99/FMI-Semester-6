#pragma once
#include "catch.hpp"
#include "Person.h"
#include "Vehicle.h"

TEST_CASE("Throws exception if person with same id exists", "[Person]")
{
	Person p("Ivan",1);
	REQUIRE_THROWS(Person("Pesho",1));
}
TEST_CASE("Add vehicle", "[Person]")
{
	Vehicle v1(Registration("AB1111XZ"), "car");
	Person p("Ivan Ivanov",1);
	p.add(&v1);
	REQUIRE(p.owns(&v1));
	REQUIRE(v1.owner() == &p);
}
TEST_CASE("Remove vehicle", "[Person]")
{
	Vehicle v(Registration("CD1234AB"), "bus");
	Person p("Georgi",2);
	Person p2("Todor", 3);
	SECTION("Successful removal")
	{
		p.add(&v);
		p.remove(&v);
		REQUIRE(!p.owns(&v));
		REQUIRE(v.owner() == nullptr);
	}
	SECTION("Trying to remove vehicle with different owner")
	{
		p2.add(&v);
		p.remove(&v);
		REQUIRE(p2.owns(&v));
		REQUIRE(!p.owns(&v));
		REQUIRE(v.owner() == &p2);
	}

}
TEST_CASE("Change ownership", "[Person]")
{
	Vehicle v(Registration("CB7552CM"), "Nissan Qashqai");
	Person p("Georgi",2);
	Person p2("Georgi Georgiev",3);
	p.add(&v);
	p2.add(&v);
	REQUIRE(!p.owns(&v));
	REQUIRE(p2.owns(&v));
	REQUIRE(v.owner() == &p2);
}
