//
// Created by Yani Drenchev on 18.05.21.
//
#include "../Source/Registration.cpp"
#include "single_include/catch2/catch.hpp"
//This method capitalize every character
TEST_CASE("Registration valid test", "[registration valid constructor test]"){
    std::string validRegistration = "S1234ST";
    Registration reg(validRegistration);
    REQUIRE(reg.getRegistration() == validRegistration);

    validRegistration = "SS1234ST";
    Registration reg2(validRegistration);
    REQUIRE(reg2.getRegistration() == validRegistration);

    validRegistration = "ss1234st";
    Registration reg3(validRegistration);
    REQUIRE(reg2.getRegistration() == "SS1234ST");
}
// tests for exception with wrong registration number
TEST_CASE("Registration invalid test", "[registration invalid constructor test]"){
    std::string invalidRegistration = "S12345ST";
    Registration *reg;
    REQUIRE_THROWS(reg = new Registration(invalidRegistration));

    invalidRegistration = "";
    REQUIRE_THROWS(reg = new Registration(invalidRegistration));

    invalidRegistration = "S1234S";
    REQUIRE_THROWS(reg = new Registration(invalidRegistration));

    invalidRegistration = "ss1dasd13e1d@e12e12312casc234";
    REQUIRE_THROWS(reg = new Registration(invalidRegistration));

    invalidRegistration = "213908128309128903";
    REQUIRE_THROWS(reg = new Registration(invalidRegistration));
}
TEST_CASE("Registration operator == valid test", "[operator == valid test]"){
    std::string validRegistration = "S1234ST";
    Registration reg(validRegistration);
    Registration reg2(validRegistration);

    REQUIRE(reg == reg2);
}
TEST_CASE("Registration operator == invalid test", "[operator == invalid test]"){
    std::string validRegistration = "S1234ST";
    std::string validRegistration2 = "S1234TT";
    Registration reg(validRegistration);
    Registration reg2(validRegistration2);
    bool equal = reg == reg2;
    REQUIRE(!equal);
}

TEST_CASE("Registration operator = valid test", "[operator = valid test]"){
    std::string validRegistration = "S1234ST";
    std::string validRegistration2 = "S1234TT";
    Registration reg(validRegistration);
    Registration reg2(validRegistration2);
    reg = reg2;
    bool equal = reg == reg2;
    REQUIRE(equal);
}
