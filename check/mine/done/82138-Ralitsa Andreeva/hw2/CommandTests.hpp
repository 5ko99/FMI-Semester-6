#pragma once
#include <string>
#include "catch.hpp"
#include "Command.h"
#include "Registration.h"

TEST_CASE("Throws exception if command is unknown", "[Command]")
{
	std::string line = "ac 123 AB1234AB";
	REQUIRE_THROWS(Command(line));
}
TEST_CASE("Small and capital letters for command", "[Command]")
{
	std::string line = "acQuIrE 123 AB1234AB";
	Command c(line);
	REQUIRE(c.command() == "acquire");
	REQUIRE(c.firstArgument() == "123");
	REQUIRE(c.secondArgument() == "AB1234AB");
}
TEST_CASE("Having spaces in argument", "[Command]")
{
	std::string line = "PERSON \"Ivan Ivanov\" 111";
	Command c(line);
	REQUIRE(c.command() == "person");
	REQUIRE(c.firstArgument() == "Ivan Ivanov");
	REQUIRE(c.secondArgument() == "111");
}
TEST_CASE("Only 1 argument", "[Command]")
{
	std::string line = "REMOVE AB1234AB";
	Command c(line);
	REQUIRE(c.command() == "remove");
	REQUIRE(c.firstArgument() == "AB1234AB");
	REQUIRE(c.secondArgument() == "");
}
TEST_CASE("Convert to person id", "[Command]")
{
	std::string line1 = "REMOVE 123";
	std::string line2 = "Person \"Atanas Atanasov\" 222";
	Command c1(line1),c2(line2);
	SECTION("Valid id")
	{
		REQUIRE(c1.convertToUInt(1) == 123);
		REQUIRE(c2.convertToUInt(2) == 222);
	}
	SECTION("Returns 0 if argument is not id")
	{
		REQUIRE(c2.convertToUInt(1) == 0);
	}
}
TEST_CASE("Convert to registration", "[Command]")
{
	std::string line1 = "remove AB1234AB";
	std::string line2 = "acquire 123 XY4321XT";
	Command c1(line1),c2(line2);
	Registration reg1("AB1234AB"), reg2("XY4321XT");
	SECTION("Valid registration")
	{
		REQUIRE(c1.convertToRegistration(1) == reg1);
		REQUIRE(c2.convertToRegistration(2) == reg2);
	}
	SECTION("Throws exception if argument is not a registration")
	{
		REQUIRE_THROWS(c2.convertToRegistration(1));
	}
}
