#define CATCH_CONFIG_MAIN
#include "catch2.hpp"
#include "MyString.h"
#include <cstring>
#include <iostream>
TEST_CASE("MyString - default constructor")
{
    MyString str;
    CHECK(str.size() == 0);
}
TEST_CASE("MyString - constructor from c-style string")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str.size() == strlen(cstr));
    for (int i = 0; i < str.size(); ++i)
    {
        CHECK(cstr[i] == str[i]);
    }
}
TEST_CASE("MyString - at()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str.at(0) == 'a');
    CHECK(str.at(1) == 'b');
    CHECK(str.at(2) == 'c');
}
TEST_CASE("MyString - operator []")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str[0] == 'a');
    CHECK(str[1] == 'b');
    CHECK(str[2] == 'c');
}
TEST_CASE("MyString - front()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str.front() == str[0]);
    str.front() = 'd';
    CHECK(str.front() == 'd');
}
TEST_CASE("MyString - back()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str.back() == str[str.size() - 1]);
    str.back() = 'd';
    CHECK(str.back() == 'd');
}
TEST_CASE("MyString - empty()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str.empty() == false);
    MyString str1;
    CHECK(str1.empty() == true);
    MyString str2("");
    CHECK(str2.empty() == true);
}
TEST_CASE("MyString - size()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    CHECK(str.size() == strlen(cstr));
}
TEST_CASE("MyString - clear()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    str.clear();
    CHECK(str.size() == 0);
}
TEST_CASE("MyString - push_back()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    str.push_back('d');
    CHECK(str.back() == 'd');
}
TEST_CASE("MyString - pop_back()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    int oldsize = str.size();
    str.pop_back();
    int newsize = str.size();
    CHECK(str.back() == 'b');
    CHECK(oldsize == newsize + 1);
}
TEST_CASE("MyString - operator =")
{
    const char *cstr1 = "abc";
    MyString str1(cstr1);
    const char *cstr2 = "dbefg";
    MyString str2(cstr2);
    str1 = str2;
    CHECK(str1.size() == str2.size());
    for (int i = 0; i < str1.size(); ++i)
    {
        CHECK(str1[i] == str2[i]);
    }
}

TEST_CASE("MyString - operator += with character")
{
    const char *cstr = "abc";
    MyString str(cstr);
    str += 'q';
    CHECK(str.size() == strlen(cstr) + 1);
    CHECK(str.back() == 'q');
}
TEST_CASE("MyString - operator += with MyString")
{
    const char *cstr1 = "abc";
    MyString str1(cstr1);
    const char *cstr2 = "ANz12";
    MyString str2(cstr2);
    str1 += str2;
    CHECK(str1.size() == strlen(cstr1) + strlen(cstr2));
    for (int i = 0; i < strlen(cstr1); ++i)
    {
        CHECK(str1[i] == cstr1[i]);
    }
    for (int i = 0; i < strlen(cstr2); ++i)
    {
        CHECK(str1[i + strlen(cstr1)] == str2[i]);
    }
}
TEST_CASE("MyString - operator + with char")
{
    const char *cstr = "abc";
    MyString str(cstr);
    MyString res = str + 'w';
    CHECK(res.size() == str.size() + 1);
    CHECK(res.back() == 'w');
}
TEST_CASE("MyString - operator + with MyString")
{
    const char *cstr1 = "abc";
    MyString str1(cstr1);
    const char *cstr2 = "qwerty";
    MyString str2(cstr2);
    MyString res = str1 + str2;
    CHECK(res.size() == str1.size() + str2.size());
    for (int i = 0; i < str1.size(); ++i)
    {
        CHECK(res[i] == str1[i]);
    }
    for (int i = 0; i < str2.size(); ++i)
    {
        CHECK(res[i + str1.size()] == str2[i]);
    }
}
TEST_CASE("MyString - c_str()")
{
    const char *cstr = "abc";
    MyString str(cstr);
    const char *newstr = str.c_str();
    CHECK(strcmp(cstr, newstr) == 0);
    delete[] newstr;
}
TEST_CASE("MyString - operator ==")
{
    SECTION("Really same")
    {
        const char *cstr1 = "abc";
        MyString str1(cstr1);
        const char *cstr2 = "abc";
        MyString str2(cstr2);
        CHECK((str1 == str2) == true);
    }
    SECTION("Different")
    {
        const char *cstr1 = "abc";
        MyString str1(cstr1);
        const char *cstr2 = "ab";
        MyString str2(cstr2);
        CHECK((str1 == str2) == false);
    }
}
TEST_CASE("MyString - operator <")
{
    SECTION("Should return true")
    {
        const char *cstr1 = "abbb";
        MyString str1(cstr1);
        const char *cstr2 = "abc";
        MyString str2(cstr2);
        CHECK((str1 < str2) == true);
    }
    SECTION("Should return false")
    {
        const char *cstr1 = "qabc";
        MyString str1(cstr1);
        const char *cstr2 = "abz";
        MyString str2(cstr2);
        CHECK((str1 < str2) == false);
    }
}
