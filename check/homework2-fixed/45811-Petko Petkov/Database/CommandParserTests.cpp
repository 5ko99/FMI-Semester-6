#include "catch2.hpp"
#include<cassert>
#include "CommandParser.h"

TEST_CASE("CommandParser constructor", "[CommandParser]") {
	SECTION("constructor_givenNonEmptyString_SplitStringProperly") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
		bool areEqual = cp.atToken(0) == "peRsoN" && cp.atToken(1) == "James" && cp.atToken(2) == "100" && cp.getRaw() == s;

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("CommandParser toUpper", "[toUpper]") {
	SECTION("toUpper_onNonUpperedString_UpperIt") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
		cp.toUpper(s);
		bool areEqual = s == "PERSON JAMES 100";

		//Assert
		REQUIRE(areEqual == true);
	}

	SECTION("toUpper_onUpperedString_DoNothing") {
		//Arrange
		char text[] = "PERSON JAMES 100";
		string s = text;
		CommandParser cp(s);

		//Act
		cp.toUpper(s);
		bool areEqual = s == text;

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("CommandParser cmdToUpper", "[cmdToUpper]") {
	SECTION("cmdToUpper_OnNonUpperedCmd_MakeItToUpper") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
		cp.cmdToUpper();

		//Assert
		REQUIRE(cp.atToken(0) == "PERSON");
	}
}

TEST_CASE("CommandParser atToken", "[atToken]") {
	SECTION("atToken_AtValidIndex_ReturnContentsAccordingly") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
		string str = cp.atToken(0);

		//Assert
		REQUIRE(str == "peRsoN");
	}

	SECTION("atToken_AtInvalidIndex_Throw") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Assert
		REQUIRE_THROWS(cp.atToken(3));
		REQUIRE_THROWS_AS(cp.atToken(3), std::out_of_range);
	}
}

TEST_CASE("CommandParser size", "[size]") {
	SECTION("size_OnNonEmptyTokens_GreaterThanZero") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
		size_t length = cp.size();

		//Assert
		REQUIRE(length == 3);
	}

	SECTION("size_OnEmptyTokens_Zero") {
		//Arrange
		CommandParser cp;

		//Assert
		REQUIRE(cp.size() == 0);
	}
}

TEST_CASE("CommandParser getRaw", "[getRaw]") {
	SECTION("getRaw_OnNonEmptyCommand_NonEmptyString") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
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

TEST_CASE("CommandParser clearCmd", "[clearCmd]") {
	SECTION("clearCmd_OnNonEmptyCommand_ClearItAccordingly") {
		//Arrange
		string s = "peRsoN James 100";
		CommandParser cp(s);

		//Act
		cp.clearCmd();

		//Assert
		REQUIRE(cp.size() == 0);
	}

	SECTION("clearCmd_callAtToken_Throw") {
		//Arrange
		CommandParser cp("peRsoN James 100");

		//Act
		cp.clearCmd();

		//Assert
		REQUIRE_THROWS(cp.atToken(0));
	}
}

TEST_CASE("CommandParser getCommandType", "[getCommandType]") {
	SECTION("getCommandType_VEHICLE_ReturnZero") {
		//Arrange
		string s = "VEHICLE James 100";
		CommandParser cp(s);

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 0);
	}

	SECTION("getCommandType_PERSON_ReturnOne") {
		//Arrange
		CommandParser cp("PERSON James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 1);
	}

	SECTION("getCommandType_ACQUIRE_ReturnTwo") {
		//Arrange
		CommandParser cp("ACQUIRE James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 2);
	}

	SECTION("getCommandType_RELEASE_ReturnThree") {
		//Arrange
		CommandParser cp("RELEASE James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 3);
	}

	SECTION("getCommandType_REMOVE_ReturnFour") {
		//Arrange
		CommandParser cp("REMOVE James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 4);
	}

	SECTION("getCommandType_SAVE_ReturnFive") {
		//Arrange
		CommandParser cp("SAVE James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 5);
	}

	SECTION("getCommandType_SHOW_ReturnSix") {
		//Arrange
		CommandParser cp("SHOW James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 6);
	}

	SECTION("getCommandType_EXIT_ReturnSeven") {
		//Arrange
		CommandParser cp("EXIT James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 7);
	}

	SECTION("getCommandType_NOCOMMAND_ReturnEight") {
		//Arrange
		CommandParser cp("INVALID James 100");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 8);
	}

	SECTION("getCommandType_NOCOMMAND_ReturnEight") {
		//Arrange
		CommandParser cp("");

		//Act
		int type = cp.getCommandType();

		//Assert
		REQUIRE(type == 8);
	}
}
