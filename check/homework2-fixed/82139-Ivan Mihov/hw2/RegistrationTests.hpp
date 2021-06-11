
#ifndef HW2_REGISTRATIONTESTS_HPP
#define HW2_REGISTRATIONTESTS_HPP
# include "Registration.h"
# include "catch.hpp"
# include <string>

TEST_CASE("Incorrect first letters", "[Registration]") {
    std::string test("cA5655AM"), test1("Ca5655AM"), test2("c5655AM"), test3("5655AM"), test4("555655AM");
    Registration t;
    REQUIRE_THROWS(t = test);
    REQUIRE_THROWS(t = test1);
    REQUIRE_THROWS(t = test2);
    REQUIRE_THROWS(t = test3);
    REQUIRE_THROWS(t = test4);
}

TEST_CASE("Registration Lenht", "[Registration]") {
    std::string test("5655AM"), test1("Ca56555AM"), test2(""), test3("5");
    Registration t;
    REQUIRE_THROWS(t = test);
    REQUIRE_THROWS(t = test1);
    REQUIRE_THROWS(t = test2);
    REQUIRE_THROWS(t = test3);

}

TEST_CASE("Middle of Registration", "[Registration]") {
    std::string test("CAA655AM"), test1("CA5B55AM"), test2("C56C5AM"), test3("CA565DAM"), test4("C565AM"),
        test5("CA55555BC");
    Registration t;
    REQUIRE_THROWS(t = test);
    REQUIRE_THROWS(t = test1);
    REQUIRE_THROWS(t = test2);
    REQUIRE_THROWS(t = test3);
    REQUIRE_THROWS(t = test4);
    REQUIRE_THROWS(t = test5);
}
TEST_CASE("End of Registration", "[Registration]") {
    std::string test("CA5655M"), test1("CA5555"), test2("C5655am"), test3("CA5655aM"), test4("C5655Am"),
        test5("CA5555BCD");
    Registration t;
    REQUIRE_THROWS(t = test);
    REQUIRE_THROWS(t = test1);
    REQUIRE_THROWS(t = test2);
    REQUIRE_THROWS(t = test3);
    REQUIRE_THROWS(t = test4);
    REQUIRE_THROWS(t = test5);
}
TEST_CASE("operators", "[Registration]") {
    Registration r("CB4545HA"), r1("CB4545HA"), r2("CB7777LK");
    REQUIRE(r.getRegistration() == r1.getRegistration());
}
#endif //HW2_REGISTRATIONTESTS_HPP
