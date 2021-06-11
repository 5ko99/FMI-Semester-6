#pragma once

#include "catch2h.h"
#include "../Homework2/Registration.cpp"
#include <string>


TEST_CASE("Case Registration","[Registration]"){


    SECTION("Registration(std::string reg)"){
        REQUIRE_THROWS(Registration ("345"));
        REQUIRE_THROWS(Registration ("98nchrf"));
        REQUIRE_THROWS(Registration ("1234GG"));
        REQUIRE_THROWS(Registration ("CV12H4NN"));
        REQUIRE_THROWS(Registration ("W123MN"));
        REQUIRE_THROWS(Registration ("1B6098QT"));
        REQUIRE_THROWS(Registration ("*65pdend"));
        REQUIRE_NOTHROW(Registration ("A0000ZZ"));
        REQUIRE_NOTHROW(Registration ("BA9999AQ"));
        REQUIRE_NOTHROW(Registration ("OV4444AR"));
    }

    SECTION("std::string getcity()"){
        Registration a("AB1234NM");
        Registration b("V0035FG");
        Registration c("LA1720XX");
        Registration d("NY7777NY");
        REQUIRE(a.getcity()=="AB");
        REQUIRE(b.getcity()=="V");
        REQUIRE(c.getcity()=="LA");
        REQUIRE(d.getcity()=="NY");

    }

    SECTION("std::string getnomer()"){
        Registration a("AB1234NM");
        Registration b("V0035FG");
        Registration c("LA1720XX");
        Registration d("NY7777NY");
        REQUIRE(a.getnomer()=="1234");
        REQUIRE(b.getnomer()=="0035");
        REQUIRE(c.getnomer()=="1720");
        REQUIRE(d.getnomer()=="7777");

    }

    SECTION("std::string getletters()"){
        Registration a("AB1234NM");
        Registration b("V0035FG");
        Registration c("LA1720XX");
        Registration d("NY7777NY");
        REQUIRE(a.getletters()=="NM");
        REQUIRE(b.getletters()=="FG");
        REQUIRE(c.getletters()=="XX");
        REQUIRE(d.getletters()=="NY");

    }

    SECTION("std::string getReg()"){
        Registration a("AB1234NM");
        Registration b("V0035FG");
        Registration c("LA1720XX");
        Registration d("NY7777NY");
        REQUIRE(a.getReg()=="AB1234NM");
        REQUIRE(b.getReg()=="V0035FG");
        REQUIRE(c.getReg()=="LA1720XX");
        REQUIRE(d.getReg()=="NY7777NY");

    }





}
