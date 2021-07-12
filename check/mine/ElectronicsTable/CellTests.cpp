#include <cassert>
#include "catch2.hpp"
#include "Cell.h"
#include "Table.h"
#include "StringType.h"
#include "IntegerType.h"
#include "DoubleType.h"
#include "FormulaType.h"

using std::move;

TEST_CASE("Cell constructor", "[Cell]")
{
	Table t;
	SECTION("constructor_withIntegerType_initializeCellProperly")
	{
		//Arrange
		Cell c("150", t);

		//Assert
		REQUIRE(c.getContentAsDouble() == 150);
	}

	SECTION("constructor_withDoubleType_initializeCellProperly")
	{
		//Arrange
		Cell c("150.151", t);

		//Assert
		REQUIRE(c.getContentAsDouble() == 150.151);
	}

	SECTION("constructor_withStringType_initializeCellProperly")
	{
		//Arrange
		Cell c("\"abcdsdaw\"", t);

		//Act
		string p = c.getContent()->toString();

		//Assert
		REQUIRE(c.getContentAsDouble() == 0);
		REQUIRE(p == "abcdsdaw");
	}

	SECTION("constructor_withFormulaType_initializeCellProperly")
	{
		//Arrange
		Cell c("\"=1500 * \"12.2133.3555\" \"", t);

		//Assert
		REQUIRE(c.getContentAsDouble() == 0);
	}
}

TEST_CASE("Cell Copy Constructor", "[Cell]")
{
	Table t;
	SECTION("copyCtor_withNonEmptyCell_CopyProperly")
	{
		//Arrange
		Cell c("150", t);
		Cell b(c);

		//Act
		bool areEqual = b.getContent()->toString() == c.getContent()->toString();

		//Assert
		REQUIRE(b.getContentAsDouble() == c.getContentAsDouble());
		REQUIRE(areEqual == true);
	}

	SECTION("copyCtor_withEmptyCell_CopyProperly")
	{
		//Arrange
		Cell c("", t);
		Cell b(c);
		b = c;

		//Assert
		REQUIRE(b.getContent() == nullptr);
	}
}

TEST_CASE("Cell Copy operator=", "[operator=]")
{
	Table t;
	SECTION("operator=_withNonEmptyCell_CopyProperly")
	{
		//Arrange
		Cell c("150", t);
		Cell b("124124", t);

		//Act
		b = c;
		bool areEqual = b.getContent()->toString() == c.getContent()->toString();

		//Assert
		REQUIRE(b.getContentAsDouble() == c.getContentAsDouble());
		REQUIRE(areEqual == true);
	}

	SECTION("operator=__withEmptyCell_CopyProperly")
	{
		//Arrange
		Cell c("", t);
		Cell b("\"Hello\"", t);

		//Act
		b = c;

		//Assert
		REQUIRE(b.getContent() == nullptr);
	}
}

TEST_CASE("Cell Move Constructor", "[Cell]")
{
	Table t;
	SECTION("moveConstructor_withNonEmptyCell_MoveProperly")
	{
		//Arrange
		Cell c("150", t);
		Cell b(move(c));

		//Act
		bool areEqual = c.getContent() == nullptr;
		bool areEqualRawDatas = b.getContent()->toString() == "150";

		//Assert
		REQUIRE(b.getContentAsDouble() != c.getContentAsDouble());
		REQUIRE(areEqualRawDatas == true);
		REQUIRE(areEqual == true);
	}

	SECTION("copyCtor_withEmptyCell_MoveProperly")
	{
		//Arrange
		Cell c("", t);
		Cell b(move(c));

		//Assert
		REQUIRE(b.getContent() == nullptr);
	}
}

TEST_CASE("Cell Move operator=", "[operator=]")
{
	Table t;
	SECTION("operator=_withNonEmptyCell_MoveProperly")
	{
		//Arrange
		Cell c("150", t);
		Cell b("", t);
		b = move(c);

		//Act
		bool areEqual = c.getContent() == nullptr;

		//Assert
		REQUIRE(b.getContentAsDouble() == 150);
		REQUIRE(areEqual == true);
	}

	SECTION("operator=_withEmptyCell_MoveProperly")
	{
		//Arrange
		Cell c("", t);
		Cell b("150", t);

		//Act
		b = move(c);

		//Assert
		REQUIRE(b.getContent() == nullptr);
	}
}