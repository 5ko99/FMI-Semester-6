#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.h"
#include "RegistrationNumber.h"


TEST_CASE("Registration Number") {
	Registration Reg1("A1234BV");
	Registration Reg2("BB5555AA");
	Reg1 = Reg2;
	Registration Reg3("CC1234CC");
	Registration Reg4(Reg3);
	REQUIRE(strcmp(Reg1.registr(), "BB5555AA") == 0);
	REQUIRE(strcmp(Reg4.registr(), "CC1234CC") == 0);
}
