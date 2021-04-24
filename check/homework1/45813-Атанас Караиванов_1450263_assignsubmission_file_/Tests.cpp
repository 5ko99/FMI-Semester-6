/*#define CATCH_CONFIG_MAIN 
#pragma once
#include "Catch2.hpp"
#include "Garage.hpp"

//MyString Tests:
TEST_CASE("Creates new object of MyString") {

	MyString str("Test text");
	MyString str2("");

	REQUIRE(strcmp(str.c_str(), "Test text") == 0);
	REQUIRE(strcmp(str2.c_str(), "") == 0);
}

TEST_CASE("Access to the element in position") {

	MyString str("Test text");
	MyString str2("a");
	MyString str3("");

	REQUIRE(str2.at(0) == 'a');
	REQUIRE(str.at(3) == 't');
	
	REQUIRE_THROWS(str.at(-1));
	REQUIRE_THROWS(str.at(9));
	REQUIRE_THROWS(str3.at(1));
}

TEST_CASE("Access to the element in position with []") {

	MyString str("Test text");
	MyString str2("a");
	MyString str3("");

	REQUIRE(str2[0] == 'a');
	REQUIRE(str[3] == 't');

	REQUIRE_THROWS(str[-1]);
	REQUIRE_THROWS(str[9]);
	REQUIRE_THROWS(str3[1]);
}

TEST_CASE("Access to the first element") {

	MyString str("Test text");
	MyString str2("");

	REQUIRE(str.front() == 'T');

	REQUIRE_THROWS(str2.front());
}

TEST_CASE("Access to the last element") {

	MyString str("Test text");
	MyString str2("");

	REQUIRE(str.back() == 't');

	REQUIRE_THROWS(str2.back());
}

TEST_CASE("Checks if the string is empty") {

	MyString str("");
	MyString str2("Test text");

	REQUIRE(str.empty() == true);
	REQUIRE(str2.empty() == false);
}

TEST_CASE("Checks the lenght of the string") {

	MyString str("");
	MyString str2("Test text");

	REQUIRE(str.size() == 0);
	REQUIRE(str2.size() == strlen("Test text"));
}

TEST_CASE("Clears the string") {

	MyString str("Test text");
	MyString str2("");

	str.clear();
	str2.clear();

	REQUIRE(str.c_str() == nullptr);
	REQUIRE(str2.c_str() == nullptr);
}

TEST_CASE("Adds a character at the end of the string") {

	MyString str("Test tex");
	MyString str2("");

	str.push_back('t');
	str2.push_back('T');

	REQUIRE(strcmp(str.c_str(), "Test text") == 0);
	REQUIRE(strcmp(str2.c_str(), "T") == 0);
}

TEST_CASE("Removes the last character from the string") {

	MyString str("Test textt");
	MyString str2("T");

	str.pop_back();
	str2.pop_back();

	REQUIRE(strcmp(str.c_str(), "Test text") == 0);
	REQUIRE(strcmp(str2.c_str(), "") == 0);
}

TEST_CASE("Adds a character at the end of the string with +=") {

	MyString str("Test tex");
	MyString str2("");

	str += 't';
	str2 += 'T';

	REQUIRE(strcmp(str.c_str(), "Test text") == 0);
	REQUIRE(strcmp(str2.c_str(), "T") == 0);
}

TEST_CASE("Adds a character at the end of the string with + ,and returns the new string") {

	MyString str("Test tex");
	MyString str2("");

	str = str + 't';
	str2 = str2 + 'T';

	REQUIRE(strcmp(str.c_str(), "Test text") == 0);
	REQUIRE(strcmp(str2.c_str(), "T") == 0);
}

TEST_CASE("Adds a new string at the end of the string with + ,and returns the new string") {

	MyString str("Test text");
	MyString str2("Second test text");
	MyString str3("");

	str = str + str2 + str3;

	REQUIRE(strcmp(str.c_str(), "Test textSecond test text") == 0);
}

TEST_CASE("Returns a pointer to an array of type char, which has content identical to that of the string") {

	MyString str("Test text");
	MyString str2("");

	REQUIRE(strcmp(str.c_str(), "Test text") == 0);
	REQUIRE(strcmp(str2.c_str(), "") == 0);
}

TEST_CASE("Checks if two character strings are the same") {

	MyString str("Test text");
	MyString str2("");
	MyString str3("Test text");
	MyString str4("");

	REQUIRE((str4 == str2) == 1);
	REQUIRE((str == str3) == 1);
	REQUIRE((str == str2) == 0);
}

TEST_CASE("Checks whether the current string precedes lexicographically rhs") {

	MyString str("Test text");
	MyString str2("");
	MyString str3("Test text");

	REQUIRE((str < str2) == 1);
	REQUIRE((str < str3) == 0);
	REQUIRE((str2 < str) == 0);
}

//Vehicle Tests:
TEST_CASE("Creates the new object of Vehicle") {
	Vehicle veh("CA1234HA", "Mercedes C 320", 2);

	REQUIRE(strcmp(veh.registration(), "CA1234HA") == 0);
	REQUIRE(strcmp(veh.description(), "Mercedes C 320") == 0);
	REQUIRE(veh.space() == 2);
}

TEST_CASE("Returns registration, description and space") {
	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("", "", 0);

	REQUIRE(strcmp(veh1.registration(), "CA1234HA") == 0);
	REQUIRE(strcmp(veh1.description(), "Mercedes C 320") == 0);
	REQUIRE(veh1.space() == 2);
	REQUIRE(strcmp(veh2.registration(), "") == 0);
	REQUIRE(strcmp(veh2.description(), "") == 0);
	REQUIRE(veh2.space() == 0);
}

//Garage Test:
TEST_CASE("Creates the new object of Garage and inserts vehicle to the garage") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	REQUIRE(gar.size() == 2);
}

TEST_CASE("Erases vehicle from the garage") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	gar.erase("CA1234HA");
	REQUIRE(gar.size() == 1);

	gar.erase("CA1234HA");
	REQUIRE(gar.size() == 1);

	gar.erase("Some text");
	REQUIRE(gar.size() == 1);
}

TEST_CASE("Access to the vehicle in position") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	REQUIRE(strcmp(gar.at(0).registration(), "CA1234HA")==0);
	REQUIRE(strcmp(gar.at(0).description(), "Mercedes C 320")==0);
	REQUIRE(gar.at(0).space()== 2);
	REQUIRE(strcmp(gar.at(1).registration(), "EH9876PA") == 0);
	REQUIRE(strcmp(gar.at(1).description(), "BMW 520") == 0);
	REQUIRE(gar.at(1).space() == 3);

	REQUIRE_THROWS(strcmp(gar.at(3).registration(), "EH9876PA") == 0);
	REQUIRE_THROWS(strcmp(gar.at(3).description(), "BMW 520") == 0);
	REQUIRE_THROWS(gar.at(3).space() == 3);
	REQUIRE_THROWS(strcmp(gar.at(-3).registration(), "EH9876PA") == 0);
	REQUIRE_THROWS(strcmp(gar.at(-3).description(), "BMW 520") == 0);
	REQUIRE_THROWS(gar.at(-3).space() == 3);
}

TEST_CASE("Access to the vehicle in position with []") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	REQUIRE(strcmp(gar[0].registration(), "CA1234HA") == 0);
	REQUIRE(strcmp(gar[0].description(), "Mercedes C 320") == 0);
	REQUIRE(gar[0].space() == 2);
	REQUIRE(strcmp(gar[1].registration(), "EH9876PA") == 0);
	REQUIRE(strcmp(gar[1].description(), "BMW 520") == 0);
	REQUIRE(gar[1].space() == 3);

	REQUIRE_THROWS(strcmp(gar[3].registration(), "EH9876PA") == 0);
	REQUIRE_THROWS(strcmp(gar[3].description(), "BMW 520") == 0);
	REQUIRE_THROWS(gar[3].space() == 3);
	REQUIRE_THROWS(strcmp(gar[-3].registration(), "EH9876PA") == 0);
	REQUIRE_THROWS(strcmp(gar[-3].description(), "BMW 520") == 0);
	REQUIRE_THROWS(gar[-3].space() == 3);
}

TEST_CASE("Checks is the garage empty") {
	Garage gar(5);
	REQUIRE(gar.empty() == 1);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	REQUIRE(gar.empty() == 0);

	gar.erase("CA1234HA");
	REQUIRE(gar.empty() == 0);

	gar.erase("EH9876PA");
	REQUIRE(gar.empty() == 1);
}

TEST_CASE("Returns the number of vehicles in the garage") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	REQUIRE(gar.size() == 2);

	gar.erase("CA1234HA");
	REQUIRE(gar.size() == 1);

	gar.erase("EH9876PA");
	REQUIRE(gar.size() == 0);

	Garage gar2(10);
	REQUIRE(gar2.size() == 0);
}

TEST_CASE("Removes all vehicles in the garage keeping the capacity the same") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("EH9876PA", "BMW 520", 3);

	gar.insert(veh1);
	gar.insert(veh2);

	gar.clear();
	REQUIRE(gar.size() == 0);

	gar.insert(veh1);
	REQUIRE(gar.size() == 1);
	REQUIRE(strcmp(gar.at(0).registration(), "CA1234HA") == 0);
	REQUIRE(strcmp(gar.at(0).description(), "Mercedes C 320") == 0);
	REQUIRE(gar.at(0).space() == 2);
	REQUIRE(strcmp(gar[0].registration(), "CA1234HA") == 0);
	REQUIRE(strcmp(gar[0].description(), "Mercedes C 320") == 0);
	REQUIRE(gar[0].space() == 2);

	gar.insert(veh2);
	
	REQUIRE_THROWS(gar.insert(veh2));
}

TEST_CASE("Finds a vehicle in the garage") {
	Garage gar(5);

	Vehicle veh1("CA1234HA", "Mercedes C 320", 2);
	Vehicle veh2("", "", 0);

	gar.insert(veh1);
	gar.insert(veh2);

	REQUIRE(strcmp(gar.find("CA1234HA")->registration(), "CA1234HA") == 0);
	REQUIRE(strcmp(gar.find("CA1234HA")->description(), "Mercedes C 320")==0);
	REQUIRE(gar.find("CA1234HA")->space() == 2);
	REQUIRE(strcmp(gar.find("")->registration(), "") == 0);
	REQUIRE(strcmp(gar.find("")->description(), "") == 0);
	REQUIRE(gar.find("")->space() == 0);
	REQUIRE(gar.find("Invalid text") == nullptr);
}*/