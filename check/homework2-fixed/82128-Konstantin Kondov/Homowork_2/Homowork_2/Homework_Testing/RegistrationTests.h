#ifndef REGISTRATIONTESTS_H
#define REGISTRATIONTESTS_H
#include "catch.h"
#include "../Homework/Registration.h"
#include <sstream>

#define RNT REQUIRE_NOTHROW
#define RT  REQUIRE_THROWS
#define R   REQUIRE


TEST_CASE("Testing initializing registration numbers", "[Registration]") {

	SECTION("Initializing with invalid strings throws exception", "[Registration]") {
		std::string str1 = "czxc asd as ";
		std::string str2 = ".., ,./";
		std::string str3 = "1123      123123123123";

		RT(Registration(str1));
		RT(Registration(str2));
		RT(Registration(str3));
	}

	SECTION("Initializng registration with string, containg capital letters and numbers, being too long or too short throws exception", "[Registration]") {

		std::string str1 = "ASFALT123";
		std::string str2 = "GSOZ1";
		std::string str3 = "DKF191";

		RT(Registration(str1));
		RT(Registration(str2));
		RT(Registration(str3));

	}

	SECTION("Initializng registration with string with lenght 7 and containg capital letters and numbers throws exception", "[Registration]") {
		//Example for valid registration number: "A1234FG"

		std::string str1 = "A123465";
		std::string str2 = "13CCCC";
		std::string str3 = "123ABC4";

		RT(Registration(str1));
		RT(Registration(str2));
		RT(Registration(str3));


	}

	SECTION("Initializng registration with string with lenght 8 and containg capital letters and numbers throws exception", "[Registration]") {
		//Example for valid registration number: "AS1234FG"

		std::string str1 = "A123G465";
		std::string str2 = "13CFCCC";
		std::string str3 = "12A3ABC4";

		RT(Registration(str1));
		RT(Registration(str2));
		RT(Registration(str3));


	}

	SECTION("Initializing with valid registration numbers doesn't  throw exception", "[Registration]") {


		std::string str1 = "XC1234SD";
		std::string str2 = "ZC9854DF";
		std::string str3 = "X1234CZ";

		RNT(Registration(str1));
		RNT(Registration(str2));
		RNT(Registration(str3));

		R(Registration(str1).GetRegNum() == "XC1234SD");
		R(Registration(str2).GetRegNum() == "ZC9854DF");
		R(Registration(str3).GetRegNum() == "X1234CZ" );
		



	}

}
TEST_CASE("Testing registration's output in the console", "[Registration]") {

	std::string str1 = "A9080KL";
	std::string str2 = "AL0987OP";


	Registration reg1(str1);
	Registration reg2(str2);

	std::stringstream regstream1;
	std::stringstream regstream2;

	regstream1 << reg1;
	regstream2 << reg2;

	R(regstream1.str() == "A9080KL");
	R(regstream2.str() == "AL0987OP");


}



#endif 
