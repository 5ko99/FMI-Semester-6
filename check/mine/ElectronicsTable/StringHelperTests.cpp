#define CATCH_CONFIG_MAIN
#include<cassert>
#include "catch2.hpp"
#include "StringHelper.h"

using sh = StringHelper;

TEST_CASE("StringHelper splitBy", "[splitBy]") {

	SECTION("splitBy_OnNonEmptyString_SplitItProperly") {
		//Arrange
		string toSplit = "Hello healthy world!";

		//Act
		vector<string> parts = sh::splitBy(toSplit, " ");

		//Assert
		REQUIRE(parts[0] == "Hello");
		REQUIRE(parts[1] == "healthy");
		REQUIRE(parts[2] == "world!");
		REQUIRE(parts.size() == 3);
	}

	SECTION("splitBy_OnEmptyString_ReturnEmptyVector") {
		//Arrange
		string toSplit = "";

		//Act
		vector<string> parts = sh::splitBy(toSplit, " ");

		//Assert
		REQUIRE(parts.size() == 0);
	}

	SECTION("splitBy_OnStringWithOneNumber_ReturnNumber") {
		//Arrange
		string toSplit = "0.5";

		//Act
		vector<string> parts = sh::splitBy(toSplit, " ");

		//Assert
		REQUIRE(parts.size() == 1);
		REQUIRE(parts[0] == "0.5");
	}

	SECTION("splitBy_WithDifferentDelimiter_ReturnNonEmptyVector") {
		//Arrange
		string toSplit = "A-|-bra-|-ca-|-da-|-bra";

		//Act
		vector<string> parts = sh::splitBy(toSplit, "-|-");

		//Assert
		REQUIRE(parts.size() == 5);
		REQUIRE(parts[0] == "A");
		REQUIRE(parts[1] == "bra");
		REQUIRE(parts[2] == "ca");
		REQUIRE(parts[3] == "da");
		REQUIRE(parts[4] == "bra");
	}

	SECTION("splitBy_WithDelimeterInEnquotedString_SplitItProperly") {
		//Arrange
		string toSplit = "hello \"Some string\" bye bye";

		//Act
		vector<string> parts = sh::splitBy(toSplit, " ");

		//Assert
		REQUIRE(parts.size() == 4);
		REQUIRE(parts[0] == "hello");
		REQUIRE(parts[1] == "\"Some string\"");
		REQUIRE(parts[2] == "bye");
		REQUIRE(parts[3] == "bye");
	}

	SECTION("splitBy_WithStringConcatenatedToQuotedString_SplitItProperly") {
		//Arrange
		string toSplit = "hello\"Some string\" bye bye";

		//Act
		vector<string> parts = sh::splitBy(toSplit, " ");

		//Assert
		REQUIRE(parts.size() == 3);
		REQUIRE(parts[0] == "hello\"Some string\"");
		REQUIRE(parts[1] == "bye");
		REQUIRE(parts[2] == "bye");
	}

	SECTION("splitBy_WithQuotedStringInTheEnd_SplitItProperly") {
		//Arrange
		string toSplit = "hello bye bye \"Some string\"";

		//Act
		vector<string> parts = sh::splitBy(toSplit, " ");

		//Assert
		REQUIRE(parts.size() == 4);
		REQUIRE(parts[0] == "hello");
		REQUIRE(parts[1] == "bye");
		REQUIRE(parts[2] == "bye");
		REQUIRE(parts[3] == "\"Some string\"");
	}
}

TEST_CASE("StringHelper isStringInteger", "[isStringInteger]") {

	SECTION("isStringInteger_OnStringThatIsInteger_True") {
		//Assert
		REQUIRE(sh::isStringInteger("1234"));
		REQUIRE(sh::isStringInteger("1234"));
		REQUIRE(sh::isStringInteger("0"));
		REQUIRE(sh::isStringInteger("5812398124"));
		REQUIRE(sh::isStringInteger("17"));
	}

	SECTION("isStringInteger_OnStringThatIsNotInteger_False") {
		//Assert
		REQUIRE(!sh::isStringInteger("95.142"));
		REQUIRE(!sh::isStringInteger("95.142.124"));
		REQUIRE(!sh::isStringInteger("95.142"));
		REQUIRE(!sh::isStringInteger("95   "));
		REQUIRE(!sh::isStringInteger("  95"));
		REQUIRE(!sh::isStringInteger("ABC"));
	}
}

