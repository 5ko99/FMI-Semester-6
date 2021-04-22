#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MyString.h"
#include <stdexcept>


TEST_CASE("Testing the setter when the string is null")
{
	SECTION("With default constructor")
	{
		MyString test;
		REQUIRE(test.getStr() == nullptr);
	}
	SECTION("With the setter")
	{
		MyString test("not null");
		test.setStr("");
		REQUIRE(test.getStr() == nullptr);
	}
	SECTION("With both")
	{
		MyString test;
		test.setStr("");
		REQUIRE(test.getStr() == nullptr);
	}
}


TEST_CASE("Default Constructor")
{
	MyString testString;

	REQUIRE(testString.getStr() == nullptr);
}

TEST_CASE("Constructor")
{
	SECTION("Inputting a nullpointer")
	{
		char* strInput = nullptr;
		MyString testString(strInput);
		REQUIRE(testString.getStr() == nullptr);
	}

	SECTION("Inputting a terminating zero")
	{
		char h = 0;
		char* input = &h;
		MyString testString(input);
		REQUIRE(testString.getStr() == nullptr);
	}

	SECTION("Inputting a normal string")
	{
		char* strInput = createDynString("Test input");
		MyString testString(strInput);
		REQUIRE_FALSE(strcmp(testString.getStr(),strInput)); // strcpm returns 0 if both strings are equal!!!
		delete[] strInput;
	}
}

TEST_CASE("Testing the copy constructor")
{
	SECTION("Inputting the same class member")
	{
		MyString testString = testString;
	}
	SECTION("Normal input")
	{
		MyString sourceString("source");
		MyString destinationString = sourceString;
		destinationString.setStr("Changed");
		MyString compareString("source");
		REQUIRE(sourceString == compareString);
		REQUIRE_FALSE(destinationString == compareString);
	}
}

TEST_CASE("Testing the operator '='")
{
	SECTION("Giving them normal input")
	{
		MyString DestinationString;
		MyString SourceString("source");
		MyString compareString = SourceString;

		DestinationString = SourceString;
		DestinationString.setStr("Changed");


		REQUIRE(SourceString == compareString);
	}

	SECTION("Giving in the same MyString as both arguements")
	{
		MyString string("Test");
		MyString testString = string;
		string = string;
		REQUIRE(string.getStr() != nullptr);
		REQUIRE(string == testString);
	}
}

TEST_CASE("Testing CopyDynStr")
{
	char* destination = createDynString("Destination");
	char* source = createDynString("Source");

	SECTION("Inputting a nullpointer as a destination")
	{
		delete[] destination; // tuka ako q iztriq za drugite section-i shte ima li effect tova
		destination = nullptr;
		CopyDynStr(source, destination);
		REQUIRE_FALSE(strcmp(destination, source));
	}
	SECTION("Inputting a nullpointer as the source")
	{
		delete[] source;
		source = nullptr; // the source being deleted, but not made null pointer should not be allowed to happed
		CopyDynStr(source, destination);
		REQUIRE(destination == nullptr);
	}
	SECTION("Inputting normal values")
	{
		CopyDynStr(source, destination);
		REQUIRE_FALSE(strcmp(destination, source)); // kak raboti taq pamka. tuk vrushta li se i zapisva li mi pamet otnovo
		// ili mi ostave source-a delete-nat ot predniqt SECTION
	}
	SECTION("Inputting the same source and destination")
	{
		char* newStr = createDynString(source);
		CopyDynStr(source, source);
		REQUIRE_FALSE(strcmp(newStr, source));
		delete[] newStr;
	}
	delete[] destination;
	delete[] source;
}

TEST_CASE("Testing the operator '[]'")
{
	MyString testString("This is a test string");
	//SECTION("Giving a position outside of the array")
	SECTION("Giving a valid position")
	{
		REQUIRE(testString[1] == 'h'); // wtf zakakvo bqh slojil teststring[1] vuv kavi4ki
	}
	SECTION("Giving the position of the first element")
	{
		REQUIRE(testString.operator[](0) == 'T');
	}
}

TEST_CASE("Testing the push_back function")
{
	const char CHAR_TO_TEST = 'd';
	SECTION("Giving it to an empty string")
	{
		MyString testString;
		testString.push_back(CHAR_TO_TEST);
		const char* theStr = testString.getStr();
		REQUIRE(strlen(theStr) == 1);
		REQUIRE(theStr[0] == CHAR_TO_TEST);
		REQUIRE(theStr[1] == 0);
	}
	SECTION("Giving a normal element to a normal string")
	{
		MyString testString("This is a test string");
		std::size_t testLen = strlen(testString.getStr());
		testString.push_back(CHAR_TO_TEST);
		REQUIRE(testString.getStr()[testLen] == CHAR_TO_TEST);

	}
	SECTION("Putting in another terminating 0 at the end of the array") // had already thought
	// of this while writing the function damn, good on me :P
	{
		const char CHAR_TO_TEST1 = 0;
		MyString testString("This is a test string");
		std::size_t testLen = strlen(testString.getStr());
		testString.push_back(CHAR_TO_TEST1);
		REQUIRE(testLen == strlen(testString.getStr()));
	}
}

TEST_CASE("Testing the operator '+=' for adding a single char")
{
	const char CHAR_TO_TEST = 'c';
	SECTION("To an empty/nullptr/ string")
	{
		MyString testString;
		testString += CHAR_TO_TEST;
		const char* theStr = testString.getStr(); // idk if this is really saving anything. don't think so honestly
		REQUIRE(strlen(theStr) == 1);
		REQUIRE(theStr[0] == CHAR_TO_TEST); // ohhh that's why it was a mistake, cause i had written just '=', not '=='
		REQUIRE(theStr[1] == 0);
		//testString.getStr()[0] - is that the right syntaxis? or are brackets needed
	}
	SECTION("To a normal string")
	{
		MyString normalString("Normal");
		std::size_t lenBegin = strlen(normalString.getStr());
		normalString += CHAR_TO_TEST;
		REQUIRE(strlen(normalString.getStr()) == lenBegin + 1);
		REQUIRE(normalString.getStr()[lenBegin] == CHAR_TO_TEST);
		REQUIRE(normalString.getStr()[lenBegin + 1] == 0); // idk how to check if that's outside the range. Shouldn't be tho
	}
}

