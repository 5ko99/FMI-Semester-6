#pragma once
#include "catch2.h"
#include "MyString.h"


TEST_CASE("Default constructor")
{
    MyString a;
    REQUIRE( 5 == 5);
    REQUIRE( a.getSize() == 0);
   // REQUIRE( strcmp(a.getStr(), "") == 0);
}


TEST_CASE("Copy assignment operator")
{
    MyString a("goshko");
    MyString b(a);
    REQUIRE( a.getSize() == 6);
    REQUIRE( b.getSize() == 6);\
    REQUIRE( strcmp(a.getStr(),"goshko") == 0 );
    REQUIRE( strcmp(b.getStr(),"goshko") == 0 );

}

TEST_CASE("Operator= ")
{
    MyString a("goshko");
    MyString b,c;
    b = c = a;
    REQUIRE( strcmp(b.getStr(),"goshko") == 0 );
    REQUIRE( strcmp(c.getStr(),"goshko") == 0 );
    REQUIRE( b.getSize() == 6 );
    REQUIRE( c.getSize() == 6 );
}

TEST_CASE("Operator at")
{
    MyString a("goshko");
    a.at(1) = 'a';
    /// next row correctly gives exception
    REQUIRE_THROWS(a.at(10) == 'a');
    REQUIRE( strcmp(a.getStr(),"gashko") == 0 );
}

TEST_CASE("Operator []")
{
    MyString a("goshko");
    a[1]='a';
    REQUIRE_NOTHROW(a[10]=='a');
    REQUIRE( strcmp(a.getStr(),"gashko") == 0 );
}

TEST_CASE("Operator+= with char")
{
    MyString a("");
    a+='v';
    std::cout << a.getStr()<<"end of string\n";
    REQUIRE(strcmp(a.getStr(), "v") == 0);
    a+="vas";
    REQUIRE(strcmp(a.getStr(), "vvas") == 0);
}

/// Pokaji na gogata toq test za null-terminated string
TEST_CASE("Null terminated string")
{
    MyString a("toshko");
    int tmpSize = a.getSize();
    // returns char* with added '\0'
    const char* tester = a.c_str();
    MyString b(tester);
    REQUIRE( b[tmpSize - 1] == 'o');
    REQUIRE( b[tmpSize] == 0 );

}





