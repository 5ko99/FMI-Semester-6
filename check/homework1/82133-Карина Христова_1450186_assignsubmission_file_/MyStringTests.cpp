#ifndef MYSTRINGTESTS_H
#define MYSTRINGTESTS_H

#include "catch.h"
#include "../Classes/MyString.h"


TEST_CASE("MyString default constructor works correct", "[MyString]")
{
	SECTION("Default constructor creates a string with size 0")
	{
		MyString str = MyString();
		REQUIRE(str.size() == 0);
	}

	SECTION("Default constructor creates an empty string")
	{
		MyString str = MyString();
		REQUIRE(str.empty() == true);
	}
}

TEST_CASE("MyString copy constructor works correct", "[MyString]")
{
	SECTION("MyString copy constructor creates string eityh correct size")
	{
		MyString str = MyString("abc");
		MyString str2 = MyString("abcd");
		MyString str3 = MyString("abcde");
		MyString str4 = MyString("abcdef");
		MyString str5 = MyString("abcdefg");
		MyString str6 = MyString("abcdefgh");
		REQUIRE(str.size() == 3);
		REQUIRE(str2.size() == 4);
		REQUIRE(str3.size() == 5);
		REQUIRE(str4.size() == 6);
		REQUIRE(str5.size() == 7);
		REQUIRE(str6.size() == 8);
	}

	SECTION("MyString copy constructor creates a string that is not empty")
	{
		MyString str = MyString("abc");
		REQUIRE(str.empty() == false);
	}
}

TEST_CASE("MyString at function works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	const MyString str2 = MyString("abcdefg");

	SECTION("Function at returns the correct symbol")
	{
		REQUIRE(str.at(0) == 'a');
		REQUIRE(str.at(1) == 'b');
		REQUIRE(str.at(2) == 'c');
		REQUIRE(str.at(3) == 'd');
		REQUIRE(str.at(4) == 'e');
		REQUIRE(str.at(5) == 'f');
		REQUIRE(str.at(6) == 'g');

		REQUIRE(str2.at(0) == 'a');
		REQUIRE(str2.at(1) == 'b');
		REQUIRE(str2.at(2) == 'c');
		REQUIRE(str2.at(3) == 'd');
		REQUIRE(str2.at(4) == 'e');
		REQUIRE(str2.at(5) == 'f');
		REQUIRE(str2.at(6) == 'g');
	}

	SECTION("Function at throws exception if pos is negative")
	{
		REQUIRE_THROWS(str.at(-1));
		REQUIRE_THROWS(str.at(-10));
		REQUIRE_THROWS(str.at(-15));
		REQUIRE_THROWS(str.at(-22));
		REQUIRE_THROWS(str.at(-43));
	}

	SECTION("Function at throws exception if there is no such element")
	{
		REQUIRE_THROWS(str.at(10));
		REQUIRE_THROWS(str.at(22));
		REQUIRE_THROWS(str.at(36));
		REQUIRE_THROWS(str.at(115));
	}
}

TEST_CASE("MyString operator[] works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	const MyString str2 = MyString("abcdefg");

	SECTION("Operator[] returns the correct symbol")
	{
		REQUIRE(str[0] == 'a');
		REQUIRE(str[1] == 'b');
		REQUIRE(str[2] == 'c');
		REQUIRE(str[3] == 'd');
		REQUIRE(str[4] == 'e');
		REQUIRE(str[5] == 'f');
		REQUIRE(str[6] == 'g');

		REQUIRE(str2[0] == 'a');
		REQUIRE(str2[1] == 'b');
		REQUIRE(str2[2] == 'c');
		REQUIRE(str2[3] == 'd');
		REQUIRE(str2[4] == 'e');
		REQUIRE(str2[5] == 'f');
		REQUIRE(str2[6] == 'g');
	}
}

