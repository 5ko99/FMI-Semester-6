# ifndef PERSONTESTS
# define PERSONTESTS
# include "Person.h"
# include "catch.hpp"
# include "Registration.h"
TEST_CASE("Initialization", "[Person]") {
	
	std::string Name("Gosho"),Name2("Ivan");
	unsigned int id = 123;
	unsigned int id2 = 125;
	Person p(Name, id);
	REQUIRE(p.getName() == Name);
	REQUIRE(p.getId() == id);
	p.setName(Name2);
	p.setId(id2);
	REQUIRE(p.getName() == Name2);
	REQUIRE(p.getId() == id2);
}
TEST_CASE("Adding Vehicles", "[Person]") {
	std::string Name("Gosho"), Name2("Ivan");
	unsigned int id = 123;
	Person p(Name, id);
	REQUIRE_THROWS(p.getVehicleAt(0));
	std::string reg("CA5577NA");
	Registration r(reg);
	Vehicle v(r, "Blue sedan");
	p.addVehicle(&v);
	REQUIRE(p.getVehicleAt(0)->getRegistration() ==reg);
	std::string r2("CB4445PA");
	Registration reg2(r2);
	Vehicle v2(reg2, "Black Jeep");
	p.addVehicle(&v2);
	REQUIRE(p.vehicleCount()==2);
	REQUIRE(p.getVehicleAt(1)->getRegistration() == r2);
}
TEST_CASE("Erasing Vehicles", "[Person]") {
	std::string r("CA2345BA"), r1("B5589LP"), r2("CA2345BA"), r3("B7589LP"),
		r4("C2345BA"), r5("B5589LZ"), r6("CA2345CA"), r7("B5089LP");
	std::string descr("car");
	Vehicle v(r, descr), v1(r1, descr), v2(r2, descr), v3(r3, descr), v4(r4, descr), v5(r5, descr), v6(r6, descr),
		v7(r7, descr) ;
	Person p("Ivan", 45);
	p.addVehicle(&v);
	p.addVehicle(&v1);
	REQUIRE_THROWS(p.addVehicle(&v2));
	p.addVehicle(&v3);
	p.addVehicle(&v4);
	p.addVehicle(&v5);
	p.addVehicle(&v6);
	p.addVehicle(&v7);
	REQUIRE(p.getVehicleAt(6)->getRegistration() == "B5089LP");
	p.eraseAt("CA2345BA");
	REQUIRE_THROWS(p.getVehicleAt(6));
	REQUIRE(p.getVehicleAt(0)->getRegistration() == "B5089LP");
	REQUIRE(p.getVehicleAt(5)->getRegistration() == "CA2345CA");
	p.eraseAt("CA2345CA");
	REQUIRE_THROWS(p.getVehicleAt(5));
	REQUIRE(p.getVehicleAt(4)->getRegistration() == "B5589LZ");
}
# endif
