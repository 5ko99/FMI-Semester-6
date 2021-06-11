#define CATCH_CONFIG_MAIN
#include "../catch2/catch2.hpp"
#include "Registration.h"

//to compile: g++ RegistrationTest.cpp ../catch2/catch2.cpp Registration.cpp
TEST_CASE ("Constructor test")
{
    SECTION("Testing with a valid registration number")
    {
        Registration firstAttempt("C1234AB"); //length = 7, fA[0], fA[5], fA[6] = capital letter, fA[1] ... fA[4] = digit
        Registration secondAttempt("XY1111YX"); //length = 8, fA[0], fA[1], fA[5], fA[6] = capital letter, fA[1] ... fA[4] = digit

        REQUIRE(strcmp(firstAttempt.getRegNumber(),"C1234AB") == 0);
        REQUIRE(strcmp(secondAttempt.getRegNumber(),"XY1111YX") == 0);
    }

    SECTION("Testing with a smaller length") 
    {
        bool validOne = true, validTwo = true, validThree = true;

        try {
            Registration firstAttempt("111145"); //length = 6
        } catch (const std::exception& except) {
            validOne = false;
        }

        try {
            Registration secondAttempt("ABCDEF"); //length = 6
        } catch (const std::exception& except) {
            validTwo = false;
        }

        try {
            Registration thirdAttempt("C11D"); //length = 4
        } catch (const std::exception& except) {
            validThree = false;
        }

        REQUIRE(!validOne);
        REQUIRE(!validTwo);
        REQUIRE(!validThree);
    }

    SECTION("Testing with a bigger length") 
    {
        bool validOne = true, validTwo = true, validThree = true;

        try {
            Registration firstAttempt("ABC34DEFG"); //length = 9
        } catch (const std::exception& except) {
            validOne = false;
        }

        try {
            Registration secondAttempt("11114545AB"); //length = 10
        } catch (const std::exception& except) {
            validTwo = false;
        }

        try {
            Registration thirdAttempt("145C11DEFGH"); //length = 11
        } catch (const std::exception& except) {
            validThree = false;
        }

        REQUIRE(!validOne);
        REQUIRE(!validTwo);
        REQUIRE(!validThree);
    }

    SECTION("Testing with a correct length but incorrect format")
    {
        bool validOne = true, validTwo = true, validThree = true;

        try {
            Registration firstAttempt("ABC34DEF"); //fA[2] = capital letter
        } catch (const std::exception& except) {
            validOne = false;
        }

        try {
            Registration secondAttempt("c1234ab"); //small letters
        } catch (const std::exception& except) {
            validTwo = false;
        }

        try {
            Registration thirdAttempt("X11111YX"); //fA[1] = digit
        } catch (const std::exception& except) {
            validThree = false;
        }

        REQUIRE(!validOne);
        REQUIRE(!validTwo);
        REQUIRE(!validThree);
    }
}

TEST_CASE ("Operator == test")
{
    SECTION("Testing with identical registration numbers")
    {
        Registration firstAttempt("XY1111YX");
        Registration secondAttempt("XY1111YX");
        REQUIRE(firstAttempt == secondAttempt);

        Registration thirdAttempt("C1234AB");
        Registration fourthAttempt = thirdAttempt;
        REQUIRE(thirdAttempt == fourthAttempt);
    }

    SECTION("Testing with different registration numbers")
    {
        Registration firstAttempt("XY1111YX");
        Registration secondAttempt("XY1121YX");
        REQUIRE(!(firstAttempt == secondAttempt));

        Registration thirdAttempt("C1234AB");
        REQUIRE(!(firstAttempt == thirdAttempt));
        REQUIRE(!(thirdAttempt == secondAttempt));
    }
}
