#include "catch2.hpp"
#include "Registration.h"


TEST_CASE("REGISTRATION TESTING")
{
    Registration reg1("AA2345DS");
    Registration reg2("WE2785D");
    Registration reg3("aa2345ds");
    Registration reg4("A5645ER");
    Registration reg5("55ABSS43");
    Registration reg6("AAA");
    Registration reg7("12345678");

    REQUIRE(reg1.get_registration() == "AA2345DS");
    REQUIRE(reg2.get_registration() == "");
    REQUIRE(reg3.get_registration() == "");
    REQUIRE(reg4.get_registration() == "A5645ER");
    REQUIRE(reg5.get_registration() == "");
    REQUIRE(reg6.get_registration() == "");
    REQUIRE(reg7.get_registration() == "");

    reg1 = reg3;
    reg2 = reg4;
    reg4 = reg1;

    REQUIRE(reg1.get_registration() == "AA2345DS");
    REQUIRE(reg2.get_registration() == "A5645ER");
    REQUIRE(reg3.get_registration() == "");
    REQUIRE(reg4.get_registration() == "AA2345DS");
}

TEST_CASE("OPERATOR== AND CLEAR TESTING ")
{
    Registration reg1("AA2345DS");
    Registration reg2("WE2785D");
    Registration reg3("aa2345ds");
    Registration reg4("A5645ER");
    Registration reg6("AAA");
    Registration reg7("12345678");

    REQUIRE_FALSE((reg1 == reg2));
    REQUIRE_FALSE((reg3 == reg4));
    REQUIRE_FALSE((reg1 == reg4));
    REQUIRE_FALSE((reg6 == reg1));
    REQUIRE((reg2 == reg3) == true);
    REQUIRE((reg6 == reg7) == true);
    REQUIRE((reg6 == reg2) == true);

    reg1.clear();
    reg4.clear();

    REQUIRE((reg2 == reg1) == true);
    REQUIRE((reg7 == reg4) == true);
    REQUIRE((reg1 == reg4) == true);
}
