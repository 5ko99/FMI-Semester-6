#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.h"
#include "Vehicle.h"



TEST_CASE("Vehicle") {
    Registration Reg1("A1234BV");
    std::string description = "Some description";
    Vehicle SomeVehicle(Reg1, description);
    REQUIRE(strcmp(SomeVehicle.GetReg().registr(), "A1234BV") == 0);
    REQUIRE(strcmp(SomeVehicle.Getdescr().c_str(), description.c_str()) == 0);
    std::string name = "Some name";
    unsigned int id = 0;
    Person SomePerson(name, id);
    SomeVehicle.addPerson(SomePerson);
    REQUIRE(SomeVehicle.GetPerson() == &SomePerson);
    SomeVehicle.RemovePerson();
    REQUIRE(SomeVehicle.GetPerson() == nullptr);
}