TEST_CASE("MyString function front works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	MyString str2 = MyString("bcd");
	MyString str3 = MyString("cde");
	MyString str4 = MyString("def");
	MyString str5 = MyString("efg");
	MyString str6 = MyString("fgh");

	const MyString cstr = MyString("abcdefg");
	const MyString cstr2 = MyString("bcd");
	const MyString cstr3 = MyString("cde");
	const MyString cstr4 = MyString("def");
	const MyString cstr5 = MyString("efg");
	const MyString cstr6 = MyString("fgh");

	SECTION("Function front returns the correct symbol")
	{
		REQUIRE(str.front() == 'a');
		REQUIRE(str2.front() == 'b');
		REQUIRE(str3.front() == 'c');
		REQUIRE(str4.front() == 'd');
		REQUIRE(str5.front() == 'e');
		REQUIRE(str6.front() == 'f');

		REQUIRE(cstr.front() == 'a');
		REQUIRE(cstr2.front() == 'b');
		REQUIRE(cstr3.front() == 'c');
		REQUIRE(cstr4.front() == 'd');
		REQUIRE(cstr5.front() == 'e');
		REQUIRE(cstr6.front() == 'f');
	}
}

TEST_CASE("MyString function back works correct", "[MyString]")
{
	MyString str = MyString("a");
	MyString str2 = MyString("ab");
	MyString str3 = MyString("abc");
	MyString str4 = MyString("abcd");
	MyString str5 = MyString("abcde");
	MyString str6 = MyString("abcdef");

	const MyString cstr = MyString("a");
	const MyString cstr2 = MyString("ab");
	const MyString cstr3 = MyString("abc");
	const MyString cstr4 = MyString("abcd");
	const MyString cstr5 = MyString("abcde");
	const MyString cstr6 = MyString("abcdef");
	SECTION("Function back returns the correct symbol")
	{
		REQUIRE(str.back() == 'a');
		REQUIRE(str2.back() == 'b');
		REQUIRE(str3.back() == 'c');
		REQUIRE(str4.back() == 'd');
		REQUIRE(str5.back() == 'e');
		REQUIRE(str6.back() == 'f');

		REQUIRE(cstr.back() == 'a');
		REQUIRE(cstr2.back() == 'b');
		REQUIRE(cstr3.back() == 'c');
		REQUIRE(cstr4.back() == 'd');
		REQUIRE(cstr5.back() == 'e');
		REQUIRE(cstr6.back() == 'f');
	}
}

TEST_CASE("MyString function empty works correct", "[MyString]")
{
	MyString emptStr = MyString();
	MyString str = MyString("abcdefg");

	SECTION("Function empty returns true")
	{
		REQUIRE(emptStr.empty() == true);
	}

	SECTION("Function empty returns false")
	{
		REQUIRE(str.empty() == false);
	}
}

TEST_CASE("MyString function size works correct", "[MyString]")
{
	MyString str = MyString();
	MyString str2 = MyString("ab");
	MyString str3 = MyString("abc");
	MyString str4 = MyString("abcd");
	MyString str5 = MyString("abcde");
	MyString str6 = MyString("abcdef");

	SECTION("Function size returns 0")
	{
		REQUIRE(str.size() == 0);
	}

	SECTION("Function size returns correct size")
	{
		REQUIRE(str2.size() == 2);
		REQUIRE(str3.size() == 3);
		REQUIRE(str4.size() == 4);
		REQUIRE(str5.size() == 5);
		REQUIRE(str6.size() == 6);
	}
}

TEST_CASE("MyString function clear works correct", "[]")
{
	MyString str = MyString("abcdefg");
	SECTION("After function clear the size changes to 0")
	{
		str.clear();
		REQUIRE(str.size() == 0);
	}
}

