#include "catch2.hpp"
#include "../MainProject/Headers/CommandExecutor.h"
#include <string>
#include <cstring>
#include <vector>

using std::vector;
using std::string;

TEST_CASE( "CommandExecutor instances can be created correctly") {
    SECTION("Testing default constructor") {
        CommandExecutor ce;
        REQUIRE(ce.isExitCommand() == false);
    }
}

TEST_CASE("Testing executeCommand and isExitCommand function") {
    SECTION("Testing with exitCommand") {
        CommandExecutor ce;
        REQUIRE(ce.isExitCommand() == false);
        vector<string> arguments;
        ce.executeCommand("exit", arguments);
        REQUIRE(ce.isExitCommand() == true);
    }

    SECTION("Testing with non-exit command") {
        CommandExecutor ce;
        REQUIRE(ce.isExitCommand() == false);
        vector<string> arguments;
        arguments.push_back("X5859KC");
        arguments.push_back("BMW 530");
        ce.executeCommand("vehicle", arguments);
        REQUIRE(ce.isExitCommand() == false);
    }

    SECTION("Testing with second non-exit command") {
        CommandExecutor ce;
        REQUIRE(ce.isExitCommand() == false);
        vector<string> arguments;
        arguments.push_back("IvanDraganov");
        ce.executeCommand("person", arguments);
        REQUIRE(ce.isExitCommand() == false);
    }
}
