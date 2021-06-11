#include "catch2.hpp"
#include "header.h"
TEST_CASE("Vehicle::Vehicle()")
{
    Registration reg("AB1234BC");
    Vehicle v(reg, std::string("mercedes"));
    bool same = (v.registration() == reg);
    CHECK(same);
    CHECK(v.description() == "mercedes");
}
TEST_CASE("Vehicle::registration()")
{
    Registration reg("N1289PP");
    Vehicle v(reg, "");
    bool same = (v.registration() == reg);
    CHECK(same);
}
TEST_CASE("Vehicle::description()")
{
    Vehicle v(Registration("AB1234BC"), "audi q7");
    CHECK(v.description() == "audi q7");
    Vehicle v1(Registration("AB1234BC"), "");
    CHECK(v1.description() == "");
}
TEST_CASE("Vehicle::setOwner()")
{
    Vehicle v("AB1234BC", "");
    Vehicle v1("RT6677UI", "");
    Person p("ivan", 10);
    v.setOwner(&p);
    CHECK(&v.owner() == &p);
    v1.setOwner(&p);
    CHECK(&v1.owner() == &p);
}
TEST_CASE("Vehicle::owner()")
{
    Vehicle v("AB5555IO", "");
    Person p("ceco", 66);
    v.setOwner(&p);
    CHECK(&v.owner() == &p);
}
TEST_CASE("Person::Person()")
{
    Person p("ivan", 10);
    CHECK(p.getName() == "ivan");
    CHECK(p.getID() == 10);
    CHECK(p.cntVehicles() == 0);
    Person p1("", 0);
    CHECK(p1.getName() == "");
    CHECK(p1.getID() == 0);
    CHECK(p1.cntVehicles() == 0);
}
TEST_CASE("Person::getID()")
{
    Person p("", 0);
    CHECK(p.getID() == 0);
    Person p1("", 111111111);
    CHECK(p1.getID() == 111111111);
}
TEST_CASE("Person::getName()")
{
    Person p("gosho", 0);
    CHECK(p.getName() == "gosho");
    Person p1("", 0);
    CHECK(p1.getName() == "");
}
TEST_CASE("Person::addVehicle()")
{
    Person p("petar", 2);
    Vehicle v("AB1234BC", "bmw");
    p.addVehicle(v);
    CHECK(p.cntVehicles() == 1);
    Vehicle v1("GG3456TY", "audi");
    p.addVehicle(v1);
    CHECK(p.cntVehicles() == 2);
}
TEST_CASE("Person::removeVehicle()")
{
    Person p("cvetomir", 4);
    Vehicle v("GH2231JK", "bmw");
    p.addVehicle(v);
    Vehicle v1("JK1234LM", "fiat");
    p.addVehicle(v1);
    CHECK(p.cntVehicles() == 2);
    p.removeVehicle(v1);
    CHECK(p.cntVehicles() == 1);
    CHECK(p[0].description() == "bmw");
}
TEST_CASE("Person::cntVehicles()")
{
    Person p("nikolay", 10);
    Vehicle v("AA1234BB", "toyota");
    CHECK(p.cntVehicles() == 0);
    p.addVehicle(v);
    CHECK(p.cntVehicles() == 1);
    Vehicle v1("CC5678UU", "honda");
    p.addVehicle(v1);
    CHECK(p.cntVehicles() == 2);
    Vehicle v2("TY1357KL", "nissan");
    p.addVehicle(v2);
    CHECK(p.cntVehicles() == 3);
}
TEST_CASE("Person::operator[]")
{
    Person p("dimitar", 12);
    Vehicle v("FT4444QZ", "ford");
    p.addVehicle(v);
    CHECK(p[0].description() == "ford");
}
