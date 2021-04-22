#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "..\MyString\myString.hpp"

TEST_CASE("MyString", "constructor")
{
    SECTION("test default constructor")
    {
        MyString myString;

        REQUIRE(myString.size() == 0);
    }

    SECTION("test constructor with parameter")
    {

        char string[10] = "hellomate";

        MyString myString(string);

        REQUIRE(myString.size() == 9);
    }

    SECTION("test assigment operator with empty myString")
    {
        char string[10] = "hellomate";

        MyString testString(string);
        MyString testSource;

        testString = testSource;
        REQUIRE(testString.size() == 0);
    }

    SECTION("test assignment operator contentful string")
    {
        char string[10] = "hellomate";

        MyString testString;
        MyString testSource(string);

        testString = testSource;
        REQUIRE(testString.size() == 9);
    }

    SECTION("testing at function with correct position")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE(testString.at(9) == 'e');
    }

    SECTION("test at function with incorrect position")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE_THROWS_AS(testString.at(-1), std::out_of_range);
        CHECK_THROWS_AS(testString.at(-1), std::out_of_range);
    }

    SECTION("testing operator[]")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE(testString[8] == 'e');
    }

    SECTION("testing first element access operator")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE(testString.front() == 'h');
    }

    SECTION("testing last element access operator")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE(testString.back() == 'e');
    }

    SECTION("testing empty function with contentful string")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE(testString.empty() == false);
    }

    SECTION("testing empty function with contentless string")
    {
        MyString testString;

        REQUIRE(testString.empty() == true);
    }

    SECTION("testing size function with contentless string")
    {
        MyString testString;

        REQUIRE(testString.size() == 0);
    }

    SECTION("testing size function with contentful string")
    {
        char string[10] = "hellomate";

        MyString testString(string);

        REQUIRE(testString.size() == 9);
    }

    SECTION("testing clear functioin with contentful string")
    {
        char string[10] = "hellomate";

        MyString testString(string);
        testString.clear();

        REQUIRE(testString.size() == 0);
    }

    SECTION("testing clear functioin with contentfless string")
    {
        MyString testString;
        testString.clear();

        REQUIRE(testString.size() == 0);
    }

    SECTION("testing push back function with contentful string")
    {
        char string[10] = "hellomate";
        char singleChar = 'a';

        MyString testString(string);
        testString.push_back(singleChar);

        REQUIRE(testString.back() == 'a');
        REQUIRE(testString.size() == 10);
    }

    SECTION("testing push back function with contentless string")
    {
        MyString testString;
        char singleChar = 'a';

        testString.push_back(singleChar);

        REQUIRE(testString.back() == 'a');
        REQUIRE(testString.size() == 1);
    }

    SECTION("testing pop back function with contentful string")
    {
        char string[10] = "hellomate";

        MyString testString(string);
        testString.pop_back();

        REQUIRE(testString.back() == 't');
        REQUIRE(testString.size() == 8);
    }

    SECTION("testing += operator with contentful string and single char")
    {
        char string[10] = "hellomate";
        char singleChar = '!';

        MyString testString(string);
        testString += singleChar;

        REQUIRE(testString.back() == '!');
        REQUIRE(testString.size() == 10);
    }

    SECTION("testing += operator with contentles string and single char")
    {
        char singleChar = '!';
        MyString testString;

        testString += singleChar;

        REQUIRE(testString.back() == '!');
        REQUIRE(testString.size() == 1);
    }

    SECTION("testing += operator with with contentful string and contentful source")
    {
        char string[10] = "hellomate";
        char source [12]= "how are you";

        MyString testString(string);
        MyString testSource(source);

        testString += testSource;

        REQUIRE(testString.back() == 'u');
        REQUIRE(testString.size() == 20);
    }

    SECTION("testing += operator with with contentful string and contentless source")
    {
        char string[10] = "hellomate";

        MyString testString(string);
        MyString testSource;

        testString += testSource;

        REQUIRE(testString.back() == 'e');
        REQUIRE(testString.size() == 9);
    }

    SECTION("testing += operator with with contentless string and contentful source")
    {
        char string[10] = "hellomate";

        MyString testString;
        MyString testSource (string);

        testString += testSource;

        REQUIRE(testString.back() == 'e');
        REQUIRE(testString.size() == 9);
    }

    SECTION("testing + operator with contentful string and contentful char")
    {
        MyString result;
        char string[10] = "hellomate";
        char singleChar = '!';

        MyString testString(string);

        result = testString + singleChar;

        REQUIRE(result.back() == '!');
        REQUIRE(result.size() == 10);
    }

    SECTION("testing + operator with contentless string and contentful char")
    {
        char singleChar = '!';

        MyString result;
        MyString testString;

        result = testString + singleChar;

        REQUIRE(result.back() == '!');
        REQUIRE(result.size() == 1);
    }

    SECTION("testing + operator with contentful string and contentful source")
    {
        const char string[10] = "hellomate";
        const char source[12] = "how are you";

        MyString result;
        MyString testString(string);
        MyString testSource(source);

        result = testString + testSource;

        REQUIRE(result.back() == 'u');
        REQUIRE(result.size() == 20);
    }

    SECTION("testing + operator with contentful string and contentless source")
    {
        const char string[10] = "hellomate";

        MyString result;
        MyString testString(string);
        MyString testSource;

        result = testString + testSource;

        REQUIRE(result.back() == 'e');
        REQUIRE(result.size() == 9);
    }

    SECTION("testing + operator with contentless string and contentful source")
    {
        const char source[10] = "hellomate";

        MyString result;
        MyString testString;
        MyString testSource(source);

        result = testString + testSource;

        REQUIRE(result.back() == 'e');
        REQUIRE(result.size() == 9);
    }

    SECTION("testing + operator with contentless string and contentless source")
    {
        MyString result;
        MyString testString;
        MyString testSource;

        result = testString + testSource;

        REQUIRE(result.size() == 0);
    }

    SECTION("testing == operator with same contentful stirngs")
    {
        const char source[10] = "hellomate";

        MyString testString(source);
        MyString testSource(source);

        REQUIRE(testString == testSource);
    }

    SECTION("testing == operator with contentless stirngs")
    {
        MyString testString;
        MyString testSource;

        REQUIRE(testString == testSource);
    }

    SECTION("testing == operator with different content and lenght strings")
    {
        const char string[10] = "hellomate";
        const char source[12] = "how are you";

        MyString testString(string);
        MyString testSource(source);

        REQUIRE(!(testString == testSource));
    }  

    SECTION("testing == operator with different content and same lenght strings")
    {
        const char string[10] = "hellomate";
        const char source[10] = "hellodude";

        MyString testString(string);
        MyString testSource(source);

        REQUIRE(!(testString == testSource));
    }    
}