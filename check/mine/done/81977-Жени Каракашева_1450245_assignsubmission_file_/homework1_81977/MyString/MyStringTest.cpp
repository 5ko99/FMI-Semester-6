#define CATCH_CONFIG_MAIN
#include "../catch2/catch2.hpp"
#include "MyString.h"

//to compile: g++ MyStringTest.cpp ../catch2/catch2.cpp MyString.cpp
TEST_CASE ("Constructors test")
{
    SECTION("Testing default constructor")
    {
        MyString test;

        REQUIRE(test.size() == 0);
        REQUIRE(test.capacity() == 0);
    }

    SECTION("Testing parameter constructor")
    {
        MyString test("Peppermint");

        REQUIRE(test.size() == 10);
        REQUIRE(test.capacity() == 20);
        REQUIRE(strcmp(test.c_str(),"Peppermint") == 0);
    }

    SECTION("Testing copy constructor")
    {
        MyString test("Luciano");
        MyString newtest(test);

        REQUIRE(strcmp(newtest.c_str(),test.c_str()) == 0);
        REQUIRE(newtest.size() == 7);
        REQUIRE(newtest.capacity() == 14);
    }
}

TEST_CASE ("Position methods test")
{
    SECTION("Testing at()")
    {
        MyString test("trainierter");

        REQUIRE(test.at(10) == 'r');
        REQUIRE(test.at(0) == 't');
    }

    SECTION("Testing operator[]")
    {
        MyString test("trainierter");

        REQUIRE(test[3] == 'i');
        REQUIRE(test[4] == 'n');
    }

    SECTION("Testing front() and back()")
    {
        MyString test("Schmetterling");

        REQUIRE(test.front() == 'S');
        REQUIRE(test.back() == 'g');
    }
}

TEST_CASE ("Size, capacity, empty methods test")
{
    MyString test("Schmetterling");
    REQUIRE(test.size() == 13);
    REQUIRE(test.capacity() == 26);
    REQUIRE(test.empty() == false);

    MyString testTwo;
    REQUIRE(testTwo.size() == 0);
    REQUIRE(testTwo.capacity() == 0);
    //REQUIRE(test.empty() == true);

    MyString testThree("Rhythm, begehre");
    REQUIRE(testThree.size() == 15);
    REQUIRE(testThree.capacity() == 30);
    REQUIRE(test.empty() == false);
}

TEST_CASE ("Push_back() and pop_back() methods test")
{
    MyString test("Schmetterling");
    REQUIRE(test.size() == 13);
    REQUIRE(test.capacity() == 26);
   
    test.push_back('c');
    REQUIRE(strcmp(test.c_str(),"Schmetterlingc") == 0);
    REQUIRE(test.size() == 14);
    REQUIRE(test.capacity() == 26);

    test.pop_back();
    test.pop_back();
    REQUIRE(strcmp(test.c_str(),"Schmetterling") == 0);
    REQUIRE(test.size() == 12);
    REQUIRE(test.capacity() == 26);
}
