#include "pch.h"
#include <iostream>
#include <string>
#include "hw2/Registration.h"
#include "Person.h"
#include "catch.hpp"
#include "main.cpp"
int main()
{
	TEST_CASE("Registration number is correct", "[reg]") {
		REQUIRE(reg[0] >= 65 && reg[0] <= 90);
		REQUIRE((reg[1] >= 65 && reg[1] <= 90)||(reg[1] >= 48 && reg[1] <= 57));
		if (reg[1] >= 65 && reg[1] <= 90)
		{
			for (size_t i = 2; i <= 6; i++)
			{
				REQUIRE(reg[i] >= 48 && reg[i] <= 57);
			}
			for (size_t i = 7; i <= 8; i++)
			{
				REQUIRE(reg[i] >= 65 && reg[i] <= 90);
			}
		}
		else
		{
			for (size_t i = 2; i <= 5; i++)
			{
				REQUIRE(reg[i] >= 48 && reg[i] <= 57);
			}
			for (size_t i = 6; i <= 7; i++)
			{
				REQUIRE(reg[i] >= 65 && reg[i] <= 90);
			}
		}
	}

	TEST_CASE("No people with two same id-s", "[id]")
	{
		REQUIRE(id)
			for (size_t i = 0; i < strlen() ; i++)
			{
				if ()
				{

				}
			}
	}
}
