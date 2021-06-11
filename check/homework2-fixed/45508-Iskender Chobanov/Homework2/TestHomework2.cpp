#define CATCH_CONFIG_MAIN


//#include "../Homework2/application.h"
#include "application.h"
#include <catch2/catch.hpp>



//Test case for plate under 7 symbols
TEST_CASE("Registration test validation : Under 7 symbols", "[Registration]") {

	Registration test("AB");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("1234");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("BAEW");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("");
	CHECK(test.plate_is_valid() == false);

	
}
//Test case for plate over 8 symbols
TEST_CASE("Registration test validation : Over 8 symbols", "[Registration]") {

	Registration test("AB1234BAA");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("1234213123");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("BAEWDWADWA");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("ABB12314A");
	CHECK(test.plate_is_valid() == false);


}
//Test case for including small letters
TEST_CASE("Registration test validation : Contains small letters", "[Registration]") {

	Registration test("AB1234bA");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("aB1234BA");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("ab1234ba");
	CHECK(test.plate_is_valid() == false);
	test.make_reg("Ab1234BA");
	CHECK(test.plate_is_valid() == false);


}
//Test case valid plate testing with 7 or 8 symbols
TEST_CASE("Registration test validation : Valid plates with 7 or 8 symbols", "[Registration]") {

	Registration test("AB1234BA");
	CHECK(test.plate_is_valid() == true);
	test.make_reg("SD3243AB");
	CHECK(test.plate_is_valid() == true);
	test.make_reg("E1234GB");
	CHECK(test.plate_is_valid() == true);
	test.make_reg("PA5629ZA");
	CHECK(test.plate_is_valid() == true);



}
TEST_CASE("PERSON <name> <id>  functionality testing: ", "[application]") {

	Application application;
	SECTION("Test restricted ids (id 0 and id of an existing person):")
	{
		CHECK(application.add_Person("Alek", 0) == false);
		//Negative ids are handled outside of add_Preson
		application.add_Person("Alek", 1);
		CHECK(application.add_Person("Tony", 1) == false);

	}
	SECTION("Test long name with spaces")
	{
		CHECK(application.add_Person("Ivan Ivanov", 2));
		CHECK(application.add_Person("Ivan Ivanov Gogata", 3));
		CHECK(application.get_person(2).get_name() == "Ivan Ivanov");
		CHECK(application.get_person(3).get_name() == "Ivan Ivanov Gogata");
	}

}
TEST_CASE("add_Person(name,id) functionality testing: ", "[application]") {

	Application application;
	SECTION("Test restricted ids (id 0 and id of an existing person):")
	{
		CHECK(application.add_Person("Alek", 0) == false);
		//Negative ids are handled outside of add_Preson
		application.add_Person("Alek", 1);
		CHECK(application.add_Person("Tony", 1) == false);

	}
	SECTION("Test long name with spaces")
	{
		CHECK(application.add_Person("Ivan Ivanov", 2));
		CHECK(application.add_Person("Ivan Ivanov Gogata", 3));
		CHECK(application.get_person(2).get_name() == "Ivan Ivanov");
		CHECK(application.get_person(3).get_name() == "Ivan Ivanov Gogata");
	}
	SECTION("Add exising person")
	{
		application.add_Person("Person Personov", 3);
		CHECK(application.add_Person("Another", 3) == false);
		CHECK(application.get_person(3).get_name() == "Person Personov");
	}
}

