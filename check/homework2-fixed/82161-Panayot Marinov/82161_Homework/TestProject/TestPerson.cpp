#include "catch2.hpp"
#include "../MainProject/Headers/Person.h"
#include "../MainProject/Headers/Vehicle.h"
#include <string>
#include <cstring>

using std::string;

TEST_CASE( "Person instances can be created correctly") {
    SECTION("Testing constructor with char*") {
        Person person("Ivan Draganov");
        REQUIRE(strcmp(person.getName(), "Ivan Draganov") == 0);
        REQUIRE(person.getNumberOfVehicles() == 0);
    }

    SECTION("Testing constructor with string") {
        Person person(string("Ivan Draganov"));
        REQUIRE(strcmp(person.getName(), "Ivan Draganov") == 0);
        REQUIRE(person.getNumberOfVehicles() == 0);
    }
}
TEST_CASE( "Testing Person operator=") {
    SECTION("Testing with 2 objects") {
        Person person(string("Ivan Draganov"));
        Person person2("Kalin kalinov");
        person2 = person;
        REQUIRE(strcmp(person2.getName(), "Ivan Draganov") == 0);
        REQUIRE(person2.getNumberOfVehicles() == 0);
    }
}

TEST_CASE( "Testing Person operator==") {
    SECTION("Testing with non-equal objects") {
        Person person(string("Ivan Draganov"));
        Person person2("Kalin kalinov");
        REQUIRE((person2 == person) == false);
    }

    SECTION("Testing with another non-equal objects") {
        Person person(string("Ivan Draganov"));
        Person person2(string("Ivan Draganov"));
        REQUIRE((person2 == person) == false);
    }

    SECTION("Testing operator== with another equal objects") {
        Person person(string("Ivan Draganov"));
        Person* person1ref = &person;
        Person* person2ref = &person;
        REQUIRE(((*person1ref) == (*person2ref)) == true);
    }
}

TEST_CASE("Testing Person addVehicle() function") {
    SECTION("Testing with one vehicle") {
        Person person(string("Ivan Draganov"));
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        person.addVehicle(&vehicle);
        REQUIRE(person.getNumberOfVehicles() == 1);
    }
}

TEST_CASE("Testing Person removeVehicle() function") {
    SECTION("Testing with one vehicle") {
        Person person(string("Ivan Draganov"));
        Vehicle vehicle("CA1111AA", "A simple vehicle");
        person.addVehicle(&vehicle);
        person.removeVehicle(&vehicle);
        REQUIRE(person.getNumberOfVehicles() == 0);
    }
}
