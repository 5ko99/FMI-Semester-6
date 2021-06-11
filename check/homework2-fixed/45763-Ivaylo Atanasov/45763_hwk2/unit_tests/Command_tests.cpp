#include "../Homework_2_2/Command/Command.hpp"
#include "catch2.hpp"

TEST_CASE("splitting commands"){
    
    SECTION("correct input single word"){
        Command cmd("test1");
        REQUIRE(cmd[0] == "test1");
    }
    SECTION("correct input multiple words"){
        Command cmd("test1 test2 test3");
        REQUIRE(cmd[0] == "test1");
        REQUIRE(cmd[1] == "test2");
        REQUIRE(cmd[2] == "test3");
    }
    
    
    SECTION("multiple spaces between words"){
        Command cmd("test1    test2      test3");
        REQUIRE(cmd[0] == "test1");
        REQUIRE(cmd[1] == "test2");
        REQUIRE(cmd[2] == "test3");
    }
    SECTION("multiple spaces at beggining"){
        Command cmd("    test1 test2 test3");
        REQUIRE(cmd[0] == "test1");
        REQUIRE(cmd[1] == "test2");
        REQUIRE(cmd[2] == "test3");
    }
    SECTION("multiple spaces at end"){
        Command cmd("test1 test2 test3    ");
        REQUIRE(cmd[0] == "test1");
        REQUIRE(cmd[1] == "test2");
        REQUIRE(cmd[2] == "test3");
    }
    
    SECTION("quotes correct input"){
        Command cmd("\"test1\"");
        REQUIRE(cmd[0] == "test1");
    }
    
    SECTION("quotes with normal text"){
        Command cmd("test1 \"test2\"");
        REQUIRE(cmd[0] == "test1");
    }
    SECTION("quotes with multiple words"){
        Command cmd("\"test1 test2 test3\"");
        REQUIRE(cmd[0] == "test1 test2 test3");
    }
    SECTION("quotes with multiple words and spaces between them"){
        Command cmd("\"test1    test2    test3\"");
        REQUIRE(cmd[0] == "test1    test2    test3");
    }
    SECTION("quotes with multiple words and spaces in beginning"){
        Command cmd("\"   test1 test2\"");
        REQUIRE(cmd[0] == "   test1 test2");
    }
    SECTION("quotes with multiple words and spaces at end"){
        Command cmd("\"test1 test2   \"");
        REQUIRE(cmd[0] == "test1 test2   ");
    }
    
    SECTION("complicated example"){
        Command cmd("   test1   test2   \"   test3     test4  \"    test5   \" test6  \"  ");
        REQUIRE(cmd[0] == "test1");
        REQUIRE(cmd[1] == "test2");
        REQUIRE(cmd[2] == "   test3     test4  ");
        REQUIRE(cmd[3] == "test5");
        REQUIRE(cmd[4] == " test6  ");
    }
    
    
    
}
