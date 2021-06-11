#ifndef HELPERSTESTS_H
#define HELPERSTESTS_H
#include "catch2.hpp"
#include "..\HW2\helpers.h"

TEST_CASE("containsInvervals function works properly")
{
    REQUIRE(containsIntervals("")==false);
    REQUIRE(containsIntervals("supercalifragilisticexcpialidocious")==false);
    REQUIRE(containsIntervals(" ")==true);
    REQUIRE(containsIntervals(" supercalifragilisticexcpialidocious")==true);
    REQUIRE(containsIntervals("supercalifragilisticexcpialidocious ")==true);
    REQUIRE(containsIntervals(" supercalifragilisticexcpialidocious ")==true);
    REQUIRE(containsIntervals(" supercalifragilistic excpialidocious")==true);
    REQUIRE(containsIntervals(" supercalifragilistic excpialidocious ")==true);
}

TEST_CASE("toLower function works properly")
{
    REQUIRE(toLower('a')=='a');
    REQUIRE(toLower('B')=='b');
    REQUIRE(toLower('5')=='5');
}

TEST_CASE("caseInsensitiveCmp works properly")
{
    char str1[]="what doesn't kill you makes you stronger";
    char str2[]="WHAT DOESN'T KILL YOU MAKES YOU STRONGER";
    char str3[]="wHaT dOEsn'T kIll yOU mAkEs YoU STrONgEr";
    char str4[]="I Think, thereFore I am";
    char str5[]="abc";
    char str6[]="d";
    char str7[]="a";
    REQUIRE(caseInsensitiveCmp(str1, str2)==0);
    REQUIRE(caseInsensitiveCmp(str1, str3)==0);
    REQUIRE(caseInsensitiveCmp(str1, str4)!=0);
    REQUIRE(caseInsensitiveCmp(str5, str6)<0);
    REQUIRE(caseInsensitiveCmp(str5, str7)>0);
}

TEST_CASE ("containsOnlyDigits works properly")
{
   REQUIRE(containsOnlyDigits("12354")==true);
   REQUIRE(containsOnlyDigits("4")==true);
   REQUIRE(containsOnlyDigits("")==false);
   REQUIRE(containsOnlyDigits("f153sdff")==false);
   REQUIRE(containsOnlyDigits("152h60d")==false);

}

TEST_CASE("strToUnsigned works properly")
{
    REQUIRE(strToUnsigned("0")==0);
    REQUIRE(strToUnsigned("1256")==1256);
    REQUIRE(strToUnsigned("42")==42);
    REQUIRE(strToUnsigned("5")==5);
    REQUIRE_THROWS(strToUnsigned("152h60d"));
}


#endif
