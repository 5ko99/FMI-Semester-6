#include "catch.h"
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"

#define CATCH_CONFIG_MAIN
TEST_CASE("Operator==InPerson")
{
    Person test1("gosho", 123);
    Person test2("tosho", 123);
    Person test3("pesho", 321);
    bool isEqual = (test1 == test2);
    bool isNotEqual = (test1 == test3);
    REQUIRE(isEqual == 1);
    REQUIRE(isNotEqual == 0);
}
TEST_CASE("getNameMethodInPerson")
{
    Person test1("gosho", 123);
    bool isEqual = (test1.getName() == "gosho");
    bool isNotEqual = (test1.getName() == "tosho");
    REQUIRE(isEqual == 1);
    REQUIRE(isNotEqual == 0);
}
TEST_CASE("getIdMethodInPerson")
{
    Person test1("gosho", 123);
    bool isEqual = (test1.getId() == 123);
    bool isNotEqual = (test1.getId() == 321);
    REQUIRE(isEqual == 1);
    REQUIRE(isNotEqual == 0);
}
