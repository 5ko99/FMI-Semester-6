#include "../HW1/MyString.h"
#include "../../catch2/include/catch.hpp"

TEST_CASE("Testing MyString constructors") {

    SECTION("Default constructor: ") {
        MyString str;

        REQUIRE(str.c_str() == nullptr);
        REQUIRE(str.size() == 0);
    }

    SECTION("C_String constructor: ") {
        MyString str("Hello");

        REQUIRE(str.c_str() == "Hello");
        REQUIRE(str.size() == 5);
    }

    SECTION("MyString copy constructor: ") {
        MyString str1("Hello");
        MyString str2(str1);

        REQUIRE(str1.c_str() == str2.c_str());
        REQUIRE(str1.size() == str2.size());
    }

}

TEST_CASE("Testing MyString class functions") {

    MyString str0;
    MyString str1("Hello, world!");
    MyString str2(str1);

    SECTION("Access to random character of MyString via .at(): ") {
        try {
            char ch = str0.at(1);
        }
        catch (const std::out_of_range& oor) {
            REQUIRE(oor.what() == "No such position in string");
        }

        REQUIRE(str1.at(2) == 'l');
        REQUIRE(str2.at(6) == ' ');
    }

    SECTION("Access to first character of MyString via .front(): ") {
        REQUIRE(str1.front() == 'H');
        REQUIRE(str2.front() == 'H');
    }

    SECTION("Access to last character of MyString via .back(): ") {
        REQUIRE(str1.back() == '!');
        REQUIRE(str2.back() == '!');
    }

    SECTION("Checking wether MyString is empty: ") {
        REQUIRE(str0.empty() == true);
        REQUIRE(str1.empty() == false);
        REQUIRE(str2.empty() == false);
    }

    SECTION("Clearing a MyString object via .clear(): ") {
        str1.clear();
        REQUIRE(str1.empty() == true);
    }

    SECTION("Adding a character to the back of MyString: ") {
        str2.push_back('?');

        REQUIRE(str2.size() == 14);
        REQUIRE(str2.back() == '?');
    }

    SECTION("Adding a character to the back of empty MyString: ") {
        str0.push_back('a');

        REQUIRE(str0.size() == 1);
        REQUIRE(str0.front() == 'a');
        REQUIRE(str0.back() == 'a');
    }

    SECTION("Adding a character to the back of empty MyString: ") {
        str1.pop_back();

        REQUIRE(str0.size() == 12);
        REQUIRE(str0.back() == 'd');
    }

    SECTION("Converting MyString to c_string: ") {
        const char* c_str = "Hello, world!";

        REQUIRE(str0.c_str() == nullptr);
        REQUIRE(str1.c_str() == c_str);
    }
}

TEST_CASE("Testing MyString class operators") {
    MyString str0;
    MyString str1("Hello");
    MyString str2(", world!");
    MyString str3(str1);

    SECTION("Access to random character of MyString via [] operator: ") {
        REQUIRE(str1[1] == 'e');
        REQUIRE(str1[4] == 'o');
    }

    SECTION("Copy assignment operator for c_string: ") {
        str0 = "Hi";

        REQUIRE(str0.size() == 2);
        REQUIRE(str0.c_str() == "Hi");
    }

    SECTION("Copy assignment operator for MyString: ") {
        str0 = str1;

        REQUIRE(str0.size() == str1.size());
        REQUIRE(str0.c_str() == str1.c_str());
    }

    SECTION("Concatenation with char using +=: ") {
        str1 += '!';

        REQUIRE(str1.size() == 5);
        REQUIRE(str1.c_str() == "Hello!");
    }

    SECTION("Concatenation with MyString using +=: ") {
        str1 += str2;

        REQUIRE(str1.size() == 13);
        REQUIRE(str1.c_str() == "Hello, world!");
    }

    SECTION("Concatenation with char using +: ") {
        str0 = str1 + '!';

        REQUIRE(str0.size() == 6);
        REQUIRE(str0.c_str() == "Hello!");
    }

    SECTION("Concatenation with MyString using +: ") {
        str0 = str1 + str2;

        REQUIRE(str0.size() == 13);
        REQUIRE(str0.c_str() == "Hello, world!");
    }

    SECTION("Lexigraphical comparison with MyString using ==: ") {
        bool torf = (str1 == str3);

        REQUIRE(torf == true);
    }

    SECTION("Lexigraphical comparison with MyString using <: ") {
        bool torf = (str2 < str1);

        REQUIRE(torf == true);
    }
}