TEST_CASE("StringHelper isStringDouble", "[isStringDouble]") {

	SECTION("isStringDouble_OnStringThatIsDouble_True") {
		//Assert
		REQUIRE(sh::isStringDouble("1234.12"));
		REQUIRE(sh::isStringDouble("1234.654012"));
		REQUIRE(sh::isStringDouble("0.1201294"));
		REQUIRE(sh::isStringDouble("5812398124.121839124"));
		REQUIRE(sh::isStringDouble("17.0"));
	}

	SECTION("isStringInteger_OnStringThatIsNotInteger_False") {
		//Assert
		REQUIRE(!sh::isStringDouble("95"));
		REQUIRE(!sh::isStringDouble("95.142.124"));
		REQUIRE(!sh::isStringDouble("95..142"));
		REQUIRE(!sh::isStringDouble("95.12   "));
		REQUIRE(!sh::isStringDouble("  95.12"));
		REQUIRE(!sh::isStringDouble("ABC.1251"));
	}
}

TEST_CASE("StringHelper isStringValidFormula", "[isStringValidFormula]") {

	SECTION("isStringValidFormula_OnValidFormula_True") {
		//Assert
		REQUIRE(sh::isStringValidFormula("=1234.12 + 2^10 - 5000"));
		REQUIRE(sh::isStringValidFormula("=1234.654012/4000*3 - 500"));
		REQUIRE(sh::isStringValidFormula("=0.1201294*1234"));
		REQUIRE(sh::isStringValidFormula("=5812398124.121839124+12"));
		REQUIRE(sh::isStringValidFormula("=-17.0-542"));
		REQUIRE(sh::isStringValidFormula("=95"));
		REQUIRE(sh::isStringValidFormula("=15/15*\"14.14.23\" +  55-55"));
		REQUIRE(sh::isStringValidFormula("=\"123\" + \"Hello world!\"   \":D\""));
		REQUIRE(sh::isStringValidFormula("    =  15"));
	}

	SECTION("isStringValidFormula_OnInvalidFormula_False") {
		//Assert
		REQUIRE(!sh::isStringValidFormula("95"));
		REQUIRE(!sh::isStringValidFormula("="));
		REQUIRE(!sh::isStringValidFormula("    =      "));
		REQUIRE(!sh::isStringValidFormula("95.142.124"));
		REQUIRE(!sh::isStringValidFormula("95..142"));
		REQUIRE(!sh::isStringValidFormula("=95....12   "));
		REQUIRE(!sh::isStringValidFormula("=  95.*.12"));
		REQUIRE(!sh::isStringValidFormula("ABC.421..1521251"));
		REQUIRE(!sh::isStringValidFormula("=\"95"));
		REQUIRE(!sh::isStringValidFormula("\"=95"));
		REQUIRE(!sh::isStringValidFormula("=95+12.12.12"));
	}
}

TEST_CASE("StringHelper trim", "[trim]") {

	SECTION("trim_OnNonTrimmedString_TrimIt") {
		//Arrange
		string nonTrimmed = "  hello mate     ";

		//Act
		sh::trim(nonTrimmed);

		//Assert
		REQUIRE(nonTrimmed.size() == 10);
	}

	SECTION("trim_OnTrimmedString_DoNothing") {
		//Arrrange
		string trimmed = "hello mate";

		//Act
		sh::trim(trimmed);

		//Assert
		REQUIRE(trimmed.size() == 10);
	}

	SECTION("trim_AfterAddingCharacterToString_TrimItProperly") {
		//Arrrange
		string nonTrimmed = "  hello mate    ";

		//Act
		sh::trim(nonTrimmed);
		nonTrimmed += "   ";
		sh::trim(nonTrimmed);

		//Assert
		REQUIRE(nonTrimmed.size() == 10);
	}
}

