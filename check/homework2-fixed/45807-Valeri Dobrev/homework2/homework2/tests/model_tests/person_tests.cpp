#define CATCH_CONFIG_MAIN
#include "../catch2.hpp"
#include "../../models/person/person.hpp"
#include "../../models/vehicle/vehicle.hpp"

TEST_CASE("Creating person"){
    //Arrange
    Person* person;

    //Act
    person = new Person(1, "John");

    //Assert
    REQUIRE(person->getId() == 1);
    REQUIRE(person->getName() == "John");

    //Clean
    delete person;
}

TEST_CASE("Copy constructor"){
    SECTION("Without vehicles"){
        //Arrange
        Person p(1, "John");

        //Act
        Person copy(p);

        //Assert
        REQUIRE(copy.getId() == 1);
        REQUIRE(copy.getName() == "John"); 
        REQUIRE(copy.getNumberOfVehicles() == 0);      
    }
    SECTION("With vehicles"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Descripiton");
        p.addVehicle(&v);

        //Act
        Person copy=p;

        //Assert
        REQUIRE(copy.getId() == 1);
        REQUIRE(copy.getName() == "John"); 
        REQUIRE(copy.getNumberOfVehicles() == 1); 
    }
}

TEST_CASE("Assign operator"){
    SECTION("Assign to a person, itself"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Description");
        p.addVehicle(&v);

        //Act
        p=p;

        //Assert
        REQUIRE(p.getId() == 1);
        REQUIRE(p.getName() == "John");
        REQUIRE(p.getNumberOfVehicles() == 1);
    }
    SECTION("Person without vehicles"){
        //Arrange
        Person p(1, "John");
        Person p2(2, "Tom");
        Vehicle v("CA1234AA", "Descripiton");
        p2.addVehicle(&v);

        //Act
        p2 = p;

        //Assert
        REQUIRE(p2.getName() == "John");
        REQUIRE(p2.getId() == 1);
        REQUIRE(p2.getNumberOfVehicles() == 0);
    }
    SECTION("Assign to a person with vehicles"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Descripiton");
        p.addVehicle(&v);

        Person p2(2, "Tom");

        //Act
        p2 = p;

        REQUIRE(p2.getName() == "John");
        REQUIRE(p2.getId() == 1);
        REQUIRE(p2.getNumberOfVehicles() == 1);
    }
}

TEST_CASE("Check if it is needed user confirmation to delete the object"){
    SECTION("Not needed"){
        //Arrange
        Person p(1, "John");

        //Assert
        REQUIRE_FALSE(p.needConfirmToDelete());
    }
    SECTION("Needed"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Descripiton");
        p.addVehicle(&v);

        //Assert
        REQUIRE(p.needConfirmToDelete());
    }
}

TEST_CASE("Acquire a Vehicle"){
    SECTION("Acquire nullptr Vehicle"){
        //Arrange
        Person p(1, "John");

        //Assert
        REQUIRE_THROWS_WITH(p.addVehicle(nullptr), "Vehicle cannot be null!");
    }
    SECTION("Acquire vehicle that is already acquired"){
        //Arrange
        Person p(1, "John");
        Vehicle vehicle("CA1234AA","Descripiton");

        REQUIRE(vehicle.getOwner()==nullptr);

        //Act
        p.addVehicle(&vehicle);

        //Assert
        REQUIRE_THROWS_WITH(p.addVehicle(&vehicle), "Vehicle already acquired by this person!");
    }
    SECTION("Acquire vehicle that is aquired by someone else"){
        //Arrange
        Person p(1, "John");
        Person p2(2, "Joshua");
        Vehicle v("CA1234AA", "Description");

        //Act
        p.addVehicle(&v);
        p2.addVehicle(&v);

        //Assert
        REQUIRE(p.getNumberOfVehicles()==0);
        REQUIRE(p2.getNumberOfVehicles() == 1);
    }
    SECTION("Acquire free vehicle"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Description");

        //Act
        p.addVehicle(&v);

        //Assert
        REQUIRE(p.getNumberOfVehicles()==1);
    }

}

TEST_CASE("Releasing a vehicle"){
    SECTION("Releasing a nullptr vehicle"){
        //Arrange
        Person p(1, "John");
        
        //Assert
        REQUIRE_THROWS_WITH(p.removeVehicle(nullptr), "Vehicle cannot be null!");
    }

    SECTION("Releasing vehicle that the person does not possess"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Description");

        //Assert
        REQUIRE_THROWS_WITH(p.removeVehicle(&v), "Vehicle not found!");
    }

    SECTION("Releasing vehicle that the person possess"){
        //Arrange
        Person p(1, "John");
        Vehicle v("CA1234AA", "Description");

        //Act
        p.addVehicle(&v);
        p.removeVehicle(&v);

        //Assert
        REQUIRE(p.getNumberOfVehicles() == 0);
    }
}
