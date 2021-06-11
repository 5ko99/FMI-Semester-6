#include "catch2.hpp"
#include "Registration.h"
#include <iostream>
TEST_CASE("Registration::isValid")
{
    char str[] = "AB1234NC";
    CHECK(Registration::isValid(str));
    strcpy(str, "A1111BQ");
    CHECK(Registration::isValid(str));
    strcpy(str, "");
    CHECK(!Registration::isValid(str));
    strcpy(str, "aaaa");
    CHECK(!Registration::isValid(str));
    strcpy(str, "AAA123VV");
    CHECK(!Registration::isValid(str));
    strcpy(str, "1111111");
    CHECK(!Registration::isValid(str));
    strcpy(str, "AB9999U");
    CHECK(!Registration::isValid(str));
    char str1[] = "PO6789222";
    CHECK(!Registration::isValid(str1));
}
TEST_CASE("Registration::operator ==")
{
    SECTION("Same with length 7")
    {
        Registration reg1("N4612MM");
        Registration reg2("N4612MM");
        bool same = (reg1 == reg2);
        CHECK(same);
    }
    SECTION("Same with length 8")
    {
        Registration reg1("VV9123KL");
        Registration reg2("VV9123KL");
        bool same = (reg1 == reg2);
        CHECK(same);
    }
    SECTION("Different length 7")
    {
        Registration reg1("Q4444PO");
        Registration reg2("Q4443PO");
        bool same = (reg1 == reg2);
        CHECK(!same);
    }
    SECTION("Different length 8")
    {
        Registration reg1("SS2378IO");
        Registration reg2("SS2278IO");
        bool same = (reg1 == reg2);
        CHECK(!same);
    }
}