TEST_CASE("add_Vehicle(registration,description) Trying to ","[application]") {

	Application application;
	SECTION("Add valid vehicles:")
	{
		CHECK(application.add_Vehicle("AB1234BA", "Description Anything"));
		CHECK(application.add_Vehicle("B1234BA", "Any Description"));
		CHECK(application.get_vehicle("AB1234BA").get_reg() == "AB1234BA");
		CHECK(application.get_vehicle("B1234BA").get_reg() == "B1234BA");
		CHECK(application.get_vehicle("AB1234BA").get_desc() == "Description Anything");
		CHECK(application.get_vehicle("B1234BA").get_desc() == "Any Description");

	}
	SECTION("Add existing vehicle")
	{
		application.add_Vehicle("AB1234BA", "Description");
		CHECK(application.add_Vehicle("AB1234BA", "Another description")==false);
		CHECK(application.reg_is_unique("AB1234BA") == false);
		CHECK(application.get_vehicle("AB1234BA").get_desc() == "Description");
	}
	SECTION("Add incorrect vehicle")
	{
		CHECK(application.add_Vehicle("1231", "Description") == false);
		CHECK(application.get_vehicle("1231").get_desc() == "");
		CHECK(application.get_vehicle("1231").get_reg() == "");
		//Because vehicle is not registered in the database
	}
}
TEST_CASE("aquire(id,registration) testing", "[application]")
{
	Application application;
	application.add_Person("Alek", 1);
	application.add_Person("Aleksei", 2);
	application.add_Vehicle("AB1234BA", "Honda Civic Type R");
	application.add_Vehicle("B1234BA", "Hyndai");
	SECTION("aquire valid examples") {
		REQUIRE(application.aquire(1, "AB1234BA") == true);
		REQUIRE(application.aquire(2, "B1234BA") == true);
		REQUIRE(application.get_person(1).owns("AB1234BA") == true);
		REQUIRE(application.get_person(2).owns("B1234BA") == true);
		CHECK(application.get_vehicle("AB1234BA").get_owner() == 1);
		CHECK(application.get_vehicle("B1234BA").get_owner() == 2);
	}
	SECTION("aquire a car with owner") {
		application.aquire(1, "AB1234BA");
		REQUIRE(application.aquire(2, "AB1234BA") == false);
	}
	SECTION("aquire a car that doesnt exist in the database")
	{
		CHECK(application.aquire(1, "AB1234SA") == false);

	}
	SECTION("aquire multiple cars")
	{
		application.aquire(1, "AB1234BA");
		application.aquire(1, "B1234BA");
		CHECK(application.get_person(1).owns("AB1234BA"));
		CHECK(application.get_person(1).owns("B1234BA"));
	}



}
TEST_CASE("RELEASE <owner-id> <vehicle-id>" "[application]")
{
	Application application;
	application.add_Person("Alek", 1);
	application.add_Person("Aleksei", 2);
	application.add_Vehicle("AB1234BA", "Honda Civic Type R");
	application.add_Vehicle("B1234BA", "Hyndai");
	application.aquire(1, "AB1234BA");
	application.aquire(2, "B1234BA");
	SECTION("release car with owner")
	{
		CHECK(application.release(2, "B1234BA"));
		CHECK(application.get_person(2).owns("B1234BA")==false);
		CHECK(application.get_vehicle("BA1234BA").get_owner() == 0);
	}
	SECTION("release car from the worng owner")
	{
		CHECK(application.release(1, "B1234BA") == false);
	}
}
TEST_CASE("REMOVE <what> testing", "[application]")
{
	Application application;
	application.add_Person("Alek", 1);
	application.add_Person("Aleksei", 2);
	application.add_Vehicle("AB1234BA", "Honda Civic Type R");
	application.add_Vehicle("B1234BA", "Hyndai");

	SECTION("Remove valid id")
	{
		CHECK(application.remove("2"));
		CHECK(application.remove("1"));
		CHECK(application.has_Person(1) == false);
		CHECK(application.has_Person(2) == false);
	}
	SECTION("Remove invalid id")
	{
		CHECK(application.remove("3") == false);
	}
	//Removing id which owns cars will ask if the user is sure
	SECTION("Remove vehicle with valid registration")
	{
		CHECK(application.remove("AB1234BA"));
	}
	SECTION("Remove vehicle with invalid registration or not in database")
	{
		CHECK(application.remove("B1234BAA")==false);
		CHECK(application.remove("SA1234BA") == false);
	}
	

}









// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
