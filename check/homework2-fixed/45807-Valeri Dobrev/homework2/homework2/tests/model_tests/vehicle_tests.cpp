#define CATCH_CONFIG_MAIN

#include "../../models/vehicle/vehicle.hpp"
#include "../../models/person/person.hpp"
#include "../catch2.hpp"


TEST_CASE("Vehicle creation"){
    SECTION("Creating vehicle with nullptr registration"){
        //Arrange
        Vehicle* v;

        //Assert
        REQUIRE_THROWS_WITH(v=new Vehicle(nullptr, "Descripiton"), "Registration cannot be null!");
    }
    SECTION("Creating vehicle with invalid registration number"){
        //Arrange
        Vehicle* v;

        //Assert
        REQUIRE_THROWS_WITH(v=new Vehicle("CA12345AA", "Descripiton"), "Invalid registration number!");
    }
    SECTION("Creating vehicle with valid registration number"){
        //Arrange
        Vehicle* v;
        
        //Act
        v = new Vehicle("CA1234AA", "Descripiton");

        //Assert
        REQUIRE(v->getId() == "CA1234AA");
        REQUIRE(v->getDescription() == "Descripiton");

        //Clean
        delete v;
    }
}

TEST_CASE("Copy constructor"){
    //Arrange
    Vehicle v ("CA1234AA", "Descripiton");
    Person p(1, "John");
    v.setOwner(&p);

    //Act
    Vehicle copy=v;

    //Assert
    REQUIRE(copy.getId() == "CA1234AA");
    REQUIRE(copy.getDescription() == "Descripiton");
    REQUIRE(copy.getOwner() == &p);
}

TEST_CASE("Assign operator"){
    SECTION("Assigning to a vehicle itself"){
        //Arrange
        Vehicle v ("CA1234AA", "Descripiton");
        Person p(1, "John");
        v.setOwner(&p);

        //Act
        v = v; 

        //Assert
        REQUIRE(v.getId() == "CA1234AA");
        REQUIRE(v.getDescription() == "Descripiton");
        REQUIRE(v.getOwner() == &p);
    }


    SECTION("Assigning to a vehicle another vehicle"){
        //Arrange
        Vehicle v ("CA1234AA", "Descripiton");
        Person p(1, "John");
        v.setOwner(&p);

        //Act
        Vehicle copy("CA5678AA", "Descripiton1234");
        copy = v; 

        //Assert
        REQUIRE(copy.getId() == "CA1234AA");
        REQUIRE(copy.getDescription() == "Descripiton");
        REQUIRE(copy.getOwner() == &p);
    }
}

TEST_CASE("Operator equal"){
    SECTION("Check if the vehicle's registration is equal to nullptr registration"){
        //Arrange
        Vehicle v ("CA1234AA", "Descripition");

        //Assert
        REQUIRE_THROWS_WITH(v==nullptr, "Registration should not be null!");
    }
    SECTION("Different reigstrations"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");

        //Assert
        REQUIRE_FALSE(vehicle=="CA1234AB");
    }
    SECTION("Equals registrations"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");

        //Assert
        REQUIRE(vehicle == "CA1234AA");
    }
}

TEST_CASE("Check if there is need of user confirmation to be deleted"){
    SECTION("No need"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");

        //Assert
        REQUIRE_FALSE(vehicle.needConfirmToDelete());        
    }
    SECTION("Needed"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");
        Person p(1, "John");
        vehicle.setOwner(&p);

        //Assert
        REQUIRE(vehicle.needConfirmToDelete());
    }
}

TEST_CASE("Assigning new owner to vehicle"){
    SECTION("The vehicle has owner already"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");
        Person p(1, "John");
        Person p2(2, "Joshua");
        vehicle.setOwner(&p);

        //Act
        vehicle.setOwner(&p2);

        //Assert
        REQUIRE(vehicle.getOwner() == &p2);
        REQUIRE(p.getNumberOfVehicles()==0);
    }
    SECTION("Reacquiring vehicle"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");
        Person p(1, "John");
        vehicle.setOwner(&p);

        //Assert
        REQUIRE_THROWS_WITH( vehicle.setOwner(&p), "Vehicle already acquired by this person!");
    }
    SECTION("The vehicle hasn't owner"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");
        Person p(1, "John");

        //Act
        vehicle.setOwner(&p);

        //Assert
        REQUIRE(vehicle.getOwner() == &p);
        REQUIRE(p.getNumberOfVehicles() == 1);
    }
    SECTION("Removing the old owner"){
        //Arrange
        Vehicle vehicle("CA1234AA", "Descripiton");
        Person p(1, "John");
        vehicle.setOwner(&p);

        //Act
        vehicle.setOwner(nullptr);

        //Assert
        REQUIRE(vehicle.getOwner() == nullptr);
        REQUIRE(p.getNumberOfVehicles() == 0);
    }
}
