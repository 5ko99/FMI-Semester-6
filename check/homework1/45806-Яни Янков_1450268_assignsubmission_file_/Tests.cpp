/*#define CATCH_CONFIG_MAIN
#include "MyString.hpp"
#include "Vehicle.hpp"
#include "Garage.hpp"
#include "catch2.hpp"

//TestMyString**********************************************************************
TEST_CASE("MyString Default Constructor", "[MyString]")
{
	SECTION("MyString Default Constructor should make an empty string")
	{
		//arrange
		MyString empty;

		//act
		const char* string = empty.c_str();
		unsigned lenght = empty.size();
		unsigned capacity = empty.get_capacity();

		//assert
		REQUIRE (string == nullptr);
		REQUIRE(lenght == 0);
		REQUIRE(capacity == 1);
	}
}

TEST_CASE("MyString  Constructor", "[MyString]")
{
	SECTION("MyString  Constructor should initialize a MyString object with an empty string ")
	{
		//arrange
		MyString empty("");

		//act
		const char* string = empty.c_str();
		unsigned lenght = empty.size();
		unsigned capacity = empty.get_capacity();

		//assert
		REQUIRE(lenght == 0);
		REQUIRE(capacity == 1);
	}

	SECTION("MyString  Constructor should initialize a MyString object with a string ")
	{
		//arrange
		MyString empty("this string is not empty!");

		//act
		unsigned lenght = empty.size();
		unsigned capacity = empty.get_capacity();

		//assert
		REQUIRE(lenght == 25);
		REQUIRE(capacity == 26);
	}
}

TEST_CASE("resize() should multiply object's capacity by 2", "[resize]")
{
	SECTION("MyString  resize() should resize a MyString object ")
	{
		//arrange
		MyString A("abc");

		//act
		A.resize();
		unsigned lenght = A.size();
		unsigned capacity = A.get_capacity();

		//assert
		REQUIRE(lenght == 3);
		REQUIRE(capacity == 8);
	}
	SECTION("MyString  resize() should resize a MyString object ")
	{
		//arrange
		MyString A("");

		//act
		A.resize();
		unsigned lenght = A.size();
		unsigned capacity = A.get_capacity();

		//assert
		REQUIRE(lenght == 0);
		REQUIRE(capacity == 2);
	}
}

TEST_CASE("Copy constructor should copy object", "[MyString()]")
{
	SECTION("Copy constructor should copy object")
	{
		//arrange
		MyString A("abc");

		//act
		MyString B(A);
		unsigned lenght = B.size();
		unsigned capacity = B.get_capacity();

		//assert
		REQUIRE(lenght == 3);
		REQUIRE(capacity == 4);
	}
}

TEST_CASE("Copy assignment should copy object", "[operator=]")
{
	SECTION("Copy copy assignment should copy object")
	{
		//arrange
		MyString A("abc");

		//act
		MyString B=A;
		unsigned lenght = B.size();
		unsigned capacity = B.get_capacity();

		//assert
		REQUIRE(lenght == 3);
		REQUIRE(capacity == 4);
	}
}

TEST_CASE("at() should return element at given position", "[at]")
{
	SECTION("at() should return element at given position ")
	{
		//arrange
		MyString A("abcdefghi");

		//act
		char c = A.at(5);

		//assert
		REQUIRE(c == 'f');
	}
	SECTION("at() should throw exception when the position is invalid")
	{
		//arrange
		MyString A("abc");

		//assert
		REQUIRE_THROWS_AS(A.at(5),out_of_range);
	
	}
}

TEST_CASE("front() should return the first element ", "[front]")
{
	SECTION("front() should return the first element")
	{
		//arrange
		MyString A("abcdefghi");

		//act
		char c = A.front();

		//assert
		REQUIRE(c == 'a');
	}
	SECTION("front() should return null char as first element")
	{
		//arrange
		MyString A("");

		//act
		char c = A.front();

		//assert
		REQUIRE(c == '\0');
	}
}

TEST_CASE("back() should return the last element ", "[back]")
{
	SECTION("back() should return the last element")
	{
		//arrange
		MyString A("abcdefghi");

		//act
		char c = A.back();

		//assert
		REQUIRE(c == 'i');
	}
	SECTION("front() should return null char as last element")
	{
		//arrange
		MyString A("");

		//act
		char c = A.back();

		//assert
		REQUIRE(c == '\0');
	}
}

TEST_CASE("empty() should return true if MyString is empty and false if it's not", "[empty]")
{
	SECTION("empty() should return true")
	{
		//arrange
		MyString A("");

		//act
		bool flag = A.empty();

		//assert
		REQUIRE(flag==true);
	}
	SECTION("empty() should return false")
	{
		//arrange
		MyString A("abc");

		//act
		bool flag = A.empty();

		//assert
		REQUIRE(flag==false);
	}
}

TEST_CASE("size() should return the lenght of MyString ", "[size]")
{
	SECTION("size() should return lenght")
	{
		//arrange
		MyString A("");

		//act
		size_t size = A.size();

		//assert
		REQUIRE(size == 0);
	}
	SECTION("size() should return lenght")
	{
		//arrange
		MyString A("abcdefg");

		//act
		size_t size = A.size();

		//assert
		REQUIRE(size == 7);
	}
}

TEST_CASE("clear() should clear the  object", "[clear]")
{
	SECTION("clear() should clear")
	{
		//arrange
		MyString A("abcdefghijk");

		//act
		A.clear();
		size_t lenght = A.size();

		//assert
		REQUIRE(lenght == 0);
		
	}
}

TEST_CASE("push_back() should add a char at the end of the string", "[push_back]")
{
	SECTION("push_back() should add char at the end of the string")
	{
		//arrange
		MyString A("abcdefghijk");

		//act
		A.push_back('Q');
		char pushed_element = A.back();

		//assert
		REQUIRE(pushed_element == 'Q');
	}
	SECTION("push_back() should add char at the end of a empty string")
	{
		//arrange
		MyString A("");

		//act
		A.push_back('E');
		char pushed_element = A.back();

		//assert
		REQUIRE(pushed_element == 'E');

	}
}

TEST_CASE("pop_back() should delete the last element of the string", "[pop_back]")
{
	SECTION("pop_back() should delete the last element of the string")
	{
		//arrange
		MyString A("abcdefghijk");

		//act
		A.pop_back();
		char pushed_element = A.back();

		//assert
		REQUIRE(pushed_element == 'j');
	}
}

TEST_CASE("operator+= should concatenate char to string", "[operator+=]")
{
	SECTION("operator+= should concatenate char to string")
	{
		//arrange
		MyString A("abcdefghijk");

		//act
		A+='L';
		char element = A.back();

		//assert
		REQUIRE(element == 'L');
	}
}

TEST_CASE("operator+= should concatenate MyString to MyString", "[operator+=]")
{
	SECTION("operator+= should concatenate MyString to MyString")
	{
		//arrange
		MyString A("abcdefghi");
		MyString B("ADDD");

		//act
		A +=B;
	
		//assert
		REQUIRE(A.back()=='D');
	}
}

TEST_CASE("c_str should return const string", "[c_str]")
{
	SECTION("c_str should return const string from MyString object")
	{
		//arrange
		MyString A("abcdefghi");
		MyString B("ADDD");

		//act
		unsigned a = (strcmp("abcdefghi", A.c_str()));
		unsigned b = (strcmp("ADDD", B.c_str()));

		//assert
		REQUIRE(a==0);
		REQUIRE(b == 0);
	}
}

TEST_CASE("operator== should return true if two MyStrings are =", "[operator==]")
{
	SECTION("operator== should return true ")
	{
		//arrange
		MyString A("ADDD");
		MyString B("ADDD");

		//act
		bool flag = A == B;

		//assert
		REQUIRE(flag == true);
	}
	SECTION("operator== should return false ")
	{
		//arrange
		MyString A("ADDD");
		MyString B("ooooo");

		//act
		bool flag = A == B;

		//assert
		REQUIRE(flag == false);
	}
}

TEST_CASE("operator< should return true if str1<str2", "[operator==]")
{
	SECTION("operator< should return true ")
	{
		//arrange
		MyString A("ADDD");
		MyString B("BDDD");

		//act
		bool flag = A < B;

		//assert
		REQUIRE(flag == true);
	}
	SECTION("operator< should return false ")
	{
		//arrange
		MyString A("aalop");
		MyString B("aaaq");

		//act
		bool flag = A < B;

		//assert
		REQUIRE(flag == false);
	}
}

//Vehicle************************************************************************
TEST_CASE("Vehicle Constructor", "[Vehicle]")
{
	SECTION("Vehicle Constructor should initialize a vehicle")
	{
		//arrange
		Vehicle v("0511", "Ford", 1);
		size_t space = v.space();


		//act


		//assert
		REQUIRE(strcmp(v.registration(), "0511") == 0);
		REQUIRE(strcmp(v.description(), "Ford") == 0);
		REQUIRE(space == 1);
	}
}

//Garage*************************************************************************
TEST_CASE("insert vehicle", "[insert]")
{
	SECTION("inser() should insert a new vehicle when there is enough space!")
	{
		//arrange
		Garage A(5);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("5544", "Mazda", 1);
		Vehicle c("6666", "BMW", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);

		//assert
		REQUIRE(A.size() == 3);
	}

	SECTION("inser() should throw an exception when there is not enough space!")
	{
		//arrange
		Garage A(3);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("5544", "Mazda", 1);
		Vehicle c("6666", "BMW", 2);

		//act
		A.insert(a);
		A.insert(b);

		//assert
	
		REQUIRE_THROWS_AS(A.insert(c), out_of_range);
	}
	SECTION("inser() should throw an exception when there is na car with the same registration number!")
	{
		//arrange
		Garage A(7);
		Vehicle a("6666", "Tesla", 2);
		Vehicle b("5544", "Mazda", 1);
		Vehicle c("6666", "BMW", 2);

		//act
		A.insert(a);
		A.insert(b);

		//assert

		REQUIRE_THROWS_AS(A.insert(c), std::invalid_argument);
	}
}

TEST_CASE("copy constructor should copy garage", "[Garage]")
{
	SECTION("copy constructor should make a copy of a given garage")
	{
		//arrange
		Garage A(5);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("5544", "Mazda", 1);
		Vehicle c("6666", "BMW", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		Garage B(A);

		//assert
		REQUIRE(B.size() == 3);
	}
}

TEST_CASE("copy assignment should copy garage", "[Garage]")
{
	SECTION("copy assignment should make a copy of a given garage")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("5544", "Mazda", 1);

		//act
		A.insert(a);
		A.insert(b);
		Garage B=A;

		//assert
		REQUIRE(B.size() == 2);
	}
}

TEST_CASE("erase should erase a vehicle from the garage by it's registration number", "[erase]")
{
	SECTION("erase should erase a vehicle")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 1);
		Vehicle c("5544", "Mazda", 1);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.erase("6666");
		

		//assert
		REQUIRE(A.size() == 2);
		REQUIRE(A.find("5544") != nullptr);
	}
}

TEST_CASE("at should return the vehicle at given position ", "[at]")
{
	SECTION("at should return a vehicle")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);


		//assert
		REQUIRE(A.at(1).space()==3);
		REQUIRE(strcmp(A.at(2).registration() , "5544")==0);
	}
	SECTION("at should throw an exception when there is invalid input")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);


		//assert
		REQUIRE_THROWS_AS(A.at(5), out_of_range);
		
	}
}

TEST_CASE("operator[] should return the vehicle at given position ", "[operator[]]")
{
	SECTION("[] should return a vehicle")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		size_t d_space = A[3].space();

		//assert
		REQUIRE(d_space==2);
		REQUIRE(strcmp(A[3].registration(), "1111") == 0);
	}
	SECTION("[] should return a vehicle")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);


		//assert
		REQUIRE_THROWS_AS(A[5], out_of_range);
	}
}

TEST_CASE("empty should return true if the garage has no vehicles in it ", "[empty]")
{
	SECTION("empty should return false")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);

		//assert
		REQUIRE(A.empty()==false);
	}
	SECTION("empty should return true")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);

		A.erase("1234");
		A.erase("6666");
		A.erase("5544");
		A.erase("1111");

		//assert
		REQUIRE(A.empty() == true);
	}
	SECTION("empty should return true")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act

		//assert
		REQUIRE(A.empty() == true);
	}
}

TEST_CASE("clear should clear the garage ", "[clear]")
{
	SECTION("empty should return true")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		A.clear();
		//assert
		REQUIRE(A.empty() == true);
		REQUIRE(A.size() == 0);
	}
}

TEST_CASE("size should return the number of vehicles in the garage ", "[size]")
{
	SECTION("size should return the number of vehicles")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		//assert
		REQUIRE(A.size() == 4);
	}
	SECTION("size should return the number of vehicles")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		A.clear();
		//assert
		REQUIRE(A.size() == 0);
	}
	SECTION("size should return the number of vehicles")
	{
		//arrange
		Garage A(10);
		//assert
		REQUIRE(A.size() == 0);
	}
}

TEST_CASE("find should return a pointer to the vehicle with given registration number", "[find]")
{
	SECTION("find should return the vehicle with given registration number")
	{
		//arrange
		Garage A(15);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 5);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		size_t mazda_space = A.find("5544")->space();
		//assert
		REQUIRE(mazda_space == 5);
	}
	SECTION("find should return nullptr")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		//assert
		REQUIRE(A.find("0000") == nullptr);
	}
	SECTION("find should return nullptr")
	{
		//arrange
		Garage A(10);
		Vehicle a("1234", "Tesla", 2);
		Vehicle b("6666", "Infinity", 3);
		Vehicle c("5544", "Mazda", 1);
		Vehicle d("1111", "Subaru", 2);

		//act
		A.insert(a);
		A.insert(b);
		A.insert(c);
		A.insert(d);
		A.clear();
		//assert
		REQUIRE(A.find("6666") == nullptr);
	}
}
*/

