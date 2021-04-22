#pragma once

#include "catch2.hpp"
#include "../MyStringGarageVihicle/Vehicle.cpp"

TEST_CASE("Case Vehicle","[Vehicle]"){


    SECTION("Vehicle(const char* registration, const char* description, std::size_t space)"){

        Vehicle a("sa123","mazda",5);
        REQUIRE(strcmp(a.registration(),"sa123"));
        REQUIRE(strcmp(a.description(),"mazda"));
        REQUIRE(a.space()==5);
        Vehicle b("","Opel",17);
        REQUIRE(strcmp(a.registration(),""));
        REQUIRE(strcmp(a.description(),"Opel"));
        REQUIRE(a.space()==17);

    }

    SECTION("const char* registration() const "){

        Vehicle a("sa123","mazda",5);
        REQUIRE(strcmp(a.registration(),"sa123"));



    }

    SECTION("const char* description() const"){

        Vehicle a("sa123","mazda",5);
        REQUIRE(strcmp(a.description(),"sa123"));

    }

    SECTION("std::size_t space() const"){

        Vehicle b("","Opel",17);
        REQUIRE(b.space()==17);

    }



}
