#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "Vehicle.h"
 

SCENARIO("Testing Vehicle functions")
{
	GIVEN("Creating a Vegicle with normal parameters")
	{
		Vehicle car("СВ2138AH", "Light and fast, what more do you need to know? Also burns 9/100", 1);
		THEN("Testing for correct number setting")
		{
			const char* reg = car.registration();
			REQUIRE(strcmp(reg, "СВ2138AH") == 0);
			delete[] reg;
		}
		THEN("Testing for correct description setting")
		{
			const char* des = car.description();
			REQUIRE(strcmp(des, "Light and fast, what more do you need to know? Also burns 9/100") == 0);
			delete[] des;
		}
		THEN("Check for correct size setting")
		{
			REQUIRE(car.space() == 1);
		}
	}//given

	GIVEN("Array of Vehicles")
	{
		const short numOfCars = 10;
		Vehicle** garage;
			try {
			garage = new Vehicle * [numOfCars];
		}
		catch (std::exception& e)
		{
			return;
		}
		int i;
		try {
			for (i = 0; i < numOfCars; i++)
			{
				garage[i] = new Vehicle("0XX0X0X0", "Looks like a car to me", i+1);
			}
		}
		catch (std::exception& e)
		{
			for (int j = 0; j < i; j++)
			{
				delete garage[j];
			}
			delete[] garage;
			return;
		}
		THEN("Check if all data is set correctly")
		{
			for (int i = 0; i < numOfCars; i++)
			{
				CHECK((*garage[i]).space()==i+1);
				const char* des = (*garage[i]).description();
				CHECK(strcmp(des, "Looks like a car to me") == 0);
				delete[] des;
				const char* reg = (*garage[i]).registration();
				REQUIRE(strcmp(reg, "0XX0X0X0") == 0);
				delete[] reg;
			}
		}

	}//given
	GIVEN("Testing operator ==")
	{
		Vehicle first("OB1234", "First car", 1);
		Vehicle second("OB1234", "Second car", 1);
		Vehicle third("OB1234", "First car", 1);
		REQUIRE(first == first);
		REQUIRE(first == third);
		REQUIRE_FALSE(first == second);
		THEN("Test copy constr")
		{
			Vehicle vehCpy(first);
			REQUIRE(vehCpy == first);
		}
	}
}//scen

