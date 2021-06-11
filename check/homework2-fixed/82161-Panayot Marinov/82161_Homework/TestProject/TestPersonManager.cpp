#include "catch2.hpp"
#include "../MainProject/Headers/Vehicle.h"
#include "../MainProject/Headers/PersonManager.h"

TEST_CASE("Tessting addPerson function") {
    SECTION("Testing with one person") {
        PersonManager pm;
        pm.addPerson("Ivan");
        Person* person = &(pm.at(0));
        REQUIRE((pm[0] == *person) == true);
        REQUIRE(pm.getNumberOfPeople() == 1);
    }

    SECTION("Testing with two people") {
        PersonManager pm;
        pm.addPerson("Ivan");
        pm.addPerson("Panayot Marinov");
        REQUIRE((pm[0].getId() == pm[1].getId()) == false);
        REQUIRE(pm.getNumberOfPeople() == 2);
    }
}

TEST_CASE("Tessting removePerson function") {
    SECTION("Testing with one person") {
        PersonManager pm;
        pm.addPerson("Ivan");
        size_t id = pm.at(0).getId();
        pm.removePerson(id);
        REQUIRE(pm.getNumberOfPeople() == 0);
    }

    SECTION("Testing with non-existing person") {
        PersonManager pm;
        REQUIRE_THROWS_AS(pm.removePerson(0), std::invalid_argument);
        CHECK_THROWS_AS(pm.removePerson(0), std::invalid_argument);
    }

    SECTION("Testing with 2 people which have vehicles") {
        PersonManager pm;
        Vehicle vehicle1("X5859KC", "BMW 530");
        Vehicle vehicle2("X9941AH", "Peugeot");
        pm.addPerson("Ivan");
        pm.addPerson("Panayot Marinov");
        pm.at(0).addVehicle(&vehicle2);
        pm.at(1).addVehicle(&vehicle1);
        size_t id = pm.at(0).getId();
        pm.removePerson(id);
        REQUIRE(pm.getNumberOfPeople() == 1);
    }
}

TEST_CASE("Tessting findPerson function") {
    SECTION("Testing with one person and size_t") {
        PersonManager pm;
        pm.addPerson("Ivan");
        size_t id = pm.at(0).getId();
        Person* pPointer = pm.findPerson(id);
        REQUIRE((*pPointer == pm.at(0)) == true);
    }

    SECTION("Testing with one person and string&") {
        PersonManager pm;
        pm.addPerson("Ivan");
        size_t id = pm.at(0).getId();
        Person* pPointer = pm.findPerson(std::to_string(id));
        REQUIRE((*pPointer == pm.at(0)) == true);
    }

    SECTION("Testing with non-existing person") {
        PersonManager pm;
        pm.addPerson("Ivan");
        size_t id = pm.at(0).getId();
        pm.removePerson(id);
        REQUIRE_THROWS_AS(pm.findPerson(std::to_string(id)), std::invalid_argument);
        CHECK_THROWS_AS(pm.findPerson(std::to_string(id)), std::invalid_argument);
    }

    SECTION("Testing with another non-existing person") {
        PersonManager pm;
        pm.addPerson("Ivan");
        size_t id = pm.at(0).getId();
        pm.removePerson(id);
        REQUIRE_THROWS_AS(pm.findPerson(id), std::invalid_argument);
        CHECK_THROWS_AS(pm.findPerson(id), std::invalid_argument);
    }

    SECTION("Testing with 2 people") {
        PersonManager pm;
        pm.addPerson("Ivan");
        pm.addPerson("Panayot Marinov");

        Person* person0 = &(pm.at(0));
        Person* person1 = &(pm.at(1));
        size_t id0 = pm.at(0).getId();
        size_t id1 = pm.at(1).getId();
        REQUIRE((*(pm.findPerson(id0)) == *person0) == true);
        REQUIRE((*(pm.findPerson(id1)) == *person1) == true);
    }
}

TEST_CASE("Tessting at function personManager") {
    SECTION("Testing with no people") {
        PersonManager pm;
        REQUIRE_THROWS_AS(pm.at(0), std::out_of_range);
        CHECK_THROWS_AS(pm.at(0), std::out_of_range);
    }
    
    SECTION("Testing with all people removed") {
        PersonManager pm;
        pm.addPerson("Ivan");
        pm.addPerson("Panayot Marinov");
        size_t id0 = pm.at(0).getId();
        size_t id1 = pm.at(1).getId();
        pm.removePerson(id1);
        pm.removePerson(id0);
        REQUIRE_THROWS_AS(pm.at(0), std::out_of_range);
        CHECK_THROWS_AS(pm.at(0), std::out_of_range);
        REQUIRE_THROWS_AS(pm.at(1), std::out_of_range);
        CHECK_THROWS_AS(pm.at(1), std::out_of_range);
    }
    
    SECTION("Testing with one person left") {
        PersonManager pm;
        pm.addPerson("Ivan");
        pm.addPerson("Panayot Marinov");
        size_t id = pm.at(1).getId();
        pm.removePerson(id);
        REQUIRE_THROWS_AS(pm.at(1), std::out_of_range);
        CHECK_THROWS_AS(pm.at(1), std::out_of_range);
    }

    SECTION("Testing with two people") {
        PersonManager pm;
        pm.addPerson("Ivan");
        pm.addPerson("Panayot Marinov");
        REQUIRE_THROWS_AS(pm.at(2), std::out_of_range);
        CHECK_THROWS_AS(pm.at(2), std::out_of_range);
    }
}