TEST_CASE("StringHelper isStringValidString", "[isStringValidString]") {

	SECTION("isStringValidString_OnString_True") {
		//Assert
		REQUIRE(sh::isStringValidString("\"1234\""));
		REQUIRE(sh::isStringValidString("\"\"1234\"	\""));
		REQUIRE(sh::isStringValidString("\"0\""));
		REQUIRE(sh::isStringValidString("\"Abracadabra\""));
		REQUIRE(sh::isStringValidString("\"17\""));
	}

	SECTION("isStringValidString_OnInvalidString_False") {
		//Assert
		REQUIRE(!sh::isStringInteger("95.142"));
		REQUIRE(!sh::isStringInteger("\"95.142.124"));
		REQUIRE(!sh::isStringInteger("95.142\""));
		REQUIRE(!sh::isStringInteger("95   "));
		REQUIRE(!sh::isStringInteger("  New York \"City\""));
		REQUIRE(!sh::isStringInteger("ABC"));
	}
}

TEST_CASE("StringHelper removeQuotations", "[removeQuotations]") {

	SECTION("removeQuotations_onQuotedString_RemoveThem") {
		//Arrange
		string quoted = "\"Hello there mate\"";

		//Act
		sh::removeQuotations(quoted);

		//Assert
		REQUIRE(quoted.size() == 16);
		REQUIRE(quoted[0] != '"');
		REQUIRE(quoted[quoted.size() - 1] != '"');
	}

	SECTION("removeQuotations_onNonQuotedString_DoNothing") {
		//Arrange
		string notQuoted = "Hello there mate";

		//Act
		sh::removeQuotations(notQuoted);

		//Assert
		REQUIRE(notQuoted.size() == 16);
		REQUIRE(notQuoted[0] == 'H');
		REQUIRE(notQuoted[notQuoted.size() - 1] == 'e');
	}
}

TEST_CASE("StringHelper addSpaceInBetweenWords", "[addSpaceInBetweenWords]") {

	SECTION("addSpaceInBetweenWords_OnNonDividedWords_DivideThemWithSpaces") {
		//Arrange
		string nonDivided = "15+44-100*55^10/3";

		//Act
		sh::addSpaceInBetweenWords(nonDivided);

		//Assert
		REQUIRE(nonDivided.size() == 27);
	}

	SECTION("addSpaceInBetweenWords_OnNonDividedNumbers_AddExtraWhiteSpace") {
		//Arrange
		string nonDivided = "15 + 44 - 100 * 55 ^ 10 / 3";

		//Act
		sh::addSpaceInBetweenWords(nonDivided);

		//Assert
		REQUIRE(nonDivided.size() == 37);
		REQUIRE(nonDivided == "15  +  44  -  100  *  55  ^  10  /  3");
	}

	SECTION("addSpaceInBetweenWords_OnNonDividedWords_AddExtraWhiteSpace") {
		//Arrange
		string nonDivided = "abc - def | ghi m 55 ( hello ) my";

		//Act
		sh::addSpaceInBetweenWords(nonDivided);

		//Assert
		REQUIRE(nonDivided.size() == 41);
		REQUIRE(nonDivided == "abc  -  def  |  ghi m 55  (  hello  )  my");
	}

	SECTION("addSpaceInBetweenWords_OnEmptyString_DoNothing") {
		//Arrange
		string nonDivided = "";

		//Act
		sh::addSpaceInBetweenWords(nonDivided);

		//Assert
		REQUIRE(nonDivided.size() == 0);
		REQUIRE(nonDivided == "");
	}
}

TEST_CASE("StringHelper removeEmptyStringsInVector", "[removeEmptyStringsInVector]") {

	vector<string> container = { "hi", "hello", "/", "", "" };
	SECTION("removeEmptyStringsInVector_OnVectorWithEmptyStrings_RemoveThem") {
		//Act
		sh::removeEmptyStringsInVector(container);

		//Assert
		REQUIRE(container.size() == 3);
	}

	SECTION("removeEmptyStringsInVector_OnVectorWithoutEmptyStrings_DoNothing") {
		//Arrange
		vector<string> container = { "hi", "hello", "/" };

		//Act
		sh::removeEmptyStringsInVector(container);

		//Assert
		REQUIRE(container.size() == 3);
	}
}

