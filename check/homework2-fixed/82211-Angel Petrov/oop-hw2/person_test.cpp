#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch2.hpp"
#include "person.h"
#include "vehicle.h"

TEST_CASE ("constructors, operator=, getID") {

    Person test, test2("name", 1);
    Person test3(test2);

    CHECK(test.getID() == 0);
    CHECK(test2.getID() == 1);
    CHECK(test3.getID() == 1);

    test = test3;

    CHECK(test.getID() == test3.getID());
}

TEST_CASE("addVehicle, releaseVehicle, accessors") {

    Person test("name", 1);
    Vehicle car;

    test.addVehicle(car);
    CHECK(test.getNumberOfVehiclesOwned() == 1);

    std::vector<Vehicle*> testVehicles = test.getVehicles();

    CHECK(testVehicles[0]->getLicensePlate() == car.getLicensePlate());
    test.releaseVehicle(car.getLicensePlate());
    CHECK(test.getNumberOfVehiclesOwned() == 0);
}
