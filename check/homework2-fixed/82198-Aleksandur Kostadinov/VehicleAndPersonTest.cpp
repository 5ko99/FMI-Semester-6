#include "VehicleAndPerson.h"
#include "catch2.hpp"

TEST_CASE("VEHICLE CREATION")
{
    Registration reg1("AA2345DS");
    Registration reg2("WE2785D");
    Registration reg3("aa2345ds");
    Registration reg4("A5645ER");
    Registration reg5("55ABSS43");
    Registration reg6("AAA");
    Registration reg7("12345678");

    Vehicle vehicle1("audi", reg1);
    Vehicle vehicle2("audi", reg2);
    Vehicle vehicle3("audi", reg3);
    Vehicle vehicle4("", reg4);

    REQUIRE(vehicle1.get_desc() == "audi");
    REQUIRE(vehicle2.get_desc() == "");
    REQUIRE(vehicle3.get_desc() == "");
    REQUIRE(vehicle4.get_desc() == "");

    REQUIRE(vehicle1.get_id() == reg1);
    REQUIRE_FALSE(vehicle2.get_id() == reg1);
    REQUIRE(vehicle3.get_id() == reg2);
    REQUIRE_FALSE(vehicle4.get_id() == reg4);

    REQUIRE(Vehicle::existing_vehicles.size() == 1);

    Vehicle vehicle9("bmw", reg1);

    REQUIRE(Vehicle::existing_vehicles.size() == 1);
}

TEST_CASE("PEOPLE CREATION")
{
    Person p1("Jeff", 1);
    Person p2("Jeff", 0);
    Person p3("", 12);
    Person p4("Sasho", 123);

    REQUIRE(p1.get_name() == "Jeff");
    REQUIRE(p2.get_name() == "");
    REQUIRE(p3.get_name() == "");
    REQUIRE(p4.get_name() == "Sasho");

    REQUIRE(p1.get_id() == 1);
    REQUIRE(p2.get_id() == 0);
    REQUIRE(p3.get_id() == 0);
    REQUIRE(p4.get_id() == 123);

    REQUIRE(Person::existing_people.size() == 2);

    Person p5(p1);
    Person p6(p2);
    Person p7(p3);
    Person p8(p4);

    REQUIRE(p5.get_name() == "Jeff");
    REQUIRE(p6.get_name() == "");
    REQUIRE(p7.get_name() == "");
    REQUIRE(p8.get_name() == "Sasho");

    REQUIRE(p5.get_id() == 1);
    REQUIRE(p6.get_id() == 0);
    REQUIRE(p7.get_id() == 0);
    REQUIRE(p8.get_id() == 123);

    REQUIRE(Person::existing_people.size() == 2);

    p1 = p3;
    p2 = p6;
    p5 = p4;
    p8 = p2;

    REQUIRE(p1.get_name() == "");
    REQUIRE(p2.get_name() == "");
    REQUIRE(p5.get_name() == "Sasho");
    REQUIRE(p8.get_name() == "");

    REQUIRE(p1.get_id() == 0);
    REQUIRE(p2.get_id() == 0);
    REQUIRE(p5.get_id() == 123);
    REQUIRE(p8.get_id() == 0);

    Person p9("Josh", 123);

    REQUIRE(Person::existing_people.size() == 2);
}

