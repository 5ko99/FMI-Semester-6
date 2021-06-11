#define CATCH_CONFIG_MAIN
#include <string>
#include "catch2.hpp"
#include "commands.h"

TEST_CASE ("constructor, toUnsigned, toRegistration, argToCaps") {

    Commands* cmnd = Commands::getInstance();
    std::string str ("123"), str2 ("A1234AA"), str3("asd");
    Registration reg(str2);

    CHECK(cmnd->toRegistration(str2) == reg);
    CHECK(cmnd->argumentToCaps(str3) == "ASD");
}
