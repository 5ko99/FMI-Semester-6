#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Program.h"

using std::cin;
using std::cout;
using std::endl;

SCENARIO("Program input and setting test")
{
	GIVEN("Declaring program") {

		Program program(10);

		WHEN("Testing garage capacity input")
		{
			cout << "Size_t input test , input a number :";
			size_t cap = program.inputSizeT();
			std::cout << "Your input:" << cap << endl;
		}
		WHEN("Teting input_isStrBiggerOrEqual")
		{
			REQUIRE(program.input_isStrBiggerOrEqual("1234", "1233"));
			REQUIRE(program.input_isStrBiggerOrEqual("12345", "12345"));
			REQUIRE_FALSE(program.input_isStrBiggerOrEqual("123456789", "123457899"));//will print
		}
		WHEN("Testing input_isValidNum")
		{
			cout << "-----------------------Num Validation------------------------------\n";
			if (std::numeric_limits<size_t>::max() == std::numeric_limits<unsigned int>::max()) {
				THEN("Case of unsigned int") {
					char str[] = "4294967296";
					char str2[] = "4294967295";
					REQUIRE_FALSE(program.input_isValidNum(str));
					REQUIRE(program.input_isValidNum(str2));

				}
			}
			else if (std::numeric_limits<size_t>::max() == std::numeric_limits<unsigned long long>::max())
			{
				THEN("Case of u long long") {
					char str[] = "18446744073709551616";
					char str2[] = "18446744073709551615";
					REQUIRE_FALSE(program.input_isValidNum(str));
					REQUIRE(program.input_isValidNum(str2));
				}
			}
		}
		WHEN("Testing input_convertToNum")
		{
			char str1[] = "4294967295";
			REQUIRE(program.input_convertToNum(str1) == 4294967295);
			str1[0] = '0';
			str1[1] = '\0';
			REQUIRE(program.input_convertToNum(str1) == 0);
		}
		WHEN("Testing input_Choice")
		{
			cout << "----------------------------------------------------------\n";
			cout << "(Testing choice input . -Expected to enter form 1 to 10-)\n";
			size_t choice = program.input_Choice(10);
			cout << "Your choice :" << choice << endl;
		}
		WHEN("Testing vehicle creation (createVehicle) to unparked cars")
		{
			cout << "----------------------------------------------------------\n";
			cout << "(Testing car creation)\n";
			program.createVehicle();
			Vehicle** cars = program.getUnparkedCars();
			const Vehicle newVeh((*cars[0])); //creating a copy
			cout << "\nThe data:\n";
			REQUIRE_NOTHROW(cars[0]->printInfo());
			REQUIRE(program.getUnparkedCarsNum() == 1);
			THEN("Testing addVehicleToGarage after creation")
			{
				cout << "----------------------------------------------------------\n";
				cout << "(Testing car moving to garage from unparked)\n";
				bool moved = true;
				try {
					program.addVehicleToGarage();
				}
				catch (int& i)
				{
					if (i == 0)
					{
						cout << "No space in garage throw :" << i << endl;
						REQUIRE((*cars[0]).space() > 10);
						moved = false;

					}
					else if (i == 1)
					{
						throw 1;
						//we have no other cars . That shouldn't happen
					}
					else if (i == -1)
					{
						//"Memory error.Could not allocate";
						throw - 1;
					}
				}
				if (moved) {
					CHECK(cars[0] == nullptr);
					REQUIRE(program.getUnparkedCarsNum() == 0);
					REQUIRE(program.getGarageSize() == 1);
					REQUIRE(program.getGarageVehAt(0) == newVeh);
					cout << "(Successfully moved)\n";
				}
				else {
					REQUIRE(*cars[0] == newVeh);
					REQUIRE(program.getUnparkedCarsNum() == 1);
					REQUIRE(program.getGarageSize() == 0);
					REQUIRE(&program.getGarageVehAt(0) == nullptr);
					cout << "(Did not move it)\n";
				}

			}
		}
		WHEN("Testing createAndAddVehicle ")
		{
			cout << "----------------------------------------------------------\n";
			cout << "(Testing car creation and then adding it to the garage)\n";
			program.createAndAddVehicle();
			bool isTrue = (program.getGarageSize() == 1 || program.getUnparkedCarsNum() == 1);
			//either added to garage or had no place and was added to unparked instead
			REQUIRE(isTrue);
			
			if (program.getGarageSize() == 0)
			{
				cout << "Created car:";
				Vehicle** cars = program.getUnparkedCars();
				cars[0]->printInfo();
				return;
			}
			cout << "Added car:";
			program.getGarageVehAt(0).printInfo();
			THEN("Testing removeVehicle from garage and add to unparked")
			{
				cout << "----------------------------------------------------------\n";
				cout << "(Testing car removing and then adding it to the unparked)\n";
				program.removeVehicle();
				REQUIRE(program.getGarageSize() == 0);
				REQUIRE(program.getUnparkedCarsNum() == 1);

				THEN("Testing destroying Vehicle")
				{
					cout << "----------------------------------------------------------\n";
					cout << "(Testing vehicle destruction )\n";

					program.destroyVeh();
					REQUIRE(program.getUnparkedCarsNum() == 0);
					Vehicle** cars = program.getUnparkedCars();
					REQUIRE(cars[0] == nullptr);

				}
			}
			/*THEN("Testing destroying Vehicle")
			{
				cout << "----------------------------------------------------------\n";
				cout << "(Testing vehicle destruction after a few move additions)\n";

				program.destroyVeh();
				REQUIRE()

			}*/
		}
	}

}//scenario
