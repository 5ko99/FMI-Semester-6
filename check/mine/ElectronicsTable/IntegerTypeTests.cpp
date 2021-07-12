#include <cassert>
#include "catch2.hpp"
#include "IntegerType.h"
#include "DoubleType.h"
#include "StringType.h"
#include "FormulaType.h"
#include "Table.h"

TEST_CASE("IntegerType constructor", "[IntegerType]") {
	SECTION("constructor_GivenIntegerAsString_InitializeProperly") {
		//Arrange
		IntegerType i("1234");

		//Assert
		REQUIRE(i.size() == 4);
	}
}

TEST_CASE("IntegerType clone", "[clone]") {
	SECTION("clone_OnNonEmptyInteger_CloneDynamically") {
		//Arrange
		IntegerType i("1234");

		CellType* g = i.clone();

		//Assert
		REQUIRE(g->toString() == i.toString());
		delete g;
	}
}

TEST_CASE("IntegerType size", "[size]") {
	SECTION("size_OnIntegerType_ReturnProperSize") {
		//Arrange
		IntegerType i("12345");

		//Assert
		REQUIRE(i.size() == 5);
	}
}

TEST_CASE("IntegerType toString", "[toString]") {
	SECTION("toString_OnIntegerType_ReturnItToString") {
		//Arrange
		IntegerType i("1234");

		//Assert
		REQUIRE(i.toString() == "1234");
	}
}

TEST_CASE("IntegerType operator+", "[operator+]") {
	SECTION("operator+_WithIntegerType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		IntegerType d("7");

		double res = i + d;

		//Assert
		REQUIRE(res == 10);
	}

	SECTION("operator+_WithDoubleType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		DoubleType d("0.14");

		double res = i + d;

		//Assert
		REQUIRE(res == 3.14);
	}

	SECTION("operator+_WithStringType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		StringType d("0.14.12");

		double res = i + d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator+_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		IntegerType i("3");
		FormulaType d("=1 + 6", t);

		double res = i + d;

		//Assert
		REQUIRE(res == 10);
	}
}

TEST_CASE("IntegerType operator-", "[operator-]") {
	SECTION("operator-_WithIntegerType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		IntegerType d("7");

		double res = i - d;

		//Assert
		REQUIRE(res == -4);
	}

	SECTION("operator-_WithDoubleType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		DoubleType d("1");

		double res = i - d;

		//Assert
		REQUIRE(res == 2);
	}

	SECTION("operator-_WithStringType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		StringType d("0.14.12");

		double res = i - d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator-_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		IntegerType i("3");
		FormulaType d("=1 + 6", t);

		double res = i - d;

		//Assert
		REQUIRE(res == -4);
	}
}

TEST_CASE("IntegerType operator*", "[operator*]") {
	SECTION("operator*_WithIntegerType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		IntegerType d("7");

		double res = i * d;

		//Assert
		REQUIRE(res == 21);
	}

	SECTION("operator*_WithDoubleType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		DoubleType d("1.5");

		double res = i * d;

		//Assert
		REQUIRE(res == 4.5);
	}

	SECTION("operator*_WithStringType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		StringType d("0.14.12");

		double res = i * d;

		//Assert
		REQUIRE(res == 0);
	}

	SECTION("operator*_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		IntegerType i("3");
		FormulaType d("=1 + 6", t);

		double res = i * d;

		//Assert
		REQUIRE(res == 21);
	}
}

TEST_CASE("IntegerType operator/", "[operator/]") {
	SECTION("operator/_WithIntegerType_CalculateProperly") {
		//Arrange
		IntegerType i("77");
		IntegerType d("7");

		double res = i / d;

		//Assert
		REQUIRE(res == 11);
	}

	SECTION("operator/_WithDoubleType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		DoubleType d("1.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 2);
	}

	SECTION("operator/_WithStringType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		StringType d("0.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 6);
	}

	SECTION("operator/_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		IntegerType i("21");
		FormulaType d("=1 + 6", t);

		double res = i / d;

		//Assert
		REQUIRE(res == 3);
	}
}

TEST_CASE("IntegerType operator^", "[operator^]") {
	SECTION("operator^_WithIntegerType_CalculateProperly") {
		//Arrange
		IntegerType i("2");
		IntegerType d("2");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 4);
	}

	SECTION("operator^_WithDoubleType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		DoubleType d("4");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 81);
	}

	SECTION("operator^_WithStringType_CalculateProperly") {
		//Arrange
		IntegerType i("3");
		StringType d("0.5");

		double res = i ^ d;

		//Assert
		REQUIRE(res == sqrt(3));
	}

	SECTION("operator^_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		IntegerType i("2");
		FormulaType d("=2 * 3", t);

		double res = i ^ d;

		//Assert
		REQUIRE(res == 64);
	}
}

