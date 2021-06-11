#include "Commands.h"
#include "catch2.hpp"

TEST_CASE("Do person testing")
{
    Commands com1("person Ivan 1");
    Commands com2("PERSON Ivann 2");
    Commands com3("PERSON Ivannn 1");
    Commands com4("Person Ivannnn 0");
    Commands com5("pERsoN 12");
    Commands com6("person Sasho");
    Commands com7("pes Sasho 123");

    com1.do_command();
    com2.do_command();
    com3.do_command();
    com4.do_command();
    com5.do_command();
    com6.do_command();
    com7.do_command();

    REQUIRE(Person::existing_people.size() == 2);
    REQUIRE(Person::existing_people[0].get_name() == "Ivan");
    REQUIRE(Person::existing_people[1].get_name() == "Ivann");
}

TEST_CASE("Do vehicle testing")
{
    Commands com1("VEHICLE v1 AA1111AA");
    Commands com2("vehicle v2 BB2222BB");
    Commands com3("Vehicle v3 AA1111AA");
    Commands com4("VEhiclE v4 A1234DS");
    Commands com5("vEHicLE v5");
    Commands com6("vehicle AS3456UJ");
    Commands com7("vehis audi AS3456UJ");

    com1.do_command();
    com2.do_command();
    com3.do_command();
    com4.do_command();
    com5.do_command();
    com6.do_command();
    com7.do_command();

    REQUIRE(Vehicle::existing_vehicles.size() == 3);
    REQUIRE(Vehicle::existing_vehicles[0].get_desc() == "v1");
    REQUIRE(Vehicle::existing_vehicles[1].get_desc() == "v2");
    REQUIRE(Vehicle::existing_vehicles[2].get_desc() == "v4");
}

TEST_CASE("Acquire Testing")
{

    Commands com11("ACQUIRE 1 AA1111AA");
    Commands com12("ACQUIRE 2 BB2222BB");
    Commands com13("ACQUIRE 1 A1234DS");
    Commands com14("ACQUIRE 1 BB2222BB");
    Commands com15("ACUIRE 2 BB2222BB");

    com11.do_command();
    com12.do_command();
    com13.do_command();
    com14.do_command();

    REQUIRE(get_all_vehicles(&Person::existing_people[0]).size() == 3);
    REQUIRE(get_all_vehicles(&Person::existing_people[1]).size() == 0);
}

TEST_CASE("Release Tesing")
{
    Commands com11("RELEASE 1 AA1111AA");
    Commands com12("release 2 BB2222BB");
    Commands com13("release 1 BB2222BB");
    Commands com14("relesaase 1 A1234DS");

    com11.do_command();
    com12.do_command();
    com13.do_command();
    com14.do_command();

    REQUIRE(get_all_vehicles(&Person::existing_people[0]).size() == 1);
    REQUIRE(get_all_vehicles(&Person::existing_people[1]).size() == 0);
}

TEST_CASE("rEMOVE TESTING")
{
    Commands com11("REmove 1");
    Commands com12("reMOve 2");
    Commands com13("removE 3");
    Commands com14("remove A1234DS");
    Commands com15("remove DQ1234DS");
    Commands com16("remove AZ4534DS");
    Commands com17("remo BB2222BB");

    com11.do_command();
    com12.do_command();
    com13.do_command();
    com14.do_command();

    com15.do_command();
    com16.do_command();
    com17.do_command();

    REQUIRE(Vehicle::existing_vehicles.size() == 2);
    REQUIRE(Person::existing_people.size() == 0);
}
