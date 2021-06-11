#include "catch2.hpp"
#include <cstring>
#include "../MainProject/Headers/CharArrUtils.h"


TEST_CASE( "Testing subarr function") {
    SECTION("Testing with start greater than end") {
        char arr[] = "Test array";
        REQUIRE_THROWS_AS(CharArrUtils::subArr(arr, 8, 5), std::invalid_argument);
        CHECK_THROWS_AS(CharArrUtils::subArr(arr, 8, 5), std::invalid_argument);
    }

    SECTION("Testing with start equal to end") {
        char arr[] = "Test array";
        REQUIRE(strcmp(CharArrUtils::subArr(arr, 8, 8), "\0") == 0);
    }

    SECTION("Testing with start more than length") {
        char arr[] = "Test array";
        REQUIRE_THROWS_AS(CharArrUtils::subArr(arr, 25, 30), std::invalid_argument);
        CHECK_THROWS_AS(CharArrUtils::subArr(arr, 25, 30), std::invalid_argument);
    }

    SECTION("Testing with end more than length") {
        char arr[] = "Test array";
        REQUIRE_THROWS_AS(CharArrUtils::subArr(arr, 5, 30), std::invalid_argument);
        CHECK_THROWS_AS(CharArrUtils::subArr(arr, 5, 30), std::invalid_argument);
    }

    SECTION("Testing with negative start") {
        char arr[] = "Test array";
        REQUIRE_THROWS_AS(CharArrUtils::subArr(arr, -1, 30), std::invalid_argument);
        CHECK_THROWS_AS(CharArrUtils::subArr(arr, -1, 30), std::invalid_argument);
    }
    
    SECTION("Testing with negative end") {
        char arr[] = "Test array";
        REQUIRE_THROWS_AS(CharArrUtils::subArr(arr, -5, -2), std::invalid_argument);
        CHECK_THROWS_AS(CharArrUtils::subArr(arr, -5, -2), std::invalid_argument);
    }

    SECTION("Testing empty array") {
        char arr[] = "";
        REQUIRE(strcmp(CharArrUtils::subArr(arr, 0, 0), "\0") == 0);
    }
}

TEST_CASE( "Testing toLowerCharArr function") {
    SECTION("Testing empty array") {
        char arr[] = "";
        CharArrUtils::toLowerCharArr(arr);
        REQUIRE(strcmp(arr, "\0") == 0);
    }

    SECTION("Testing simple array") {
        char arr[] = "A SiMpLE aRR";
        CharArrUtils::toLowerCharArr(arr);
        REQUIRE(strcmp(arr, "a simple arr") == 0);
    }

    SECTION("Testing with digits array") {
        char arr[] = "122333";
        CharArrUtils::toLowerCharArr(arr);
        REQUIRE(strcmp(arr, "122333") == 0);
    }
}
