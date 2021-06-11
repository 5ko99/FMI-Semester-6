#include "catch2.hpp"
#include "../MainProject/Headers/ValidationUtils.h"
#include <string>
#include <cstring>
#include <vector>

using std::vector;
using std::string;

TEST_CASE( "Testing isValid NumberPlate functions") {
    SECTION("Testing with a valid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("CA1234BA") == true);
    }
    SECTION("Testing with another valid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("C1234BA") == true);
    }
    SECTION("Testing with an invalid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("CAA1234BA") == false);
    }
    SECTION("Testing with another invalid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("CA1234B") == false);
    }
    SECTION("Testing with third invalid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("CA123456") == false);
    }
    SECTION("Testing with fourth invalid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("12345678") == false);
    }
    SECTION("Testing with fourth invalid number plate") {
        REQUIRE(ValidationUtils::isValidNumberPlate("CAAAAAAA") == false);
    }
}

TEST_CASE( "Testing isValidId functions") {
    SECTION("Testing with a valid id") {
        REQUIRE(ValidationUtils::isValidId("1") == true);
    }
    SECTION("Testing with another valid id") {
        REQUIRE(ValidationUtils::isValidId("123") == true);
    }
    SECTION("Testing with third valid id") {
        REQUIRE(ValidationUtils::isValidId("1234") == true);
    }
    SECTION("Testing with an invalid id") {
        REQUIRE(ValidationUtils::isValidId("12345") == false);
    }
    SECTION("Testing with another invalid id") {
        REQUIRE(ValidationUtils::isValidId("") == false);
    }
}

TEST_CASE( "Testing isLetter function") {
    SECTION("Testing with a valid letter") {
        REQUIRE(ValidationUtils::isLetter('B') == true);
    }
    SECTION("Testing with another valid letter") {
        REQUIRE(ValidationUtils::isLetter('A') == true);
    }
    SECTION("Testing with third valid letter") {
        REQUIRE(ValidationUtils::isLetter('Z') == true);
    }
    SECTION("Testing with fourth invalid letter") {
        REQUIRE(ValidationUtils::isLetter('5') == false);
    }
    SECTION("Testing with fifth invalid letter") {
        REQUIRE(ValidationUtils::isLetter('\n') == false);
    }
}

TEST_CASE( "Testing isDigit function") {
    SECTION("Testing with a valid letter") {
        REQUIRE(ValidationUtils::isDigit('1') == true);
    }
    SECTION("Testing with another valid letter") {
        REQUIRE(ValidationUtils::isDigit('0') == true);
    }
    SECTION("Testing with third valid letter") {
        REQUIRE(ValidationUtils::isDigit('9') == true);
    }
    SECTION("Testing with fourth invalid letter") {
        REQUIRE(ValidationUtils::isDigit('a') == false);
    }
    SECTION("Testing with fifth invalid letter") {
        REQUIRE(ValidationUtils::isDigit('A') == false);
    }
    SECTION("Testing with sixth invalid letter") {
        REQUIRE(ValidationUtils::isDigit('\n') == false);
    }
}
