#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "MyString.h"


SCENARIO("Testing all of String functions")
{
	//REQUIRE(false);
	GIVEN("Default constructor")
	{
		MyString str;
		REQUIRE(str.size() == 0);

		WHEN("Add one element")
		{
			const char symbowToAdd = 'a';
			const char symbowToChange = 'b';
			str.push_back(symbowToAdd);
		
			THEN("Testing str.front and push_back") {
				CHECK(str.front() == symbowToAdd);
				str.front() = symbowToChange;
				CHECK(str.front() == symbowToChange);
			}
			THEN("Testing str.back() with one element")
			{
				str.front() = symbowToAdd; //we have one symbow yet , first==last
				CHECK(str.back() == symbowToAdd);
				str.back() = symbowToChange;
				CHECK(str.back() == symbowToChange);
			}
			THEN("Testing operator []")
			{
				//str.front() = symbowToAdd;
				str.push_back(symbowToAdd);
				REQUIRE(str[0] == symbowToAdd);
				str[0] = symbowToChange;
				REQUIRE(str[0] == symbowToChange);
			}
			THEN("Testing .at ()")
			{
				str.push_back(symbowToAdd);
				REQUIRE(str.at(0) == symbowToAdd);
				str.at(0) = symbowToChange;
				REQUIRE(str.at(0) == symbowToChange);
			}
			THEN("Testing size() ")
			{
				str.push_back(symbowToAdd);
				REQUIRE(str.size() == 2);
			}
			THEN("Testing pop_back")
			{
				str[0] = symbowToAdd;
				str.push_back(symbowToChange);
				size_t oldSize = str.size();
				str.pop_back();
				REQUIRE(str.back() == str[oldSize - 2]);
				REQUIRE(str.size() == oldSize - 1);

			}
			//
			THEN("Testing clear()")
			{
				str.clear();
				REQUIRE(str.size() == 0);
			}
			//
			THEN("Testing empty()")
			{
				str.clear();
				REQUIRE(str.empty());
			}
			THEN("Testing resizing / adding more elements than it's capacity")
			{
				str.clear();
				for (int i = 0; i < 100; i++)
				{
					str.push_back(symbowToAdd);
				}
				REQUIRE(str.size() == 100);
				str.clear();
			}
		}
		WHEN("Testing operator += for one char")
		{
			const char symbowToAdd = 'a';
			size_t oldSize = str.size();
			str += symbowToAdd;
			REQUIRE(str.size() == oldSize + 1);
			REQUIRE(str.back() == symbowToAdd);
		}
	}//given
	
	GIVEN("Testing with constr of string of 10+ characters") {

		MyString str("Testing that string capacity");

		WHEN("Testing for  c_str() ")
		{
			const char* testStr = str.c_str();
			REQUIRE(strcmp(testStr, "Testing that string capacity") == 0);
			REQUIRE(strlen(testStr) == str.size());
			delete[] testStr;
		}
		WHEN("Testing += for other string")
		{
			str.clear();
			str.push_back('a');
			MyString newStr = "Hello world";
			str += newStr;
			const char* testStr = str.c_str();
			REQUIRE(strcmp(testStr, "aHello world") == 0);
			delete[] testStr;
		}
	}//given

	GIVEN("Testing for constr that's a copy of another MyString")
	{
		MyString first("My name is Stringy");
		MyString second(first);
		REQUIRE(first == second);
		WHEN("Testing <= and >=")
		{
			THEN("== of <=") {
				REQUIRE(first <= second);
			}
			THEN("== of >=") {
				REQUIRE(first >= second);
			}
			THEN("< of <=") {
				//first.pop_back();
				first.back();
				REQUIRE(first <= second);
				second[0] = first[0]+1;
				REQUIRE(first <= second);
				REQUIRE(first < second);
			}
			THEN("> of >=")
			{
				//second.pop_back();
				second.back();
				REQUIRE(first >= second);
				first[0] = second[0]+1;
				REQUIRE(first >= second);
				REQUIRE(first > second);
			}
		}
	}//given

	GIVEN("Testing operator = ")
	{
		
		MyString str("Hello");
		MyString newStr("Hi");
		newStr = str;
		
		REQUIRE(str == newStr);
		REQUIRE(str.size() == newStr.size());
		WHEN("Testing == from MyString to char* ")
		{
			char* chStr = new char[] {"Hello"};
			REQUIRE(str == chStr);
			delete[] chStr;
		}
		WHEN("Testing for + operation on MyStrings")
		{
			newStr = str + str;
			THEN("str+str = str conct str?")
			{
				const char* st = newStr.c_str();
				
				REQUIRE(strcmp(st, "HelloHello") == 0);
				delete[] st;
			}
			newStr = str + str + newStr+str;//5* (str)
			THEN("Can + be used multiple times at ones?")
			{
				const char* st = newStr.c_str();
				REQUIRE(strcmp(st, "HelloHelloHelloHelloHello") == 0);
				delete[] st;
			}
			newStr = str+str[0];
			THEN("Trying + char from [] ")
			{
				const char* st = newStr.c_str();
				REQUIRE(strcmp(st, "HelloH") == 0);
				delete[] st;
			}

		}//when
	}//given
	GIVEN("Testing move constr and move asign operator")
	{
		
		MyString newStr(std::move(MyString("Hello There...")));

		THEN("Test move constr for setting things right") {
			REQUIRE(newStr == "Hello There...");
		}
		WHEN("Test move asign operator")
		{
			MyString secStr("General Kenobi!");
			newStr = std::move(secStr);
			REQUIRE(secStr.size() == 0);//if we have deleted it
			const char* strPointer = secStr.c_str();
			REQUIRE(strcmp(strPointer,"")==0);
			delete[] strPointer;

			REQUIRE(newStr == "General Kenobi!"); //if we have moved it
			REQUIRE(newStr.size() == strlen("General Kenobi!"));
		}
	}

	GIVEN("Not enough dynamic memory for array case")
	{
		unsigned long long superBigNum=0;
		superBigNum--; 
		MyString str(superBigNum); //in case you don't have the memory , it will allocate 2 or 0
		//REQUIRE_THROWS(str[3]); //undefined behavior . Not guaranteed to throw
	}//given

}//scen
