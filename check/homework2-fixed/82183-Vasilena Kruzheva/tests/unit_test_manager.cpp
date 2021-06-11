#include <cstring>
#include <fstream>
#include <iostream>
#include "../lib/catch.hpp"
#include "../include/manager.hpp"

using std::fstream;

TEST_CASE("Testing manager")
{
    Manager manager;
    Person p1("Ivan Georgiev", 123123);
    Person p2("Ivanka Petrova", 123121);

    Vehicle v1("C1234AF", "Beautiful magenda car!");
    Vehicle v2("FA2144FA", "Beautiful orange car!");

    REQUIRE(manager.getPeopleCount() == 0);
    REQUIRE(manager.getVehiclesCount() == 0);

    manager.addPerson(p1.getName(), p1.getID());
    REQUIRE(manager.getPeopleCount() == 1);
    REQUIRE_THROWS_AS(manager.addPerson("Georgi Ivanov", p1.getID()), std::invalid_argument);
    REQUIRE(manager.getPeopleCount() == 1);


    manager.addVehicle(v1.getRegistration(), v1.getDescription());
    REQUIRE(manager.getVehiclesCount() == 1);
    REQUIRE_THROWS_AS(manager.addVehicle(v1.getRegistration(), "Beautiful magenda car!2"), std::invalid_argument);
    REQUIRE(manager.getVehiclesCount() == 1);

    REQUIRE_THROWS_AS(manager.remove("123122"), std::invalid_argument);
    REQUIRE_THROWS_AS(manager.remove("VA1242FD"), std::invalid_argument);

    manager.addPerson(p2.getName(), p2.getID());
    manager.addVehicle(v2.getRegistration(), v2.getDescription());
    
    REQUIRE(manager.getPeopleCount() == 2);
    REQUIRE(manager.getVehiclesCount() == 2);
}
