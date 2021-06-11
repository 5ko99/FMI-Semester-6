#include "Catch2/catch_amalgamated.hpp"
#include "Person.h"

TEST_CASE("Testing class Person", "[vehicle]")
{
    SECTION("Testing contructor")
    {
        WHEN("Testing with good arguments")
        {
            REQUIRE_NOTHROW(Person("Betka", 42));
            REQUIRE_NOTHROW(Person("A123Z", 689));
            REQUIRE_NOTHROW(Person("Fifi Peroto", 472954122));
            REQUIRE_NOTHROW(Person("Pablo Diego JosГ© Francisco\
                                    de Paula Juan Nepomuceno\
                                    MarГ­a de los Remedios Cipriano\
                                    de la SantГ­sima Trinidad Ruiz\
                                    y Picasso", 000));

        }

        WHEN("Testing with bad arguments")
        {
            REQUIRE_THROWS(Person("", 0));
            // REQUIRE_THROWS(Person("", ));
            // REQUIRE_THROWS(Person("Asen Petrov", 234.12));
        }

    }

    SECTION("Testing the other functions without vehicle relationships")
    {
        Person test1("Liz", 2201);
        Person test2("Stephen", 888999);

        WHEN("Testing get ID")
        {
            REQUIRE(test1.getID() == 2201);
            REQUIRE(test1.getName() == "Liz");

        }

        WHEN("Testing get name")
        {
            REQUIRE(test2.getID() == 888999);
            REQUIRE(test2.getName() == "Stephen");
        }

        WHEN("Testing operator =")
        {
            Person test1("Alex", 1234);
            Person test2("Deo", 4321);
            test1 = test2;

            REQUIRE(test1.getID() == 4321);
            REQUIRE(test1.getName() == "Deo");
            
        }
    }

}
