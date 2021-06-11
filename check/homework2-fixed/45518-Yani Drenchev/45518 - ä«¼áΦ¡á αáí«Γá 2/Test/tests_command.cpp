//
// Created by Yani Drenchev on 18.05.21.
//
#define CATCH_CONFIG_MAIN
#include "../Source/Command.cpp"
#include "single_include/catch2/catch.hpp"


TEST_CASE("ParseCommand valid tests", "[parseCommand valid]") {
    std::string testCommand = "Person yani 2";
    auto x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::PERSON);
    REQUIRE(x.second[0] == "yani");
    REQUIRE(x.second[1] == "2");

    testCommand = "vehicle TS1234TS 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::VEHICLE);
    REQUIRE(x.second[0] == "TS1234TS");
    REQUIRE(x.second[1] == "2");

    testCommand = "vehicle TS1234TS \"description \" ";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::VEHICLE);
    REQUIRE(x.second[0] == "TS1234TS");
    REQUIRE(x.second[1] == "\"description \"");

    testCommand = "acquire TS1234TS 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::ACQUIRE);
    REQUIRE(x.second[0] == "TS1234TS");
    REQUIRE(x.second[1] == "2");

    testCommand = "release TS1234TS 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::RELEASE);
    REQUIRE(x.second[0] == "TS1234TS");
    REQUIRE(x.second[1] == "2");

    testCommand = "person \"Yani Drenchev\" 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::PERSON);
    REQUIRE(x.second[0] == "\"Yani Drenchev\"");
    REQUIRE(x.second[1] == "2");

    testCommand = "remove 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::REMOVE);
    REQUIRE(x.second[0] == "2");
}

//all functions included in reading commands are tested in these two cases
TEST_CASE("ParseCommand invalid tests", "[parseCommand invalid]") {
    std::string testCommand = "release 2";
    auto x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "release TS1234TS";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "release";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "person ";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "person 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "vehicle 2";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "vehicle TS1234TS";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "vehicle ";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "remove ";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = "";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);

    testCommand = " ";
    x = parseCommand(testCommand);
    REQUIRE(x.first == CommandCode::NIL);
}

