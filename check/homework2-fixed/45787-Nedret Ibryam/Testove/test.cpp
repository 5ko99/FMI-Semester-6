#define CATCH_CONFIG_MAIN

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "SomeFeatures.h"
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
#include "Commands.h"
#include "catch2.cpp"

TEST_CASE("REGISTRATION NUMBER")
{
    REQUIRE(is_valid("T0000RR")==true);
    REQUIRE(is_valid("K1234RR")==true);
    REQUIRE(is_valid("AZ1984TT")==true);
    REQUIRE(is_valid("PP1324RR")==true);
    REQUIRE(is_valid("t0123PP")==false);
    REQUIRE(is_valid("p4567pP")==false);
    REQUIRE(is_valid("t5677pp")==false);
    REQUIRE(is_valid("M123PP")==false);
    REQUIRE(is_valid("KK123LL")==false);
    REQUIRE(is_valid("J6678B")==false);
    REQUIRE(is_valid("VV5674DDD")==false);
}
TEST_CASE("REGISTRATION ")
{
    Registration reg;
    REQUIRE(reg.isEmpty()==true);
    reg.setRegistration("");
    REQUIRE(reg.isEmpty()==true);
    REQUIRE(reg.getRegNumber()!="K8996DS");
}
TEST_CASE("PERSON")
{
    Person per;
    per.setID(12345);
    REQUIRE(per.getID()==12345);
    per.setName("Bai Ganio");
    REQUIRE(per.getPersonName()=="Bai Ganio");
    per.setName("Bai");
    REQUIRE(per.getPersonName()=="Bai");
}
TEST_CASE("SOME FEATURES")
{
    REQUIRE(strsize("")==0);
    REQUIRE(strsize("a")==1);
    REQUIRE(strsize("dsadsa")==6);
    REQUIRE(strsize("aa aa aa")==8);
    REQUIRE(strsize("789a aaa aaa")==12);

    REQUIRE(convertToString("adsdsa", 6)=="adsdsa");
    REQUIRE(convertToString("5a5a5a", 6)=="5a5a5a");
    REQUIRE(convertToString("6aa aaa", 7)=="6aa aaa");

    REQUIRE(correctID("5677")==true);
    REQUIRE(correctID("123456")==true);
    REQUIRE(correctID("329803")==true);
    REQUIRE(correctID("0")==true);
    REQUIRE(correctID("5677a89")==false);
    REQUIRE(correctID("as578")==false);
    REQUIRE(correctID("jdska")==false);
    REQUIRE(correctID("a0")==false);

    REQUIRE(cmp_commands("a", "aa")==1);
    REQUIRE(cmp_commands("bvg", "bvg")==0);
    REQUIRE(cmp_commands("as as", "as as")==0);
    REQUIRE(cmp_commands("0088", "0088")==0);
}
