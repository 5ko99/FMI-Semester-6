//#define CATCH_CONFIG_MAIN 
//#include"Catch.h"
//#include"Vehicle.h"
//
//
////Registration tests
////=============================================================================================
//TEST_CASE("Testing registration evaluation function", "[bool isValid(const string reg_num)]") {
//	Registration test("TE1234ST");
//	REQUIRE(test.Return_reg() == "TE1234ST");
//}
//
////Vehicle tests
////=============================================================================================
//
//TEST_CASE("Testing show registration function", "[string show_reg()]") {
//	string registration = "TE1234ST";
//	string description = "Description";
//	Vehicle test(registration, description);
//	REQUIRE(!registration.compare(test.show_reg()));
//}
//
//TEST_CASE("Testing show description function", "[string show_descr()]") {
//	string registration = "TE1234ST";
//	string description = "Description";
//	Vehicle test(registration, description);
//	REQUIRE(!description.compare(test.show_descr()));
//}
//
//TEST_CASE("Testing assign new owner function, and assign owner function", "[void assign_owner(size_t new_owner), size_t does_it_have_an_owner()]") {
//	string registration = "TE1234ST";
//	string description = "Description";
//	size_t new_owner_id = 69;
//	Vehicle test(registration, description);
//	REQUIRE(!test.does_it_have_an_owner());
//	test.assign_owner(new_owner_id);
//	REQUIRE(test.does_it_have_an_owner() == 69);
//}
//
//TEST_CASE("Testing remove owner function", "[void remove_owner()]") {
//	string registration = "TE1234ST";
//	string description = "Description";
//	size_t new_owner_id = 69;
//	Vehicle test(registration, description);
//	REQUIRE(!test.does_it_have_an_owner());
//	test.assign_owner(new_owner_id);
//	REQUIRE(test.does_it_have_an_owner());
//	test.remove_owner();
//	REQUIRE(!test.does_it_have_an_owner());
//}
