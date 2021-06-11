# pragma once
# include "catch.hpp"
# include "Commands.h"

TEST_CASE("Adding Persons", "[Commands]") {
	Commands c;
	std::string str ("Ivan");
	std::string str1 ("Gosho"); 
	std::string str2 ( "Pesho");
	
	

	c.newPerson(str, 12);
	REQUIRE(c.getPersonAt(0).getName() == "Ivan");
	REQUIRE(c.getPersonAt(0).getId() == 12);
	REQUIRE_THROWS(c.newPerson(str, 12));
	c.newPerson(str1, 13);
	c.newPerson(str2, 18);
	REQUIRE(c.getPersonAt(1).getId() == 13);
	REQUIRE(c.getPersonAt(1).getName() == str1);
	REQUIRE(c.getPersonAt(2).getId() == 18);
	REQUIRE(c.getPersonAt(2).getName() == str2);
	REQUIRE_THROWS(c.getPersonAt(3).getId() == 13);
	REQUIRE_THROWS(c.getPersonAt(3).getName() == str2);
}
TEST_CASE("Add Vehicle", "[Commands]") {
	Commands c;
	std::string
		test1("CA6456NB"), test2("Black sedan"),
		test3("CB5588MN"), test4("Blue rich guy car");
	Registration r(test1), r1(test3);
	c.newVehicle(r, test2);
	c.newVehicle(r1, test4);
	REQUIRE(c.getVehicleAt(0).getRegistration() == test1);
	REQUIRE(c.getVehicleAt(0).getDescription() == test2);
	REQUIRE(c.getVehicleAt(1).getRegistration() == test3);
	REQUIRE(c.getVehicleAt(1).getDescription() == test4);
	REQUIRE_THROWS(c.newVehicle(r, test4));
}
TEST_CASE("Aquire", "[Commands]") {
	Commands c;
	std::string str("Ivan");
	std::string str1("Gosho");
	std::string str2("Pesho");
	c.newPerson(str, 12);
	c.newPerson(str1, 13);
	c.newPerson(str2, 18);
	std::string
		test1("CA6456NB"), test2("Black sedan"),
		test3("CB5588MN"), test4("Blue rich guy car");
	Registration r(test1), r1(test3),r3("CB4545LO");
	c.newVehicle(r, test2);
	c.newVehicle(r1, test4);
	c.Aquire(12, r);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getRegistration() == test1);
	REQUIRE(c.getVehicleAt(0).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(0).getOwner()->getId() == 12);
	REQUIRE_THROWS(c.Aquire(12, r3));
	REQUIRE_THROWS(c.Aquire(15, r1));
	c.Aquire(13, r);
	REQUIRE(c.getPersonAt(1).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(c.getPersonAt(1).getVehicleAt(0)->getRegistration() == test1);
	REQUIRE(c.getVehicleAt(0).getOwner()->getName() == "Gosho");
	REQUIRE(c.getVehicleAt(0).getOwner()->getId() == 13);
	REQUIRE_THROWS(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE_THROWS(c.getPersonAt(0).getVehicleAt(0)->getRegistration() == test1);

}
TEST_CASE("Release", "[Commands]") {
	Commands c;
	std::string str("Ivan");
	std::string str1("Gosho");
	std::string str2("Pesho");
	c.newPerson(str, 12);
	c.newPerson(str1, 13);
	c.newPerson(str2, 18);
	std::string
		test1("CA6456NB"), test2("Black sedan"),
		test3("CB5588MN"), test4("Blue rich guy car");
	Registration r(test1), r1(test3), r2("CB4545LO");
	c.newVehicle(r, test2);
	c.newVehicle(r1, test4);
	c.newVehicle(r2, test2);
	c.Aquire(12, r);
	c.Aquire(12, r1);
	c.Aquire(12, r2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getRegistration() == test1);
	REQUIRE(c.getVehicleAt(0).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(0).getOwner()->getId() == 12);
	REQUIRE(c.getPersonAt(0).getVehicleAt(1)->getDescription() == test4);
	REQUIRE(c.getPersonAt(0).getVehicleAt(1)->getRegistration() == test3);
	REQUIRE(c.getVehicleAt(1).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(1).getOwner()->getId() == 12);
	REQUIRE(c.getPersonAt(0).getVehicleAt(2)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(2)->getRegistration() =="CB4545LO" );
	REQUIRE(c.getVehicleAt(2).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(2).getOwner()->getId() == 12);
	REQUIRE(c.getVehicleAt(0).isItOwned());
	REQUIRE(c.getVehicleAt(1).isItOwned());
	REQUIRE(c.getVehicleAt(2).isItOwned());
	c.Release(12, r);
	/// Because it swaps the last and the one that is going to be deleted
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getRegistration() == "CB4545LO");
	REQUIRE_THROWS(c.getPersonAt(0).getVehicleAt(2)->getDescription() == test2);
	REQUIRE(!c.getVehicleAt(0).isItOwned());
	c.Release(12, r1);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getRegistration() == "CB4545LO");
	REQUIRE_THROWS(c.getPersonAt(0).getVehicleAt(1)->getDescription() == test2);
	REQUIRE(!c.getVehicleAt(1).isItOwned());
	c.Release(12, r2);
	REQUIRE_THROWS(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(!c.getVehicleAt(2).isItOwned());

}
TEST_CASE("Remove", "[Commands]") {
	Commands c;
	std::string str("Ivan");
	std::string str1("Gosho");
	std::string str2("Pesho");
	c.newPerson(str, 12);
	c.newPerson(str1, 13);
	c.newPerson(str2, 18);
	std::string
		test1("CA6456NB"), test2("Black sedan"),
		test3("CB5588MN"), test4("Blue rich guy car");
	Registration r(test1), r1(test3), r2("CB4545LO");
	c.newVehicle(r, test2);
	c.newVehicle(r1, test4);
	c.newVehicle(r2, test2);
	c.Aquire(12, r);
	c.Aquire(12, r1);
	c.Aquire(12, r2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(0)->getRegistration() == test1);
	REQUIRE(c.getVehicleAt(0).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(0).getOwner()->getId() == 12);
	REQUIRE(c.getPersonAt(0).getVehicleAt(1)->getDescription() == test4);
	REQUIRE(c.getPersonAt(0).getVehicleAt(1)->getRegistration() == test3);
	REQUIRE(c.getVehicleAt(1).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(1).getOwner()->getId() == 12);
	REQUIRE(c.getPersonAt(0).getVehicleAt(2)->getDescription() == test2);
	REQUIRE(c.getPersonAt(0).getVehicleAt(2)->getRegistration() == "CB4545LO");
	REQUIRE(c.getVehicleAt(2).getOwner()->getName() == "Ivan");
	REQUIRE(c.getVehicleAt(2).getOwner()->getId() == 12);
	REQUIRE(c.getVehicleAt(0).isItOwned());
	REQUIRE(c.getVehicleAt(1).isItOwned());
	REQUIRE(c.getVehicleAt(2).isItOwned());
	REQUIRE(c.getPersonAt(0).getId() == 12);
	c.remove(12);
	REQUIRE_THROWS(c.getPersonAt(0).getVehicleAt(0)->getDescription() == test2);
	REQUIRE_THROWS(c.getPersonAt(2).getId() == 12);
	REQUIRE(!c.getVehicleAt(0).isItOwned());
	REQUIRE(!c.getVehicleAt(1).isItOwned());
	REQUIRE(!c.getVehicleAt(2).isItOwned());
	REQUIRE_THROWS(c.remove(12));
	c.Aquire(13, r);
	c.Aquire(13, r1);
	c.Aquire(13, r2);
	REQUIRE(c.getVehicleAt(0).getRegistration() == r.getRegistration());
	REQUIRE(c.getVehicleAt(2).getRegistration() == r2.getRegistration());
	REQUIRE(c.getPersonAt(1).getVehicleAt(2)->getRegistration() == "CB4545LO");
	c.remove(r);
	REQUIRE_THROWS(c.getPersonAt(1).getVehicleAt(2)->getRegistration() == "CB4545LO");
	REQUIRE_THROWS(c.remove(r));
	REQUIRE_THROWS(c.getVehicleAt(2).getRegistration());

}
