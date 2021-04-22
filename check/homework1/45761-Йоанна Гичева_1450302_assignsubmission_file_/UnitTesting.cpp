#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

#include <iostream>
#include "../Homework1/Garage.hpp"
#include "../Homework1/Vehicle.hpp"
#include "../Homework1/MyString.hpp"


TEST_CASE("Garage_CLEAR", "[garage]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);
	Vehicle vehicle2 = Vehicle("UC12436", "Tesla X", 2);
	Vehicle vehicle3 = Vehicle("UC12438", "MASSIVE BIG BUS", 4);
	Garage garage = Garage(32);
	garage.insert(vehicle);
	garage.insert(vehicle2);
	garage.insert(vehicle3);

	garage.clear();

	REQUIRE(garage.size() == 0);
}

TEST_CASE("Garage_OPERATOR[]", "[garage]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);
	Vehicle vehicle2 = Vehicle("UC12436", "Tesla X", 2);
	Vehicle vehicle3 = Vehicle("UC12438", "MASSIVE BIG BUS", 4);
	Garage garage = Garage(32);
	garage.insert(vehicle);
	garage.insert(vehicle2);
	garage.insert(vehicle3);

	const Vehicle result = garage[2];

	REQUIRE(result.description()[0] == 'M');
	REQUIRE(result.description()[3] == 'S');
	REQUIRE(result.description()[14] == 'S');
	REQUIRE(result.space() == 4);
}

TEST_CASE("Garage_AT", "[garage]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);
	Vehicle vehicle2 = Vehicle("UC12436", "Tesla X", 2);
	Vehicle vehicle3 = Vehicle("UC12438", "MASSIVE BIG BUS", 4);
	Garage garage = Garage(32);
	garage.insert(vehicle);
	garage.insert(vehicle2);
	garage.insert(vehicle3);

	const Vehicle result = garage.at(2);

	REQUIRE(result.description()[0] == 'M');
	REQUIRE(result.description()[3] == 'S');
	REQUIRE(result.description()[14] == 'S');
	REQUIRE(result.space() == 4);
}
TEST_CASE("Garage_ERASE", "[garage]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);
	Vehicle vehicle2 = Vehicle("UC12436", "Tesla X", 2);
	Vehicle vehicle3 = Vehicle("UC12438", "MASSIVE BIG BUS", 4);
	Garage garage = Garage(32);
	garage.insert(vehicle);
	garage.insert(vehicle2);
	garage.insert(vehicle3);

	REQUIRE(garage.size() == 3);

	garage.erase("UC12438");

	REQUIRE(garage.size() == 2);
}

TEST_CASE("Garage_FIND", "[garage]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);
	Vehicle vehicle2 = Vehicle("UC12436", "Tesla X", 2);
	Vehicle vehicle3 = Vehicle("UC12438", "MASSIVE BIG BUS", 4);

	Garage garage = Garage(32);
	garage.insert(vehicle);
	garage.insert(vehicle2);
	garage.insert(vehicle3);

	const Vehicle* result = garage.find("UC12438");
	const Vehicle* result2 = garage.find("unreachable");

	REQUIRE(result->description()[0] == 'M');
	REQUIRE(result->description()[3] == 'S');
	REQUIRE(result->description()[14] == 'S');
	REQUIRE(result->space() == 4);
	REQUIRE(result2 == nullptr);

}

TEST_CASE("Garage_INSERT", "[myString]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);
	Vehicle vehicle2 = Vehicle("UC12436", "Tesla X", 2);

	Garage garage = Garage(32);
	garage.insert(vehicle);
	garage.insert(vehicle2);

	REQUIRE(garage.size() == 2);
}

TEST_CASE("Vehicle_SPACE", "[vehicle]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);

	REQUIRE(vehicle.space() == 1);
}


TEST_CASE("Vehicle_DESCRIPTION", "[vehicle]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);

	REQUIRE(vehicle.description()[0] == 'A');
	REQUIRE(vehicle.description()[1] == 'u');
	REQUIRE(vehicle.description()[2] == 'd');
	REQUIRE(vehicle.description()[6] == '5');
}

TEST_CASE("Vehicle_REGISTRATION", "[vehicle]") {
	Vehicle vehicle = Vehicle("US12436", "Audi A5", 1);

	REQUIRE(vehicle.registration()[0] == 'U');
	REQUIRE(vehicle.registration()[1] == 'S');
	REQUIRE(vehicle.registration()[2] == '1');
	REQUIRE(vehicle.registration()[6] == '6');
}

TEST_CASE("MyString_OPERATOR<", "[myString]") {
	MyString str = MyString("YOJI's string!");
	MyString str1 = MyString("YOJI's string!#");
	MyString str2 = MyString("gg");

	bool result1 = str < str1;
	bool result2 = str < str2;

	REQUIRE(result1);
	REQUIRE(!result2);
}
TEST_CASE("MyString_OPERATOR==", "[myString]") {
	MyString str = MyString("YOJI's string!");
	MyString str1 = MyString("YOJI's string!");
	MyString str2 = MyString("YOJI's string!#");

	bool result1 = str == str1;
	bool result2 = str == str2;

	REQUIRE(result1);
	REQUIRE(!result2);
}
TEST_CASE("MyString_c_str", "[myString]") {
	MyString str = MyString("YOJI's string!");

	const char* result = str.c_str();

	REQUIRE(result[0] == 'Y');
	REQUIRE(result[13] == '!');
}

