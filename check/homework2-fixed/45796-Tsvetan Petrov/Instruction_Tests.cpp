#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Instruction.h"

TEST_CASE("Constructor") {

	Instruction instr("Test 35d gfk 3jf");
	SECTION("Command") {
		REQUIRE(instr.get_command() == "TEST");
	}
	SECTION("First argument") {
		REQUIRE(instr.get_first_argument() == "35d");
	}
	SECTION("Second argument") {
		REQUIRE(instr.get_second_argument() == "gfk");
	}
}

TEST_CASE("Commands") {

	SECTION("VEHICLE") {
		Instruction instr("Vehicle AH4728DG fhsk");
		REQUIRE(instr.get_command() == "VEHICLE");
		REQUIRE(instr.get_first_argument() == "AH4728DG");
		REQUIRE(instr.get_second_argument() == "fhsk");
	}

	SECTION("PERSON") {
		Instruction instr("person Ivan 65");
		REQUIRE(instr.get_command() == "PERSON");
		REQUIRE(instr.get_first_argument() == "Ivan");
		REQUIRE(instr.get_second_argument() == "65");

		Instruction instr2("person \"Ivan Ivanov\" 65");
		REQUIRE(instr2.get_first_argument() == "Ivan Ivanov");
		REQUIRE(instr2.get_second_argument() == "65");
	}

	SECTION("ACQUIRE") {
		Instruction instr("aCquire 65 AH4859HH");
		REQUIRE(instr.get_command() == "ACQUIRE");
		REQUIRE(instr.get_first_argument() == "65");
		REQUIRE(instr.get_second_argument() == "AH4859HH");
	}

	SECTION("RELEASE") {
		Instruction instr("release 65 AH4859HH");
		REQUIRE(instr.get_command() == "RELEASE");
		REQUIRE(instr.get_first_argument() == "65");
		REQUIRE(instr.get_second_argument() == "AH4859HH");
	}

	SECTION("SAVE") {
		Instruction instr("save \"some_path.txt\"");
		REQUIRE(instr.get_command() == "SAVE");
		REQUIRE(instr.get_first_argument() == "some_path.txt");
	}
	SECTION("REMOVE") {
		Instruction instr("reMove something");
		REQUIRE(instr.get_command() == "REMOVE");
		REQUIRE(instr.get_first_argument() == "something");
	}
	SECTION("SHOW") {
		Instruction instr("show something");
		REQUIRE(instr.get_command() == "SHOW");
		REQUIRE(instr.get_first_argument() == "something");
	}
}
