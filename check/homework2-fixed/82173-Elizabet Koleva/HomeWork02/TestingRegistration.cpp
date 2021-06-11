#include "Catch2/catch_amalgamated.hpp"
#include "Registration.h"

TEST_CASE("Testing class Registration", "[registration]")
{
    SECTION("Constructor taking string")
    {
        WHEN("Registration from string variable")
        {
            string regN = "E1808BK";
            Registration test(regN);
            REQUIRE(test.getRegNumber() == regN);
        }

        WHEN("Registration with a valid argument")
        {
            REQUIRE_NOTHROW(Registration("AA1234BB"));
            REQUIRE_NOTHROW(Registration("A a 124 3 B b"));
            REQUIRE_NOTHROW(Registration("aa3333ff"));
            REQUIRE_NOTHROW(Registration("a4334ff"));
            REQUIRE_NOTHROW(Registration("H3433MM"));
            REQUIRE_NOTHROW(Registration("m 8322 WW"));
            REQUIRE_NOTHROW(Registration("a a 2 3 2 1 e e"));
            REQUIRE_NOTHROW(Registration("TX2201XT"));
            REQUIRE_NOTHROW(Registration("A0000ZZ"));
            REQUIRE_NOTHROW(Registration("a0000ZZ"));
            REQUIRE_NOTHROW(Registration("Z0000AA"));
        }

        WHEN("Registration with an invalid argument")
        {
            REQUIRE_THROWS(Registration("ABCDEFGH"));
		    REQUIRE_THROWS(Registration("12345678"));
            REQUIRE_THROWS(Registration("AAA123BB"));
            REQUIRE_THROWS(Registration("aa12aa"));
            REQUIRE_THROWS(Registration("a"));
            REQUIRE_THROWS(Registration("b0000"));
            REQUIRE_THROWS(Registration("H9999Y"));
            REQUIRE_THROWS(Registration("CC122334BB"));
            REQUIRE_THROWS(Registration("111111DH"));
            REQUIRE_THROWS(Registration("hh232h3jj"));
            REQUIRE_THROWS(Registration("23nnnb47"));
            REQUIRE_THROWS(Registration("68BAHF89"));
            REQUIRE_THROWS(Registration("a 4 3 2 1 h "));
            REQUIRE_THROWS(Registration(""));
        }
    }

    SECTION("Constructor taking registration") 
    {
        // WHEN("Taking invalid registration") 
        // {
        //     Registration faulty("A1234b");
        //     REQUIRE_THROWS(faulty);
        //     Registration test1(faulty);
        //     REQUIRE_THROWS(test1);
        //     REQUIRE(test1.getRegNumber() == "A1234b");
        // }
        WHEN("Taking correct registration") 
        {
            Registration good("A1234bW");
            Registration test(good);
            REQUIRE(test.getRegNumber() == "A1234BW");
        }
    }
    
    SECTION("Testing other functions")
    {
        WHEN("Testing capitalise letters")
        {
            Registration test("aa1234bb");
            REQUIRE(test.getRegNumber() == "AA1234BB");
        }
        
        // WHEN("Testing check reg")
        // {
        //     Registration test2("b2134ae");
        //     REQUIRE(test2.checkRegNumb() == true);
        // }
        
        WHEN("Testing get reg number")
        {
            Registration test("aa1234bb");
            REQUIRE(test.getRegNumber() == "AA1234BB");
        }
    }

    SECTION("Testing overloaded operators")
    {
        WHEN("Testing operator =")
        {
            Registration good("A1234bW");
            Registration test("r3332FT");
            test = good;
            REQUIRE(test.getRegNumber() == "A1234BW");
        }

        WHEN("Testing operator ==")
        {
            Registration good("A1234bW");
            Registration test("r3332FT");
            REQUIRE_FALSE(good == test);

            Registration test2("TX1234TW");
            Registration test3("tx1234tw");
            REQUIRE(test2 == test3);
        }
    }
}
