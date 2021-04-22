#include "catch.h"
#include "MyString.h"
#define CATCH_CONFIG_MAIN

TEST_CASE("At_func")
{
    MyString test1("Car1");
    SECTION("testes with wrong pos") {
        REQUIRE_THROWS_AS(test1.at(5), std::out_of_range);
        REQUIRE_THROWS_AS(test1.at(-3), std::out_of_range);
    }
    REQUIRE(test1.at(1)=='a');
}
TEST_CASE("Front_func")
{
    MyString test1("Car2");
    REQUIRE(test1.front()=='C');
}
TEST_CASE("Back_func")
{
    MyString test1("Car3");
    REQUIRE(test1.back()=='3');
}
TEST_CASE("Empty_func")
{
    MyString test1("Car4");
    REQUIRE(test1.empty() == 0);
    test1 = MyString("");
    REQUIRE(test1.empty() == 1);
}
TEST_CASE("Size_func")
{
    MyString test1("Car5");
    REQUIRE(test1.size()==4);
}
TEST_CASE("Clear_func")
{
    MyString test1("Car6");
    MyString test2("");
    test1.clear();
    REQUIRE(test1==test2);
}
TEST_CASE("Push_back_func")
{
    MyString test1("Car7");
    test1.push_back('0');
    REQUIRE(strcmp(test1.c_str(),"Car70") == 0);
}
TEST_CASE("Pop_back_func")
{
    MyString test1("Car8");
    test1.pop_back();
    REQUIRE(strcmp(test1.c_str(),"Car") == 0);
}
TEST_CASE("c_str_func")
{
    MyString test1("Car9");
    REQUIRE(strcmp(test1.c_str(),"Car9") == 0);
}
