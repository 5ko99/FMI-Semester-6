#include "catch2.hpp"
#include "Person.hpp"
#include "Commander.hpp"

TEST_CASE( "Commander tests", "[Commander]" )
{
    Commander& com = Commander::getInstance();

    SECTION("Split words")
    {
        REQUIRE(com.splitWords("  abvg   aa") == "abvg");
        REQUIRE(com.splitWords("abvg   aa") == "abvg");
        REQUIRE(com.splitWords("aa") == "aa");
        REQUIRE(com.splitWords("  ") == "");
        REQUIRE(com.splitWords("\"a\"") == "a");
        REQUIRE(com.splitWords(" \"a a a \" ") == "a a a ");
        REQUIRE(com.splitWords(" 12 3") == "12");
    }

}
