#define CATCH_CONFIG_MAIN

#include"../../catch2.hpp"
#include "../../../services/model_relations/person_vehicle_relation.hpp"

//TODO ask Kris if I need to write tests for all cases and throws of the inner methods

TEST_CASE("Acquire vehicle"){
    //Arrange
    PersonFactory* personFactory = PersonFactory::getInstance();
    VehicleFactory* vehicleFactory = VehicleFactory::getInstance();
    Person* p = personFactory->create(1,"John");
    Vehicle* v = vehicleFactory->create("CA1234AA", "Description");

    //Act
    PersonVehicleRelation::acquire(1, "CA1234AA");

    //Assert
    REQUIRE(p->getNumberOfVehicles()==1);
    REQUIRE(v->getOwner() == p);

    //Clean
    personFactory->destroy();
    vehicleFactory->destroy();
}

TEST_CASE("Release vehicle"){
    //Arrange
    PersonFactory* personFactory = PersonFactory::getInstance();
    VehicleFactory* vehicleFactory = VehicleFactory::getInstance();
    Person* p = personFactory->create(1,"John");
    Vehicle* v = vehicleFactory->create("CA1234AA", "Description");

    //Act
    PersonVehicleRelation::acquire(1, "CA1234AA");

    PersonVehicleRelation::release(1, "CA1234AA");
    //Assert
    REQUIRE(p->getNumberOfVehicles()==0);
    REQUIRE(v->getOwner() == nullptr);

    //Clean
    personFactory->destroy();
    vehicleFactory->destroy();
}
