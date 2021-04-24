#define CATCH_CONFIG_MAIN
#include <assert.h>

#include <cstring>
#include <iostream>

#include "Headers/Garage.hpp"
#include "Headers/MyString.hpp"
#include "Headers/Vehicle.hpp"
#include "catch2/catch2.hpp"

TEST_CASE("Tests of MyString") {
    MyString mystringEmpty;
    MyString mystring1("123");
    MyString mystring1copy("123");
    MyString mystring1copy2("143");
    MyString mystring2("abcde");
    const MyString mystring2const("abcde");
    MyString mystring3("My");

    SECTION("Copy and access strings test") {
        MyString mystring3 = mystring2;
        REQUIRE(strcmp(mystring3.c_str(), mystring2.c_str()) == 0);
    }

    SECTION("Access index of string test") {
        REQUIRE(mystring2.at(0) == 'a');
        REQUIRE(mystring2.at(1) == 'b');
        REQUIRE(mystring2.at(2) == 'c');
        REQUIRE(mystring2.at(3) == 'd');
        REQUIRE(mystring2.at(4) == 'e');
    }

    SECTION("Access index of string test error") {
        REQUIRE_THROWS_AS(mystring2.at(10), std::out_of_range);
    }

    SECTION("Access index of string with constant test") {
        char symbol = mystring2const.at(1);
        REQUIRE(symbol == 'b');
        symbol = mystring2const.at(3);
        REQUIRE(symbol == 'd');
    }

    SECTION("Access index of string with constant test error") {
        REQUIRE_THROWS_AS(mystring2const.at(10), std::out_of_range);
    }

    SECTION("Access index of string with [] test") {
        REQUIRE(mystring1[0] == '1');
        REQUIRE(mystring1[1] == '2');
        REQUIRE(mystring1[2] == '3');
        REQUIRE(mystring2[0] == 'a');
        REQUIRE(mystring2[1] == 'b');
        REQUIRE(mystring2[2] == 'c');
        REQUIRE(mystring2[3] == 'd');
        REQUIRE(mystring2[4] == 'e');
    }

    SECTION("Access index of string with [] and constant test") {
        char symbol = mystring2const[3];
        REQUIRE(symbol == 'd');
    }

    SECTION("First symbol access test") {
        REQUIRE(mystring1.front() == '1');
        REQUIRE(mystring2.front() == 'a');
    }

    SECTION("First symbol access test const") {
        const MyString string1("hello");
        const char character = string1.front();
        REQUIRE(character == 'h');
    }

    SECTION("Last symbol access test") {
        REQUIRE(mystring1.back() == '3');
        REQUIRE(mystring2.back() == 'e');
    }

    SECTION("Last symbol access test const") {
        const MyString string1("hello");
        const char character = string1.back();
        REQUIRE(character == 'o');
    }

    SECTION("First symbol access const test") {
        char symbol = mystring2.front();
        REQUIRE(symbol == 'a');
    }

    SECTION("Last symbol access const test") {
        char symbol = mystring2const.back();
        REQUIRE(symbol == 'e');
    }
    SECTION("String size test") {
        REQUIRE(mystring1.size() == 3);
        REQUIRE(mystring2.size() == 5);
    }

    SECTION("Empty string test") {
        REQUIRE(mystringEmpty.empty() == true);
        REQUIRE(mystring1.empty() == false);
    }

    SECTION("Clear string test") {
        mystring1.clear();
        REQUIRE(mystring1[0] == ' ');
        REQUIRE(mystring1[1] == ' ');
        REQUIRE(mystring1[2] == ' ');
    }

    SECTION("Puсh character test") {
        mystring1.push_back('#');
        REQUIRE(mystring1.back() == '#');
    }

    SECTION("Pop character test") {
        mystring1.pop_back();
        REQUIRE(mystring1.back() == '2');
    }

    SECTION("Concatenation with symbol test") {
        mystring3 += '#';
        REQUIRE(mystring3.back() == '#');
    }

    SECTION("Concatenation with string test") {
        mystring3 += mystring1;
        REQUIRE(mystring3[2] == '1');
    }

    SECTION("String concatenation with symbol test") {
        MyString mystring4 = mystring1 + '?';
        REQUIRE(mystring4[3] == '?');
    }

    SECTION("String concatenation with symbol test") {
        MyString mystring5 = mystring1 + mystring2;
        REQUIRE(mystring5[3] == 'a');
    }

    SECTION("Comparing strings test") {
        REQUIRE((mystring1 == mystring2) == 0);
        REQUIRE((mystring1 == mystring1copy) == 1);
        REQUIRE((mystring1copy == mystring1) == 1);
    }

    SECTION("Comparing strings test") {
        REQUIRE((mystring1 == mystring1copy2) == 0);
    }

    SECTION("Comparing strings test") { REQUIRE((mystring1 < mystring2) == 1); }

    SECTION("Comparing strings test") {
        REQUIRE((mystring1 < mystring1copy) == 0);
    }

    SECTION("Comparing strings test") {
        REQUIRE((mystring1 < mystring1copy2) == 1);
    }
}

