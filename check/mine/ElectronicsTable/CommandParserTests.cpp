#include "catch2.hpp"
#include<cassert>
#include "CommandParser.h"

TEST_CASE("CommandParser constructor", "[CommandParser]") {
	SECTION("constructor_givenNonEmptyString_SplitStringProperly") {
		//Arrange
		CommandParser cp;
		cp.setData("peRsoN James 100");

		//Act
		bool areEqual = cp.atToken(0) == "peRsoN" && cp.atToken(1) == "James" && cp.atToken(2) == "100" && cp.getRaw() == "peRsoN James 100";

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("CommandParser atToken", "[atToken]") {
	CommandParser cp;
	SECTION("atToken_AtValidIndex_ReturnContentsAccordingly") {
		//Arrange
		cp.setData("peRsoN James 100");

		//Act
		string str = cp.atToken(0);

		//Assert
		REQUIRE(str == "peRsoN");
	}

	SECTION("atToken_AtInvalidIndex_Throw") {
		//Arrange
		cp.setData("peRsoN James 100");

		//Assert
		REQUIRE_THROWS(cp.atToken(3));
		REQUIRE_THROWS_AS(cp.atToken(3), std::out_of_range);
	}
}

TEST_CASE("CommandParser size", "[size]") {
	CommandParser cp;
	SECTION("size_OnEmptyTokens_Zero") {
		//Assert
		REQUIRE(cp.size() == 0);
	}

	SECTION("size_OnNonEmptyTokens_GreaterThanZero") {
		//Arrange
		cp.setData("peRsoN James 100");

		//Act
		size_t length = cp.size();

		//Assert
		REQUIRE(length == 3);
	}
}

TEST_CASE("CommandParser getRaw", "[getRaw]") {
	SECTION("getRaw_OnNonEmptyCommand_NonEmptyString") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp;

		//Act
		cp.setData(s);
		string cpy = cp.getRaw();

		//Assert
		REQUIRE(cpy == s);
	}

	SECTION("getRaw_OnEmptyCommand_EmptyString") {
		//Arrange
		CommandParser cp;

		//Assert
		REQUIRE(cp.getRaw().size() == 0);
	}
}

TEST_CASE("CommandParser setData", "[setData]") {
	SECTION("setData_WithValidData_InitializeProperly") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp;

		//Act
		cp.setData(s);

		//Assert
		REQUIRE(cp.size() == 3);
		REQUIRE(cp.atToken(0) == "peRsoN");
		REQUIRE(cp.atToken(1) == "James");
		REQUIRE(cp.atToken(2) == "100");
	}

	SECTION("setData_OnInvalidData_Throw") {
		//Arrange
		CommandParser cp;

		//Assert
		REQUIRE_THROWS(cp.setData("peRsoN \"James 100"));
		REQUIRE_THROWS_AS(cp.setData("peRsoN \"James 100"), std::invalid_argument);
	}
}

TEST_CASE("CommandParser clearCmd", "[clearCmd]") {
	CommandParser cp;
	SECTION("clearCmd_OnNonEmptyCommand_ClearItAccordingly") {
		//Act
		cp.setData("peRsoN James 100");
		cp.clearCmd();

		//Assert
		REQUIRE(cp.size() == 0);
	}

	SECTION("clearCmd_callAtToken_Throw") {
		//Arrange
		cp.setData("peRsoN James 100");

		//Act
		cp.clearCmd();

		//Assert
		REQUIRE_THROWS(cp.atToken(0));
	}
}

TEST_CASE("CommandParser getCommandType", "[getCommandType]") {
	CommandParser cp;
	SECTION("getCommandType_OPEN_ReturnZero") {
		//Arrange
		cp.setData("OPEN config.txt");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 0);
	}

	SECTION("getCommandType_CLOSE_ReturnOne") {
		//Arrange
		cp.setData("CLOSE");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 1);
	}

	SECTION("getCommandType_NEW_ReturnTwo") {
		//Arrange
		cp.setData("NEW");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 2);
	}

	SECTION("getCommandType_SAVE_ReturnThree") {
		//Arrange
		cp.setData("SAVE");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 3);
	}

	SECTION("getCommandType_SAVEAS_ReturnFour") {
		//Arrange
		cp.setData("SAVEAS");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 4);
	}

	SECTION("getCommandType_EDIT_ReturnFive") {
		//Arrange
		cp.setData("EDIT");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 5);
	}

	SECTION("getCommandType_PRINT_ReturnSix") {
		//Arrange
		cp.setData("PRINT");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 6);
	}

	SECTION("getCommandType_EXIT_ReturnSeven") {
		//Arrange
		cp.setData("EXIT");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 7);
	}

	SECTION("getCommandType_NOCOMMAND_ReturnEight") {
		//Arrange
		cp.setData("INVALID");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 8);
	}

	SECTION("getCommandType_NOCOMMAND_ReturnEight") {
		//Arrange
		cp.setData("das");

		//Act
		int type = (int)cp.getCommandType();

		//Assert
		REQUIRE(type == 8);
	}
}

TEST_CASE("CommandParser tokenizeInnerString", "[tokenizeInnerString]") {
	CommandParser cp;
	SECTION("tokenizeInnerString_NonEmptyString_TokenizeProperly") {
		//Arrange
		cp.setData("Edit argument1 argument2");

		//Assert
		REQUIRE(cp.size() == 3);
		REQUIRE(cp.atToken(0) == "Edit");
		REQUIRE(cp.atToken(1) == "argument1");
		REQUIRE(cp.atToken(2) == "argument2");
	}

	SECTION("tokenizeInnerString_GivenQuotedString_TokenizeProperly") {
		//Arrange
		cp.setData("  Edit \"argument1\" argument2  ");

		//Assert
		REQUIRE(cp.size() == 3);
		REQUIRE(cp.atToken(0) == "Edit");
		REQUIRE(cp.atToken(1) == "\"argument1\"");
		REQUIRE(cp.atToken(2) == "argument2");
	}

	SECTION("tokenizeInnerString_GivenQuotedStringInQuotedString_TokenizeProperly") {
		//Arrange
		cp.setData("  Edit \"\"argument1\"\" argument2  ");

		//Assert
		REQUIRE(cp.size() == 3);
		REQUIRE(cp.atToken(0) == "Edit");
		REQUIRE(cp.atToken(1) == "\"\"argument1\"\"");
		REQUIRE(cp.atToken(2) == "argument2");
	}

	SECTION("tokenizeInnerString_GivenQuotedStringInQuotedString_TokenizeProperly") {
		//Arrange
		cp.setData("  Edit \"\"argument1\" a second quoted \"argument\"\" argument2  ");

		//Assert
		REQUIRE(cp.size() == 3);
		REQUIRE(cp.atToken(0) == "Edit");
		REQUIRE(cp.atToken(1) == "\"\"argument1\" a second quoted \"argument\"\"");
		REQUIRE(cp.atToken(2) == "argument2");
	}
}