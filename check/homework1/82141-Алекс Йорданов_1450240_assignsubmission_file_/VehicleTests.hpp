#ifndef  VEHICLETESTS_H
#define  VEHICLETESTS_H

#include "catch2.hpp"
#include "../HW1/Vehicle.h"
#include <cstring>
TEST_CASE("Incorrect vehicle throws an exception","[vehicle]")
{

 Vehicle test1("test1","test_1",1);
 REQUIRE(strcmp(test1.registration(),"test1")==0);
 Vehicle a("test1","test_1",1);
 REQUIRE(strcmp(a.registration(),"test1")==0);

}
#endif //VEHICLETESTS_H
