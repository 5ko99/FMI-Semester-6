#include "catch2.hpp"
#include "MyString.h"
#include "Vehicle.h"


TEST_CASE("Getters Testing for Vehicle")
{
    Vehicle vehicle1("Test", "Medium", 6);
    Vehicle vehicle2("Car", "Small", 4);
    Vehicle vehicle3("Bus", "Big", 8);
    Vehicle vehicle4("Bus", "Small", 6);
   

    const char *name1 = vehicle1.get_registration();
    const char *name2 = vehicle2.get_registration();
    const char *name3 = vehicle3.get_registration();
    const char *name4 = vehicle4.get_registration();

    REQUIRE(MystrcmpareEquality(name1, vehicle1.get_registration()) == 1);
    REQUIRE(MystrcmpareEquality(name2, vehicle2.get_registration()) == 1);
    REQUIRE(MystrcmpareEquality(name3, vehicle3.get_registration()) == 1);
    REQUIRE(MystrcmpareEquality(name4, vehicle4.get_registration()) == 1);

    const char *descr1 = vehicle1.get_description();
    const char *descr2 = vehicle2.get_description();
    const char *descr3 = vehicle3.get_description();
    const char *descr4 = vehicle4.get_description();

    REQUIRE(MystrcmpareEquality(descr1, vehicle1.get_description()) == 1);
    REQUIRE(MystrcmpareEquality(descr2, vehicle2.get_description()) == 1);
    REQUIRE(MystrcmpareEquality(descr3, vehicle3.get_description()) == 1);
    REQUIRE(MystrcmpareEquality(descr4, vehicle4.get_description()) == 1);

    std::size_t size1 = vehicle1.get_space();
    std::size_t size2 = vehicle2.get_space();
    std::size_t size3 = vehicle3.get_space();
    std::size_t size4 = vehicle4.get_space();

    REQUIRE(size1 == 6);
    REQUIRE(size2 == 4);
    REQUIRE(size3 == 8);
    REQUIRE(size4 == 6);

   // Vehicle vehicle5("Plane", "VeryBig", 0); // Deliberate error
   // Vehicle vehicle6(nullptr, "VeryBig", 1); // Deliberate error
   // Vehicle vehicle7("Plane", nullptr, 2);   // Deliberate error
}

