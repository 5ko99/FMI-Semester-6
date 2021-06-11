#include "catch2.hpp"
#include "Registration.hpp"

TEST_CASE( "Verifications check", "[Registration]" )
{
    Registration valid1("AB2787CD");
    Registration valid2("A3738XC");
    
    // Registration test2("12873827");
    // Registration test3("a1728ab");
    // Registration test4("xz1111ab");

    SECTION("should pass")
    {
        REQUIRE(valid1.getReg() == "AB2787CD");
        REQUIRE(valid2.getReg() == "A3738XC");
    }
    SECTION("should throw an exception")
    {
        try
        {
            Registration test("JDjdjdJD");
        }
        catch(const std::exception& e)
        {
            REQUIRE(e.what() == "This registration is not valid"); //I do it this way, because the exception should be 
            //thrown on construction
        }
    }
    SECTION("should throw an exception")
    {
        try
        {
            Registration test("AB1222CD1");
        }
        catch(const std::exception& e)
        {
            REQUIRE(e.what() == "This registration is not valid");
        }
    }
    SECTION("should throw an exception")
    {
        try
        {
            Registration test("a7777xy");
        }
        catch(const std::exception& e)
        {
            REQUIRE(e.what() == "This registration is not valid");
        }
    }
    SECTION("should throw an exception")
    {
        try
        {
            Registration test("12777712");
        }
        catch(const std::exception& e)
        {
            REQUIRE(e.what() == "This registration is not valid");
        }
    }

}