TEST_CASE("Testing the function 'at'")
{
	SECTION("Wanted position is outside of the range")
	{
		bool exceptionCaught = 0;
		char atWantedPosition;
		MyString testString("This string is a test");
		try {
			atWantedPosition = testString.at(30); 
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what(); 
			exceptionCaught = 1;

		}
		REQUIRE(exceptionCaught); 
	}
	SECTION("Wanted position is valid")
	{
		bool exceptionCaught = 0;
		char atWantedPosition;
		MyString testString("This string is a test");
		try {
			atWantedPosition = testString.at(0); // what happens to this guy here
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what(); // oofff zatva mi davashe greshka shtoto zabravqm skobite
			exceptionCaught = 1;

		}
		REQUIRE_FALSE(exceptionCaught);
		REQUIRE(atWantedPosition == 'T');
	}
}

TEST_CASE("Testing pop-back")
{
	MyString testString;
	SECTION("Inputting an empty array")
	{
		// this is actually asserted as correct?
	}

	SECTION("Inputting valid data")
	{
		testString.setStr("New String");
		std::size_t stringLen = strlen(testString.getStr());
		testString.pop_back();
		REQUIRE(strlen(testString.getStr()) == stringLen - 1);
		REQUIRE(testString.getStr()[stringLen - 1] == 0);
	}

	SECTION("Inputting an array with only one element")
	{
		testString.setStr("a");
		testString.pop_back();
		REQUIRE(testString.empty());
	}
}

TEST_CASE("Testing the function clear")
{
	MyString testString;
	SECTION("Clearing a nullptr")
	{
		testString.clear();
		REQUIRE(testString.getStr() == nullptr);
	}

	SECTION("Clearing a normal string")
	{
		testString.setStr("This is the test string");
		testString.clear();
		REQUIRE(testString.getStr() == nullptr);
	}

	SECTION("Clearing a string that has been given only a terminating zero")
	{
		testString.setStr(""); // this should act the same way as the nullptr case
		testString.clear();
		REQUIRE(testString.getStr() == nullptr);
	}
}

TEST_CASE("Testing the empty function")
{
	MyString testString;
	SECTION("Inputting a non-empty string")
	{
		testString.setStr("non-empty String");
		REQUIRE_FALSE(testString.empty());
	}
	SECTION("Inputting an empty string")
	{
		REQUIRE(testString.empty());
	}
	SECTION("Inputting a string that has been given a terminating zero")
	{
		testString.setStr("");
		REQUIRE(testString.empty()); // should act the same way as the nullptr case
	}
}

TEST_CASE("Testing operator '<'")
{
	MyString firstString, secondString;
	SECTION("Inputting same the same string")
	{
		firstString.setStr("New first string");
		REQUIRE_FALSE(firstString < firstString);
	}
	SECTION("Inputting two strings that are the same")
	{
		firstString.setStr("The same");
		secondString.setStr("The same");
		REQUIRE_FALSE(firstString < secondString);
	}
	SECTION("First string is smaller")
	{
		firstString.setStr("Smaller");
		secondString.setStr("The bigger");
		REQUIRE(firstString < secondString);
	}
	SECTION("Second string is smaller")
	{
		firstString.setStr("The bigger");
		secondString.setStr("Smaller");
		REQUIRE_FALSE(firstString < secondString);
	}
	SECTION("First string is nullptr")
	{
		secondString.setStr("Not a nullptr");
		REQUIRE(firstString < secondString);
	}
	SECTION("Second string is nullptr")
	{
		firstString.setStr("Not a nullptr");
		REQUIRE_FALSE(firstString < secondString);
	}
	SECTION("Both strings are nullptr")
	{
		REQUIRE_FALSE(firstString < secondString);
	}
}

TEST_CASE("Testing operator '=='")
{
	MyString firstString, secondString;
	SECTION("Inputting same the same string")
	{
		firstString.setStr("New first string");
		REQUIRE(firstString == firstString);
	}
	SECTION("Inputting two strings that are the same")
	{
		firstString.setStr("The same");
		secondString.setStr("The same");
		REQUIRE(firstString == secondString);
	}
	SECTION("The strings are different")
	{
		firstString.setStr("First");
		secondString.setStr("Second");
		REQUIRE_FALSE(firstString == secondString);
	}
	SECTION("First string is nullptr")
	{
		secondString.setStr("Not a nullptr");
		REQUIRE_FALSE(firstString == secondString);
	}
	SECTION("Second string is nullptr")
	{
		firstString.setStr("Not a nullptr");
		REQUIRE_FALSE(firstString == secondString);
	}
	SECTION("Both strings are nullptr")
	{
		REQUIRE(firstString == secondString);
	}
}

TEST_CASE("Testing c_str")
{
	MyString testString;
	SECTION("Inputting a nullptr")
	{
		const char* newStr = testString.c_str();
		REQUIRE(newStr == nullptr);
		delete[] newStr; // in case there was an error and memory was in fact allocated
	}
	SECTION("Inputting a valid pointer")
	{
		testString.setStr("Not a nullptr");
		const char* newStr = testString.c_str();
		REQUIRE_FALSE(strcmp(newStr, testString.getStr()));
		delete[] newStr;
	}
}