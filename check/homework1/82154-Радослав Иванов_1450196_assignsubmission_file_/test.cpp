#include "../../Catch2/catch.h"
#include "../Code/garagesystem.h"
#define CATCH_CONFIG_MAIN

TEST_CASE("Testing MyString")
{
    MyString string("Hello");
    REQUIRE(string.size() == 5);
    REQUIRE(string[2] == 'l');
    REQUIRE_THROWS_AS(string[6], std::out_of_range);
    REQUIRE_THROWS_AS(string[-1], std::out_of_range);
    REQUIRE(string.front() == 'H');
    REQUIRE(string.back() == 'o');
    MyString copy(string);
    REQUIRE(string == copy);
    string.push_back('x');
    REQUIRE(string.back() == 'x');
    string.pop_back();
    string += MyString(" World");
    REQUIRE(string == MyString("Hello World"));
    string += string;
    REQUIRE(string == MyString("Hello WorldHello World"));
    REQUIRE(string > copy); //copy should be 'Hello'
    copy += 'c';
    REQUIRE(string < copy); //because 'c' > ' '
    string.clear();
    REQUIRE(string.empty() == true);
    string.push_back('-');
    string.push_back('s');
    string = string + string + copy + ' ' + copy + ' ' + 'a'; 
    REQUIRE(string == MyString("-s-sHelloc Helloc a"));
}

TEST_CASE("Testing Vehicle")
{
    Vehicle v("EO 2021 FW", "My favourite car", 10);
    REQUIRE(MyString(v.registration()) == MyString("EO 2021 FW"));
    REQUIRE(MyString(v.description()) == MyString("My favourite car"));
    REQUIRE(v.space() == 10);
}

TEST_CASE("Testing Garage")
{
    Garage garage(20);
    REQUIRE(garage.empty());
    Vehicle v1("12345", "First Vehicle", 10);
    garage.insert(v1);
    REQUIRE(garage.size() == 1);
    REQUIRE(!garage.empty());
    Vehicle v2("12346", "Big Vehicle", 15);
    REQUIRE_THROWS_AS(garage.insert(v2), const char*);
    REQUIRE(garage.find("12346") == nullptr);
    REQUIRE_THROWS_AS(garage.at(1), std::out_of_range);
    Vehicle v3("12347", "Small Vehicle", 1);
    garage.insert(v3);
    REQUIRE(garage.size() == 2);
    garage.erase("12345");
    garage.erase("12347");
    REQUIRE(garage.empty());
    
    garage.insert(v2);
    garage.insert(v3);
    REQUIRE_THROWS_AS(garage.insert(v3), const char*); //trying to add an existing vehicle
    REQUIRE(garage.size() == 2);
    garage.clear();
    REQUIRE(garage.empty());
}

TEST_CASE("Testing DynamicArray")
{
    DynamicArray DA(2);
    Vehicle v1("12345", "First vehicle", 10);
    DA.addVehicle(v1);
    Vehicle v2("12346", "Second Vehicle", 12);
    DA.addVehicle(v2);
    Vehicle v3("12347123", "Third vehicle", 15);
    DA.addVehicle(v3);
    REQUIRE(MyString(DA.getLastAdded().registration()) == MyString("12347123"));
    REQUIRE(MyString(DA.getLastAdded().description()) == MyString("Third vehicle"));
    REQUIRE(DA.getLastAdded().space() == 15);
}