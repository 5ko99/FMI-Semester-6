#ifndef VEHICLETESTS_H
#define VEHICLETESTS_H
#include "../Homework/Vehicle.h"
#include "../Homework/Person.h"
#include "RegistrationTests.h"


TEST_CASE("Initializing Vehicles with strings and registration numbers", "[Vehicle]"){


	SECTION("Initializing Vehicle with invalid registration number throws eception", "[Vehicle]") {

		std::string str1 = "AXC9484ASSSS";
		std::string str2 = "asdasdasdasdasda";
		std::string str3 = "                                       ";

		std::string description = "description";

		RT(Vehicle(str1, description));
		RT(Vehicle(str2, description));
		RT(Vehicle(str3, description));

	}

	SECTION("Initializing Vehicle with valid registration number doesn't throw eception", "[Vehicle]") {

		std::string str1 = "L0981KO";
		std::string str2 = "KJ2837MM";
		std::string str3 = "BA0987AB";

		std::string description = "description";

		RNT(Vehicle(str1, description));
		RNT(Vehicle(str2, description));
		RNT(Vehicle(str3, description));

		R(Vehicle(str1, description).GetUniRegNum()== "L0981KO");
		R(Vehicle(str2, description).GetUniRegNum()== "KJ2837MM");
		R(Vehicle(str3, description).GetUniRegNum()== "BA0987AB");


	}

}

TEST_CASE("Testing Copy Construcotr for class Vehicle", "[Vehicle]") {

	SECTION("Having Vehicle with invalid registration throws eception", "[Vehicle]") {
		
		std::string str1 = "123sad";
		std::string description = "description";

		RT(Vehicle(Vehicle(str1, description)));
		


	}

	SECTION("Having Vehicle with valid registration doesnt throw exception", "[Vehicle]") {

		std::string str1 = "AS1234BH";
		std::string description = "description";

		RNT(Vehicle(Vehicle(str1, description)));

		R(Vehicle(Vehicle(str1, description)).GetUniRegNum() == "AS1234BH");



	}

}


SCENARIO("Initiliazing Vehicle to an Owner", "[Vehicle]") {


	SECTION("Wanting to set owner where owner was set throws exception", "[Vehicle]") {

		std::string name1 = "Ivan Ivanov";
		std::string name2 = "DIMITURRRRRR";

		std::string reg1 = "AX0987HF";
		std::string description = "description";

		Person per1(name1, 213);
		Person per2(name2, 17221);

		Vehicle veh(reg1, description);

		veh.SetOwner(per1);
		RT(veh.SetOwner(per2));

	}

	SECTION("Setting the same owner againg throws exception", "[Vehicle]") {

		std::string name1 = "Ivan Ivanov";

		std::string reg1 = "AX0987HF";
		std::string description = "description";

		Person per(name1, 123);
		Vehicle veh(reg1, description);

		veh.SetOwner(per);
		RT(veh.SetOwner(per));

	}



	std::string name1 = "MARCUS";
	std::string name2 = "OUStin";
	std::string name3 = "DA VINci";

	std::string reg1 = "AE1234FG";
	std::string reg2 = "A3456HJ";
	std::string reg3 = "LK9876ZL";
	std::string description = "description";

	//creating owners
	Person per1(name1, 12341);
	Person per2(name2, 123123);
	Person per3(name3, 9783);

	//creating vehicles
	Vehicle veh1(reg1, description);
	Vehicle veh2(reg2,description);
	Vehicle veh3(reg3, description);

	//setting the owners (nothrow)
	RNT(veh1.SetOwner(per1));
	RNT(veh2.SetOwner(per2));
	RNT(veh3.SetOwner(per3));

	//owners name matched
	R(veh1.GetOwner().GetName() == name1);
	R(veh2.GetOwner().GetName() == name2);
	R(veh3.GetOwner().GetName() == name3);

	//disownning vehicles
	RNT(veh1.DisOwn());
	RNT(veh2.DisOwn());
	RNT(veh3.DisOwn());

	R(veh1.Is_Taken() == false);
	R(veh2.Is_Taken() == false);
	R(veh3.Is_Taken() == false);

}

TEST_CASE("Testing vehicle's output in the console", "[Vehicle]") {

	std::string reg1 = "XC9837KL";
	std::string reg2 = "P5423DD";

	std::string description = "description";

	Vehicle veh1(reg1, description);
	Vehicle veh2(reg2, description);

	std::stringstream vehstream1;
	std::stringstream vehstream2;

	vehstream1 << veh1;
	vehstream2 << veh2;

	R(vehstream1.str() == "XC9837KL/description\n");
	R(vehstream2.str() == "P5423DD/description\n");



}
#endif
