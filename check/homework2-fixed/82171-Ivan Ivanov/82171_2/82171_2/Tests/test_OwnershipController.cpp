// #define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../OwnershipController/OwnershipController.h"
#include "../CustomExceptions/VehicleException/VehicleException.h"

SCENARIO("Testing acquiring a vehicle which does not have an owner") {
    GIVEN("A person and a vehicle") {
        std::string testPersonName = "test person's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";
        
        Vehicle testVehicle(testRegistration, testDescriptionValue);

        WHEN("Vehicle is acquired") {
            OwnershipController::acquireVehicle(*testVehicle, *testPerson);

            THEN("Ownership on both ends is correct") {
                VehiclePtr* ownedVehicles = testPerson.getVehicles();

                REQUIRE(testVehicle.getOwner() == *testPerson);
                REQUIRE(testPerson.getVehiclesCount() == 1);
                REQUIRE(ownedVehicles[0] == *testVehicle);

                delete[] ownedVehicles;
            }
        }
    }

    GIVEN("A person owning three vehicles and a forth vehicle") {
        std::string testPersonName = "test person's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        std::string testRegistrationValueA = "tt0000AA";
        Registration testRegistrationA(testRegistrationValueA);
        std::string testDescriptionValueA = "test description A";
        Vehicle testVehicleA(testRegistrationA, testDescriptionValueA);

        std::string testRegistrationValueB = "tt0000BB";
        Registration testRegistrationB(testRegistrationValueB);
        std::string testDescriptionValueB = "test description B";
        Vehicle testVehicleB(testRegistrationB, testDescriptionValueB);

        std::string testRegistrationValueC = "tt0000CC";
        Registration testRegistrationC(testRegistrationValueC);
        std::string testDescriptionValueC = "test description C";
        Vehicle testVehicleC(testRegistrationC, testDescriptionValueC);

        std::string testRegistrationValueD = "tt0000DD";
        Registration testRegistrationD(testRegistrationValueD);
        std::string testDescriptionValueD = "test description D";
        Vehicle testVehicleD(testRegistrationD, testDescriptionValueD);

        OwnershipController::acquireVehicle(*testVehicleA, *testPerson);
        OwnershipController::acquireVehicle(*testVehicleB, *testPerson);
        OwnershipController::acquireVehicle(*testVehicleC, *testPerson);

        WHEN("The forth one is acquired") {
            THEN("An exception is thrown and nothing is changed") {
                VehiclePtr* ownedVehicles = testPerson.getVehicles();
            
                REQUIRE(testVehicleA.getOwner() == *testPerson);
                REQUIRE(testVehicleB.getOwner() == *testPerson);
                REQUIRE(testVehicleC.getOwner() == *testPerson);
                REQUIRE(testPerson.getVehiclesCount() == 3);
                REQUIRE(ownedVehicles[0] == *testVehicleA);
                REQUIRE(ownedVehicles[1] == *testVehicleB);
                REQUIRE(ownedVehicles[2] == *testVehicleC);
                
                delete[] ownedVehicles;
            }
        }
    }
}

SCENARIO("Testing acquiring a vehicle which has an owner") {
    GIVEN("Two people and a vehicle, belonging to one of them") {
        std::string testPersonNameA = "test person's name A";
        unsigned int testPersonIDA = 1;
        Person testPersonA(testPersonNameA, testPersonIDA);

        std::string testPersonNameB = "test person's name B";
        unsigned int testPersonIDB = 2;
        Person testPersonB(testPersonNameB, testPersonIDB);

        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";
        
        Vehicle testVehicle(testRegistration, testDescriptionValue);

        OwnershipController::acquireVehicle(*testVehicle, *testPersonA);

        WHEN("Vehicle is acquired by the other person") {
            OwnershipController::acquireVehicle(*testVehicle, *testPersonB);

            THEN("Ownership on both ends is correct") {
                VehiclePtr* ownedVehicles = testPersonB.getVehicles();
            
                REQUIRE(testVehicle.getOwner() == *testPersonB);
                REQUIRE(testPersonA.getVehiclesCount() == 0);
                REQUIRE(testPersonB.getVehiclesCount() == 1);
                REQUIRE(ownedVehicles[0] == *testVehicle);
                
                delete[] ownedVehicles;
            }
        }
    }
}

SCENARIO("Testing releasing a vehicle") {
    GIVEN("A person and a vehicle") {
        std::string testPersonName = "test person's name";
        unsigned int testPersonID = 1;
        Person testPerson(testPersonName, testPersonID);

        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";
        
        Vehicle testVehicle(testRegistration, testDescriptionValue);

        WHEN("Vehicle is acquired and then released by passing both vehicle and owner") {
            OwnershipController::acquireVehicle(*testVehicle, *testPerson);
            OwnershipController::releaseVehicle(*testVehicle, *testPerson);

            THEN("Ownership on both ends is correct") {
                REQUIRE(testVehicle.getOwner() == nullptr);
                REQUIRE(testPerson.getVehiclesCount() == 0);
            }
        }

        WHEN("Vehicle is acquired and then released by passing only the vehicle") {
            OwnershipController::acquireVehicle(*testVehicle, *testPerson);
            OwnershipController::releaseVehicle(*testVehicle);

            THEN("Ownership on both ends is correct") {
                REQUIRE(testVehicle.getOwner() == nullptr);
                REQUIRE(testPerson.getVehiclesCount() == 0);
            }
        }

        WHEN("Vehicle is acquired and then released by passing only the owner") {
            OwnershipController::acquireVehicle(*testVehicle, *testPerson);
            OwnershipController::releaseVehiclesOf(*testPerson);

            THEN("Ownership on both ends is correct") {
                REQUIRE(testVehicle.getOwner() == nullptr);
                REQUIRE(testPerson.getVehiclesCount() == 0);
            }
        }

        WHEN("The vehicle does not belong to the person") {
            THEN("Releasing it by passing both person and vehicle throws an exception and does not change anything") {
                REQUIRE_THROWS_AS(OwnershipController::releaseVehicle(*testVehicle, *testPerson), PersonException);
                REQUIRE(testVehicle.getOwner() == nullptr);
                REQUIRE(testPerson.getVehiclesCount() == 0);
            }

            AND_THEN("Releasing it by passing only the vehicle throws an exception and does not change anything") {
                REQUIRE_NOTHROW(OwnershipController::releaseVehicle(*testVehicle));
                REQUIRE(testVehicle.getOwner() == nullptr);
                REQUIRE(testPerson.getVehiclesCount() == 0);
            }

            AND_THEN("Releasing the vehicles owned by the person throws an exception and does not change anything") {
                REQUIRE_NOTHROW(OwnershipController::releaseVehiclesOf(*testPerson));
                REQUIRE(testVehicle.getOwner() == nullptr);
                REQUIRE(testPerson.getVehiclesCount() == 0);
            }
        }
    }
}
