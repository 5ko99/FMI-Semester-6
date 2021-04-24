#include "catch_amalgamated.hpp"
#include "Garage.h"
#include "Vehicle.h"

TEST_CASE("Garage constructor", "[Garage]")
{
	REQUIRE_NOTHROW(Garage(0));
	REQUIRE_NOTHROW(Garage(5));
}

TEST_CASE("Garage copy constructor", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	base.insert(car1);
	base.insert(car2);

	Garage copy = base;

	REQUIRE(base[0] == copy[0]);
	REQUIRE(base[1] == copy[1]);
}

TEST_CASE("Garage - [] access", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	base.insert(car1);
	base.insert(car2);

	REQUIRE(base[0] == car1);
	REQUIRE(base[1] == car2);
}

TEST_CASE("Garage - insert no throw in capacity", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	REQUIRE_NOTHROW(base.insert(car1));
	REQUIRE_NOTHROW(base.insert(car2));
}

TEST_CASE("Garage - insert throw with overflow", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(2);
	REQUIRE_NOTHROW(base.insert(car1));
	REQUIRE_THROWS_AS(base.insert(car2), std::length_error);
}

TEST_CASE("Garage - insert throw with same registration", "[Garage]")
{
	Vehicle car1("Same reg", "Description of the first car", 1);
	Vehicle car2("Same reg", "Description of the second car", 2);

	Garage base(10);

	REQUIRE_NOTHROW(base.insert(car1));
	REQUIRE_THROWS_AS(base.insert(car2), std::invalid_argument);
}

TEST_CASE("Garage - erase does nothing with empty garage", "[Garage]")
{
	Garage base(10);

	REQUIRE_NOTHROW(base.erase("Some registration"));
}

TEST_CASE("Garage - erase removes", "[Garage]")
{
	Vehicle car1("car1", "Description of the first car", 1);
	Garage base(10);
	base.insert(car1);
	REQUIRE_NOTHROW(base.erase("car1"));
	REQUIRE_THROWS_AS(base.at(0), std::out_of_range);
}

TEST_CASE("Garage - at access", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	base.insert(car1);
	base.insert(car2);
	REQUIRE(base.at(0) == car1);
	REQUIRE(base.at(1) == car2);
	REQUIRE_THROWS(base.at(-1));
}

TEST_CASE("Garage - empty check", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	REQUIRE(base.empty());

	base.insert(car1);
	base.insert(car2);
	REQUIRE(!base.empty());

	base.erase(car1.registration());
	base.erase(car2.registration());
	REQUIRE(base.empty());
}

TEST_CASE("Garage - empty size", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	REQUIRE(base.size() == 0);

	base.insert(car1);
	REQUIRE(base.size() == 1);
	base.insert(car2);
	REQUIRE(base.size() == 2);

	base.erase(car1.registration());
	REQUIRE(base.size() == 1);

	base.erase(car2.registration());
	REQUIRE(base.size() == 0);
}


TEST_CASE("Garage - clear", "[Garage]")
{
	Vehicle car1("The first car registration", "Description of the first car", 1);
	Vehicle car2("The second car registration", "Description of the second car", 2);
	Garage base(3);
	REQUIRE(base.size() == 0);
	REQUIRE(base.empty());

	base.insert(car1);
	base.insert(car2);
	REQUIRE(base.size() == 2);
	REQUIRE(!base.empty());

	base.clear();
	REQUIRE(base.size() == 0);
	REQUIRE(base.empty());
}

TEST_CASE("Garage - find", "[Garage]")
{
	Vehicle car1("car1", "Description of the first car", 1);
	Vehicle car2("car2", "Description of the second car", 2);
	Garage base(3);

	base.insert(car1);
	base.insert(car2);

	REQUIRE(base.find(car1.registration()) == &car1);
	REQUIRE(base.find(car2.registration()) == &car2);
	REQUIRE(base.find("Not existent") == nullptr);
	REQUIRE(base.find("") == nullptr);
	REQUIRE(base.find(nullptr) == nullptr);
}