TEST_CASE("MyString_OPERATOR+_CONST", "[myString]") {
	const MyString str = MyString("YOJI's string!");

	MyString result = str + '#';

	REQUIRE(str.size() == 14);
	REQUIRE(result.size() == 15);
	REQUIRE(result.at(1) == 'O');
	REQUIRE(result.back() == '#');
}
TEST_CASE("MyString_OPERATOR+", "[myString]") {
	MyString str = MyString("YOJI's string!");

	MyString result = str + '#';

	REQUIRE(str.size() == 14);
	REQUIRE(result.size() == 15);
	REQUIRE(result.at(1) == 'O');
	REQUIRE(result.back() == '#');
}

TEST_CASE("MyString_OPERATOR+=_CONST", "[myString]") {
	MyString str = MyString("YOJI's string!");
	const MyString toAppend = MyString("123");

	str += toAppend;

	REQUIRE(str.size() == 17);
	REQUIRE(str.back() == '3');
}

TEST_CASE("MyString_OPERATOR+=", "[myString]") {
	MyString str = MyString("YOJI's string!");

	str += '#';

	REQUIRE(str.size() == 15);
	REQUIRE(str.back() == '#');
}
TEST_CASE("MyString_POP_BACK", "[myString]") {
	MyString str = MyString("YOJI's string!#");
	MyString strEmpty = MyString("");

	str.pop_back();

	REQUIRE(str.size() == 14);
	REQUIRE(str.back() == '!');
}

TEST_CASE("MyString_PUSH_BACK", "[myString]") {
	MyString str = MyString("YOJI's string!");
	MyString strEmpty = MyString("");

	str.push_back('#');
    strEmpty.push_back('#');

	REQUIRE(str.size() == 15);
	REQUIRE(str.back() == '#');
	REQUIRE(strEmpty.size() == 1);
	REQUIRE(strEmpty.back() == '#');
}

TEST_CASE("MyString_CLEAR", "[myString]") {
	MyString str = MyString("YOJI's string!");
	MyString strEmpty = MyString("");

	str.clear();
	strEmpty.clear();

	REQUIRE(str.size() == 0);
	REQUIRE(str.empty());
	REQUIRE(strEmpty.size() == 0);
	REQUIRE(strEmpty.empty());

}

TEST_CASE("MyString_SIZE", "[myString]") {
	MyString str = MyString("bestString!");
	MyString strEmpty = MyString();
	MyString strEmpty2 = MyString("");

	REQUIRE(str.size() == 11);
	REQUIRE(strEmpty.size() == 0);
	REQUIRE(strEmpty2.size() == 0);
}


TEST_CASE("MyString_EMPTY", "[myString]") {
	MyString str = MyString("bestString!");
	MyString strEmpty = MyString();
	MyString strEmpty2 = MyString("");

	REQUIRE(!str.empty());
	REQUIRE(strEmpty.empty());
	REQUIRE(strEmpty2.empty());
}

TEST_CASE("MyString_BACK_CONST", "[myString]") {
	const MyString str = MyString("bestString!");

	REQUIRE(str.back() == '!');
}

TEST_CASE("MyString_BACK", "[myString]") {
    MyString str = MyString("bestString!");

	REQUIRE(str.back() == '!');
}

TEST_CASE("MyString_FRONT_CONST", "[myString]") {
	const MyString str = MyString("bestString!");

	REQUIRE(str.front() == 'b');
}

TEST_CASE("MyString_FRONT", "[myString]") {
	MyString str = MyString("bestString!");

	REQUIRE(str.front() == 'b');
}

TEST_CASE("MyString_OPERATOR[]", "[myString]") {
	MyString str = MyString("yoji's garage!");

	REQUIRE(str[0] == 'y');
	REQUIRE(str[1] == 'o');
	REQUIRE(str[3] == 'i');
	REQUIRE(str[13] == '!');
	REQUIRE_NOTHROW(str[-1]);
}

TEST_CASE("MyString_OPERATOR[]_CONST", "[myString]") {
	const MyString str = MyString("yoji's best garage!");

	REQUIRE(str[0] == 'y');
	REQUIRE(str[1] == 'o');
	REQUIRE(str[3] == 'i');
	REQUIRE_NOTHROW(str[13]);
}


TEST_CASE("MyString_AT", "[myString]") {
	MyString* str = new MyString("yoji's garage!");

	REQUIRE(str->at(0) == 'y');
	REQUIRE(str->at(1) == 'o');
	REQUIRE(str->at(2) == 'j');
	REQUIRE(str->at(3) == 'i');
	REQUIRE(str->at(5) == 's');
	REQUIRE(str->at(13) == '!');
}

TEST_CASE("MyString_AT_CONST", "[myString]") {
	const MyString str = MyString("yoji's garage!");

	REQUIRE(str.at(0) == 'y');
	REQUIRE(str.at(1) == 'o');
	REQUIRE(str.at(2) == 'j');
	REQUIRE(str.at(3) == 'i');
	REQUIRE(str.at(5) == 's');
	REQUIRE(str.at(13) == '!');
}

TEST_CASE("MyString_AT_THROW_EXCEPTION", "[myString]") {
	MyString* str = new MyString("yoji's garage!");

	REQUIRE_THROWS(str->at(23), "The given position is out of the range of this string!");
}
