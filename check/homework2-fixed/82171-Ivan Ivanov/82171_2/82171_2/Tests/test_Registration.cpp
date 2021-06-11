#define CATCH_CONFIG_MAIN
#include "../Catch2/catch.hpp"
#include "../Registration/Registration.h"

SCENARIO("Testing copy constructor of registration", "[copy]") {
    GIVEN("A valid registration") {
        std::string testRegistrationValue = "tt0000tt";
        Registration testRegistrationA(testRegistrationValue);

        WHEN("Another is created through copy constructor") {
            Registration testRegistrationB(testRegistrationA);

            THEN("The registrations are equal") {
                REQUIRE(testRegistrationA == testRegistrationB);
            }
        }
    }
}

SCENARIO("Testing copy assignement of registration", "[copy]") {
    GIVEN("Two different valid registrations") {
        std::string testRegistrationValueA = "tt0000tA";
        std::string testRegistrationValueB = "tt0000tB";

        Registration testRegistrationA(testRegistrationValueA);
        Registration testRegistrationB(testRegistrationValueB);

        WHEN("Assignment operator is used") {
            testRegistrationA = testRegistrationB;

            THEN("The registrations are equal") {
                REQUIRE(testRegistrationA == testRegistrationB);
            }
        }
    }
}

SCENARIO("Testing comparing registrations", "[operators]") {
    GIVEN("Two valid registrations with different values") {
        std::string testRegistrationValueA = "tt0000tA";
        std::string testRegistrationValueB = "tt0000tB";

        Registration testRegistrationA(testRegistrationValueA);
        Registration testRegistrationB(testRegistrationValueB);
        
        THEN("The registrations are different") {
            REQUIRE(!(testRegistrationA == testRegistrationB));
        }
    }

    GIVEN("Two valid registrations with equal values") {
        std::string testRegistrationValue = "tt0000tt";

        Registration testRegistrationA(testRegistrationValue);
        Registration testRegistrationB(testRegistrationValue);
        
        THEN("The registrations are equal") {
            REQUIRE(testRegistrationA == testRegistrationB);
        }
    }
}

SCENARIO("Testing recognising valid registration values", "[validation") {
    GIVEN("Strings which are valid registration values") {
        std::string testInvalidRegistrationValueA = "a8900es";
        std::string testInvalidRegistrationValueB = "te0000te";
        std::string testInvalidRegistrationValueC = "te0000tR";

        THEN("The registrations are valid") {
            REQUIRE(Registration::isValid(testInvalidRegistrationValueA) == true);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueB) == true);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueC) == true);
        }
    }

    GIVEN("Strings with length bigger than the max one") {
        std::string testInvalidRegistrationValueA = "test too long string";
        std::string testInvalidRegistrationValueB = "te0890ngg";

        THEN("The registrations are invalid") {
            REQUIRE(Registration::isValid(testInvalidRegistrationValueA) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueB) == false);
        }
    }

    GIVEN("Strings with length smaller than the min one") {
        std::string testInvalidRegistrationValueA = "short";
        std::string testInvalidRegistrationValueB = "t0890g";

        THEN("The registrations are invalid") {
            REQUIRE(Registration::isValid(testInvalidRegistrationValueA) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueB) == false);
        }
    }

    GIVEN("Strings without ending chars") {
        std::string testInvalidRegistrationValueA = "t089000";
        std::string testInvalidRegistrationValueB = "te08900g";
        std::string testInvalidRegistrationValueC = "te0890g0";

        THEN("The registrations are invalid") {
            REQUIRE(Registration::isValid(testInvalidRegistrationValueA) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueB) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueC) == false);
        }
    }

    GIVEN("A string withoutout the needed digits") {
        std::string testInvalidRegistrationValueA = "t089tes";
        std::string testInvalidRegistrationValueB = "te08r0te";
        std::string testInvalidRegistrationValueC = "tea890te";

        THEN("The registrations are invalid") {
            REQUIRE(Registration::isValid(testInvalidRegistrationValueA) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueB) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueC) == false);
        }
    }
    GIVEN("A string beginnning no or more than three letters") {
        std::string testInvalidRegistrationValueA = "08900es";
        std::string testInvalidRegistrationValueB = "tea8r0te";
        std::string testInvalidRegistrationValueC = "800090te";

        THEN("The registrations are invalid") {
            REQUIRE(Registration::isValid(testInvalidRegistrationValueA) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueB) == false);
            REQUIRE(Registration::isValid(testInvalidRegistrationValueC) == false);
        }
    }
}
