
// to use the test coment out main_4.cpp

#define CATCH_CONFIG_MAIN

#include "MyString.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("MyString : at ") {

	SECTION("Empty string") {
		MyString str{};

		bool exeptionCought = false;

		try {
			str.at(0);
		}
		catch (std::out_of_range&) {
			exeptionCought = true;
		}

		REQUIRE(exeptionCought == true);
	}
	SECTION("Normal String") {
		MyString str{ "abc 1a2z 1!@ 42" };

		REQUIRE(str.at(0) == 'a');
		REQUIRE(str.at(3) == ' ');
		REQUIRE(str.at(10) == '!');
		REQUIRE(str.at(11) == '@');

		bool expeptionCought = false;

		try {
			str.at(20);
		}
		catch (std::out_of_range&) {
			expeptionCought = true;
		}

		REQUIRE(expeptionCought == true);
	}
	SECTION("Change character in string") {
		MyString str{ "abc 1a2z 1!@ 42" };
		str.at(0) = '3';
		REQUIRE(str.at(0) == '3');
		str.at(4) = '$';
		REQUIRE(str.at(4) == '$');
	}
}

TEST_CASE("MyString : operator[] ") {
	MyString str{ "45827 uuddlrlrba" };

	SECTION("Normal String") {
		REQUIRE(str[3] == '2');

		REQUIRE(str[5] == ' ');

		REQUIRE(str[12] == 'l');
	}
	SECTION("Change character in string") {
		str[3] = 'A';
		REQUIRE(str[3] == 'A');

		str[6] = 'k';
		REQUIRE(str[6] == 'k');

		str[12] = '8';
		REQUIRE(str[12] == '8');
	}
}
TEST_CASE("MyString : front ") {
	MyString str{ "abc 123" };

	SECTION("Normal String")

	{
		REQUIRE(str.front() == 'a');
	}

	SECTION("Change character in string") {
		str.front() = 'b';

		REQUIRE(str.front() == 'b');
	}
}
TEST_CASE("MyString : back ") {
	MyString str{ "zxc 456" };

	SECTION("Normal String") { REQUIRE(str.back() == '6'); }

	SECTION("Change character in string") {
		str.back() = 'X';
		REQUIRE(str.back() == 'X');
	}
}

TEST_CASE("MyString : empty ") {

	SECTION("Empty string") {
		MyString str{};
		REQUIRE(str.empty() == true);
	}
	SECTION("Normal string") {
		MyString str{ "abc 123" };
		REQUIRE(str.empty() == false);
	}
}
TEST_CASE("MyString : size ") {
	SECTION("Empty string") {
		MyString str{};
		REQUIRE(str.size() == 0);
	}

	SECTION("Normal string") {
		MyString str{ "abc 123" };
		REQUIRE(str.size() == 7);
	}
}
TEST_CASE("MyString : clear ") {
	SECTION("Empty string") {
		MyString str{};
		str.clear();
		REQUIRE(str.size() == 0);
	}
	SECTION("Normal string") {
		MyString str{ "abc 123" };
		str.clear();
		REQUIRE(str.size() == 0);
	}
}
TEST_CASE("MyString : push_back ") {
	SECTION("Empty string") {
		MyString str{};
		str.push_back('a');
		REQUIRE(str[0] == 'a');
		REQUIRE(str.size() == 1);
	}
	SECTION("Normal string") {
		MyString str{ "abc 123" };

		str.push_back('X');
		REQUIRE(str.back() == 'X');
		REQUIRE(str.size() == 8);

		str.push_back('Z');
		REQUIRE(str.back() == 'Z');
		REQUIRE(str.size() == 9);
	}
}

TEST_CASE("MyString : pop_back") {
	SECTION("Normal string") {
		MyString str{ "abc 123" };

		str.pop_back();
		REQUIRE(str.size() == 6);
		REQUIRE(str.back() == '2');

		str.pop_back();
		REQUIRE(str.size() == 5);
		REQUIRE(str.back() == '1');
	}
}