TEST_CASE("Tests of Vehicle") {
    Vehicle myvehicle1("1234", "Vehicle description", 3);
    Vehicle myvehicle2("2000", "Blue car", 2);

    SECTION("Access registration test") {
        REQUIRE(strcmp(myvehicle1.registration(), "1234") == 0);
        REQUIRE(strcmp(myvehicle2.registration(), "2000") == 0);
    }

    SECTION("Access description test") {
        REQUIRE(strcmp(myvehicle1.description(), "Vehicle description") == 0);
        REQUIRE(strcmp(myvehicle2.description(), "Blue car") == 0);
    }

    SECTION("Access space test") {
        REQUIRE(myvehicle1.space() == 3);
        REQUIRE(myvehicle2.space() == 2);
    }
}


TEST_CASE("Tests of Garage") {
    Garage mygarage1(10);
    Vehicle myvehicle1("1234", "Red car", 1);
    Vehicle myvehicle2("2000", "Blue car", 2);
    Vehicle myvehicle3("2468", "Yellow car", 1);
    Vehicle myvehicle4("4242", "Black spaceship", 2);
    Vehicle myvehicleBig("9999", "White submarine", 7);
    mygarage1.insert(myvehicle1);
    mygarage1.insert(myvehicle2);
    mygarage1.insert(myvehicle3);
    mygarage1.insert(myvehicle4);

    SECTION("Garage is created, vehicles are added, index access test") {
        REQUIRE(strcmp(mygarage1.at(1).registration(), "1234") == 0);
        REQUIRE(strcmp(mygarage1.at(2).registration(), "2000") == 0);
        REQUIRE(strcmp(mygarage1.at(3).description(), "Yellow car") == 0);
        REQUIRE(strcmp(mygarage1.at(4).description(), "Black spaceship") == 0);
    }

    SECTION("Garage is created, vehicles are added, index access [] test") {
        REQUIRE(strcmp(mygarage1[1].description(), "Red car") == 0);
        REQUIRE(strcmp(mygarage1[2].description(), "Blue car") == 0);
        REQUIRE(strcmp(mygarage1[3].registration(), "2468") == 0);
        REQUIRE(strcmp(mygarage1[4].registration(), "4242") == 0);
    }

    SECTION("Copy constructor test") {
        Garage mygarage2(mygarage1);
        REQUIRE(strcmp(mygarage2[1].registration(), "1234") == 0);
        REQUIRE(strcmp(mygarage2[2].description(), "Blue car") == 0);
        REQUIRE(mygarage2[3].space() == 1);
    }

    SECTION("Copy assignment operator test") {
        Garage mygarage2(4);
        mygarage2 = mygarage1;
        REQUIRE(mygarage2[2].space() == 2);
        REQUIRE(strcmp(mygarage2[3].registration(), "2468") == 0);
        REQUIRE(strcmp(mygarage2[4].description(), "Black spaceship") == 0);
    }

    SECTION("Insert multiple test error") {
        REQUIRE_THROWS_AS(mygarage1.insert(myvehicle1), std::logic_error);
        REQUIRE_THROWS_AS(mygarage1.insert(myvehicle2), std::logic_error);
    }

    SECTION("Insert big vehicle test error") {
        REQUIRE_THROWS_AS(mygarage1.insert(myvehicleBig), std::logic_error);
    }

    SECTION("Remove vehicle test") {
        mygarage1.erase("2000");
        REQUIRE(strcmp(mygarage1[1].registration(), "1234") == 0);
        REQUIRE(strcmp(mygarage1[2].registration(), "4242") == 0);
        REQUIRE(strcmp(mygarage1[3].registration(), "2468") == 0);
    }

    SECTION("Access element test error") {
        REQUIRE_THROWS_AS(mygarage1.at(10), std::out_of_range);
    }

    SECTION("Empty garage test") {
        Garage mygarageempty(0);
        REQUIRE(mygarageempty.empty() == true);
    }

    SECTION("Empty garage test") { REQUIRE(mygarage1.empty() == false); }

    SECTION("Size of garage test") {
        REQUIRE(mygarage1.size() == 4);
        Vehicle myvehicle5("5555", "Silver UFO", 1);
        mygarage1.insert(myvehicle5);
        REQUIRE(mygarage1.size() == 5);
    }

    SECTION("Find in garage test") {
        REQUIRE(strcmp(mygarage1.find("2468")->description(), "Yellow car") ==
                0);
    }

    SECTION("Find in garage test error") {
        REQUIRE(mygarage1.find("0000") == nullptr);
    }

    SECTION("Clear garage test") {
        mygarage1.clear();
        REQUIRE(mygarage1.size() == 0);
    }

}
