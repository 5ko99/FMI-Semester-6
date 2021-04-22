#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "MyString.h"
#include "cstring"

TEST_CASE("MyString", " tests")
{
    SECTION("constructors")
    {
        const char* str = {"abc"};
        MyString newStr(str);

        size_t i = 0;
        while(str[i])
        {
            REQUIRE(newStr[i] == str[i]);
            i++;
        }
    }

    SECTION("at []")
    {
        MyString str("abc");

        REQUIRE( str.at(1) == 'b');
        REQUIRE( str[1] == 'b');
    }

    SECTION("front back")
    {
        MyString str("abc");

        REQUIRE( str.front() == 'a');
        REQUIRE( str.back() == 'c');
    }

    SECTION("push pop")
    {
        MyString str("abc");

        REQUIRE( str.back() == 'c');
        str.pop_back();
        REQUIRE(str.back() == 'b');
        str.push_back('c');
        REQUIRE( str.back() == 'c');
    }

    SECTION("mischevous")
    {
        MyString str("abc");

        REQUIRE( str.empty() == false );
        REQUIRE( str.size() == 3 );
        str.clear();
        REQUIRE( str.empty() == true );
    }

    SECTION("operators + =")
    {   
        MyString str1("abc");
        str1 +='d';

        REQUIRE( str1.size() == 4);
        REQUIRE( str1.back() == 'd');


        MyString str2("def");
        str1 += str2;
        
        REQUIRE( str1.size() == 7 );

    }

    SECTION("operators +")
    {  
        MyString str("abc");
        MyString newStr = str + 'd';

        REQUIRE(newStr.back() == 'd');
        REQUIRE(newStr.size() == 4);

        MyString str2("abc");
        MyString newStr2 = str + str2;

        REQUIRE(newStr2.size() == 6);

    }

    SECTION("operators == !=")
    {  
        MyString str("abc");
        MyString str2("abc");

        REQUIRE( bool(str == str2) == 1);
        REQUIRE( bool(str != str2) == 0);
        str[1] = 'a';
        REQUIRE( bool(str == str2) == 0);

    }

    SECTION("operators < >")
    {  
        MyString str("abc");
        MyString str2("abcc");

        REQUIRE(bool(str < str2) == 1);
        str.push_back('d');
        REQUIRE(bool(str > str2) == 1);
    }

}

TEST_CASE("MyString1", "constructors")
{
    SECTION("Copy Constructor - """)
    {
        MyString str("");
        MyString newStr(str);

        REQUIRE(str == newStr);
    }
    SECTION("Copy Constructor - " "")
    {
        MyString str(" ");
        MyString newStr(str);

        REQUIRE(str == newStr);
    }
    SECTION("Copy Constructor - \"a\" ")
    {
        MyString str("a");
        MyString newStr(str);

        REQUIRE(str == newStr);
    }
    SECTION("Copy Constructor - very long char array")
    {
        MyString str("qwertyuiopasdfghjklzxcvbnmaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
        MyString newStr(str);

        REQUIRE(str == newStr);
    }
    /*****************************************************************/
    SECTION("Copy Assignment Operator")
    {
        MyString str("");
        MyString newStr("aa");

        str = newStr;
        REQUIRE(str == newStr);
    }
    SECTION("Copy Assignment Operator - x = x")
    {
        MyString str("aa");

        str = str;
        REQUIRE(str == "aa");
    }


}
