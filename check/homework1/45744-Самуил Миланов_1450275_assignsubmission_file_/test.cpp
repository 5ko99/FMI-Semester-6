#include "../Catch2/catch_amalgamated.cpp"
#include "MyString.cpp"
#include <cstring>

TEST_CASE("_str"){
    MyString a("Poe");
    REQUIRE(strcmp(a.c_str(), "Poe") == 0);
}

TEST_CASE("at"){
    MyString a("Poe");
    REQUIRE(a.at(3) == 'e');
}
TEST_CASE("operator[]"){
    MyString a("Poe");
    REQUIRE(a.operator[](3) == 'e');
}
TEST_CASE("front"){
    MyString a("Poe");
    REQUIRE(a.front() == 'P');
}
TEST_CASE("back"){
    MyString a("Poe");
    REQUIRE(a.back() == 'e');
}

TEST_CASE("empty"){
    MyString a("Poe");
    REQUIRE(a.empty() == 0);
}
TEST_CASE("size"){
    MyString a("Poe");
    REQUIRE(a.size() == 3);
}
TEST_CASE("clear"){
    MyString a("Poe");
    a.clear();
    REQUIRE(a.size() == 0);
}
TEST_CASE("push_back"){
    MyString a("Poe");
    a.push_back('c');
    REQUIRE(a.back() == 'c');
}
TEST_CASE("operator+="){
    MyString a("Poe");
    a = a.operator+=('c');
    REQUIRE(a.back() == 'c');
}