TEST_CASE("StringHelper getStringFilledWithSpaces", "[getStringFilledWithSpaces]") {

	SECTION("getStringFilledWithSpaces_WithPositiveNumber_ReturnProperNumberOfSpaces") {
		//Arrange
		size_t numOfSpaces = 5;

		//Act
		string spaces = sh::getStringFilledWithSpaces(numOfSpaces);

		//Assert
		REQUIRE(spaces == "     ");
		REQUIRE(spaces.size() == 5);
	}

	SECTION("getStringFilledWithSpaces_WithZero_ReturnEmptyString") {
		//Arrange
		size_t numOfSpaces = 0;

		//Act
		string spaces = sh::getStringFilledWithSpaces(numOfSpaces);

		//Assert
		REQUIRE(spaces == "");
		REQUIRE(spaces.size() == 0);
	}
}

TEST_CASE("StringHelper isStringValidCellAddress", "[isStringValidCellAddress]") {

	SECTION("isStringValidCellAddress_OnValidCell_True") {
		//Assert
		REQUIRE(sh::isStringValidCellAddress("A1"));
		REQUIRE(sh::isStringValidCellAddress("Z100"));
		REQUIRE(sh::isStringValidCellAddress("C6005129"));
		REQUIRE(sh::isStringValidCellAddress("H105129"));
	}

	SECTION("isStringValidCellAddress_OnInvalidCell_False") {
		//Assert
		REQUIRE(!sh::isStringValidCellAddress("AA1"));
		REQUIRE(!sh::isStringValidCellAddress(" ZZ100"));
		REQUIRE(!sh::isStringValidCellAddress("	C6005129.125"));
		REQUIRE(!sh::isStringValidCellAddress("H105129A"));
		REQUIRE(!sh::isStringValidCellAddress("H"));
		REQUIRE(!sh::isStringValidCellAddress("10"));
		REQUIRE(!sh::isStringValidCellAddress("123.da"));
	}
}

TEST_CASE("StringHelper extractCellAddressDetails", "[extractCellAddressDetails]") {

	SECTION("extractCellAddressDetails_WithSize_t_ReturnProperPair") {
		//Arrange		
		string str = "A100";

		//Act
		Pair pair = sh::extractCellAddressDetails(str);

		//Assert
		REQUIRE(pair.key == 99);
		REQUIRE(pair.value == 0);
	}

	SECTION("extractCellAddressDetails_WithSize_t_ReturnProperPair") {
		//Arrange		
		string str = "Z50000";

		//Act
		Pair pair = sh::extractCellAddressDetails(str);

		//Assert
		REQUIRE(pair.key == 49999);
		REQUIRE(pair.value == 25);
	}
}

TEST_CASE("StringHelper enquoteString", "[enquoteString]") {

	SECTION("enquoteString_onNonEmptyString_EnquoteIt") {
		//Arrange
		string str = "hey";

		//Act
		sh::enquoteString(str);

		//Assert
		REQUIRE(str.size() == 5);
		REQUIRE(str[0] == '"');
		REQUIRE(str[str.size() - 1] == '"');
	}
}

TEST_CASE("StringHelper toUpper", "[toUpper]") {
	SECTION("toUpper_onNonUpperedString_UpperIt") {
		//Arrange
		string s = "peRsoN James 100";

		//Act
		bool areEqual = sh::toUpper(s) == "PERSON JAMES 100";

		//Assert
		REQUIRE(areEqual == true);
	}

	SECTION("toUpper_onUpperedString_DoNothing") {
		//Arrange
		string s = "PERSON JAMES 100";

		//Act
		bool areEqual = sh::toUpper(s) == "PERSON JAMES 100";

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("StringHelper getQuotesCount", "[getQuotesCount]") {
	SECTION("getQuotesCount_OnNonQuotedStrings_0") {
		//Arrange
		string s = "peRsoN James 100";

		//Act
		size_t quotes = sh::getQuotesCount(s);

		//Assert
		REQUIRE(quotes == 0);
	}

	SECTION("getQuotesCount_OnProperlyQuotedString_0") {
		//Arrange
		string s = "peRsoN \"James\" 100";

		//Act
		size_t quotes = sh::getQuotesCount(s);

		//Assert
		REQUIRE(quotes == 2);
	}
}