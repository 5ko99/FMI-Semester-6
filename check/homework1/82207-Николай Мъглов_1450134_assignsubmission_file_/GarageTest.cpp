#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "Garage.h"
TEST_CASE("Garage - constuctor with paramter")
{
    Garage g(10);
    CHECK(g.size() == 0);
}
TEST_CASE("Garage - copy constructor")
{
    Garage g(10);
    Vehicle v("", "", 0);
    g.insert(v);
    Garage g1(g);
    CHECK(g.size() == g1.size());
}
TEST_CASE("Garage - insert()")
{
    Garage g(10);
    Vehicle v("", "", 20);
    try
    {
        g.insert(v);
    }
    catch (...)
    {
        CHECK(g.size() == 0);
    }
    Vehicle v1("1234", "", 5);
    try
    {
        g.insert(v1);
    }
    catch (...)
    {
        CHECK(g.size() == 1);
    }
    CHECK(g.size() == 1);
    Vehicle v2("1234", "", 2);
    try
    {
        g.insert(v2);
    }
    catch (...)
    {
        CHECK(g.size() == 1);
    }
}
TEST_CASE("Garage - erase()")
{
    Garage g(10);
    Vehicle v("1234", "", 5);
    g.insert(v);
    Vehicle v1("4321", "", 2);
    g.insert(v1);
    g.erase("5555");
    CHECK(g.size() == 2);
    g.erase("1234");
    CHECK(g.size() == 1);
    g.erase("4321");
    CHECK(g.size() == 0);
}
TEST_CASE("Garage - at()")
{
    Garage g(10);
    const char *registration = "2222";
    const char *description = "bmw";
    Vehicle v(registration, description, 3);
    g.insert(v);
    const char *vRegistration = g.at(0).registration();
    const char *vDescription = g.at(0).description();
    CHECK(strcmp(registration, vRegistration) == 0);
    CHECK(strcmp(description, vDescription) == 0);
    CHECK(g.at(0).space() == 3);
    delete[] vRegistration;
    delete[] vDescription;
}
TEST_CASE("Garage - operator[]")
{
    Garage g(10);
    const char *registration = "2222";
    const char *description = "bmw";
    Vehicle v(registration, description, 3);
    g.insert(v);
    const char *vRegistration = g[0].registration();
    const char *vDescription = g[0].description();
    CHECK(strcmp(registration, vRegistration) == 0);
    CHECK(strcmp(description, vDescription) == 0);
    CHECK(g[0].space() == 3);
    delete[] vRegistration;
    delete[] vDescription;
}
TEST_CASE("Garage - empty()")
{
    Garage g(10);
    CHECK(g.size() == 0);
}
TEST_CASE("Garage - size()")
{
    Garage g(200);
    CHECK(g.size() == 0);
    Vehicle v("", "", 0);
    g.insert(v);
    CHECK(g.size() == 1);
}
TEST_CASE("Garage - clear()")
{
    Garage g(200);
    CHECK(g.size() == 0);
    Vehicle v("", "", 0);
    g.insert(v);
    Vehicle v1("1", "", 1);
    g.insert(v1);
    g.clear();
    CHECK(g.size() == 0);
}
TEST_CASE("Garage - find()")
{
    Garage g(10);
    Vehicle v("1234", "honda", 3);
    g.insert(v);
    Vehicle v1("5687", "vw", 3);
    const Vehicle *vptr = g.find("1234");
    const char *registration = vptr->registration();
    const char *description = vptr->description();
    CHECK(strcmp(description, "honda") == 0);
    CHECK(strcmp(registration, "1234") == 0);
    CHECK(vptr->space() == 3);
    delete[] registration;
    delete[] description;
}
TEST_CASE("Garage - operator=")
{
    Garage g(10), g1(100);
    Vehicle v("1234", "honda", 50);
    g1.insert(v);
    g = g1;
    CHECK(g1.size() == g.size());
    const char *registration0 = g.at(0).registration();
    const char *registration1 = g1.at(0).registration();
    const char *description0 = g.at(0).description();
    const char *description1 = g1.at(0).description();
    CHECK(strcmp(registration0, registration1) == 0);
    CHECK(strcmp(description0, description1) == 0);
    CHECK(g.at(0).space() == g1.at(0).space());
    delete[] registration0;
    delete[] registration1;
    delete[] description0;
    delete[] description1;
}