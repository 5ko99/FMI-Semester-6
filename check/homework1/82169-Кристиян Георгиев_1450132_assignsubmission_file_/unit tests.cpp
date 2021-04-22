#include "../../Catch2/catch.h"
#include "../code/MyString.h"
#define CATCH_CONFIG_MAIN

TEST_CASE("Constructors"){

SECTION("Default Constructor"){     
        MyString testSTR;
        REQUIRE(testSTR.size() == 0);
}
SECTION("MyString(const char* str)"){
        MyString testSTR2("hello");
        REQUIRE(testSTR2.size() == 5);
}
    
SECTION("Copy constructors"){
        MyString testSTR2("Hello");

        MyString testSTR3(testSTR2);    
        REQUIRE(testSTR3.size() == 5);


        MyString testSTR4("there");
        testSTR2 = testSTR4;

        //some tests with MyString::at();
        REQUIRE(testSTR2.at(2) == 'e');
        REQUIRE(testSTR2.at(3) == 'r');

        //some tests with MyString::front() and back();
        testSTR2.front() = '?';
        testSTR2.back() = '!';
        REQUIRE(testSTR2.at(0) == '?');
        REQUIRE(testSTR2.at(4) == '!');

        //some tests with bool empty() and bool clear()
        REQUIRE(testSTR2.empty() == false);
        testSTR2.clear();
        REQUIRE(testSTR2.empty() == true);

        //some tests with push_back() and pop_back();
        testSTR2.push_back('t');
        REQUIRE(testSTR2.at(0) == 't');
        REQUIRE(testSTR2.size() == 1);
        testSTR2.pop_back();
        REQUIRE(testSTR2.size() == 0);

        //some tests with operator+=
        MyString testSTR11("helloo");
        MyString testSTR12("there!");
        testSTR11 += testSTR12;
        
        REQUIRE(testSTR11.size() == 12);
        REQUIRE(testSTR11.at(11) == '!');
        testSTR11 += '?';
        testSTR11 += 'h';
        REQUIRE(testSTR11.size() == 14);
        REQUIRE(testSTR11.at(12) == '?');
        
        //some tests with operator+
        MyString testSTR21("He");
        MyString testSTR22("llo");
        testSTR21 = testSTR21 + testSTR22;
        REQUIRE(testSTR21.size() == 5);
        REQUIRE(testSTR11.at(4) == 'o');
        testSTR21 = testSTR21 + '!';
        REQUIRE(testSTR21.size() == 6);

        //some tests with operator==
        MyString HelloString("Hello!");
        REQUIRE((HelloString == testSTR21) == true);

        
        //some tests with operator<
        MyString testSTR100("sh");
        REQUIRE((HelloString < testSTR100) == true);       
}

}

//g++ *cpp ../code/*cpp ../../Catch2/*cpp -I Catch2

