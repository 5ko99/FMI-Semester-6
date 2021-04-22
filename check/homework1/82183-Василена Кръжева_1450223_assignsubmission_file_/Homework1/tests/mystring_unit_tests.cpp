//#define CATCH_CONFIG_MAIN
//used separate file test_main.cpp that should be compiled once 
//and then for compilation of mystring_unit_tests.cpp we should include test_main.o in the command
#include <iostream>
#include <cstring>
#include "../lib/catch.hpp"
#include "../include//mystring.hpp"

TEST_CASE("Testing constructors", "[constructors]")
{
    SECTION("Default constructor")
    {
        MyString str;

        REQUIRE(str.size() == 0);
        REQUIRE_THROWS_AS(str.at(0) == '\0', std::out_of_range);
    }

    SECTION("Constructor taking char *")
    {
        char arr[] = "Test arr";
        MyString string(arr);
        const char * str = string.c_str();
        
        REQUIRE(strlen(arr) == string.size());
        REQUIRE(strcmp(arr, str) == 0);
    }

    SECTION("Constructor taking MyString object")
    {
        MyString source("Source");
        MyString destination(source);

        REQUIRE(source == destination); //Checks whether their content is equal
        REQUIRE(source.size() == destination.size());
    }
}

TEST_CASE("Testing basic functionality of overloaded operators")
{
    MyString string1, string2;
    const char testValue[] = "Test"; //testValue can be changed from here without making any additional changes
    const char testChar = 'c';
    const int testValLen = strlen(testValue);

    SECTION("Operator = taking char*")
    {
        string1 = testValue;
        
        REQUIRE(string1.size() == testValLen);
        for (size_t i = 0; i < testValLen; i++)
        {
            REQUIRE(string1.at(i) == testValue[i]);
        }
    }

    SECTION("Operator = taking MyString")
    {
        string1 = testValue;
        string2 = string1;

        REQUIRE(string2 == string1); //Checks whether their content is equal
        REQUIRE(string2.size() == string1.size());
    }

    SECTION("Operator += char")
    {
        string1 = testValue;
        string1 += testChar;

        for (size_t i = 0; i < testValLen; i++)
        {
            REQUIRE(string1.at(i) == testValue[i]);
        }

        REQUIRE(string1.size() == testValLen + 1);
    }

    SECTION("Operator += MyString")
    {
        string1 = testValue;
        string2 = " Passed";
        int size2 = string2.size();

        string1 += string2;
        
        REQUIRE(string1.size() == size2 + testValLen);

        for (size_t i = 0; i < testValLen; i++)
        {
            REQUIRE(string1.at(i) == testValue[i]);
        }
        for (size_t i = 0; i < size2; i++)
        {
            REQUIRE(string1.at(i + testValLen) == string2.at(i));
        }
    }

    SECTION("Operator + char")
    {
        string1 = testValue;
        string2 = string1 + testChar;
        
        REQUIRE(string2.size() == string1.size() + 1);
        for (size_t i = 0; i < testValLen; i++)
        {
            REQUIRE(string2.at(i) == testValue[i]);
        }
        REQUIRE(string2.at(testValLen) ==  testChar);
    }

    SECTION("Operator + MyString")
    {
        string1 = testValue;
        string2 = "Passed";
        int size2 = string2.size();

        MyString result = string1 + ' ' + string2 + '!';
        
        for (size_t i = 0; i < testValLen; i++)
        {
            REQUIRE(result.at(i) == string1.at(i));
        }

        REQUIRE(result.at(testValLen) == ' ');
        for (size_t i = 0; i < size2; i++)
        {
            REQUIRE(result.at(testValLen + i + 1) == string2.at(i));
        }
        
        REQUIRE(result.at(size2 + testValLen + 1) == '!');
        REQUIRE(result.size() == testValLen + size2 + 2);
    }

    SECTION("Operator == ")
    {
        string1 = testValue;
        string2 = testValue;

        REQUIRE(string1 == string2);
        REQUIRE(string1 == testValue);
        REQUIRE((string1 +'\0') == string2);
        REQUIRE_FALSE((string1 + '!') == string2);
    }
    
    SECTION("Operator < and >")
    {
        string1 = testValue;
        string2 = testValue;
        string2 += testChar;

        REQUIRE(string1 < string2);
        REQUIRE(string2 > string1);
        REQUIRE_FALSE(string1 > string2);
        REQUIRE_FALSE(string2 < string1);
        REQUIRE_FALSE(string1 == string2);
    }

    SECTION("Operator []")
    {
        string1 = testValue;
        int length = string1.size();

        for (size_t i = 0; i < length; i++)
        {
            REQUIRE(string1[i] == testValue[i]);
        }
    }
}

