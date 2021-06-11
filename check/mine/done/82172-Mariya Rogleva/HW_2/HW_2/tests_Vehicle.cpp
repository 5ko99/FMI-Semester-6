#include "catch2.hpp"
#include "Vehicle.hpp"

TEST_CASE( "Creation", "[Vehicle]" )
{
    Vehicle test("AB1234CD", "car");

    SECTION("description, owner, registration")
    {
        REQUIRE(test.getOwnerId() == 0);
        REQUIRE(test.getDescription() == "car");
        REQUIRE(test.getReg() == "AB1234CD");
    }
    SECTION("invalid registration")
    {
        try
        {
            Vehicle invalid("ajsjsj", "aja");
        }
        catch(const std::exception& e)
        {
            REQUIRE(e.what() == "This registration is not valid");
        }
    }
    SECTION("add and remove owner")
    {
        unsigned id = 12;
        test.addOwner(12);
        REQUIRE(test.getOwnerId() == 12);
        test.removeOwner();
        REQUIRE(test.getOwnerId() == 0);
    }
}
