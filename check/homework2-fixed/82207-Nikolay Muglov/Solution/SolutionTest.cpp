#include "catch2.hpp"
#include "Solution.h"
#include <iostream>
TEST_CASE("Solution::vehicle()")
{
    SolutionTest t;

    Registration reg("AB1234BC");
    std::string desc("kia");
    t.sol.vehicle(reg, desc);
    CHECK(t.vehiclesAt(0).description() == "kia");
    bool same = (t.vehiclesAt(0).registration() == reg);
    CHECK(same);
}
TEST_CASE("Solution::person()")
{
    SolutionTest t;

    std::string name("ivan");
    t.sol.person(name, 10);
    CHECK(t.personAt(0).getName() == name);
    CHECK(t.personAt(0).getID() == 10);
}
TEST_CASE("Solution::acquire()")
{
    SolutionTest t;

    std::string name("svetoslav");
    t.sol.person(name, 15);
    Registration reg("AA3456BB");
    std::string desc("bmw");
    t.sol.vehicle(reg, desc);
    t.sol.acquire(15, reg);
    CHECK(&t.vehiclesAt(0).owner() == &t.personAt(0));
    CHECK(t.personAt(0).cntVehicles() == 1);
}
TEST_CASE("Solution::release")
{
    SolutionTest t;

    std::string name("svetoslav");
    t.sol.person(name, 15);
    Registration reg("AA3456BB");
    std::string desc("bmw");
    t.sol.vehicle(reg, desc);
    t.sol.acquire(15, reg);
    CHECK(&t.vehiclesAt(0).owner() == &t.personAt(0));
    t.sol.release(15, reg);
    CHECK(&t.vehiclesAt(0).owner() == nullptr);
}
TEST_CASE("Solution::remove()")
{
    SolutionTest t;

    std::string name("stan");
    t.sol.person(name, 20);
    name = "kalin";
    t.sol.person(name, 30);
    Registration reg("AB5522NM");
    std::string desc("lada");
    t.sol.vehicle(reg, desc);
    t.sol.acquire(30, reg);
    std::string what;

    what = "20";
    t.sol.remove(what);

    CHECK(t.cntPeople() == 1);
    what = "AB5522NM";
    t.sol.remove(what);

    CHECK(t.cntVehicles() == 0);
    CHECK(t.personAt(0).cntVehicles() == 0);

    what = "30";
    t.sol.remove(what);

    CHECK(t.cntVehicles() == 0);
    CHECK(t.cntPeople() == 0);

    Registration regs[] = {"AB1234BC", "GH2222HG", "QW1111QW"};
    std::string descs[] = {"mercedes", "bmw", "audi"};
    std::string names[] = {"ivan", "petar", "georgi"};
    t.sol.person(names[0], 1);
    t.sol.person(names[1], 2);
    t.sol.person(names[2], 3);
    for (int i = 0; i < 3; ++i)
        t.sol.vehicle(regs[i], descs[i]);
    t.sol.acquire(1, regs[2]);
    t.sol.acquire(3, regs[1]);
    t.sol.acquire(1, regs[0]);

    what = "QW1111QW";
    t.sol.remove(what);

    CHECK(t.cntVehicles() == 2);
    CHECK(t.cntPeople() == 3);
    CHECK(t.personAt(0).cntVehicles() == 1);
    CHECK(&t.vehiclesAt(0).owner() == &t.personAt(0));

    what = "3";
    t.sol.remove(what);
    CHECK(t.cntPeople() == 2);
    CHECK(&t.vehiclesAt(1).owner() == nullptr);

    what = "3";
    t.sol.remove(what);
    CHECK(t.cntPeople() == 2);
    CHECK(&t.vehiclesAt(1).owner() == nullptr);

    what = "AB1234BC";
    t.sol.remove(what);
    CHECK(t.cntVehicles() == 1);
    CHECK(t.personAt(0).cntVehicles() == 0);
    CHECK(&t.vehiclesAt(0).owner() == nullptr);

    what = "1";
    t.sol.remove(what);
    CHECK(t.cntPeople() == 1);

    what = "2";
    t.sol.remove(what);
    CHECK(t.cntPeople() == 0);
    CHECK(t.cntVehicles() == 1);

    what = "GH2222HG";
    t.sol.remove(what);
    CHECK(t.cntVehicles() == 0);
}
