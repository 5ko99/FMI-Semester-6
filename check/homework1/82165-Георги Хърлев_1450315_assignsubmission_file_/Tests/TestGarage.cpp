#define CATCH_CONFIG_MAIN  
#include <cstring>
#include "catch.hpp"
#include "Garage.h"


SCENARIO("Testing all Garage functions")
{
	GIVEN("Testing for size constructor")
	{
		const size_t size = 10;
		Garage garage(10);
		THEN("Check for data being set correctly after creation") //not much that can be tested here
		{
			REQUIRE(garage.size() == 0);
		}
		WHEN("Add Vehicles untill it's full")
		{//10=1+2+3+4
			Vehicle** veh;
			try {
				veh = new Vehicle * [4];
			}
			catch (std::exception& e)
			{
				return;
			}
			char* newChar = new char[] {"XAB12"};
			for (short i = 0; i < 4; i++)
			{
				newChar[0] = i + 10;
				veh[i] = new Vehicle(newChar, "Ala Bala", i + 1);
				garage.insert(*veh[i]);
			}
			THEN("Check if everything is set correct")
			{
				for (short i = 0; i < 4; i++)
				{
					CHECK(garage[i] == *veh[i]);
					CHECK(garage[i].space() == veh[i]->space());
				}
			}
			THEN("Check if we can add cars to full garage")
			{
				Vehicle lastOne("XXX123", "Jigula", 1);
				//REQUIRE_THROWS_AS(garage.insert(lastOne), int );
				try {
					garage.insert(lastOne);
				}
				catch (int& i)
				{

					REQUIRE(i == 0); //no space
				}
			}
			THEN("Check is erase function works")
			{
				newChar[0] = 10; //first elemenet
				short oldSize = garage.size();
				Vehicle firstVeh(garage[0]);
				garage.erase(newChar);
				REQUIRE_FALSE(garage[0] == firstVeh);
				REQUIRE(garage.size()+1 == oldSize);
				THEN("Check if we can add a car with already existing registration")
				{

					try {
						garage.insert(*veh[0]);
					}
					catch (int& i)
					{
						REQUIRE(i == 1); //already exist
					}
				}
			}
			THEN("Test clear function ")
			{
				garage.clear();
				REQUIRE(garage.size() == 0);
				for (int i = 0; i < 4; i++)
				{
					REQUIRE(&garage[i]==nullptr);
				}
			}
			THEN("Testing operator =")
			{
				//garage.clear();
				Garage newGr(3);
				newGr = garage;
				REQUIRE(newGr.size() == garage.size());
				for (int i = 0; i < 4; i++)
				{
					REQUIRE(&garage[i] == &newGr[i]);
				}
				THEN("Testing operator ==") {
					REQUIRE(newGr == garage);
				}
				
			}
			THEN("Testing move assignment")
			{
				Garage newGr(std::move(Garage (3)));
				Vehicle first("AC12", "first car", 1);
				Vehicle second("DC34", "Second car", 2);
				REQUIRE_NOTHROW(newGr.insert(first));
				REQUIRE(newGr[0] == first);
				REQUIRE_NOTHROW(newGr.insert(second));
				REQUIRE(newGr[1] == second);
				REQUIRE(newGr.size() == 2);
				REQUIRE_THROWS_AS(newGr.insert(first), int);

			}
			THEN("Testing move assign operator =")
			{
				const short currentSize = garage.size();
				Garage newGr(2);
				newGr= std::move(garage);
				REQUIRE(garage.empty());
				REQUIRE(newGr.size() == currentSize);
				for (short i = 0; i < currentSize; i++)
				{
					REQUIRE(&newGr[i] != nullptr);
				}
			}
		}//when until its full
		

	}//given


}//scen