#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.h"
#include "Person.h"


TEST_CASE("Person") {
    Registration Reg1("A1234BV");
    std::string description = "Some description";
    Vehicle SomeVehicle(Reg1, description);
    std::string name = "Some name";
    unsigned int id = 0;
    Person SomePerson(name, id);
    REQUIRE(SomePerson.GetId() == 0);
    REQUIRE(strcmp(SomePerson.GetName().c_str(), name.c_str()) == 0);
    SomePerson.AddVehicle(SomeVehicle);
    REQUIRE(SomePerson.GetSize() == 1);
    REQUIRE(strcmp(SomePerson.GetVehicle(0).Getdescr().c_str(), SomeVehicle.Getdescr().c_str()) == 0);
    REQUIRE(!SomePerson.isEmpty());
    SomePerson.RELEASE(Reg1.registr());
    REQUIRE(SomePerson.isEmpty());

}
