
#include "../Catch2/catch_amalgamated.cpp"
#include "MyString.cpp"
#include "Vehicle.cpp"
#include "Garage.cpp"

#include <cstring>

TEST_CASE("GarageTestInsert"){
    Vehicle a("Poe", "The Best Car", 12);
    Garage b(100);
    b.insert(a);
    REQUIRE(b.empty() == false);
    REQUIRE(strcmp(b.at(1).description(), "The Best Car" ) == 0);
    REQUIRE(strcmp(b.operator[](1).registration(), "Poe" ) == 0);
    REQUIRE(b.size() == 1);

    b.erase("Poe");
    REQUIRE(b.empty() == true);
    b.insert(a);
    b.clear();
    REQUIRE(b.size() == 0);
    b.insert(a);
    REQUIRE(strcmp(b.find("Poe")->description(), "The Best Car") == 0) ;

}
