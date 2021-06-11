#pragma once

#include "catch2h.h"
#include "../Homework2/Vehicle.cpp"


TEST_CASE("Case Vehicle","[Vehicle]"){
    Registration r1("CA2815XA");
    Registration r2("FF0321CC");
    Registration r3("ifjveivfv");
    Person p0;
    Person p("Ivan",1234);
    Person p2("noobmaster69",12);
    Vehicle v1(r1,"mazda",p0);
    Vehicle v2(r2,"audi",p);



    SECTION("Vehicle(Registration* reg,std::string descr, Person* owner)"){
            REQUIRE_THROWS(Vehicle(r2,"no desc",p2));
            REQUIRE_THROWS(Vehicle(r1,"gae43g",p2));
            REQUIRE_THROWS(Vehicle(r3,"dgf",p2));
            REQUIRE_THROWS(Vehicle(r3,"jeep",p0));
            REQUIRE_NOTHROW(Vehicle(r1,"Tabant",p0));
            REQUIRE_NOTHROW(Vehicle(r2,"Truk",p));
            REQUIRE_NOTHROW(Vehicle(r2,"bus",p0));
            REQUIRE_NOTHROW(Vehicle(r1,"Hubava kola",p));
    }

    SECTION("std::string& getRegVehStr()"){

            REQUIRE(v1.getRegVehStr()=="CA2815XA");
            REQUIRE(v2.getRegVehStr()=="FF0321CC");
    }

    SECTION("Registration& getRegVeh()"){
            REQUIRE(v1.getRegVeh().getReg()=="CA2815XA");
    }

    SECTION("std::string& getDescr()"){
            REQUIRE(v1.getDescr()=="mazda");
            REQUIRE(v2.getDescr()=="audi");
    }

    SECTION("Person& getPerVeh() "){
            REQUIRE(v1.getPerVeh().getId()==p.getId());
    }




}