TEST_CASE("MyString : operator += char c") {
	SECTION("Empty string") {
		MyString str{};

		str += 'a';
		REQUIRE(str[0] == 'a');
		REQUIRE(str.size() == 1);
	}
	SECTION("Normal string") {
		MyString str{ "abc 123" };

		str += 'X';
		REQUIRE(str.back() == 'X');
		REQUIRE(str.size() == 8);

		str += 'Z';
		REQUIRE(str.back() == 'Z');
		REQUIRE(str.size() == 9);
	}
}
TEST_CASE("MyString : operator += MyString &rhs ") {
	SECTION("Empty + Empty") {

		MyString str1{};
		MyString str2{};

		str2 += str1;

		REQUIRE(str2.empty() == true);
	}
	SECTION("Empty += NotEmpty")
	{
		MyString str1{};
		MyString str2{ "abc" };

		str1 += str2;

		REQUIRE(str1.size() == 3);
	}
	SECTION("NotEmpty + Empty")
	{
		MyString str1{ "abc" };
		MyString str2{};

		str1 += str2;

		REQUIRE(str1.size() == 3);
	}
	SECTION("Normal string") {
		MyString str1{ "abc" };
		MyString str2{ "9 87" };

		str1 += str2;

		REQUIRE(str1.size() == 7);
		REQUIRE(str1[3] == '9');
		REQUIRE(str1[4] == ' ');
		REQUIRE(str1[5] == '8');
		REQUIRE(str1[6] == '7');
		REQUIRE(str1.back() == '7');
	}
}
TEST_CASE("MyString : operator + c char") {
	SECTION("Empty sting") {
		MyString str1{};
		MyString str2{ str1 + 'X' };

		REQUIRE(str2.size() == 1);
		REQUIRE(str2[0] == 'X');
	}
	SECTION("Normal String") {
		MyString str1{ "abc" };
		MyString str2{ str1 + 'X' };

		REQUIRE(str2.size() == 4);
		REQUIRE(str2[0] == 'a');
		REQUIRE(str2[3] == 'X');
	}
}
TEST_CASE("MyString : operator + string") {
	SECTION("Empty + Empty") {
		MyString str1{};
		MyString str2{};
		MyString str3{ str1 + str2 };

		REQUIRE(str3.size() == 0);
	}
	SECTION("Empty + NotEmpty") {
		MyString str1{};
		MyString str2{ "abc" };
		MyString str3{ str1 + str2 };

		REQUIRE(str3.size() == 3);
		REQUIRE(str3[2] == 'c');
	}
	SECTION("NotEmpty + Empty") {
		MyString str1{ "XYZ" };
		MyString str2{};
		MyString str3{ str1 + str2 };

		REQUIRE(str3.size() == 3);
		REQUIRE(str3[2] == 'Z');
	}
	SECTION("Empty + Empty") {
		MyString str1{};
		MyString str2{};
		MyString str3{ str1 + str2 };

		REQUIRE(str3.size() == 0);
	}
	SECTION("Normal string") {
		MyString str1{ "abc" };
		MyString str2{ "XYZ" };
		MyString str3{ str1 + str2 };

		REQUIRE(str3.size() == 6);
		REQUIRE(str3[0] == 'a');
		REQUIRE(str3[5] == 'Z');
	}
}
TEST_CASE("MyString : c_str") {
	SECTION("Normal string") {
		MyString str{ "abc" };

		const char* tmp{ "abc" };

		const char* cStyleStr = str.c_str();

		REQUIRE(tmp[0] == cStyleStr[0]);
		REQUIRE(tmp[1] == cStyleStr[1]);
		REQUIRE(tmp[2] == cStyleStr[2]);
	}
}
TEST_CASE("MyString : opperator == ") {
	SECTION("Empty string") {
		MyString str1{};
		MyString str2{};

		bool success = (str1 == str2);
		REQUIRE(success);
	}
	SECTION("Normal string") {
		MyString str1{ "abc" };
		MyString str2{ "abc" };

		bool success = (str1 == str2);
		REQUIRE(success);
	}
}
TEST_CASE("MyString : opperator < ") {
	SECTION("Normal string") {
		MyString str1{ "abcA" };
		MyString str2{ "abcB" };

		bool success = (str1 < str2);
		REQUIRE(success);
	}
	SECTION("Same string") {
		MyString str1{ "abcA" };
		MyString str2{ "abcA" };

		bool success = (str1 < str2);
		REQUIRE(!success);
	}
	SECTION("Empty string") {
		MyString str1{};
		MyString str2{};

		bool success = (str1 < str2);
		REQUIRE(!success);
	}
}
