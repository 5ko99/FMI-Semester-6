#include <cassert>
#include "catch2.hpp"
#include "Table.h"

TEST_CASE("Table expandRows", "[expandRows]") {
	SECTION("expandRows_OnEmptyTable_expandProperly") {
		//Arrange
		Table t;

		//Act
		t.expandRows(2);

		//Assert
		REQUIRE(t.getRows() == 2);
	}

	SECTION("expandRows_ArgumentZero_DoNothing") {
		//Arrange
		Table t;

		//Act
		t.expandRows(0);

		//Assert
		REQUIRE(t.getRows() == 0);
	}

	SECTION("expandRows_NonEmptyTable_expandProperly") {
		//Arrange
		Table t;

		//Act
		t.expandRows(2);
		t.expandRows(10);

		//Assert
		REQUIRE(t.getRows() == 10);
	}
}

TEST_CASE("Table expandCols", "[expandCols]") {
	SECTION("expandCols_emptyTable_expandProperly") {
		//Arrange
		Table t;

		//Act
		t.expandCols(2);

		//Assert
		REQUIRE(t.getCols() == 2);
	}

	SECTION("expandCols_ArgumentZero_DoNothing") {
		//Arrange
		Table t;

		//Act
		t.expandCols(0);

		//Assert
		REQUIRE(t.getRows() == 0);
	}

	SECTION("expandRows_NonEmptyTable_expandProperly") {
		//Arrange
		Table t;

		//Act
		t.expandRows(2);
		t.expandRows(10);

		//Assert
		REQUIRE(t.getRows() == 10);
	}
}

TEST_CASE("Table operator[]", "[operator[]]") {
	SECTION("operator[]_NonEmptyTable_RetrunProperRow") {
		//Arrange
		Table t;
		t.expandRows(1);
		t.expandCols(4);

		//Act
		size_t sizeOfRow = t[0].size();

		//Assert
		REQUIRE(sizeOfRow == 4);
	}
}

TEST_CASE("Table getRows", "[getRows]") {
	SECTION("getRows_NonEmptyTable_ReturnProperRows") {
		//Arrange
		Table t;

		//Act
		t.expandRows(2);

		//Assert
		REQUIRE(t.getRows() == 2);
	}
}

TEST_CASE("Table getCols", "[getCols]") {
	SECTION("getCols_NonEmptyTable_RetrunProperCols") {
		//Arrange
		Table t;

		//Act
		t.expandRows(2);
		t.expandCols(2);

		//Assert
		REQUIRE(t.getCols() == 2);
		t.clearTable();
	}
}

TEST_CASE("Table empty", "[empty]") {
	SECTION("empty_OnEmptyTable_True") {
		//Arrange
		Table t;

		//Assert
		REQUIRE(t.empty() == true);
	}

	SECTION("empty_OnNonEmptyTable_False") {
		//Arrange
		Table t;

		//Act
		t.expandRows(2);
		t.expandCols(2);

		//Assert
		REQUIRE(t.empty() == false);
	}
}

TEST_CASE("Table setCellAt", "[setCellAt]") {
	SECTION("setCellAt_ValidCell_SetProperly") {
		//Arrange
		Table t;
		Cell c("1234", t);

		//Act
		t.setCellAt(0, 0, c);

		//Assert
		REQUIRE(t.empty() == false);
		REQUIRE(t[0][0].getContentAsDouble() == 1234);
		REQUIRE(t[0][0].getContent() != nullptr);
	}

	SECTION("setCellAt_ExceedingRowsAndCols_ExpandWhilstSettingCell") {
		//Arrange
		Table t;
		Cell c("1234", t);

		//Act
		t.setCellAt(4, 4, c);

		//Assert
		REQUIRE(t.empty() == false);
		REQUIRE(t[4][4].getContentAsDouble() == 1234);
		REQUIRE(t[4][4].getContent() != nullptr);
	}
}

TEST_CASE("Table clearTable", "[clearTable]") {
	SECTION("clearTable_OnEmptyTable_DoNothing") {
		//Arrange
		Table t;

		//Act
		t.clearTable();

		//Assert
		REQUIRE(t.empty() == true);
	}

	SECTION("clearTable_OnNonEmptyTable_ClearItProperly") {
		//Arrange
		Table t;
		Cell c("1234", t);

		//Act
		t.setCellAt(0, 0, c);
		t.clearTable();

		//Assert
		REQUIRE(t.empty() == true);
	}
}