#ifndef PERSONSTESTS_H
#define PERSONSTESTS_H
#include "../Homework/Person.h"
#include "../Homework/Vehicle.h"

TEST_CASE("Initializng Person object with different strings", "[Person]") {

	SECTION("Initializng with any kind of string doesnt throw exception", "[Person]") {

		std::string name1 = "Petur Dimitrov";
		std::string name2 = "[[]][];asdzxczxc";
		std::string name3 = "                    1";

		RNT(Person(name1,123));
		RNT(Person(name2,377373));
		RNT(Person(name3,921));

		R(Person(name1, 123).GetName() == name1);
		R(Person(name2, 48109).GetName()== name2);
		R(Person(name3, 28791).GetName() == name3);

	}

}
TEST_CASE("Testing output of person in console", "[Person]") {


	std::string name1 = "Harry Poter";
	std::string name2 = "Johny Bravo";
	std::string name3 = "Donald Trump";

	Person per1(name1, 9383);
	Person per2(name2,312312);
	Person per3(name3, 1566);

	std::stringstream perstream1;
	std::stringstream perstream2;
	std::stringstream perstream3;

	perstream1 << per1;
	perstream2 << per2;
	perstream3 << per3;

	R(perstream1.str() == "Harry Poter/9383\n");
	R(perstream2.str() =="Johny Bravo/312312\n");
	R(perstream3.str() == "Donald Trump/1566\n");



}







#endif
