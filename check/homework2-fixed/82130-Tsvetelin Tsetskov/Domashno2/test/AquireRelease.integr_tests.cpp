#include "catch_amalgamated.hpp"
#include "Person.h"
#include "Vehicle.h"

#include <string>

TEST_CASE("Person aquiring and releasing of car", "[Aquire/Release]")
{
	Person pesho("Pesho", 1);
	Vehicle lada("AB1234AB", "Lada");

	pesho.aquire(&lada);
	REQUIRE(pesho.owns(&lada));
	REQUIRE(*lada.getOwner() == pesho);

	pesho.release(&lada);
	REQUIRE(!pesho.owns(&lada));
	REQUIRE(lada.getOwner() == nullptr);
}

TEST_CASE("Aquiring removes the previous owner", "[Aquire/Release]")
{
	Person pesho("Pesho", 1);
	Person gosho("Gosho", 2);
	Vehicle lada("AB1234AB", "Lada");

	pesho.aquire(&lada);
	REQUIRE(pesho.owns(&lada));
	REQUIRE(*lada.getOwner() == pesho);

	gosho.aquire(&lada);
	REQUIRE(!pesho.owns(&lada));
	REQUIRE(gosho.owns(&lada));
	REQUIRE(lada.getOwner() == &gosho);

	gosho.release(&lada);
	REQUIRE(!pesho.owns(&lada));
	REQUIRE(!gosho.owns(&lada));
	REQUIRE(lada.getOwner() == nullptr);
}

TEST_CASE("Release no owned car does not affect", "[Aquire/Release]")
{
	Person pesho("Pesho", 1);
	Vehicle lada("AB1234AB", "Lada");

	pesho.release(&lada);
	REQUIRE(!pesho.owns(&lada));
	REQUIRE(lada.getOwner() == nullptr);
}
