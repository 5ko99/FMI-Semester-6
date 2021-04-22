#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "myString.h"

TEST_CASE("Class initialization and copy functionality")
{
    MyString s("Hello World!");

    SECTION("Constructor is assigning correct values")
    {
        REQUIRE(strcmp(s.getData(), "Hello World!") == 0);
        REQUIRE(s.size() == strlen("Hello World!"));
    }

    SECTION("Copy constructor is working properly")
    {
        MyString copy(s);

        REQUIRE(strcmp(copy.getData(), s.getData()) == 0);
        REQUIRE(copy.size() == s.size());
    }

    SECTION("Copy operator")
    {
        MyString s1;
        s1 = s;

        REQUIRE(strcmp(s1.getData(), s.getData()) == 0);
        REQUIRE(s1.size() == s.size());
    }
}

TEST_CASE("Single element access")
{
    MyString s("Hello World!");

    SECTION("At function working properly with correct position as input")
    {
        REQUIRE(s.at(6) == 'W');
    }

    SECTION("At function throws an exception when given incorrect position")
    {
        REQUIRE_THROWS_AS(s.at(25), std::out_of_range);
    }

    SECTION("Operator is working properly")
    {
        REQUIRE(s[2] == 'l');
    }

    SECTION("Front function")
    {
        REQUIRE(s.front() == 'H');
    }

    SECTION("Back function")
    {
        REQUIRE(s.back() == '!');
    }
}

TEST_CASE("Check if the string is empty")
{
    SECTION("If it is empty then return true")
    {
        MyString s;
        REQUIRE(s.empty() == true);
    }

    SECTION("If it is not empty then return false")
    {
        MyString s("Hello World!");
        REQUIRE(s.empty() == false);
    }
}

TEST_CASE("Clear function operating as intended")
{
    MyString s("Hello World!");

    s.clear();
    REQUIRE(s.empty() == true);
}

TEST_CASE("push_back function")
{
    MyString s("Hello World!");

    SECTION("Is adding last symbol properly")
    {
        s.push_back('?');

        REQUIRE(strcmp(s.getData(), "Hello World!?") == 0);
        REQUIRE(s.size() == strlen("Hello World!?"));
    }

    SECTION("If MyString is empty")
    {
        MyString s1;

        s1.push_back('?');
        REQUIRE(strcmp(s1.getData(), "?") == 0);
        REQUIRE(s1.size() == strlen("?"));
    }

    SECTION("Operator += is working as intended")
    {
        s += '?';

        REQUIRE(strcmp(s.getData(), "Hello World!?") == 0);
        REQUIRE(s.size() == strlen("Hello World!?"));
    }
}

TEST_CASE("pop_back function")
{
    SECTION("Is removing last symbol properly")
    {
        MyString s("Hello World!");
        s.pop_back();

        REQUIRE(strcmp(s.getData(), "Hello World") == 0);
        REQUIRE(s.size() == strlen("Hello World"));
    }
}

TEST_CASE("Concatenate operator +=")
{
    SECTION("Is concatenating properly")
    {
        MyString s("Hello World!");
        MyString s1("First test");

        s += s1;

        REQUIRE(strcmp(s.getData(), "Hello World!First test") == 0);
        REQUIRE(s.size() == strlen("Hello World!") + strlen("First test"));
    }

    SECTION("If secong string is empty")
    {
        MyString s("Hello World!");
        MyString s1;

        s += s1;

        REQUIRE(strcmp(s.getData(), "Hello World!") == 0);
        REQUIRE(s.size() == strlen("Hello World!"));
    }

    SECTION("If first string is empty")
    {
        MyString s;
        MyString s1("First test");

        s += s1;

        REQUIRE(strcmp(s.getData(), "First test") == 0);
        REQUIRE(s.size() == strlen("First test"));
    }
}

TEST_CASE("Operator + with character that returns new string is concatenating properly")
{
    MyString s("Hello World!");
    MyString s1 = s + '?';

    SECTION("Copies correctly to new class")
    {
        REQUIRE(strcmp(s1.getData(), "Hello World!?") == 0);
        REQUIRE(s1.size() == s.size() + 1);
    }

    SECTION("Doesn't change other data")
    {
        REQUIRE(strcmp(s.getData(), "Hello World!") == 0);
        REQUIRE(s.size() == strlen("Hello World!"));
    }
}

TEST_CASE("Operator + string that returns new string")
{
    MyString s("Hello World!");
    MyString s0("Wow");
    MyString s1 = s + s0;

    SECTION("Copies correctly to new class")
    {
        REQUIRE(strcmp(s1.getData(), "Hello World!Wow") == 0);
        REQUIRE(s1.size() == s.size() + strlen("Wow"));
    }

    SECTION("Doesn't change other data")
    {
        REQUIRE(strcmp(s.getData(), "Hello World!") == 0);
        REQUIRE(s.size() == strlen("Hello World!"));

        REQUIRE(strcmp(s0.getData(), "Wow") == 0);
        REQUIRE(s0.size() == strlen("Wow"));
    }
}

TEST_CASE("c_str func")
{
    MyString s("Hello World!");
    const char *str = s.c_str();

    REQUIRE(strcmp(str, s.getData()) == 0);
}

TEST_CASE("Operator == is working correctly")
{
    MyString s("Hello World!");

    SECTION("If two strings are the same")
    {
        MyString s1(s);
        REQUIRE(s == s1);
    }

    SECTION("If two strings are not the same")
    {
        MyString s1("I have never seen two pretty best friends");
        REQUIRE_FALSE(s == s1);
    }
}

TEST_CASE("Operator < is functioning correctly")
{
    MyString s("Hello World!");

    SECTION("If s length is equal to s1 length and they are identical")
    {
        MyString s1(s);

        REQUIRE((s < s1) == false);
    }

    SECTION("If s length is equal to s1 length and they are NOT identical, s1 is shorter")
    {
        MyString s1("WOW");

        REQUIRE((s < s1) == false);
    }

    SECTION("If s length is equal to s1 length and they are identical, s is shorter")
    {
        MyString s1("alalallalalalalla");

        REQUIRE((s < s1) == true);
    }

    SECTION("If both are empty")
    {
        MyString s2;
        MyString s3;

        REQUIRE((s2 < s3) == true);
    }
}