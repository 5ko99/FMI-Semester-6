#define CATCH_CONFIG_MAIN
#include <cstring>
#include "catch2.hpp"
#include "myString.h"

TEST_CASE ("default constructor") {

    MyString test;

    CHECK(!strcmp(test.c_str(), "N/A"));
    CHECK(test.size() == 3);
}

TEST_CASE ("constructor with parameters") {

    MyString test ("test");

    CHECK(!strcmp(test.c_str(), "test"));
    CHECK(test.size() == 4);
}

TEST_CASE ("copy constructor") {

    MyString test("test");
    MyString test2(test);

    CHECK(!strcmp(test.c_str(), test2.c_str()));
    CHECK(test.size() == test2.size());
}

TEST_CASE ("operator =") {

    MyString test("test");
    MyString test2 = test;

    CHECK(!strcmp(test.c_str(), test2.c_str()));
    CHECK(test.size() == test2.size());
}

TEST_CASE ("char at, operator [], fornt, back") {

    MyString test("test");

    CHECK(test.at(1) == 'e');
    CHECK(test[1] == 'e');
    CHECK(test.front()== 't');
    CHECK(test.back()== 't');
}

TEST_CASE ("empty, size") {

    MyString test("test");

    CHECK(!test.empty());
    CHECK(test.size() == 4);
}

TEST_CASE ("push back, pop back") {

    MyString test("test");

    test.push_back('c');
    CHECK(test[4] == 'c');
    test.pop_back();
    CHECK(test.size() == 4);
}

TEST_CASE ("operator +=, + ") {

    MyString test("tes");
    test += 't';
    CHECK(!strcmp(test.c_str(), "test"));
    MyString test2 = test + '2';
    CHECK(!strcmp(test2.c_str(), "test2"));

    MyString test3("test3");
    test3 += test;
    CHECK(!strcmp(test3.c_str(), "test3test"));
    MyString test4 = test + test2;
    CHECK(!strcmp(test4.c_str(), "testtest2"));
}

TEST_CASE ("operator ==, <") {

    MyString test("test"), test2("test2");
    CHECK(!(test == test2));
    CHECK(test < test2);
}