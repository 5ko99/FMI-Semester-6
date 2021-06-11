// #define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../../ObjectHolders/VehicleHolder/VehicleHolder.h"

SCENARIO("Testing getting vehicle by registration", "[getters]") {
    GIVEN("A holder and a vehicle in it") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        VehicleHolder vH;
        vH.add(testVehicle);

        WHEN("A registration, which belongs to a vehicle in the holder, is searched") {
            Vehicle* resultVehicle = vH.getByRegistration(testRegistrationValue);
            THEN("The returned vehicle has the same name and id") {
                REQUIRE(resultVehicle->getDescription() == testDescriptionValue);
                REQUIRE(resultVehicle->getRegistration() == testRegistrationValue);
            }
        }

        WHEN("An Registration, which does not belong to a vehicle in the holder, is searched") {
            std::string wrongRegistrationValue = "tt0000BB";
            Registration wrongRegistration(wrongRegistrationValue);
            THEN("An exception is thrown") {
                REQUIRE_THROWS_AS(vH.getByRegistration(wrongRegistration), VehicleException);
            }
        }
    }
}

SCENARIO("Testing getting all vehicles", "[getters]") {
    GIVEN("A holder and a vehicle in it") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        VehicleHolder vH;
        vH.add(testVehicle);

        WHEN("A getter for all vehicles is called") {
            std::vector<Vehicle> resultVehicles = vH.getAllVehicles();
            THEN("The returned vector is right") {
                REQUIRE(resultVehicles.size() == 1);
                REQUIRE(resultVehicles.at(0).getRegistration() == testRegistrationValue);
            }
        }
    }
}

SCENARIO("Testing adding vehicles", "[add]") {
    GIVEN("A holder and a vehicle, which is not in the holder") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        VehicleHolder vH;

        WHEN("The vehicle is added") {
            vH.add(testVehicle);
            THEN("The vehicle can be found in the holder") {
                std::vector<Vehicle> resultVehicles = vH.getAllVehicles();

                REQUIRE(resultVehicles.size() == 1);
                REQUIRE(resultVehicles.at(0).getRegistration() == testRegistrationValue);
            }

            AND_WHEN("The same vehicle is added again") {
                THEN("An exception is thrown") {
                    REQUIRE_THROWS_AS(vH.add(testVehicle), VehicleException);
                }
            }
        }
    }
}

SCENARIO("Testing removing vehicles by registration", "[remove]") {
    GIVEN("A holder and two vehicles, one of which is in the holder") {
        std::string testRegistrationValueA = "tt0000AA";
        Registration testRegistrationA(testRegistrationValueA);
        std::string testDescriptionValueA = "test description A";

        Vehicle testVehicleA(testRegistrationA, testDescriptionValueA);

        VehicleHolder vH;
        vH.add(testVehicleA);

        std::string testRegistrationValueB = "tt0000BB";
        Registration testRegistrationB(testRegistrationValueB);
        std::string testDescriptionValueB = "test description B";

        Vehicle testVehicleB(testRegistrationB, testDescriptionValueB);

        WHEN("The vehicle in the holder is released") {
            vH.removeByRegistration(testRegistrationA);
            THEN("The vehicle cannot be found in the holder and the vector's size has changed") {
                std::vector<Vehicle> resultVehicles = vH.getAllVehicles();

                REQUIRE(resultVehicles.size() == 0);

                REQUIRE_THROWS_AS(vH.getByRegistration(testRegistrationA), VehicleException);
            }
        }

        WHEN("The vehicle which is not in the holder is removed") {
            THEN("An exception is thrown") {
                REQUIRE_THROWS_AS(vH.removeByRegistration(testRegistrationB), VehicleException);
            }
        }
    }
}

SCENARIO("Testing getting pointer (operator*) to vehicle Holder", "[operator]") {
    GIVEN("A holder and a vehicle in it") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        VehicleHolder vH;
        vH.add(testVehicle);

        WHEN("A function as called through a pointer to the holder") {
            Vehicle* resultVehicle = (*vH)->getByRegistration(testRegistrationValue);
            THEN("The returned result is valid") {
                REQUIRE(resultVehicle->getDescription() == testDescriptionValue);
                REQUIRE(resultVehicle->getRegistration() == testRegistrationValue);
            }
        }
    }
}
