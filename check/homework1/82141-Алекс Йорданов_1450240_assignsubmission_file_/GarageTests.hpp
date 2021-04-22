#ifndef  GARAGETESTS_H
#define  GARAGEETESTS_H

#include "catch2.hpp"
#include "../HW1/Garage.h"
#include "../HW1/Vehicle.h"
#include <cstring>

TEST_CASE("Incorrect capacity throws an exception","[garage]")
{


    Garage garage1(50);
    Vehicle test1("test1","test_1",1);
    garage1.insert(test1);
    REQUIRE(strcmp(garage1.at(0).registration(),"test1")==0);


    Garage garage2(60);
    Vehicle test2("test2","test_2",2);
    garage2.insert(test2);
    garage2=garage1;
    REQUIRE(strcmp(garage2.at(0).registration(),"test1")==0);

}

#endif //GARAGETESTS_H
