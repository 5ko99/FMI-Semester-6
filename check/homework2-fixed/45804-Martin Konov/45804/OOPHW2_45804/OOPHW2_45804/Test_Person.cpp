//#define CATCH_CONFIG_MAIN 
//#include"Catch.h"
//#include "Person.h"
//
//
//TEST_CASE("Testing show id function", "[size_t show_id()]") {
//	Person test_subject("Name", 420);
//	size_t id = 420;
//	size_t wrong_id = 69;
//	REQUIRE(id == test_subject.show_id());
//	REQUIRE(!(wrong_id == test_subject.show_id()));
//}
//
//TEST_CASE("Testing show name function", "[string show_name()]") {
//	Person test_subject("Name", 420);
//	string name = "Name";
//	string wrong_name = "emaN";
//	REQUIRE(!name.compare(test_subject.show_name()));
//	REQUIRE(wrong_name.compare(test_subject.show_name()));
//}
//
//TEST_CASE("Testing add vehicle function", "[void add_vehicle(const string veh_id_to_add)]") {
//	Person test_subject("Name", 420);
//	string veh_registration = "TE1234ST";
//	string second_veh_registration = "TE9876ST";
//	
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 0);
//	
//	test_subject.add_vehicle(veh_registration);
//	
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 1);
//	
//	test_subject.add_vehicle(second_veh_registration);
//	
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 2);
//}
//
//TEST_CASE("Testing remove vehicle function", "[void remove_vehicle(const string veh_to_remove)]") {
//	Person test_subject("Name", 420);
//	string veh_registration = "TE1234ST";
//	string second_veh_registration = "TE9876ST";
//
//	CHECK_THROWS(test_subject.remove_vehicle("TE1234ST"));
//
//	test_subject.add_vehicle(veh_registration);
//
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 1);
//
//	test_subject.remove_vehicle(veh_registration);
//
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 0);
//
//	test_subject.add_vehicle(veh_registration);
//	test_subject.add_vehicle(second_veh_registration);
//
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 2);
//
//	test_subject.remove_vehicle(veh_registration);
//
//	REQUIRE(test_subject.list_of_owned_vehicles.size() == 1);
//	REQUIRE(test_subject.list_of_owned_vehicles[0] == second_veh_registration);
//
//}
//
//TEST_CASE("Testing check position function", "[size_t check_pos_for_veh_to_remove(const string veh_to_remove)]") {
//	Person test_subject("Name", 420);
//	string veh_registration = "TE1234ST";
//	string second_veh_registration = "TE9876ST";
//	test_subject.add_vehicle(veh_registration);
//	test_subject.add_vehicle(second_veh_registration);
//
//	REQUIRE(test_subject.check_pos_for_veh_to_remove(second_veh_registration) == 1); 
//
//	REQUIRE(test_subject.check_pos_for_veh_to_remove(veh_registration) == 0);
//}