TEST_CASE("Testing other member functions")
{
    MyString string1, string2;
    const char* testValue = "Passed";
    const int testLength = strlen(testValue);

    SECTION("Testing at function")
    {
        string1 = testValue;

        for (size_t i = 0; i < testLength; i++)
        {
            REQUIRE(string1.at(i) == testValue[i]);
        }
        REQUIRE_THROWS_AS(string1.at(testLength) == '\0', std::out_of_range);
    }

    SECTION("Testing front and back functions")
    {
        string1 = testValue;

        REQUIRE(string1.front() == testValue[0]);
        REQUIRE(string1.back() == testValue[testLength - 1]);
    }

    SECTION("Testing clear and empty section")
    {
        string1 = testValue;
        string1.clear();

        REQUIRE(string1.empty() == true);
        REQUIRE(string1.size() == 0);
        REQUIRE_THROWS_AS(string1.at(0) == '\0', std::out_of_range);
    }

    SECTION("Testing push_back function")
    {
        string2 = testValue;
        
        for (size_t i = 0; i < testLength; i++)
        {
            string2.push_back(testValue[i]);
            REQUIRE(string2[testLength + i] == testValue[i]);
        }
        
        REQUIRE(string2.size() ==  testLength * 2);
    }

    SECTION("Testing pop_back function")
    {
        string2 = testValue;
        int length = testLength;

        while (length > 0)
        {
            string2.pop_back();
            REQUIRE(string2.size() == --length);
        }
    }

    SECTION("Testing c_str function")
    {
        string2 = testValue;
        const char * str = string2.c_str();

        for (size_t i = 0; i < testLength; i++)
        {
            REQUIRE(str[i] == string2[i]);
        }

        string2.clear();
        REQUIRE(strcmp(str, "") == 0);
    }
}

TEST_CASE("testing const MyString")
{
    char content[] = "Hello World";
    const MyString string(content);
    const char c = '!';
    MyString test;

    SECTION("const MyString + char")
    {
        test = string + c;

        REQUIRE(test.size() == string.size() + 1);
        
        for (size_t i = 0; i < string.size(); i++)
        {
            REQUIRE(test.at(i) == string.at(i));
        }
        REQUIRE(test.at(string.size()) == c);
        REQUIRE_THROWS_AS(string.at(string.size()), std::out_of_range);
    }

    SECTION("test operators ==, >, < ")
    {
        test = string;

        REQUIRE(string == string);
        REQUIRE(test == string);
        REQUIRE(test == string + '\0');

        test+="!!!";

        REQUIRE(string < test);
        REQUIRE_FALSE(string > test);
    }

    SECTION("test front and back function")
    {
        REQUIRE(string.front() == content[0]);
        REQUIRE(string.front() == string[0]);
        REQUIRE(string.back() == string[string.size() - 1]);
        REQUIRE(string.back() == content[strlen(content) - 1]);
    }
}

TEST_CASE("Testing edge cases and special requirements")
{
    SECTION("test MyString += function when it exceeds the capacity")
    {
        char arr[] = "passed";
        MyString string1 = arr;

        MyString string2(arr);
        string2+=arr;

        MyString test;
        test += (string1 + string2);

        REQUIRE(test.size() == string1.size() + string2.size());
    }

    SECTION("test push_back function when it reaches the string capacity")
    {
        MyString test("a");
        int defCapacity = test.DEFAULT_CAPACITY;

        for (size_t i = 0; i < defCapacity + 3; i++)
        {
            test.push_back('!');
        }
        
        REQUIRE(test.size() == defCapacity + 4);
    }
}