#include "Catch2/catch_amalgamated.hpp"
// #define CATCH_CONFIG_MAIN  
// #include "catch.hpp"
#include "Vehicle.h"

TEST_CASE("Testing the relationship between Vehicle & Person", "[relationship]")
{
	SECTION("Testing from Vehicles' side")
	{
		Vehicle testCar(Registration("TX1007XT"), "James Bond's car");
		Person testPerson("James Bond", 1007);
		Person testNewOwner("Ernst Stavro Blofeld", 2015);

		WHEN("Setting owner")
		{
		    REQUIRE_NOTHROW(testCar.setOwner(testPerson));
			REQUIRE(testCar.getOwner() == (&testPerson));
		    REQUIRE(testCar.isOwned());
		    REQUIRE_FALSE(testCar.getOwner() == (&testNewOwner));
		}

	    WHEN("Changing owner")
	    {
	        REQUIRE_NOTHROW(testCar.setOwner(testPerson));	
	        REQUIRE(testCar.getOwner() == (&testPerson));
	        REQUIRE_NOTHROW(testCar.setOwner(testNewOwner));
	        REQUIRE(testCar.getOwner() == (&testNewOwner));
	    }

	    WHEN("Removing owner")
	    {
	        REQUIRE_NOTHROW(testCar.setOwner(testPerson));
	        REQUIRE_NOTHROW(testCar.removeOwner());
	        REQUIRE_FALSE(testCar.getOwner() == (&testPerson));

	    }

	}

	SECTION("Testing from Person's side")
	{
		Person human("Angel", 9234);

		Vehicle first(Registration("AA1234ww"), "Nice");
		Vehicle second(Registration("h9342rr"), "Good");
		// Vehicle first("", "");


		WHEN("Adding vehicles")
		{
			first.setOwner(human);
			second.setOwner(human);
			// REQUIRE_NOTHROW(first.setOwner(human));
			// REQUIRE_NOTHROW(second.setOwner(human));
			REQUIRE(human.doIPossessVehicles());
			REQUIRE(human.getOwnedVehNum() == 2);
			REQUIRE((human.vehiclePositionStorage(first) != -1) == true);
			REQUIRE((human.vehiclePositionStorage(second) != -1) == true);

			// REQUIRE_NOTHROW(human.removeAllOwnedVehicles());
			human.removeAllOwnedVehicles();

			REQUIRE_FALSE(human.doIPossessVehicles());
			REQUIRE(human.getOwnedVehNum() == 0);
			REQUIRE((human.vehiclePositionStorage(first) == -1) == true);
			REQUIRE((human.vehiclePositionStorage(second) == -1) == true);

		}

		WHEN("Inserting duplicates")
		{
			//first.setOwner(human);
			REQUIRE_NOTHROW(first.setOwner(human)); 
			first.setOwner(human);
			//REQUIRE_THROWS(first.setOwner(human));
			REQUIRE_NOTHROW(second.setOwner(human));
			//REQUIRE_THROWS(second.setOwner(human));

			Vehicle faulty(Registration("AA1234ww"), "Cool description");
			REQUIRE_THROWS(faulty.setOwner(human));

			REQUIRE(human.doIPossessVehicles());
			REQUIRE(human.getOwnedVehNum() == 2);

		}

		WHEN("Removing vehicles")
		{
			REQUIRE_NOTHROW(first.setOwner(human));
			REQUIRE(human.doIPossessVehicles());
			REQUIRE(human.getOwnedVehNum() == 1);
			REQUIRE((human.vehiclePositionStorage(first) != -1) == true);

			REQUIRE_NOTHROW(first.removeOwner());
			REQUIRE_FALSE(human.doIPossessVehicles());
			REQUIRE(human.getOwnedVehNum() == 0);
			REQUIRE((human.vehiclePositionStorage(first) == -1) == true);


		}

		WHEN("Inserting multiple vehicles (dynamic memory)")
		{
			std::vector<Vehicle*> testCars;
			std::string firstReg = "A0000BC";

			Vehicle* newTestCar = new Vehicle(firstReg, "Testing");

			REQUIRE_NOTHROW((*newTestCar).setOwner(human));
			testCars.push_back(newTestCar);

			// 999 different car plates (factory101)
			unsigned j = 0, k = 0, l = 0, t = 0;
			for (unsigned i = 1; i < 1000; ++i)
			{
				++j;
				// startingReg[1] = j;
				firstReg[1] = '0'+ t;
				firstReg[2] = '0' + k;
				firstReg[3] = '0' + l;
				firstReg[4] = '0' + j;

				if (j == 9) {
					j = 0;
					++l;
				}
				if (l == 9) {
					l = 0;
					++k;
				}
				if (k == 9) {
					k = 0;
					++t;
				}

				//++j;

				try
				{
					Vehicle* newTestCar = new Vehicle(firstReg, "Just Test");
					(*newTestCar).setOwner(human);
					//REQUIRE_NOTHROW((*newTestCar).setOwner(human));
					testCars.push_back(newTestCar);
					REQUIRE((human.vehiclePositionStorage(*newTestCar) != -1));
				}
				catch (const std::bad_alloc& e) { //allocation error
					std::cerr << e.what() << std::endl;
					for (unsigned m = 0; m < testCars.size(); ++m) {
						delete testCars[m];
					}
					testCars.clear();
					break;
				}
				catch (std::invalid_argument&) {
					i; j; k; l; t;
				
					std::cerr << "Vehicle with this car plate is already owned by this person!" << endl;
				}

			}

			THEN("Testing getting the number of cars")
			{
				REQUIRE(human.getOwnedVehNum() == 1000);
			}

			THEN("Testing removing all cars") {
				human.removeAllOwnedVehicles();
				REQUIRE(human.getOwnedVehNum() == 0);
				REQUIRE_FALSE(human.doIPossessVehicles());
			}

			for (short n = 0; n < testCars.size(); ++n) {
				delete testCars[n];
			}
			testCars.clear();

		}
	}

}
