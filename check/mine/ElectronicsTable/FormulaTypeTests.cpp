#include <cassert>
#include "catch2.hpp"
#include "IntegerType.h"
#include "DoubleType.h"
#include "StringType.h"
#include "FormulaType.h"
#include "Table.h"

TEST_CASE("FormulaType constructor", "[FormulaType]") {
	SECTION("constructor_GivenFormulaToCalculate_InitializeProperly") {
		//Arrange
		Table t;
		FormulaType i("=1234 + 0.0000001", t);

		//Assert
		REQUIRE(i.size() == 11);
	}
}

TEST_CASE("FormulaType clone", "[clone]") {
	SECTION("clone_OnNonEmptyFormulaType_CloneDynamically") {
		//Arrange
		Table t;
		FormulaType i("1234", t);

		CellType* g = i.clone();

		//Assert
		REQUIRE(g->toString() == i.toString());
		delete g;
	}
}

TEST_CASE("FormulaType size", "[size]") {
	SECTION("size_OnFormulaType_ReturnProperSize") {
		//Arrange
		Table t;
		FormulaType i("=12345", t);

		//Assert
		REQUIRE(i.size() == 12);
	}
}

TEST_CASE("FormulaType toString", "[toString]") {
	SECTION("toString_OnFormulaType_ReturnItToString") {
		//Arrange
		Table t;
		FormulaType i("=1234", t);

		//Assert
		REQUIRE(i.toString() == "=1234");
	}
}

TEST_CASE("FormulaType operator+", "[operator+]") {
	Table t;
	SECTION("operator+_WithIntegerType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		IntegerType d("7");

		double res = i + d;

		//Assert
		REQUIRE(res == 10);
	}

	SECTION("operator+_WithDoubleType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		DoubleType d("0.14");

		double res = i + d;

		//Assert
		REQUIRE(res == 3.14);
	}

	SECTION("operator+_WithStringType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		StringType d("0.14.12");

		double res = i + d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator+_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		FormulaType i("=3", t);
		FormulaType d("=1 + 6", t);

		double res = i + d;

		//Assert
		REQUIRE(res == 10);
	}
}

TEST_CASE("FormulaType operator-", "[operator-]") {
	Table t;
	SECTION("operator-_WithIntegerType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		IntegerType d("7");

		double res = i - d;

		//Assert
		REQUIRE(res == -4);
	}

	SECTION("operator-_WithDoubleType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		DoubleType d("1");

		double res = i - d;

		//Assert
		REQUIRE(res == 2);
	}

	SECTION("operator-_WithStringType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		StringType d("0.14.12");

		double res = i - d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator-_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		FormulaType i("=3", t);
		FormulaType d("=1 + 6", t);

		double res = i - d;

		//Assert
		REQUIRE(res == -4);
	}
}

TEST_CASE("FormulaType operator*", "[operator*]") {
	Table t;
	SECTION("operator*_WithIntegerType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		IntegerType d("7");

		double res = i * d;

		//Assert
		REQUIRE(res == 21);
	}

	SECTION("operator*_WithDoubleType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		DoubleType d("1.5");

		double res = i * d;

		//Assert
		REQUIRE(res == 4.5);
	}

	SECTION("operator*_WithStringType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		StringType d("0.14.12");

		double res = i * d;

		//Assert
		REQUIRE(res == 0);
	}

	SECTION("operator*_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		FormulaType i("=3", t);
		FormulaType d("=1 + 6", t);

		double res = i * d;

		//Assert
		REQUIRE(res == 21);
	}
}

TEST_CASE("FormulaType operator/", "[operator/]") {
	Table t;
	SECTION("operator/_WithIntegerType_CalculateProperly") {
		//Arrange
		FormulaType i("=77", t);
		IntegerType d("7");

		double res = i / d;

		//Assert
		REQUIRE(res == 11);
	}

	SECTION("operator/_WithDoubleType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		DoubleType d("1.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 2);
	}

	SECTION("operator/_WithStringType_CalculateProperly") {
		//Arrange
		FormulaType i("=3", t);
		StringType d("0.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 6);
	}

	SECTION("operator/_WithFormulaType_CalculateProperly") {
		//Arrange
		Cell c("2", t);
		t.setCellAt(0, 0, c);
		FormulaType i("=A1*2 *(1+2)", t);
		FormulaType d("=1 + 5", t);

		double res = i / d;

		//Assert
		REQUIRE(res == 2);
	}
}

TEST_CASE("FormulaType operator^", "[operator^]") {
	Table t;
	SECTION("operator^_WithIntegerType_CalculateProperly") {
		//Arrange
		Cell c("2", t);
		t.setCellAt(0, 0, c);
		FormulaType i("=A1+2", t);
		IntegerType d("2");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 16);
	}

	SECTION("operator^_WithDoubleType_CalculateProperly") {
		//Arrange
		Cell c("2", t);
		t.setCellAt(0, 0, c);
		FormulaType i("=A1-2", t);
		DoubleType d("4");

		//Act
		double res = i ^ d;

		//Assert
		REQUIRE(res == 0);
	}

	SECTION("operator^_WithStringType_CalculateProperly") {
		//Arrange
		Cell c("2", t);
		t.setCellAt(0, 0, c);
		FormulaType i("=A1+2", t);
		StringType d("0.5");

		//Act
		double res = i ^ d;

		//Assert
		REQUIRE(res == 2);
	}

	SECTION("operator^_WithFormulaType_CalculateProperly") {
		//Arrange
		Cell c("2", t);
		t.setCellAt(0, 0, c);
		FormulaType i("=A1+2", t);
		FormulaType d("=2 * 3", t);

		//Act
		double res = i ^ d;

		//Assert
		REQUIRE(res == 4096);
	}
}