TEST_CASE("ADDING OWNERS, VEHICLES AND RELEASING THEM")
{
    Registration reg1("AC2345DD");
    Registration reg2("WE2785SD");
    Registration reg3("WS2345ER");
    Registration reg4("A1778ER");

    Vehicle vehicle1("toyota", reg1);
    Vehicle vehicle2("nissan", reg2);
    Vehicle vehicle3("bmw", reg3);
    Vehicle vehicle4("opel", reg4);

    Person p1("Steve", 145);
    Person p2("Kasho", 155);
    Person p3("Mark", 126);
    Person p4("Iva", 331);

    REQUIRE(vehicle1.get_owner() == nullptr);
    REQUIRE(vehicle2.get_owner() == nullptr);
    REQUIRE(vehicle3.get_owner() == nullptr);
    REQUIRE(vehicle4.get_owner() == nullptr);

    REQUIRE(get_all_vehicles(&p1).size() == 0);
    REQUIRE(get_all_vehicles(&p2).size() == 0);
    REQUIRE(get_all_vehicles(&p3).size() == 0);
    REQUIRE(get_all_vehicles(&p4).size() == 0);

    vehicle1.add_owner(p1);
    vehicle2.add_owner(p2);
    vehicle3.add_owner(p3);
    vehicle4.add_owner(p4);

    REQUIRE(vehicle1.get_owner() == &p1);
    REQUIRE(vehicle2.get_owner() == &p2);
    REQUIRE(vehicle3.get_owner() == &p3);
    REQUIRE(vehicle4.get_owner() == &p4);

    REQUIRE(get_all_vehicles(&p1).size() == 1);
    REQUIRE(get_all_vehicles(&p2).size() == 1);
    REQUIRE(get_all_vehicles(&p3).size() == 1);
    REQUIRE(get_all_vehicles(&p4).size() == 1);

    /* vehicle1.add_owner(p3);
    vehicle1.add_owner(p2);

    REQUIRE(vehicle1.get_owner() == &p2);
    REQUIRE(vehicle2.get_owner() == &p2);
    REQUIRE(vehicle3.get_owner() == &p3);

    REQUIRE(get_all_vehicles(&p1).size() == 0);
    REQUIRE(get_all_vehicles(&p2).size() == 2);
    REQUIRE(get_all_vehicles(&p3).size() == 1); */

    vehicle1.release_owner();
    vehicle2.release_owner();

    REQUIRE(vehicle1.get_owner() == nullptr);
    REQUIRE(vehicle2.get_owner() == nullptr);
    REQUIRE(get_all_vehicles(&p1).size() == 0);
    REQUIRE(get_all_vehicles(&p2).size() == 0);

    REQUIRE(vehicle1.get_desc() == "toyota");
    REQUIRE(vehicle2.get_desc() == "nissan");
    REQUIRE(vehicle1.get_id() == reg1);
    REQUIRE(vehicle2.get_id() == reg2);

    vehicle3.add_owner(p4);

    REQUIRE(vehicle3.get_owner() == &p3);
    REQUIRE(get_all_vehicles(&p3).size() == 1);

    vehicle1.add_owner(p1);

    REQUIRE(vehicle1.get_owner() == &p1);
    REQUIRE(get_all_vehicles(&p1).size() == 1);

    /*  p3.add_vehicle(vehicle1);
    p3.add_vehicle(vehicle2);

    REQUIRE(vehicle1.get_owner() == &p3);
    REQUIRE(vehicle2.get_owner() == &p3);
    REQUIRE(get_all_vehicles(&p3).size() == 3); */

    /* vehicle1.add_owner(p3);
    vehicle2.add_owner(p3);

    REQUIRE(vehicle1.get_owner() == &p3);
    REQUIRE(vehicle2.get_owner() == &p3);
    REQUIRE(get_all_vehicles(&p3).size() == 3); */

    Registration reg5("QC5745DD");
    Registration reg6("WD2685SD");
    Registration reg7("ZX2354ER");
    Registration reg8("S1458ER");

    Vehicle vehicle5("toyota", reg5);
    Vehicle vehicle6("nissan", reg6);
    Vehicle vehicle7("bmw", reg7);
    Vehicle vehicle8("opel", reg8);

    Person p5("Steve", 1456);

    p5.add_vehicle(vehicle5);
    p5.add_vehicle(vehicle6);
    p5.add_vehicle(vehicle7);
    p5.add_vehicle(vehicle8);

    REQUIRE(get_all_vehicles(&p5).size() == 4);
    REQUIRE(vehicle5.get_owner() == &p5);
    REQUIRE(vehicle6.get_owner() == &p5);
    REQUIRE(vehicle7.get_owner() == &p5);
    REQUIRE(vehicle8.get_owner() == &p5);
    /*
  
    REQUIRE(vehicle5.get_owner() == &p5);
    REQUIRE(vehicle6.get_owner() == &p5);
    REQUIRE(vehicle7.get_owner() == &p5);
    REQUIRE(vehicle8.get_owner() == &p5);

     */
}

TEST_CASE("IS_FREE TESTING")
{
    Registration reg6("AB3685SD");
    Registration reg7("ZX2352KL");
    Registration reg8("S1433ER");

    Vehicle vehicle5("toyota", reg8);
    Vehicle vehicle6("nissan", reg6);
    Vehicle vehicle7("bmw", reg7);

    Person p1("Jack", 789);
    Person p2("Sarah", 23451);
    Person p3("Michael", 676);

    REQUIRE(vehicle5.is_free() == true);
    REQUIRE(vehicle6.is_free() == true);
    REQUIRE(vehicle7.is_free() == true);

    vehicle5.add_owner(p1);
    vehicle6.add_owner(p2);
    vehicle7.add_owner(p3);

    REQUIRE(vehicle5.is_free() == false);
    REQUIRE(vehicle6.is_free() == false);
    REQUIRE(vehicle7.is_free() == false);

    vehicle7.release_owner();
    vehicle6.release_owner();
    p1.add_vehicle(vehicle6);

    REQUIRE(vehicle6.is_free() == false);
    REQUIRE(vehicle7.is_free() == true);
}

TEST_CASE("REMOVE VEHILCE/PERSON")
{
    Registration reg6("AQ6865SD");
    Registration reg7("ZR2352KL");
    Registration reg8("S2833ER");

    Vehicle vehicle5("toyota", reg8);
    Vehicle vehicle6("nissan", reg6);
    Vehicle vehicle7("bmw", reg7);

    Person p1("Jacki", 7890);
    Person p2("Sarah", 9182);
    Person p3("Ken", 666);

    Person::existing_people[Person::existing_people.size() - 1].add_vehicle(vehicle5);
    Person::existing_people[Person::existing_people.size() - 1].add_vehicle(vehicle6);

    Person::remove_person(666);

    REQUIRE(Vehicle::existing_vehicles[Vehicle::existing_vehicles.size() - 3].get_owner() == nullptr);
    REQUIRE(Vehicle::existing_vehicles[Vehicle::existing_vehicles.size() - 2].get_owner() == nullptr);
   
    Person::existing_people[Person::existing_people.size() - 2].add_vehicle(vehicle7);
    REQUIRE(get_all_vehicles(&Person::existing_people[Person::existing_people.size() - 2]).size() == 1);
   
}
