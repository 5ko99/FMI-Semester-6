#define CATCH_CONFIG_MAIN
#include <stdexcept>
#include <iostream>
#include "catch.hpp"
#include "mystring.h"
#include "vehicle.h"
#include "garage.h"

TEST_CASE("Test MyString")
{
    SECTION("Default Constructor")
    {
        MyString str1;
        REQUIRE(str1.size() == 0);
    }

    SECTION("Constructor With Parameters")
    {
        MyString str1("Hello world!");
        REQUIRE(str1.size() == strlen("Hello world!"));
        int compare = strcmp(str1.c_str(), "Hello world!");
        REQUIRE(compare == 0);
    }

    SECTION("Copy Constructor")
    {
        MyString str1("I love c++!");
        MyString str2(str1);

        REQUIRE(str2.size() == str1.size());
        REQUIRE(str2.size() == strlen("I love c++!"));
        REQUIRE(strcmp(str1.c_str(), str2.c_str()) == 0);
        REQUIRE(strcmp(str1.c_str(), "I love c++!") == 0);

        str1[0] = 'i';
        REQUIRE(str1[0] == 'i');
        REQUIRE(str2[0] == 'I'); // checks that any change on the 1st string is not applied to the 2nd one
    }


    SECTION("Test \"at\" function")
    {
        MyString str("c++ is really cool!");
        REQUIRE(str.at(0) == 'c');
        REQUIRE(str.at(1) == '+');
        REQUIRE(str.at(4) == 'i');

        try
        {
            str.at(100) = 'l';
            REQUIRE(str[100] == 'l');

        }
        catch (const std::out_of_range& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    SECTION("Operator For Index")
    {
        MyString str("Hello world");
        str[1] = 'E';
        REQUIRE(str[0] == 'H');
        REQUIRE(str[1] == 'E');
    }

    SECTION("Test front functon")
    {
        MyString str("i love c++");
        str.front() = 'I';
        REQUIRE(str[0] == 'I');
    }

    SECTION("Test back function")
    {
        MyString str("car");
        str.back() = 't';
        REQUIRE(strcmp(str.c_str(), "cat") == 0);
        REQUIRE(str[2] == 't');
    }

    SECTION("Test empty function")
    {
        MyString str1;
        REQUIRE(str1.empty());

        MyString str2("a");
        REQUIRE(!str2.empty());
    }

    SECTION("Test size of string")
    {
        MyString str1;
        REQUIRE(str1.size() == 0);

        MyString str2("abc");
        REQUIRE(str2.size() == 3);
    }

    SECTION("Test clear function")
    {
        MyString str1("I love c++!");
        str1.clear();
        REQUIRE(str1.empty());
        REQUIRE(str1.c_str() == nullptr);
    }

    SECTION("Test push back function")
    {
        MyString str1("How are ");
        str1.push_back('U');
        REQUIRE(str1.size() == strlen("How are U"));
        REQUIRE(strcmp(str1.c_str(), "How are U") == 0);

        MyString str2;
        str2.push_back('h');
        REQUIRE(str2.size() == 1);
    }

    SECTION("Test pop back function")
    {
        MyString str2("hello");
        str2.pop_back();
        REQUIRE(str2.size() == 4);
        REQUIRE(strcmp(str2.c_str(), "hell") == 0);
    }

    SECTION("Test operator +=")
    {
        MyString str1;
        str1 += 'C';
        str1 += "++ is the best";

        REQUIRE(str1.size() == strlen("C++ is the best"));
        REQUIRE(strcmp(str1.c_str(), "C++ is the best") == 0);
    }

    SECTION("Test operator +")
    {
        MyString str1;
        MyString str2 = str1 + 'I';
        REQUIRE(str2[0] == 'I');
        REQUIRE(str2.size() == 1);

        MyString str3 = str2 + " love C++";
        REQUIRE(str3.size() == strlen("I love C++"));
        REQUIRE(strcmp(str3.c_str(), "I love C++") == 0);
    }

    SECTION("Test converting to C-style string")
    {
        MyString str1;
        REQUIRE(str1.c_str() == nullptr);

        MyString str2("hello");
        REQUIRE(strcmp(str2.c_str(), "hello") == 0);
    }

    SECTION("Test Operator ==")
    {
        MyString str1("c++ is the best");
        MyString str2("c++ is the bestt");
        MyString str3("c++ is the best");


        REQUIRE(!(str1 == str2));
        REQUIRE(str1 == str3);

        MyString str4;
        MyString str5;
        REQUIRE(str4 == str5); //we assume two emty strings are equal
    }

    SECTION("Test Operator <")
    {
        MyString str1("abc");
        MyString str2("bcd");

        REQUIRE(str1 < str2);
        REQUIRE(!(str2 < str1));

        MyString str3("abc");
        REQUIRE(!(str1 < str3));
    }

}


TEST_CASE("Test Vehicle")
{
    Vehicle car1("BG1234", "this is a red car", 2);

    REQUIRE(strcmp(car1.registration(), "BG1234") == 0);
    REQUIRE(strcmp(car1.description(), "this is a red car") == 0);
    REQUIRE(car1.space() == 2);
}

TEST_CASE("Test Garage")
{
    Vehicle car1("BG1234", "this is a red car", 2);
    Vehicle car2("UK6767", "big car", 3);

    Garage garage(10);


    SECTION("Test size")
    {
        REQUIRE(garage.size() == 0);
        garage.insert(car1);
        REQUIRE(garage.size() == 1);
    }

    SECTION("Test empty function")
    {
        REQUIRE(garage.empty());
        garage.insert(car2);
        REQUIRE(!garage.empty());
    }

    SECTION("Test inserting")
    {
        garage.insert(car1);
        garage.insert(car2);
        REQUIRE(garage.size() == 2);
        garage.insert(car2); // tests cars with equal numbers
        REQUIRE(garage.size() == 2);
    }

    SECTION("Test indexing")
    {
        garage.insert(car1);
        garage.insert(car2);
        REQUIRE(strcmp(garage[0].registration(), "BG1234") == 0);
        REQUIRE(strcmp(garage[1].registration(), "UK6767") == 0);
    }

    SECTION("Test find function")
    {
        garage.insert(car1);
        garage.insert(car2);
        const Vehicle* curr = garage.find("BG1234");
        REQUIRE(curr->space() == 2);
    }

    SECTION("Test clear function")
    {
        garage.insert(car1);
        garage.clear();
        REQUIRE(garage.empty());
        REQUIRE(garage.size() == 0);

        garage.insert(car1);
        REQUIRE(garage.size() == 1);
    }


    SECTION("Test erasing")
    {
        garage.insert(car1);
        garage.insert(car2);
        garage.erase("BG1234");
        REQUIRE(garage.size() == 1);

    }

}