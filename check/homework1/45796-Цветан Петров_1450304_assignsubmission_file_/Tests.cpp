#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Header.h"
#include <cstring>

TEST_CASE("MyString", "[Mystring]")
{
	SECTION("Constructor") {
		MyString str("asd");
		REQUIRE(str.getLenght() == 3);
	}
	SECTION("At") {
		MyString str("asd");
		REQUIRE(str.at(0) == 'a');
		REQUIRE(str.at(1) == 's');
		REQUIRE(str.at(2) == 'd');
		REQUIRE(str[0] == 'a');
		REQUIRE(str[1] == 's');
		REQUIRE(str[2] == 'd');
	}
	SECTION("Front") {
		MyString str("asd");
		REQUIRE(str.front() == 'a');
		
	}
	SECTION("Back") {
		MyString str("asd");
		REQUIRE(str.back() == 'd');
	}
	SECTION("Empty") {
		MyString str;
		REQUIRE(str.empty());
		MyString str2("asd");
		REQUIRE(!str2.empty());
	}
	SECTION("Empty") {
		MyString str("asd");
		str.clear();
		REQUIRE(str.empty());
	}
	SECTION("Push back") {
		MyString str("asd");
		str.push_back('b');
		REQUIRE(str.getLenght() == 4);
		REQUIRE(str[3] == 'b');
	}
	SECTION("Pop back") {
		MyString str("asd");
		str.pop_back();
		REQUIRE(str.getLenght() == 2);
	}
	SECTION("Operator +=") {
		MyString str("asd");
		str += 'b';
		REQUIRE(str.getLenght() == 4);
		REQUIRE(str[3] == 'b');
	}

	SECTION("Operator +") {
		MyString str("asd");
		MyString str2("bcd");
		MyString str3 = str + str2;
		REQUIRE(str3.getLenght() == 6);
		REQUIRE(str3[0] == 'a');
		REQUIRE(str3[1] == 's');
		REQUIRE(str3[2] == 'd');
		REQUIRE(str3[3] == 'b');
		REQUIRE(str3[4] == 'c');
		REQUIRE(str3[5] == 'd');
	}

	SECTION("c_tring") {
		MyString str("asd");
		const char* content = str.c_str();
		const char* original = "asd";
		REQUIRE( *content == *original);

		delete[] content, original;
	}

	SECTION("Operator ==") {
		MyString first("margl");
		MyString second("margl");
		MyString third("cdg");

		REQUIRE(first == second);
		REQUIRE(!(first == third));
	}

	SECTION("Operator ==") {
		MyString first("Rei Kawakubo");
		MyString second("Rei");
		MyString third("cdg");

		REQUIRE(second < first);
		REQUIRE(!(third < first));
	}
}


TEST_CASE("Vehicle", "[Vehicle]")
{
	SECTION("Constructor"){
		Vehicle car("45796", "descr", 8);

		REQUIRE (strcmp(car.registration(), "45796") == 0);
		REQUIRE (strcmp(car.description(), "descr") == 0);
		REQUIRE(car.space() == 8);
	}
	
}

TEST_CASE("Garage", "[Garage]")
{

	SECTION("Insert") {
		Garage gar(100);
		Vehicle car("45796", "descr", 8);

		gar.insert(car);                 //checks if a car is added correctly
		REQUIRE(gar.size() == 1);
		REQUIRE(&gar[0] == &car);

		Vehicle car2("45796", "dscr", 3);
		gar.insert(car2);				 // checks if a car with the same number can be added twice
		REQUIRE(gar.size() == 1);

		Vehicle car3("45796", "descr", 800);
		gar.insert(car3);
		REQUIRE(gar.size() == 1);

	}


	SECTION("Erase") {
		Garage gar(100);
		Vehicle car("45796", "descr", 8);

		gar.insert(car);
		gar.erase(car.registration());

		REQUIRE(gar.size() == 0);
		
	}

	SECTION("Empty") {
		Garage gar(100);
		Vehicle car("45796", "descr", 8);

		REQUIRE(gar.empty());

		gar.insert(car);
		gar.erase(car.registration());

		REQUIRE(gar.empty());
	}

	SECTION("Clear") {
		Garage gar(100);
		Vehicle car("45796", "descr", 8);
		Vehicle car1("4796", "descr", 1);
		Vehicle car2("4576", "descr", 48);
		gar.insert(car);
		gar.insert(car1);
		gar.insert(car2);

		gar.clear();
		
		REQUIRE(gar.empty());
		REQUIRE(strcmp(car.registration(), "45796") == 0);
	}

	SECTION("Size") {
		Garage gar(100);
		REQUIRE(gar.size() == 0);

		Vehicle car("45796", "descr", 8);
		Vehicle car1("4796", "descr", 8);
		Vehicle car2("4576", "descr", 8);
		gar.insert(car);
		gar.insert(car1);
		gar.insert(car2);

		REQUIRE(gar.size() == 3);
	
	}

	SECTION("Find") {
		Garage gar(100);
		

		Vehicle car("45796", "descr", 8);
		Vehicle car1("4796", "descr", 8);
		Vehicle car2("4576", "descr", 8);
		gar.insert(car);
		gar.insert(car1);
		gar.insert(car2);

		REQUIRE(gar.find("45796") == &car);
		REQUIRE(gar.find("4796") == &car1);
		REQUIRE(gar.find("4576") == &car2);

	}
}
