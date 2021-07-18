#include <cassert>
#include "catch2.hpp"
#include "DoubleType.h"
#include "IntegerType.h"
#include "StringType.h"
#include "FormulaType.h"
#include "Table.h"

TEST_CASE("DoubleType constructor", "[DoubleType]") {
	SECTION("constructor_GivenDoubleAsString_InitializeProperly") {
		//Arrange
		DoubleType i("1234.50");

		//Assert
		REQUIRE(i.size() == 11);
	}
}

TEST_CASE("DoubleType clone", "[clone]") {
	SECTION("clone_OnNonEmptyString_CloneDynamically") {
		//Arrange
		DoubleType i("1234");

		CellType* g = i.clone();

		//Assert
		REQUIRE(g->toString() == i.toString());
		delete g;
	}
}

TEST_CASE("DoubleType size", "[size]") {
	SECTION("size_OnDoubleType_ReturnProperSize") {
		//Arrange
		DoubleType i("12345.123");

		//Assert
		REQUIRE(i.size() == 12);
	}
}

TEST_CASE("DoubleType toString", "[toString]") {
	SECTION("toString_OnDoubleType_ReturnItToString") {
		//Arrange
		DoubleType i("1234.123");

		//Assert
		REQUIRE(i.toString() == "1234.123000");
	}
}

TEST_CASE("DoubleType operator+", "[operator+]") {
	SECTION("operator+_WithDoubleType_CalculateProperly") {
		//Arrange
		DoubleType i("3.2");
		DoubleType d("7.8");

		double res = i + d;

		//Assert
		REQUIRE(res == 11);
	}

	SECTION("operator+_WithIntegerType_CalculateProperly") {
		//Arrange
		DoubleType i("3.14");
		IntegerType d("5");

		double res = i + d;

		//Assert
		REQUIRE(res == 8.14);
	}

	SECTION("operator+_WithStringType_CalculateProperly") {
		//Arrange
		DoubleType i("3.123");
		StringType d("0.14.12");

		double res = i + d;

		//Assert
		REQUIRE(res == 3.123);
	}

	SECTION("operator+_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		DoubleType i("3.123");
		FormulaType d("=1 + 6", t);

		double res = i + d;

		//Assert
		REQUIRE(res == 10.123000000000001);
	}
}

TEST_CASE("DoubleType operator-", "[operator-]") {
	SECTION("operator-_WithDoubleType_CalculateProperly") {
		//Arrange
		DoubleType i("3.123");
		DoubleType d("7.123");

		double res = i - d;

		//Assert
		REQUIRE(res == -4);
	}

	SECTION("operator-_WithIntegerType_CalculateProperly") {
		//Arrange
		DoubleType i("3.14");
		IntegerType d("1");

		double res = i - d;

		//Assert
		REQUIRE(res == 2.14);
	}

	SECTION("operator-_WithStringType_CalculateProperly") {
		//Arrange
		DoubleType i("3.12");
		StringType d("0.12");

		double res = i - d;

		//Assert
		REQUIRE(res == 3);
	}

	SECTION("operator-_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		DoubleType i("3.14");
		FormulaType d("=1 + 6", t);

		double res = i - d;

		//Assert
		REQUIRE(res == -3.86);
	}
}

TEST_CASE("DoubleType operator*", "[operator*]") {
	SECTION("operator*_WithDoubleType_CalculateProperly") {
		//Arrange
		DoubleType i("3.14");
		DoubleType d("7");

		double res = i * d;

		//Assert
		REQUIRE(res == 21.98);
	}

	SECTION("operator*_WithIntegerTypeType_CalculateProperly") {
		//Arrange
		DoubleType i("1.5");
		IntegerType d("3");

		double res = i * d;

		//Assert
		REQUIRE(res == 4.5);
	}

	SECTION("operator*_WithStringType_CalculateProperly") {
		//Arrange
		DoubleType i("3");
		StringType d("0.14.12");

		double res = i * d;

		//Assert
		REQUIRE(res == 0);
	}

	SECTION("operator*_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		DoubleType i("3.14");
		FormulaType d("=1 + 6", t);

		double res = i * d;

		//Assert
		REQUIRE(res == 21.98);
	}
}

TEST_CASE("DoubleType operator/", "[operator/]") {
	SECTION("operator/_WithDoubleType_CalculateProperly") {
		//Arrange
		DoubleType i("77.77");
		DoubleType d("7.7");

		double res = i / d;

		//Assert
		REQUIRE(res == 10.1);
	}

	SECTION("operator/_WithIntegerType_CalculateProperly") {
		//Arrange
		DoubleType i("4.6");
		IntegerType d("2");

		double res = i / d;

		//Assert
		REQUIRE(res == 2.3);
	}

	SECTION("operator/_WithStringType_CalculateProperly") {
		//Arrange
		DoubleType i("3.5");
		StringType d("0.5");

		double res = i / d;

		//Assert
		REQUIRE(res == 7);
	}

	SECTION("operator/_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		DoubleType i("21.98");
		FormulaType d("=1 + 6", t);

		double res = i / d;

		//Assert
		REQUIRE(res == 3.14);
	}
}

TEST_CASE("DoubleType operator^", "[operator^]") {
	SECTION("operator^_WithDoubleType_CalculateProperly") {
		//Arrange
		DoubleType i("2.2");
		DoubleType d("2.2");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 5.6666957787500811);
	}

	SECTION("operator^_WithIntegerType_CalculateProperly") {
		//Arrange
		DoubleType i("3.14");
		IntegerType d("4");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 97.211712160000019);
	}

	SECTION("operator^_WithStringType_CalculateProperly") {
		//Arrange
		DoubleType i("3.2");
		StringType d("0.5");

		double res = i ^ d;

		//Assert
		REQUIRE(res == 1.7888543819998317);
	}

	SECTION("operator^_WithFormulaType_CalculateProperly") {
		//Arrange
		Table t;
		DoubleType i("2.2");
		FormulaType d("=2 * 3", t);

		double res = i ^ d;

		//Assert
		REQUIRE(res == 113.37990400000005);
	}
}

