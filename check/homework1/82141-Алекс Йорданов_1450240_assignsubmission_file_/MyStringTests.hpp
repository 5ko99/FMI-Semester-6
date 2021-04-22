#ifndef  MYSTRINGTESTS_H
#define  MYSTRINGTESTS_H

#include "catch2.hpp"
#include "../HW1/MyString.h"
#include <cstring>

TEST_CASE("Incorrect str throws an exception","[str]")
{
    MyString test1("test1");
    REQUIRE(strcmp(test1.c_str(),"test1")==0);
    REQUIRE(strcmp("test1",test1.c_str())==0);

    MyString test2("test2");
    test2=test1;
    REQUIRE(strcmp(test1.c_str(),test2.c_str())==0);
    REQUIRE(strcmp(test2.c_str(),test1.c_str())==0);

    MyString test3(" ");
    REQUIRE(strcmp(test3.c_str()," ")==0);
    REQUIRE(strcmp(" ",test3.c_str())==0);
    test3=test1;
    REQUIRE(strcmp(test1.c_str(),test3.c_str())==0);
    REQUIRE(strcmp(test3.c_str(),test1.c_str())==0);

    MyString test4("test4");
    test4+="test1";
    REQUIRE(strcmp(test4.c_str(),"test4test1")==0);
    REQUIRE(strcmp("test4test1",test4.c_str())==0);

}

#endif //MYSTRINGTESTS_H
