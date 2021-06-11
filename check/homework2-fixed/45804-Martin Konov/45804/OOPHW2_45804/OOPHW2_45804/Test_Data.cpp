//#define CATCH_CONFIG_MAIN 
//#include"Catch.h"
//#include "Data.h"
//
//TEST_CASE("Testing create a vehicle function", "[void create_veh()]") {
//
//	string registration = "TE1234ST";
//	string description = "description";
//
//	Data test(registration, description);
//
//	test.create_veh();
//
//	REQUIRE(test.list_of_created_vehicles.size() == 1);
//	REQUIRE(test.list_of_created_vehicles[0].show_reg() == registration);
//	REQUIRE(test.list_of_created_vehicles[0].show_descr() == description);
//
//	CHECK_THROWS(test.create_veh());
//
//	test.remove_if_veh(registration);
//}
//
//TEST_CASE("Testing create a person function", "[void create_person()]") {
//	
//	string name = "Test subject";
//	size_t id = 10;
//	
//	Data test(name, id);
//	
//	test.create_person();
//
//	REQUIRE(test.list_of_created_people.size() == 1);
//	REQUIRE(test.list_of_created_people[0].show_id() == id);
//	REQUIRE(test.list_of_created_people[0].show_name() == name);
//
//	CHECK_THROWS(test.create_person());
//
//	test.remove_if_person(id);
//}
//
//TEST_CASE("testing acquire function", "[void acquire(const size_t id, const string registration)]") {
//	
//	string name = "Test subject";
//	size_t id = 10;
//	Data person(name, id);
//	person.create_person();
//
//	string registration = "TE1234ST";
//	string description = "description";
//
//	Data vehicle(registration, description);
//	vehicle.create_veh();
//
//
//	Data test("", "");
//	test.acquire(id, registration);
//
//	REQUIRE(person.list_of_created_people[0].list_of_owned_vehicles[0] == registration);
//
//	REQUIRE(vehicle.list_of_created_vehicles[0].does_it_have_an_owner() == id);
//
//	CHECK_THROWS(test.acquire(id, registration));
//
//
//
//	test.release(id, registration);
//	person.remove_if_person(id);
//	vehicle.remove_if_veh(registration);
//}
//
//TEST_CASE("Testing release function", "[void release(const size_t id, const string registration)]") {
//
//	string name = "Test subject";
//	size_t id = 10;
//	Data person(name, id);
//	person.create_person();
//
//	string registration = "TE1234ST";
//	string description = "description";
//
//	Data vehicle(registration, description);
//	vehicle.create_veh();
//
//
//	Data test("", "");
//	test.acquire(id, registration);
//
//	REQUIRE(person.list_of_created_people[0].list_of_owned_vehicles[0] == registration);
//	REQUIRE(vehicle.list_of_created_vehicles[0].does_it_have_an_owner() == id);
//
//	test.release(id, registration);
//
//	REQUIRE(person.list_of_created_people[0].list_of_owned_vehicles.size() == 0);
//	REQUIRE(vehicle.list_of_created_vehicles[0].does_it_have_an_owner() == 0);
//
//	CHECK_THROWS(test.release(id, registration));
//
//	person.remove_if_person(id);
//	vehicle.remove_if_veh(registration);
//
//}
//
//TEST_CASE("Testing the remove function if remove person", "[void remove_if_person(const size_t id)]") {
//	string name = "Test subject";
//	size_t id = 10;
//	Data person(name, id);
//	person.create_person();
//
//	Data test("", "");
//
//	REQUIRE(test.list_of_created_people.size() == 1);
//	REQUIRE(test.list_of_created_people[0].show_id() == id);
//	REQUIRE(test.list_of_created_people[0].show_name() == name);
//
//
//	test.remove_if_person(id);
//
//	REQUIRE(test.list_of_created_people.size() == 0);
//}
//
//TEST_CASE("Testing the remove function if remove vehicle", "[void remove_if_veh(const string registration)]") {
//	string registration = "TE1234ST";
//	string description = "description";
//
//	Data vehicle(registration, description);
//	vehicle.create_veh();
//
//	Data test("", "");
//
//	REQUIRE(test.list_of_created_vehicles.size() == 1);
//	REQUIRE(test.list_of_created_vehicles[0].show_reg() == registration);
//	REQUIRE(test.list_of_created_vehicles[0].show_descr() == description);
//
//	test.remove_if_veh(registration);
//
//	REQUIRE(test.list_of_created_vehicles.size() == 0);
//}
//
