#ifndef GARAGETESTS_H
#define GARAGETESTS_H

#include "catch.h"
#include "../Classes/Garage.h"

TEST_CASE("Garage constructor works correct", "[Garage]")
{
	Garage g = Garage(20);

	REQUIRE(g.empty() == true);
	REQUIRE(g.size() == 0);
}

TEST_CASE("Garage function insert works correct", "[Garage]")
{
	Garage g = Garage(20);

	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	g.insert(v1);
	g.insert(v2);
	g.insert(v3);

	SECTION("Garage function insert throws an exception if user tries to add an existing car")
	{
		REQUIRE_THROWS(g.insert(v1));
		REQUIRE_THROWS(g.insert(v2));
		REQUIRE_THROWS(g.insert(v3));
	}

	SECTION("Garage function insert throws an exception if there is no more space in the garage")
	{
		REQUIRE_THROWS(g.insert(v4));
	}
}

TEST_CASE("Garage function erase works correct", "[Garage]")
{
	Garage g1 = Garage(30);
	Garage g2 = Garage(30);

	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	g1.insert(v1);
	g1.insert(v2);
	g1.insert(v3);
	g1.insert(v4);

	g2.insert(v1);
	g2.insert(v2);
	g2.insert(v3);
	g2.insert(v4);

	int g1InitSize = g1.size();
	int g2InitSize = g2.size();

	g1.erase("Bb5678cC");
	g2.erase("Aa1234bB");

	SECTION("Garage function erase decreases the count of stored vehicles")
	{
		REQUIRE(g1InitSize > g1.size());
		REQUIRE(g2InitSize > g2.size());
	}
}

TEST_CASE("Garage function at works correct", "[Garage]")
{
	Garage g = Garage(30);
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	g.insert(v1);
	g.insert(v2);
	g.insert(v3);
	g.insert(v4);

	Garage g2 = Garage(20);

	SECTION("Garage function throws an exception if the position is invalid")
	{
		REQUIRE_THROWS(g.at(-1));
		REQUIRE_THROWS(g.at(10));
		REQUIRE_THROWS(g.at(4));

		REQUIRE_THROWS(g2.at(-1));
		REQUIRE_THROWS(g2.at(2));
		REQUIRE_THROWS(g2.at(10));
	}

	const Vehicle& v = g.at(0);
	MyString vReg = MyString(v.registration());
	MyString expectedReg = MyString(v1.registration());

	const Vehicle& vr2 = g.at(1);
	MyString v2Reg = MyString(vr2.registration());
	MyString expectedReg2 = MyString(v2.registration());
	
	SECTION("Garage function at returns correct vehicle")
	{
		REQUIRE((vReg == expectedReg));
		REQUIRE((v2Reg == expectedReg2));
	}
}

TEST_CASE("Garage operator[] works correct", "[Garage]")
{
	Garage g = Garage(30);
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	g.insert(v1);
	g.insert(v2);
	g.insert(v3);
	g.insert(v4);

	const Vehicle& v = g[0];
	MyString vReg = MyString(v.registration());
	MyString expectedReg = MyString(v1.registration());

	const Vehicle& vr2 = g[1];
	MyString v2Reg = MyString(vr2.registration());
	MyString expectedReg2 = MyString(v2.registration());

	const Vehicle& vr3 = g[2];
	MyString v3Reg = MyString(vr3.registration());
	MyString expectedReg3 = MyString(v3.registration());

	const Vehicle& vr4 = g[3];
	MyString v4Reg = MyString(vr4.registration());
	MyString expectedReg4 = MyString(v4.registration());

	SECTION("Garage operator[] returns the correct vehicle") 
	{
		REQUIRE((vReg == expectedReg));
		REQUIRE((v2Reg == expectedReg2));
		REQUIRE((v3Reg == expectedReg3));
		REQUIRE((v4Reg == expectedReg4));
	}
}

TEST_CASE("Garage function empty works correct", "[Garage]")
{
	Garage g1 = Garage(20);
	Garage g2 = Garage(30);
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	g2.insert(v1);
	g2.insert(v2);
	g2.insert(v3);
	g2.insert(v4);

	SECTION("Garage function empty returns correct value")
	{
		REQUIRE(g1.empty() == true);
		REQUIRE(g2.empty() == false);
	}
}

TEST_CASE("Garage function size works correct", "[Garage]")
{
	Garage g1 = Garage(40);
	Garage g2 = Garage(30);
	Garage g3 = Garage(20);
	Garage g4 = Garage(16);
	Garage g5 = Garage(7);


	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);
	Vehicle v3 = Vehicle("Cc91011dD", "My third car", 9);
	Vehicle v4 = Vehicle("Dd121314eE", "My fourth car", 15);

	g1.insert(v1);
	g1.insert(v2);
	g1.insert(v3);
	g1.insert(v4);

	g2.insert(v1);
	g2.insert(v2);
	g2.insert(v3);

	g3.insert(v1);
	g3.insert(v2);

	g4.insert(v2);

	SECTION("Garage function size returns correct size")
	{
		REQUIRE(g1.size() == 4);
		REQUIRE(g2.size() == 3);
		REQUIRE(g3.size() == 2);
		REQUIRE(g4.size() == 1);
		REQUIRE(g5.size() == 0);
	}
}

TEST_CASE("Garage function clear wokrs correct", "[Garage]")
{
	Garage g = Garage(20);
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);

	g.insert(v1);
	g.insert(v2);

	g.clear();

	SECTION("Garage function clear decreases stored vehicles count to 0")
	{
		REQUIRE(g.size() == 0);
	}
}

TEST_CASE("Garage function find works correct", "[Garage]")
{
	Garage g = Garage(20);
	Vehicle v1 = Vehicle("Aa1234bB", "My first car", 1);
	Vehicle v2 = Vehicle("Bb5678cC", "My second car", 2);

	g.insert(v1);
	g.insert(v2);

	const Vehicle* first = g.find("Aa1234bB");
	MyString firstReg = MyString(first->registration());
	MyString expectedFirstReg = MyString("Aa1234bB");
	const Vehicle* second = g.find("Bb5678cC");
	MyString secondReg = MyString(second->registration());
	MyString expectedSecondReg = MyString("Bb5678cC");
	const Vehicle* third = g.find("Cc91011dD");
	const Vehicle* fourth = g.find("Dd121314eE");
	SECTION("Garage funtion find returns correct value")
	{
		REQUIRE(first != nullptr);
		REQUIRE((firstReg == expectedFirstReg));
		REQUIRE((secondReg == expectedSecondReg));
		REQUIRE(second != nullptr);
		REQUIRE(third == nullptr);
		REQUIRE(fourth == nullptr);
	}
}
#endif GARAGETESTS_H