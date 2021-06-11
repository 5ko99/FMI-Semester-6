#define CATCH_CONFIG_MAIN

#include "../catch2.hpp"
#include "../../models/registration/registration.hpp"

TEST_CASE("Creating new Registration"){
    SECTION("Nullptr argument"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_THROWS_WITH(reg=new Registration(nullptr), "Registration cannot be null!");
    }
    SECTION("Invalid number - only numbers, but valid length"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_THROWS_WITH(reg=new Registration("12345678"), "Invalid registration number!");
    }
    SECTION("Invalid number - only letters"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_THROWS_WITH(reg=new Registration("AABBBBCC"), "Invalid registration number!");
    }
    SECTION("Invalid number - valid symbols, but invalid length"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_THROWS_WITH(reg=new Registration("S3456SSA"), "Invalid registration number!");
    }
    SECTION("Invalid number - invalid number of numbers"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_THROWS_WITH(reg=new Registration("SS12345AA"), "Invalid registration number!");
    }
    SECTION("Invalid number - lower case letters"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_THROWS_WITH(reg=new Registration("sA1234AA"), "Invalid registration number!");
    }
    SECTION("Valid number with 2 letters in the beginning"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_NOTHROW(reg=new Registration("SS1234AA"));
    }
    SECTION("Valid number with one letter in the beginning"){
        //Arrange
        Registration* reg;

        //Assert
        REQUIRE_NOTHROW(reg=new Registration("S1234AA"));
    }

    
}

TEST_CASE("Check if the registration mathches the given string"){
    SECTION("Invalid argument - nullptr"){
        //Arrange
        Registration reg("S1234AA");

        //Assert
        REQUIRE_THROWS_WITH(reg==nullptr, "Registration should not be null!");
    }

    SECTION("Not equal"){
        //Arrange
        Registration reg("S1234AA");

        //Assert
        REQUIRE_FALSE(reg=="SA1234AA");
    }

    SECTION("Equal"){
        //Arrange
        Registration reg("S1234AA");

        //Assert
        REQUIRE(reg=="S1234AA");
    }
}
