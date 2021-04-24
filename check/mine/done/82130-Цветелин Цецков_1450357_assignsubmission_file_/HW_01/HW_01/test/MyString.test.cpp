#include <cstring>
#include <stdexcept>
#include "MyString.h"
#include "catch_amalgamated.hpp"

TEST_CASE("MyString constructors with empty strings", "[MyString]") {
	MyString defaultConstr = MyString();
	MyString emptyStrCharPtr = MyString("");

	MyString copyConstrFromDefault = defaultConstr;
	MyString copyConstrFromEmpty = emptyStrCharPtr;

	MyString assignmentFromDefaultConstr;
	assignmentFromDefaultConstr = defaultConstr;
	MyString assignmentFromEmpty;
	assignmentFromEmpty = emptyStrCharPtr;

	const char* emptyStr = "";

	REQUIRE(strcmp(defaultConstr.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(emptyStrCharPtr.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(copyConstrFromDefault.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(copyConstrFromEmpty.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(assignmentFromDefaultConstr.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(assignmentFromEmpty.c_str(), emptyStr) == 0);
}

TEST_CASE("MyString constructors with nullptr", "[MyString]") {
	MyString defaultConstr = MyString();
	MyString emptyStrCharPtr = MyString("");
	MyString nullptrConstr = MyString(nullptr);

	const char* emptyStr = "";

	REQUIRE(strcmp(defaultConstr.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(emptyStrCharPtr.c_str(), emptyStr) == 0);
	REQUIRE(strcmp(nullptrConstr.c_str(), emptyStr) == 0);
}

TEST_CASE("MyString - copy constructor expands size(but to a different buffer)", "[MyString]") {
	MyString longer = "Hello World!";
	MyString constr = longer;

	REQUIRE(strcmp(longer.c_str(), constr.c_str()) == 0);
	REQUIRE(longer.c_str() != constr.c_str());
}

TEST_CASE("MyString - constructing from raw ptr copies", "[MyString]") {
	const char* raw = "Hello World!";
	MyString myStr = raw;

	REQUIRE(strcmp(myStr.c_str(), raw) == 0);
	REQUIRE(raw != myStr.c_str());
}

TEST_CASE("MyString - at(size_t) correct(var/const)", "[MyString]") {
	const char* helloRaw = "Hello";
	MyString hello = helloRaw;
	const MyString constHello = helloRaw;

	for (std::size_t i = 0; i < 5; i++)
	{
		REQUIRE(hello.at(i) == helloRaw[i]);
		REQUIRE(constHello.at(i) == helloRaw[i]);
	}
}

TEST_CASE("MyString - at(size_t) throws(var/const)", "[MyString]") {
	MyString empty = "";
	const MyString constEmpty = "";

	REQUIRE_THROWS_AS(empty.at(0), std::out_of_range);
	REQUIRE_THROWS_AS(constEmpty.at(0), std::out_of_range);
	REQUIRE_THROWS_AS(empty.at(1), std::out_of_range);
	REQUIRE_THROWS_AS(constEmpty.at(1), std::out_of_range);
	REQUIRE_THROWS_AS(empty.at(-1), std::out_of_range);
	REQUIRE_THROWS_AS(constEmpty.at(-1), std::out_of_range);
}


TEST_CASE("MyString - [std::size_t] (var/const)", "[MyString]") {
	const char* helloRaw = "Hello";
	MyString hello = helloRaw;
	const MyString constHello = helloRaw;

	for (std::size_t i = 0; i < 5; i++)
	{
		REQUIRE(hello[i] == helloRaw[i]);
		REQUIRE(constHello[i] == helloRaw[i]);
	}
}

TEST_CASE("MyString - front() - (var/const)", "[MyString]") {
	const char* helloRaw = "Hello";
	MyString hello = helloRaw;
	const MyString constHello = helloRaw;

	REQUIRE(hello.front() == helloRaw[0]);
	REQUIRE(constHello.front() == helloRaw[0]);
}

TEST_CASE("MyString - back() (var/const)", "[MyString]") {
	const char* helloRaw = "Hello";
	std::size_t lastIndex = strlen(helloRaw) - 1;
	MyString hello = helloRaw;
	const MyString constHello = helloRaw;

	REQUIRE(hello.back() == helloRaw[lastIndex]);
	REQUIRE(constHello.back() == helloRaw[lastIndex]);
}

TEST_CASE("MyString - empty() (var/const)", "[MyString]") {
	MyString defConstr = MyString();
	MyString emptyStrConstr = MyString("");

	const char* helloRaw = "Hello";
	MyString hello = helloRaw;
	const MyString constHello = helloRaw;

	REQUIRE(defConstr.empty() == true);
	REQUIRE(emptyStrConstr.empty() == true);
	REQUIRE(hello.empty() == false);
	REQUIRE(constHello.empty() == false);
}

TEST_CASE("MyString - empty after clear", "[MyString]") {
	const char* helloRaw = "Hello";
	MyString copiedCleared = helloRaw;
	copiedCleared.clear();

	REQUIRE(copiedCleared.empty() == true);
}

TEST_CASE("MyString - size() (var/const)", "[MyString]") {
	MyString defConstr = MyString();
	MyString emptyStrConstr = "";

	const char* helloRaw = "Hello";
	MyString hello = helloRaw;
	std::size_t rawLen = strlen(helloRaw);
	const MyString constHello = helloRaw;

	REQUIRE(defConstr.size() == 0);
	REQUIRE(emptyStrConstr.size() == 0);
	REQUIRE(hello.size() == rawLen);
	REQUIRE(constHello.size() == rawLen);
}

TEST_CASE("MyString - clear()", "[MyString]") {
	MyString defConstr = MyString();
	MyString emptyStrConstr = "";
	const char* helloRaw = "Hello";
	MyString hello = helloRaw;

	defConstr.clear();
	emptyStrConstr.clear();
	hello.clear();

	REQUIRE(strcmp(defConstr.c_str(), "") == 0);
	REQUIRE(strcmp(emptyStrConstr.c_str(), "") == 0);
	REQUIRE(strcmp(hello.c_str(), "") == 0);
}

TEST_CASE("MyString - push_back()", "[MyString]") {
	const char* helloRaw = "Hello";
	const std::size_t rawLen = strlen(helloRaw);
	MyString str = MyString();

	for (std::size_t i = 0; i < rawLen; i++)
	{
		str.push_back(helloRaw[i]);
	}
	REQUIRE(strcmp(str.c_str(), helloRaw) == 0);
}

TEST_CASE("MyString - pop_back()", "[MyString]") {
	const char* helloRaw = "Hello";
	const std::size_t rawLen = strlen(helloRaw);
	MyString original = helloRaw;
	MyString cleared = original;
	MyString popped = original;

	cleared.clear();

	for (std::size_t i = 0; i < rawLen; i++)
	{
		popped.pop_back();
	}

	REQUIRE(strcmp(cleared.c_str(), popped.c_str()) == 0);
	REQUIRE(strcmp(popped.c_str(), "") == 0);
}

TEST_CASE("MyString - operator+=(char)", "[MyString]") {
	const char* helloRaw = "Hello";
	const std::size_t rawLen = strlen(helloRaw);
	MyString str = MyString();

	for (std::size_t i = 0; i < rawLen; i++)
	{
		str += helloRaw[i];
	}
	REQUIRE(strcmp(str.c_str(), helloRaw) == 0);
}

TEST_CASE("MyString - operator+=(MyString)", "[MyString]") {
	const std::size_t len = 12;
	MyString str = "";
	MyString other = "a";

	for (std::size_t i = 0; i < len; i++)
	{
		str += other;
	}
	REQUIRE(strcmp(str.c_str(), "aaaaaaaaaaaa") == 0);
}

TEST_CASE("MyString - ==(empties)", "[MyString]") {
	MyString empty = "";
	MyString defaultConstr = "";

	REQUIRE(empty == defaultConstr);
	REQUIRE(empty.c_str() != defaultConstr.c_str());
}

TEST_CASE("MyString - ==(with copied)", "[MyString]") {
	MyString hello = "hello";
	MyString copied = hello;

	REQUIRE(hello == copied);
	REQUIRE(hello.c_str() != copied.c_str());
}

TEST_CASE("MyString - ==(with operator=)", "[MyString]") {
	MyString hello = "hello";
	MyString copied;
	copied = hello;

	REQUIRE(hello == copied);
	REQUIRE(hello.c_str() != copied.c_str());
}

TEST_CASE("MyString - + operator", "[MyString]") {
	MyString hello = "Hello";
	MyString world = "world";
	MyString helloWorld = "Hello world!";
	MyString helloWorldExpr = hello + ' ' + world + '!';

	REQUIRE(helloWorldExpr == helloWorld);
	REQUIRE(helloWorldExpr.c_str() != helloWorld.c_str());
}

TEST_CASE("MyString - < operator(lexicographic order) (single letter)", "[MyString]") {
	MyString letter;
	MyString empty = "";

	for (char i = 'a'; i < 'z'; i++)
	{
		letter.push_back(i);
		REQUIRE(empty < letter);
		letter.pop_back();
	}
}

TEST_CASE("MyString - < operator(lexicographic order) (same strings)", "[MyString]") {
	MyString hello1 = "hello";
	MyString hello2 = "hello";

	REQUIRE_FALSE(hello1 < hello1);
	REQUIRE_FALSE(hello1 < hello2);
	REQUIRE_FALSE(hello2 < hello1);
	REQUIRE_FALSE(hello2 < hello2);
}

TEST_CASE("MyString - < operator(lexicographic order) (numbers)", "[MyString]") {
	MyString _1 = "1";
	MyString _2 = "2";
	MyString _3 = "3";
	MyString _10 = "10";
	MyString _15 = "15";
	MyString _33 = "33";
	MyString _153 = "153";

	REQUIRE(_1 < _2);
	REQUIRE(_1 < _3);
	REQUIRE(_1 < _10);
	REQUIRE(_1 < _15);
	REQUIRE(_1 < _33);

	REQUIRE(_2 < _3);
	REQUIRE(_2 < _33);

	REQUIRE(_10 < _15);
	REQUIRE(_10 < _33);

	REQUIRE(_15 < _33);

	REQUIRE(_153 < _2);
	REQUIRE(_153 < _3);
	REQUIRE(_153 < _33);
}
