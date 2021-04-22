#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "VehicleVector.h"

TEST_CASE("VehicleVector - constructor")
{
    VehicleVector v;
    CHECK(v.size() == 0);
}
TEST_CASE("VehicleVector - push_bacK()")
{
    VehicleVector vv;
    const char *registration = "5612";
    const char *description = "vw golf";
    Vehicle v(registration, description, 2);
    vv.push_back(v);
    Vehicle tmp = vv.at(0);
    const char *vRegistration = vv.at(0).registration();
    const char *vDescription = vv.at(0).description();
    CHECK(strcmp(registration, vRegistration) == 0);
    CHECK(strcmp(description, vDescription) == 0);
    CHECK(vv.at(0).space() == 2);
    delete[] vRegistration;
    delete[] vDescription;
}

TEST_CASE("VehicleVector - erase()")
{
    VehicleVector vv;
    const char *registration = "7812";
    const char *description = "audi Q7";
    Vehicle v(registration, description, 10);
    vv.push_back(v);
    vv.erase(registration);
    CHECK(vv.size() == 0);
}
TEST_CASE("VehicleVector - size()")
{
    VehicleVector vv;
    const char *registration = "7812";
    const char *description = "audi Q7";
    Vehicle v(registration, description, 10);
    vv.push_back(v);
    registration = "5612";
    description = "toyota";
    Vehicle v1(registration, description, 5);
    vv.push_back(v1);
    CHECK(vv.size() == 2);
}
TEST_CASE("VehicleVector - at()")
{
    VehicleVector vv;
    const char *registration = "7812";
    const char *description = "audi Q7";
    Vehicle v(registration, description, 10);
    vv.push_back(v);
    const char *vRegisration = vv.at(0).registration();
    const char *vDescription = vv.at(0).description();
    std::size_t vSpace = vv.at(0).space();
    CHECK(strcmp(registration, vRegisration) == 0);
    CHECK(strcmp(description, vDescription) == 0);
    CHECK(vSpace == 10);
}
TEST_CASE("VehicleVector - clear()")
{
    VehicleVector vv;
    const char *registration = "7812";
    const char *description = "audi Q7";
    Vehicle v(registration, description, 10);
    vv.push_back(v);
    vv.clear();
    CHECK(vv.size() == 0);
}
TEST_CASE("VehicleVector - operator=")
{
    VehicleVector vv, vv1;
    const char *registration = "7812";
    const char *description = "audi Q7";
    Vehicle v(registration, description, 10);
    vv.push_back(v);
    registration = "2212";
    description = "renault";
    Vehicle v1(registration, description, 20);
    vv1.push_back(v1);
    vv = vv1;
    const char *vRegistration = vv.at(0).registration();
    const char *vDescription = vv.at(0).description();
    CHECK(strcmp(vRegistration, registration) == 0);
    CHECK(strcmp(vDescription, description) == 0);
    CHECK(vv.at(0).space() == 20);
    delete[] vRegistration;
    delete[] vDescription;
}
