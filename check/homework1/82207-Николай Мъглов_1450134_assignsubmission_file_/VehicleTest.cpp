#define CATCH_CONFIG_MAIN
#include "Vehicle.h"
#include "catch2.hpp"
TEST_CASE("Vehicle - constuctor")
{
    const char *registration = "1234";
    const char *description = "merc benz 2004";
    std::size_t space = 10;
    Vehicle v(registration, description, space);
    const char *vRegistration = v.registration();
    const char *vDescription = v.description();
    std::size_t vSpace = v.space();
    CHECK(strcmp(vRegistration, registration) == 0);
    CHECK(strcmp(vDescription, description) == 0);
    CHECK(vSpace == space);
    delete[] vRegistration;
    delete[] vDescription;
}
TEST_CASE("Vehicle - registration()")
{
    Vehicle v("4129", "", 0);
    const char *registration = "4129";
    const char *vRegistration = v.registration();
    CHECK(strcmp(vRegistration, registration) == 0);
    registration = "3819";
    CHECK(strcmp(vRegistration, registration) != 0);
    delete[] vRegistration;
}
TEST_CASE("Vehicle - description()")
{
    Vehicle v("", "bmw 7 series ", 0);
    const char *description = "bmw 7 series ";
    const char *vDescription = v.description();
    CHECK(strcmp(vDescription, description) == 0);
    description = "audi a8";
    CHECK(strcmp(vDescription, description) != 0);
    delete[] vDescription;
}
TEST_CASE("Vehicle - space()")
{
    Vehicle v("", "", 12);
    CHECK(v.space() == 12);
}