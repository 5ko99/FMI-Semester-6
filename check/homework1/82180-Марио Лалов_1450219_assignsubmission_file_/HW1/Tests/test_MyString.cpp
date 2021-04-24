#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../MyString/MyString.h"

TEST_CASE("String constructors and assignment operator")
{
    MyString string1("first");
    MyString string2("second");

    SECTION("test paramater constructor")
    {
        REQUIRE(strcmp(string1.c_str(), "first") == 0);
    }

    SECTION("test copy constructor")
    {
        MyString string3(string1);

        REQUIRE(strcmp(string1.c_str(), string3.c_str()) == 0);
    }

    SECTION("test operator =")
    {
        MyString string3 = string1;

        REQUIRE(strcmp(string1.c_str(), string3.c_str()) == 0);
    }
}

TEST_CASE("String getters")
{
    MyString string1("first");

    SECTION("test getters")
    {
        REQUIRE(string1.at(1) == 'i');
        REQUIRE(string1[2] == 'r');
    }

    SECTION("test at() exceptions")
    {
        REQUIRE_THROWS_AS(string1.at(5), std::out_of_range);
        REQUIRE_THROWS_AS(string1.at(-1), std::out_of_range);
    }

    SECTION("test first and last")
    {
        REQUIRE(string1.front() == 'f');
        REQUIRE(string1.back() == 't');
    }

    SECTION("test char pointer getter")
    {
        REQUIRE(strcmp(string1.c_str(), "first") == 0);
    }

}

TEST_CASE("Empty string")
{
    MyString string1("first");

    SECTION("test empty when true")
    {
        MyString empty;

        REQUIRE(empty.empty() == true);
    }

    SECTION("test empty when false")
    {
        REQUIRE(string1.empty() == false);
    }

    SECTION("test if pop can make string empty")
    {
        MyString test("abc");
        test.pop_back();
        test.pop_back();
        test.pop_back();

        REQUIRE(test.empty() == true);
    }

    SECTION("test lenght getter")
    {
        REQUIRE(string1.size() == 5);
    }

    SECTION("test lenght getter for empty")
    {
        MyString empty;

        REQUIRE(empty.size() == 0);
    }

    SECTION("test clear")
    {
        string1.clear();

        REQUIRE(string1.empty() == true);
    }
}

TEST_CASE("String pop and push")
{
    MyString string1("first");

    SECTION("test push")
    {
        string1.push_back('a');

        REQUIRE(string1.back() == 'a');
    }

    SECTION("test push for empty string")
    {
        MyString test;
        test.push_back('a');

        REQUIRE(strcmp(test.c_str(), "a") == 0);
    }

    SECTION("test pop")
    {
        string1.pop_back();

        REQUIRE(string1.back() == 's');
    }

    SECTION("test pop with empty")
    {
        MyString empty;

        REQUIRE_THROWS_AS(empty.pop_back(), std::length_error);
    }

    SECTION("test pop then push")
    {
        string1.pop_back();
        string1.push_back('a');

        REQUIRE(strcmp(string1.c_str(), "firsa") == 0);
    }

    SECTION("test full pop then push")
    {
        MyString test("a");
        test.pop_back();
        test.push_back('b');

        REQUIRE(strcmp(test.c_str(), "b") == 0);
    }

    SECTION("test clear then push")
    {
        string1.clear();
        string1.push_back('a');

        REQUIRE(strcmp(string1.c_str(), "a") == 0);
    }
}

TEST_CASE("String concatenation operators")
{
    MyString string1("first");
    MyString string2("second");

    SECTION("operator += test for single char")
    {
        string1 += 'a';

        REQUIRE(strcmp(string1.c_str(), "firsta") == 0);
    }

    SECTION("test operator += for empty string and single char")
    {
        MyString empty;
        empty += 'a';

        REQUIRE(strcmp(empty.c_str(), "a") == 0);
    }

    SECTION("operator += test for strings")
    {
        string1 += string2;

        REQUIRE(strcmp(string1.c_str(), "firstsecond") == 0);
    }

    SECTION("test operator += for strings with first one empty")
    {
        MyString empty;
        empty += string2;

        REQUIRE(strcmp(string2.c_str(), "second") == 0);
    }

    SECTION("test operator += for strings with second one empty")
    {
        MyString empty;
        string2 += empty;

        REQUIRE(strcmp(string2.c_str(), "second") == 0);
    }

    SECTION("operator + test for single char")
    {
        MyString string3;
        string3 = string1 + 'a';

        REQUIRE(strcmp(string3.c_str(), "firsta") == 0);
    }

    SECTION("test operator + for single char and empty string")
    {
        MyString empty;
        MyString string3 = empty + 'a';

        REQUIRE(strcmp(string3.c_str(), "a") == 0);
    }

    SECTION("test operator + check for strings")
    {
        MyString string3;
        string3 = string1 + string2;

        REQUIRE(strcmp(string3.c_str(), "firstsecond") == 0);
    }

    SECTION("operator + test if right string is empty")
    {
        MyString empty;
        MyString string3;
        string3 = string1 + empty;

        REQUIRE(strcmp(string3.c_str(), "first") == 0);
    }

    SECTION("operator + test if left string is empty")
    {
        MyString empty;
        MyString string3;
        string3 = empty + string1;

        REQUIRE(strcmp(string3.c_str(), "first") == 0);
    }
}

TEST_CASE("String comparisons")
{
    MyString string1("first");

    SECTION("operator == check when true")
    {
        MyString string3("first");

        REQUIRE(string1 == string3);
    }

    SECTION("operator == check when false")
    {
        MyString string3("second");

        REQUIRE(!(string1 == string3));
    }

    SECTION("operator < check when true")
    {
        MyString string3("fast");

        REQUIRE(string3 < string1);
    }

    SECTION("operator < check when false")
    {
        MyString string3("fast");

        REQUIRE(!(string1 < string3));
    }
}