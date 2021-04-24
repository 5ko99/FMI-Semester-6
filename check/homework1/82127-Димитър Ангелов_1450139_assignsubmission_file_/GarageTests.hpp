#pragma once

#include "catch2.hpp"
#include "../MyStringGarageVihicle/Garage.cpp"


TEST_CASE("Case Garage","[Garage]"){

    SECTION("Garage(std::size_t space)"){


    Garage a(5);
    REQUIRE(a.size()==5);

    }

    SECTION("Garage()"){

    Garage a;
    //REQUIRE(a.space==0);
    //REQUIRE(a.freespace==0);
    //REQUIRE(a.vehiclecount==0);

    }

    SECTION("Garage& operator=(const Garage& other)"){


    }

    SECTION("void insert(Vehicle& v)"){


    }

    SECTION("void erase(const char* registration)"){


    }

    SECTION("const Vehicle& at(std::size_t pos) const"){


    }

    SECTION("const Vehicle& operator[](std::size_t pos) const"){


    }

    SECTION("bool empty() const "){


    }

    SECTION("std::size_t size() const"){


    }

    SECTION("void clear() "){


    }

    SECTION("const Vehicle* find(const char* registration) const "){


    }



}