TEST_CASE("MyString function push_back works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	int str1InitSize = str.size();
	str.push_back('h');
	int str1AfterSize = str.size();

	MyString str2 = MyString();
	int str2InitSize = str2.size();
	str2.push_back('a');
	int str2AfterSize = str2.size();

	SECTION("Function push_back increases the size of the string")
	{
		REQUIRE(str1InitSize < str1AfterSize);
		REQUIRE(str1InitSize + 1 == str1AfterSize);

		REQUIRE(str2InitSize < str2AfterSize);
		REQUIRE(str2InitSize + 1 == str2AfterSize);
	}

	SECTION("Function push_back adds the correct symbol to the end of the string")
	{
		REQUIRE(str.back() == 'h');
		REQUIRE(str2.back() == 'a');
	}
}

TEST_CASE("MyString function pop_back works correct", "[MyString]")
{
	MyString str = MyString("abcdefgh");
	int str1InitSize = str.size();
	str.pop_back();
	int str1AfterSize = str.size();

	MyString str2 = MyString("abcd");
	int str2InitSize = str2.size();
	str2.pop_back();
	int str2AfterSize = str2.size();

	SECTION("Function pop_back decreases the size of the string")
	{
		REQUIRE(str1InitSize > str1AfterSize);
		REQUIRE(str1InitSize - 1 == str1AfterSize);

		REQUIRE(str2InitSize > str2AfterSize);
		REQUIRE(str2InitSize - 1 == str2AfterSize);
	}

	SECTION("Function pop_back removes the correct symbol from the end of the string")
	{
		REQUIRE(str.back() == 'g');
		REQUIRE(str2.back() == 'c');
	}
}

TEST_CASE("MyString operator += (char c) works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	int str1InitSize = str.size();
	str += 'h';
	int str1AfterSize = str.size();

	MyString str2 = MyString();
	int str2InitSize = str2.size();
	str2 += 'a';
	int str2AfterSize = str2.size();

	SECTION("Operator += increases the size of the string")
	{
		REQUIRE(str1InitSize < str1AfterSize);
		REQUIRE(str1InitSize + 1 == str1AfterSize);

		REQUIRE(str2InitSize < str2AfterSize);
		REQUIRE(str2InitSize + 1 == str2AfterSize);
	}

	SECTION("Operator += adds the correct symbol to the end of the string")
	{
		REQUIRE(str.back() == 'h');
		REQUIRE(str2.back() == 'a');
	}
}

TEST_CASE("MyString operator += (const MyString&) works correct", "[MyString]")
{
	MyString str = MyString("abcd");
	int str1InitSize = str.size();

	const MyString str2 = MyString("efg");
	int str2InitSize = str2.size();

	str += str2;
	SECTION("Operator += increases the size of the string")
	{
		REQUIRE(str1InitSize < str.size());
		REQUIRE(str1InitSize + 3 == str.size());
	}
}

TEST_CASE("MyString function c_str works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	const char* p = str.c_str();
	MyString returnedStr = MyString(p);
	REQUIRE((str == returnedStr) == true);
}

TEST_CASE("MyString operator == works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	MyString str2 = MyString("abcdefg");
	MyString str3 = MyString();
	MyString str4 = MyString("abc");
	MyString str5 = MyString();

	SECTION("Operator == increases returns true")
	{
		REQUIRE((str == str2) == true);
		REQUIRE((str == str3) == false);
		REQUIRE((str == str4) == false);
		REQUIRE((str3 == str5) == true);
	}

}

TEST_CASE("MyString operator < works correct", "[MyString]")
{
	MyString str = MyString("abcdefg");
	MyString str2 = MyString("abcdefg");
	MyString str3 = MyString();
	MyString str4 = MyString("abc");
	MyString str5 = MyString();

	SECTION("Operator < returns false")
	{
		REQUIRE((str < str2) == false);
		REQUIRE((str < str3) == false);
		REQUIRE((str < str4) == false);
		REQUIRE((str3 < str5) == false);
	}

	SECTION("Operator < returns true")
	{
		REQUIRE((str4 < str) == true);
		REQUIRE((str3 < str) == true);
	}

}

#endif MYSTRINGTESTS_H
