#include <cassert>
#include "catch2.hpp"
#include "IntegerType.h"
#include "DoubleType.h"
#include "StringType.h"
#include "FormulaType.h"
#include "Table.h"

TEST_CASE("StringType constructor", "[StringType]") {
	SECTION("constructor_GivenIntegerAsString_InitializeProperly") {
		//Arrange
		StringType i("1234");

		//Assert
		REQUIRE(i.size() == 4);
	}
}

TEST_CASE("StringType clone", "[clone]") {
	SECTION("clone_OnNonEmptyInteger_CloneDynamically") {
		//Arrange
		StringType i("1234");

		CellType* g = i.clone();

		//Assert
		REQUIRE(g->toString() == i.toString());
		delete g;
	}
}

TEST_CASE("StringType size", "[size]") {
	SECTION("size_OnStringType_ReturnProperSize") {
		//Arrange
		StringType i("abcde");

		//Assert
		REQUIRE(i.size() == 5);
	}
}

TEST_CASE("StringType toString", "[toString]") {
	SECTION("toString_OnStringType_ReturnItToString") {
		//Arrange
		StringType i("1234");

		//Assert
		REQUIRE(i.toString() == "1234");
	}
}

TEST_CASE("StringType operator+", "[operator+]") {
	SECTION("operator+_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("abc");
		IntegerType d("7");

		double res = i + d;

		//Assert
		REQUIRE(res == 7);
	}

	SECTION("operator+_WithDoubleType_CalculateProperly") {
		//Arrange
		StringType i("3");
		DoubleType d("0.14");

		double res = i + d;

		//Assert
		REQUIRE(res == 3.14);
	}

	SECTION("operator+_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("3");
		StringType d("0.14.12");

		double res = i + d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator+_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		StringType i("Hello friend");
		FormulaType d("=1 + 6", t);

		double res = i + d;

		//Assert
		REQUIRE(res == 7);
	}
}

TEST_CASE("StringType operator-", "[operator-]") {
	SECTION("operator-_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("abc");
		IntegerType d("7");

		double res = i - d;

		//Assert
		REQUIRE(res == -7);
	}

	SECTION("operator-_WithDoubleType_CalculateProperly") {
		//Arrange
		StringType i("3");
		DoubleType d("1.1");

		double res = i - d;

		//Assert
		REQUIRE(res == 1.9);
	}

	SECTION("operator-_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("3");
		StringType d("0.14.12");

		double res = i - d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator-_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		StringType i("3");
		FormulaType d("=1 + 6", t);

		double res = i - d;

		//Assert
		REQUIRE(res == -4);
	}
}

TEST_CASE("StringType operator*", "[operator*]") {
	SECTION("operator*_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("3");
		IntegerType d("7");

		double res = i * d;

		//Assert
		REQUIRE(res == 21);
	}

	SECTION("operator*_WithDoubleType_CalculateProperly") {
		//Arrange
		StringType i("abc");
		DoubleType d("1.5");

		double res = i * d;

		//Assert
		REQUIRE(res == 0);
	}

	SECTION("operator*_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("3");
		StringType d("0.14.12");

		double res = i * d;

		//Assert
		REQUIRE(res == 0);
	}

	SECTION("operator*_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		StringType i("3");
		FormulaType d("=1 + 6", t);

		double res = i * d;

		//Assert
		REQUIRE(res == 21);
	}
}

TEST_CASE("StringType operator/", "[operator/]") {
	SECTION("operator/_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("77");
		IntegerType d("7");

		double res = i / d;

		//Assert
		REQUIRE(res == 11);
	}

	SECTION("operator/_WithDoubleType_CalculateProperly") {
		//Arrange
		StringType i("3");
		DoubleType d("1.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 2);
	}

	SECTION("operator/_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("3");
		StringType d("0.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 6);
	}

	SECTION("operator/_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		StringType i("21");
		FormulaType d("=1 + 6", t);

		double res = i / d;

		//Assert
		REQUIRE(res == 3);
	}
}

TEST_CASE("StringType operator^", "[operator^]") {
	SECTION("operator^_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("2");
		IntegerType d("2");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 4);
	}

	SECTION("operator^_WithDoubleType_CalculateProperly") {
		//Arrange
		StringType i("3");
		DoubleType d("4");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 81);
	}

	SECTION("operator^_WithStringType_CalculateProperly") {
		//Arrange
		StringType i("3");
		StringType d("abc");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 1);
	}

	SECTION("operator^_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		StringType i("2");
		FormulaType d("=2 * 3", t);

		double res = i ^ d;

		//Assert
		REQUIRE(res == 64);
	}
}

