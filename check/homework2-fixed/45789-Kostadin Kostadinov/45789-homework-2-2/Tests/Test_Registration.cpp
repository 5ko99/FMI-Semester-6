#include "../catch2/catch2.hpp"
#include "../Registration/Registration.hpp"
#include <cstring>

char num1[9] = "BX4753BV";
char num2[8] = "U8549VG";
char num3[11] = "TR5435NTSO";
char num4[5] = "H54G";
char num5[9] = "5346BGYN";
std::string str1 = num1, str2 = num2, str3 = num3, str4 = num4, str5 = num5;


Registration reg("B1306TS"), reg1("BG1234BG"), reg2("BG1234BG"), reg3("GB4321GB");

TEST_CASE("Construct Registration") {
    bool error;
    
    SECTION("correct long") {
        error = false;
        try {
            Registration a(num1);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }

    SECTION("correct short") {
        error = false;
        try {
            Registration b(num2);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }

    SECTION("number too long") {
        error = false;
        try {
            Registration c(num3);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }
    
    SECTION("number too short") {
        error = false;
        try {
            Registration d(num4);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }

    SECTION("invalid number") {
        error = false;
        try {
            Registration e(num5);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }
}

TEST_CASE("Construct Registration String") {
    bool error;
    
    SECTION("correct long") {
        error = false;
        try {
            Registration a(str1);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }

    SECTION("correct short") {
        error = false;
        try {
            Registration b(str2);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }

    SECTION("number too long") {
        error = false;
        try {
            Registration c(str3);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }
    
    SECTION("number too short") {
        error = false;
        try {
            Registration d(str4);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }

    SECTION("invalid number") {
        error = false;
        try {
            Registration e(str5);
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }
}

TEST_CASE("Assaign Registration") {
    bool error;

    SECTION("correct long") {
        error = false;
        try {
            reg = num1;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }

    SECTION("correct short") {
        error = false;
        try {
            reg = num2;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }
    
    SECTION("number too long") {
        error = false;
        try {
            reg = num3;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }

    SECTION("number too short") {
        error = false;
        try {
            reg = num4;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }

    SECTION("invalid number") {
        error = false;
        try {
            reg = num5;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }
}

TEST_CASE("Assaign Registration String") {
    bool error;

    SECTION("correct long") {
        error = false;
        try {
            reg = str1;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }

    SECTION("correct short") {
        error = false;
        try {
            reg = str2;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(!error);
    }
    
    SECTION("number too long") {
        error = false;
        try {
            reg = str3;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }

    SECTION("number too short") {
        error = false;
        try {
            reg = str4;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }

    SECTION("invalid number") {
        error = false;
        try {
            reg = str5;
        } catch(std::exception& e) {
            error = true;
        }
        REQUIRE(error);
    }
}

TEST_CASE("Return Registration") {
    REQUIRE(!strcmp(reg1.c_str(),"BG1234BG"));
}

TEST_CASE("Compare Registration") {
    SECTION("equal") REQUIRE((reg1 == reg2));
    SECTION("different") REQUIRE(!(reg1 == reg3));
}

TEST_CASE("Copy Registration") {
    reg = reg1;
    bool case2 = (reg == reg1);
    REQUIRE(case2);
}
