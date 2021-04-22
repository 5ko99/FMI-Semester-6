#include "MyString.h"
#include "catch2.hpp"

TEST_CASE("Constructors Testing for MyString")
{
    MyString testString2("Hello");
    MyString testString3(testString2);
    MyString testString5("Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");
    MyString testString6(testString5);

    REQUIRE(testString2 == "Hello");
    REQUIRE(testString3 == "Hello");

    REQUIRE(testString5 == "Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");
    REQUIRE(testString6 == "Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");
}

TEST_CASE("Operator= Testing for MyString")
{
    const char *charTestString1 = "Sasho";
    const char *charTestString2 = "Basho";
    const char *charTestString3 = "";

    MyString testString2("Hello");
    MyString testString3(testString2);
    MyString testString5("Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");
    MyString testString6("Heyyy");

    testString6 = testString5;
    testString3 = testString6;
    testString2 = charTestString3;

    REQUIRE(testString2 == "");
    REQUIRE(testString3 == "Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");
    REQUIRE(testString5 == "Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");
    REQUIRE(testString6 == "Hellofrhtukio809o6etrw4t6uj7t5uetgertrtyhru65rtg4yhu6tu");

    testString6 = charTestString1;
    testString3 = charTestString2;

    REQUIRE(testString3 == "Basho");
    REQUIRE(testString6 == "Sasho");
}

TEST_CASE("Operator+= Testing for MyString")
{
    const char charTestString1 = 'S';
    const char charTestString2 = 'B';
    const char charTestString3 = '\0';

    MyString testString2("Hello");
    MyString testString3(testString2);

    testString3 += testString3;

    REQUIRE(testString2 == "Hello");
    REQUIRE(testString3 == "HelloHello");

    testString2 += charTestString2;
    testString3 += charTestString3;
    
    REQUIRE(testString2 == "HelloB");
    REQUIRE(testString3 == "HelloHello");

    testString3 += 'c';
    testString3 += charTestString1;

    REQUIRE(testString3 == "HelloHellocS");
}

TEST_CASE("Operator+ Testing for MyString")
{
    const char charTestString1 = 'S';
    const char charTestString2 = 'B';
    const char charTestString3 = '\0';

    MyString testString2("Hello");
    MyString testString3(testString2);

    REQUIRE(testString3 + testString3 + testString2 == "HelloHelloHello");
    REQUIRE(testString2 + charTestString2 == "HelloB");
    REQUIRE(testString3 + charTestString3 == "Hello");
}

TEST_CASE("Operator== Testing for MyString")
{
    const MyString testString2("DisPolice");
    const MyString testString3(testString2);
    const MyString testString4("DisPoliced");

    REQUIRE((testString2 == testString4) == false);
    REQUIRE((testString3 == testString2) == true);
    REQUIRE((testString4 == testString3) == false);
}

TEST_CASE("Operator< Testing for MyString")
{
    const MyString testString1("59");
    const MyString testString2("58");
    const MyString testString3(testString2);

    REQUIRE((testString2 < testString1) == true);
    REQUIRE((testString3 < testString2) == false);
    REQUIRE((testString1 < testString3) == false);
}

TEST_CASE("SIZE Testing for MyString")
{
    MyString testString1("   ");
    MyString testString2("YOUSHALLPASS!");
    MyString testString3(testString2);

    REQUIRE(testString1.size() == 0);
    REQUIRE(testString2.size() == 13);
    REQUIRE(testString3.size() == 13);
}

TEST_CASE("at(std::size_t index) Testing for MyString")
{
    MyString testString2("HelloBoys");
    MyString testString3(testString2);

    REQUIRE(testString2.at(1) == 'e');
    REQUIRE(testString3.at(3) == 'l');
    REQUIRE(testString3.at(4) == 'o');
}

TEST_CASE("operator[] Testing for MyString")
{
    MyString testString2("UGANDA");
    MyString testString3(testString2);

    //assert
    REQUIRE(testString2[1] == 'G');
    REQUIRE(testString3[3] == 'N');
    REQUIRE(testString3[4] == 'D');
}

TEST_CASE("front and back Testing for MyString")
{
    MyString testString2("KungFu");
    MyString testString3(testString2);

    REQUIRE(testString2.front() == 'K');
    REQUIRE(testString3.front() == 'K');

    REQUIRE(testString2.back() == 'u');
    REQUIRE(testString3.back() == 'u');

    testString2.back() = 'D';
    testString3.front() = 'F';

    REQUIRE(testString2.back() == 'D');
    REQUIRE(testString3.front() == 'F');
}

TEST_CASE("Empty Testing for MyString")
{
    MyString testString1("       ");
    MyString testString2("KFC");
    MyString testString3(testString2);

     REQUIRE(testString1.isEmpty() == 1);
    REQUIRE(testString2.isEmpty() == 0);
    REQUIRE(testString3.isEmpty() == 0);
}

TEST_CASE("C-str Testing for MyString")
{
    MyString testString2("Hello");
    MyString testString3(testString2);

    const char *Hello = "Hello";

    REQUIRE(MystrcmpareEquality(Hello, testString2.c_str()));
    REQUIRE(MystrcmpareEquality(Hello, testString3.c_str()));
}

TEST_CASE("Clear Testing for MyString")
{
    MyString testString2("What");
    MyString testString3(testString2);

    testString2.clear();
    testString3.clear();

    REQUIRE(testString2.size() == 0);
    REQUIRE(testString2.isEmpty() == 1);

    REQUIRE(testString3.size() == 0);
    REQUIRE(testString3.isEmpty() == 1);
}

TEST_CASE("Push and Pop Testing for MyString")
{
    MyString testString2("Something");
    MyString testString3(testString2);

    testString2.push_back('d');
    testString3.push_back('\0');

    REQUIRE(testString2 == "Somethingd");
    REQUIRE(testString2.size() == 10);

    REQUIRE(testString3 == "Something");
    REQUIRE(testString3.size() == 9);

    testString2.pop_back();
    testString3.pop_back();

    REQUIRE(testString2 == "Something");
    REQUIRE(testString2.size() == 9);

    REQUIRE(testString3 == "Somethin");
    REQUIRE(testString3.size() == 8);

    testString3.push_back('c');
    testString2.push_back('s');

    REQUIRE(testString2 == "Somethings");
    REQUIRE(testString2.size() == 10);

    REQUIRE(testString3 == "Somethinc");
    REQUIRE(testString3.size() == 9);

    testString3.pop_back();
    testString3.pop_back();
    testString3.pop_back();
    testString3.pop_back();

    REQUIRE(testString3 == "Somet");
    REQUIRE(testString3.size() == 5);

    testString3.push_back('c');
    testString3.push_back('c');
    testString3.push_back('c');
    testString3.push_back('c');

    REQUIRE(testString3 == "Sometcccc");
    REQUIRE(testString3.size() == 9);
}
