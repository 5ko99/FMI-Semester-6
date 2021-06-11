#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../include/Vehicle.hpp"

using std::vector;

TEST_CASE("Validate vehicle test")
{
    Vehicle vehicle("AB1111AB", "Test vehicle 1");
    CHECK_THROWS(Vehicle("AB1111A", "Test vehicle 2"));
    CHECK_THROWS(Vehicle("11AAlk23", "Test vehicle 3"));
}

TEST_CASE("Validate person test")
{
    Person person("Ivan", 1);
    CHECK_THROWS(Person("Alex", 1));
    CHECK_NOTHROW("Ivan", 2);
}

TEST_CASE("Person vehicle relation test")
{
    Person person1("Person1", 3);
    Vehicle vehicle1("AB2222AB", "Test vehicle 1");
    person1.addCar(&vehicle1);

    Person person2("Person2", 4);
    person2.addCar(&vehicle1);
    REQUIRE(vehicle1.getOwner() == &person2);

    Vehicle vehicle2("AB1234AB", "Test vehicle 2");
    person2.addCar(&vehicle2);
    person1.addCar(&vehicle2);

    REQUIRE(vehicle2.getOwner() == &person1);

    vehicle2.setOwner(nullptr);
    REQUIRE(vehicle2.getOwner() == nullptr);
}
