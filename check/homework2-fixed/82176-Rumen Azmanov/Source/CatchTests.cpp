#define CATCH_CONFIG_MAIN
#include <assert.h>

#include <cstring>
#include <iostream>

#include "../Headers/Command.hpp"
#include "../Headers/Person.hpp"
#include "../Headers/Registration.hpp"
#include "../Headers/Vehicle.hpp"
#include "../catch2/catch2.hpp"

TEST_CASE("Tests of Registration") {
    std::vector<Person> mypeople;
    std::vector<Vehicle> myvehicles;
    Command mycommand(&mypeople, &myvehicles);

    SECTION("Compare strings") {
        Registration myregistration1("AB0000CD");
        Registration myregistration2("EF1234GH");
        Registration myregistration3("IJ5678KL");

        REQUIRE(strcmp(myregistration1.getRegistration(), "AB0000CD") == 0);
        REQUIRE(strcmp(myregistration2.getRegistration(), "EF1234GH") == 0);
        REQUIRE(strcmp(myregistration3.getRegistration(), "IJ5678KL") == 0);
    }

    SECTION("Error already existing registration") {
        char redCarID[] = "RR0000AA";
        char redCar[] = "Red car";
        char yellowCarID[] = "YY1111BB";
        char yellowCar[] = "Yellow car";
        char blueCarID[] = "BB2222CC";
        char blueCar[] = "Blue car";

        mycommand.createVehicle(redCarID, redCar);
        mycommand.createVehicle(yellowCarID, yellowCar);
        mycommand.createVehicle(blueCarID, blueCar);

        char blackSubmarineID[] = "BB3333DD";
        char blackSubmarine[] = "Black submarine";
        REQUIRE_THROWS_AS(myvehicles.push_back(Vehicle(yellowCarID, blackSubmarine)), std::invalid_argument);
        REQUIRE_THROWS_AS(myvehicles.push_back(Vehicle(yellowCarID, blackSubmarine)), std::invalid_argument);
        REQUIRE_THROWS_AS(Vehicle(yellowCarID, blackSubmarine), std::invalid_argument);
    }

    SECTION("Error invalid registrations") {
        char whiteAirplaneID0[] = "WW3333DD";
        char whiteAirplaneID1[] = "WWW333DD";
        char whiteAirplaneID2[] = "WW333DDD";
        char whiteAirplaneID3[] = "W33333DD";
        char whiteAirplaneID4[] = "WW33333D";
        char whiteAirplane[] = "White airplain";

        REQUIRE_THROWS_AS(myvehicles.push_back(Vehicle(whiteAirplaneID1, whiteAirplane)), std::invalid_argument);
        REQUIRE_THROWS_AS(myvehicles.push_back(Vehicle(whiteAirplaneID2, whiteAirplane)), std::invalid_argument);
        REQUIRE_THROWS_AS(myvehicles.push_back(Vehicle(whiteAirplaneID3, whiteAirplane)), std::invalid_argument);
        REQUIRE_THROWS_AS(myvehicles.push_back(Vehicle(whiteAirplaneID4, whiteAirplane)), std::invalid_argument);
    }
}

TEST_CASE("Tests of Person and Vehicle") {
    std::vector<Person> mypeople2;
    std::vector<Vehicle> myvehicles2;

    SECTION("Create vehicle") {
        char regNumber[9] = "MN0000OP";
        char descriptionVehicle[] = "Description of vehicle";
        Vehicle myvehicle1(regNumber, descriptionVehicle);

        REQUIRE(strcmp(myvehicle1.getRegistration().getRegistration(), "MN0000OP") == 0);
        REQUIRE(strcmp(myvehicle1.getDescription().c_str(), "Description of vehicle") == 0);
    }

    SECTION("Create person") {
        char personName[] = "Name Name";
        unsigned int personID = 1234;
        Person myperson1(personName, personID);

        REQUIRE(strcmp(myperson1.getName().c_str(), "Name Name") == 0);
        REQUIRE(myperson1.getIdentifier() == 1234);
    }

    SECTION("Aquire") {
        char personName[] = "Name Name";
        unsigned int personID = 5678;
        Person myperson2(personName, personID);

        char regNumber[9] = "MN5678OP";
        char descriptionVehicle[] = "Description of vehicle";
        Vehicle myvehicle2(regNumber, descriptionVehicle);

        myperson2.acquireVehicleToPerson(&myvehicle2);
        myvehicle2.acquireVehicle(&myperson2);

        REQUIRE(strcmp(myperson2.getOwnedVehicles().at(0)->getRegistration().getRegistration(), "MN5678OP") == 0);
        REQUIRE(myvehicle2.getOwner()->getIdentifier() == 5678);

        myperson2.releaseVehicle(myvehicle2.getRegistration().getRegistration());
        myperson2.emptyVehicle();
        myvehicle2.freeVehicle();

        REQUIRE(myperson2.getOwnedVehicles().size() == 0);
        REQUIRE(myvehicle2.getOwner() == nullptr);
    }
}

TEST_CASE("Tests of Command") {
    std::vector<Person> mypeople3;
    std::vector<Vehicle> myvehicles3;
    Command mycommand3(&mypeople3, &myvehicles3);

    SECTION("Commands") {
        char operation1[] = "PERSON Person1000Name 1000";
        char operation2[] = "PERSON Person2000Name 2000";
        char operation3[] = "PERSON Person3000Name 3000";
        char operation4[] = "VEHICLE AA1000AA VehicleA";
        char operation5[] = "VEHICLE BB1000BB VehicleB";
        char operation6[] = "VEHICLE CC2000CC VehicleC";
        char operation7[] = "AQUIRE 1000 AA1000AA";
        char operation8[] = "AQUIRE 1000 BB1000BB";
        char operation9[] = "AQUIRE 2000 CC2000CC";

        mycommand3.setCommandLine(operation1);
        mycommand3.setCommandLine(operation2);
        mycommand3.setCommandLine(operation3);
        mycommand3.setCommandLine(operation4);
        mycommand3.setCommandLine(operation5);
        mycommand3.setCommandLine(operation6);
        mycommand3.setCommandLine(operation7);
        mycommand3.setCommandLine(operation8);
        mycommand3.setCommandLine(operation9);

        REQUIRE(mypeople3.at(0).getIdentifier() == 1000);
        REQUIRE(strcmp(myvehicles3.at(0).getRegistration().getRegistration(), "AA1000AA") == 0);
        REQUIRE(strcmp(mypeople3.at(0).getOwnedVehicles().at(0)->getRegistration().getRegistration(), "AA1000AA") == 0);
        REQUIRE(myvehicles3.at(0).getOwner()->getIdentifier() == 1000);

        REQUIRE(mypeople3.at(0).getOwnedVehicles().size() == 2);
        REQUIRE(mypeople3.at(1).getOwnedVehicles().size() == 1);
        REQUIRE(mypeople3.at(2).getOwnedVehicles().size() == 0);

        char operation10[] = "RELEASE 1000 AA1000AA";
        mycommand3.setCommandLine(operation10);
        REQUIRE(mypeople3.at(0).getOwnedVehicles().size() == 1);

        char operation11[] = "REMOVE 3000";
        mycommand3.setCommandLine(operation11);
        char operation12[] = "REMOVE CC2000CC";
        mycommand3.setCommandLine(operation12);
        REQUIRE(mypeople3.size() == 2);
        REQUIRE(myvehicles3.size() == 2);
    }
}
