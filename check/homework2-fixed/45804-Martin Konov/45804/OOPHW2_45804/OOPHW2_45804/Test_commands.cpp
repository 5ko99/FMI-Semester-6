//#define CATCH_CONFIG_MAIN 
//#include"Catch.h"
//#include "Commands.h"
//
//TEST_CASE("Testing constructor", "[Commands(string start_cmd)]") {
//	Commands test("VEHICLE TE1234ST descr");
//	string first_cmd = "VEHICLE";
//	string second_cmd = "TE1234ST";
//	string third_cmd = "descr";
//
//
//	REQUIRE(test.split_command[0] == first_cmd);
//	REQUIRE(test.split_command[1] == second_cmd);
//	REQUIRE(test.split_command[2] == third_cmd);
//
//	REQUIRE(test.main_cmd() == first_cmd);
//	REQUIRE(test.list_of_used_commands[0] == "VEHICLE TE1234ST descr");
//
//	test.list_of_used_commands.clear();
//}
//
//TEST_CASE("Testing constructor 2", "[Commands(string start_cmd)]") {
//	Commands test("PERSON \"Ivan Ivanov\" 123");
//	string first_cmd = "PERSON";
//	string third_cmd = "123";
//
//	REQUIRE(test.split_command[0] == first_cmd);
//	REQUIRE(test.split_command[1] == "\"Ivan");
//	REQUIRE(test.split_command[2] == "Ivanov\"");
//	REQUIRE(test.split_command[3] == "123");
//
//}
//
//TEST_CASE("Testing function, that converts all the chars in a string to capital letters", "[void capitals(string& src)]") {
//	Commands test("");
//	string first_cmd = "PeRsOn";
//	test.capitals(first_cmd);
//	
//	
//	REQUIRE(first_cmd == "PERSON");
//}
//
//TEST_CASE("Testing return main command function", "[string main_cmd()]") {
//	Commands test("PERSON \"Ivan Ivanov\" 123");
//
//	string first_cmd = "PERSON";
//	string second_cmd = "iLoVeFmI";
//
//	REQUIRE(test.main_cmd() == first_cmd);
//	REQUIRE(test.main_cmd() != second_cmd);
//}
