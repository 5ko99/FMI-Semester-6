#include "../catch2/catch2.hpp"
#include "../Command/Command.hpp"  

std::string arg1 = "command", arg2 = "argument", arg3 = "another one", arg4 = "location", arg5 = "path to file";
std::string arg4Q = '\"' + arg4 + '\"', arg5Q = '\"' + arg5 + '\"';

TEST_CASE("Command storage") {
    std::string command = arg1 + ' ' + arg2;
    Command arguments(command);
    REQUIRE(!strcmp(arguments.getString(),command.c_str()));
}

TEST_CASE("Command split") {
    SECTION("2 arguments, no space in args, no quotes") {
        std::string command = arg1 + ' ' + arg2;
        Command arguments(command);
        REQUIRE(arguments[0] == arg1);
        REQUIRE(arguments[1] == arg2);
    }

    SECTION("3 arguments, space in args, no quotes") {
        std::string command = arg1 + ' ' + arg2 + ' ' + arg3;
        Command arguments(command);
        REQUIRE(arguments[0] == arg1);
        REQUIRE(arguments[1] == arg2);
        REQUIRE(arguments[2] != arg3);
        std::string buffer = arguments[2] + ' ' + arguments[3];
        REQUIRE(buffer == arg3);
    }

    SECTION("2 arguments, no space in args, quotes") {
        std::string command = arg1 + ' ' + arg4Q;
        Command arguments(command);
        REQUIRE(arguments[0] == arg1);
        REQUIRE(arguments[1] == arg4);
    }
    
    SECTION("2 arguments, space in args, quotes") {
        std::string command = arg1 + ' ' + arg5Q;
        Command arguments(command);
        REQUIRE(arguments[0] == arg1);
        REQUIRE(arguments[1] == arg5);
    }
}
