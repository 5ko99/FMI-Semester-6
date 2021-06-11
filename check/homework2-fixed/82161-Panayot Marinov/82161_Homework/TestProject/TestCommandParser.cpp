#include "catch2.hpp"
#include "../MainProject/Headers/CommandParser.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using std::string;
using std::fstream;

TEST_CASE( "Testing parseCommandFunction") {
    SECTION("Testing with valid command") {
        CommandParser cm;
        fstream file("testFile.txt", std::ios::in);
        if(file.good()) {
            cm.parseCommand(file);
            REQUIRE(strcmp(cm.getCommandType(), "vehicle") == 0);
        } 
    }
    SECTION("Testing with invalid command") {
        CommandParser cm;
        fstream file("testFile.txt", std::ios::in);
        if(file.good()) {
            file.ignore(21,'\n');
            REQUIRE_THROWS_AS(cm.parseCommand(file), std::invalid_argument);
        } 
        file.close();
    }
    SECTION("Testing with invalid command") {
        CommandParser cm;
        fstream file("testFile.txt", std::ios::in);
        if(file.good()) {
            file.ignore(21,'\n');
            REQUIRE_THROWS_AS(cm.parseCommand(file), std::invalid_argument);
        } 
        file.close();
    }
    SECTION("Testing with another invalid command") {
        CommandParser cm;
        fstream file("testFile.txt", std::ios::in);
        if(file.good()) {
            file.ignore(21,'\n');
            file.ignore(21,'\n');
            REQUIRE_THROWS_AS(cm.parseCommand(file), std::invalid_argument);
        } 
        file.close();
    }
    SECTION("Testing with third invalid command") {
        CommandParser cm;
        fstream file("testFile.txt", std::ios::in);
        if(file.good()) {
            file.ignore(21,'\n');
            file.ignore(21,'\n');
            file.ignore(21,'\n');
            REQUIRE_THROWS_AS(cm.parseCommand(file), std::invalid_argument);
        } 
        file.close();
    }
}
