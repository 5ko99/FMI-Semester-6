// #define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Vehicle/Vehicle.h"
#include "../Person/Person.h"


SCENARIO("Testing copy constructor of vehicle", "[copy]") {
    GIVEN("aA valid vehicle") {
        std::string testRegistrationValueA = "tt0000AA";
        Registration testRegistrationA(testRegistrationValueA);
        std::string testDescriptionValueA = "test description A";

        std::string testOwnerNameA = "test owner's name A";
        unsigned int testOwnerIDA = 1;
        Person testOwnerA(testOwnerNameA, testOwnerIDA);

        Vehicle testVehicleA(testRegistrationA, testDescriptionValueA);
        testVehicleA.setOwner(*testOwnerA);

        WHEN("Another is created through copy constructor") {
            Vehicle testVehicleB(testVehicleA);

            THEN("The registrations and the owners are equal") {
                REQUIRE(testVehicleA.getRegistration() == testVehicleB.getRegistration());
                REQUIRE(testVehicleA.getOwner() == testVehicleB.getOwner());
            }
        }
    }
}

SCENARIO("Testing copy assignment of vehicle", "[copy]") {
    GIVEN("Two valid vehicles") {
        std::string testRegistrationValueA = "tt0000AA";
        Registration testRegistrationA(testRegistrationValueA);
        std::string testDescriptionValueA = "test description A";

        std::string testOwnerNameA = "test owner's name A";
        unsigned int testOwnerIDA = 1;
        Person testOwnerA(testOwnerNameA, testOwnerIDA);

        std::string testRegistrationValueB = "tt0000BB";
        Registration testRegistrationB(testRegistrationValueB);
        std::string testDescriptionValueB = "test description B";

        std::string testOwnerNameB = "test owner's name B";
        unsigned int testOwnerIDB = 2;
        Person testOwnerB(testOwnerNameB, testOwnerIDB);

        Vehicle testVehicleA(testRegistrationA, testDescriptionValueA);
        Vehicle testVehicleB(testRegistrationB, testDescriptionValueB);

        testVehicleA.setOwner(*testOwnerA);
        testVehicleB.setOwner(*testOwnerB);

        WHEN("Assignment operator is used") {
            testVehicleB = testVehicleA;

            THEN("The registrations are equal") {
                REQUIRE(testVehicleA.getRegistration() == testVehicleB.getRegistration());
                REQUIRE(testVehicleA.getOwner() == testVehicleB.getOwner());
            }
        }
    }
}

SCENARIO("Testing getters", "[getters]") {
    GIVEN("A valid vehicle") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        THEN("The getters return the rigth values") {
            REQUIRE(testVehicle.getRegistration() == testRegistrationValue);
            REQUIRE(testVehicle.getOwner() == nullptr);
        } 

        WHEN("An owner is set") {
            std::string testOwnerName = "test owner's name";
            unsigned int testOwnerID = 1;
            Person testOwner(testOwnerName, testOwnerID);

            testVehicle.setOwner(*testOwner);

            THEN("The getters return the rigth values") {
                REQUIRE(testVehicle.getRegistration() == testRegistrationValue);
                REQUIRE(testVehicle.getOwner() == *testOwner);
            }
        }
    }
}

SCENARIO("Testing setting owner", "[owner]") {
    GIVEN("A valid vehicle") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        WHEN("An owner is set") {
            std::string testOwnerName = "test owner's name";
            unsigned int testOwnerID = 1;
            Person testOwner(testOwnerName, testOwnerID);

            testVehicle.setOwner(*testOwner);

            THEN("The owner is set right") {
                REQUIRE(testVehicle.getOwner() == *testOwner);
            }
        }
    }
}

SCENARIO("Testing clearing owner", "[owner]") {
    GIVEN("A valid vehicle with a set owner") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        std::string testOwnerName = "test owner's name";
        unsigned int testOwnerID = 1;
        Person testOwner(testOwnerName, testOwnerID);

        testVehicle.setOwner(*testOwner);

        WHEN("The owner is cleared") {
            testVehicle.clearOwner();

            THEN("The car has no owner") {
                REQUIRE(testVehicle.getOwner() == nullptr);
            }

            AND_WHEN("The owner of a not owned is cleared") {
                THEN("The function throw esception") {
                    REQUIRE_THROWS_AS(testVehicle.clearOwner(), VehicleException);
                }
            }
        }
    }
}

SCENARIO("Testing getting pointer (operator*) to vehicle", "[operator]") {
    GIVEN("A valid vehicle") {
        std::string testRegistrationValue = "tt0000AA";
        Registration testRegistration(testRegistrationValue);
        std::string testDescriptionValue = "test description";

        Vehicle testVehicle(testRegistration, testDescriptionValue);

        THEN("The methods can be called through the pointer") {
            REQUIRE((*testVehicle)->getRegistration() == testRegistrationValue);
            REQUIRE((*testVehicle)->getOwner() == nullptr);
        }
    }
}
