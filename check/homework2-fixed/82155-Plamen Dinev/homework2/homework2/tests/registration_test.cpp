/*
 * registration_test.cpp
 *
 *  Created on: 24.05.2021 Рі.
 *      Author: plamen
 */

#include <catch2/catch.hpp>

#include <exception>
#include <stdexcept>
#include <cstring>

#include "registration.h"

TEST_CASE("Invalid registrations")
{
    const char *reg = GENERATE("", "ABACSASD", "AV1111DA1", "AV1111DAC", "A1111DAC", "A1111DA1");
    REQUIRE(!Registration::is_valid_registration(reg));

    REQUIRE_THROWS_AS(Registration(reg), std::invalid_argument);
}

TEST_CASE("Validity of the stored registration")
{
	const char *reg = GENERATE("AV1351DA", "AV7584DA", "A1696DA", "A1201DA");

	REQUIRE(Registration::is_valid_registration(reg));

	Registration r(reg);

	char test[10];
	r.get(test);

	REQUIRE(std::strcmp(reg, test) == 0);
}

TEST_CASE("operator == test and hash")
{
	const char *reg1 = GENERATE("AV1351DA", "AV7584DA", "A1696DA", "A1201DA");
	const char *reg2 = GENERATE("AV1351DA", "AV7584DA", "A1696DA", "A1201DA");

	REQUIRE(Registration::is_valid_registration(reg1));
	REQUIRE(Registration::is_valid_registration(reg2));

	Registration r1(reg1);
	Registration r2(reg2);

	char test1[10];
	char test2[10];
	r1.get(test1);
	r2.get(test2);

	if(std::strcmp(test1, test2) == 0)
	{
		REQUIRE(r1 == r2);
		REQUIRE(std::hash<Registration>()(r1) == std::hash<Registration>()(r2));
	}
}
