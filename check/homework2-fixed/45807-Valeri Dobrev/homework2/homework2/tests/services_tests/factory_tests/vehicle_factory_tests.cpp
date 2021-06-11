#define CATCH_CONFIG_MAIN
#include "../../catch2.hpp"
#include "../../../services/factories/factory.hpp"


TEST_CASE("Single instance of the factory"){
    //Arrange
    VehicleFactory* factory = VehicleFactory::getInstance();

    //Act
    VehicleFactory* factory2 = VehicleFactory::getInstance();

    //Assert
    REQUIRE(factory==factory2);

    //Clean
    factory->destroy();
}

TEST_CASE("Adding vehicle"){
    SECTION("Creating a vehicle with null ID"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->create(nullptr, "Description"), "ID should not be null!");

        //Clean
        factory->destroy();
    }
    SECTION("Creating a vehicle with duplicated ID"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();
        factory->create("CA1234AA","Description");

        //Assert
        REQUIRE_THROWS_WITH(factory->create("CA1234AA", "Description"), "Vehicle with id: CA1234AA already exists!");

        //Clean
        factory->destroy();
    }
    SECTION("Creating unique valid Vehicle"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();

        //Act
        Vehicle* v = factory->create("CA1234AA", "Description");

        //Assert
        REQUIRE(factory->getById("CA1234AA") == v);
        REQUIRE(factory->getNumberOfElements() == 1);

        //Clean
        factory->destroy();
    }
}

TEST_CASE("Remove vehicle"){
    SECTION("Removing vehicle, when id is nullptr"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->remove(nullptr), "ID should not be null!");

        //Clean 
        factory->destroy();
    }
    SECTION("Removing vehicle, when invalid ID is provided"){
        //Arrange
        VehicleFactory* factory= VehicleFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->remove("CA1234AA"), "Vehicle not found!");
    
        //Clean
        factory->destroy();
    }

    SECTION("Removing vehicle who has relation, without user confirmation"){
        //Arrange
        VehicleFactory* vehicleFactory= VehicleFactory::getInstance();
        PersonFactory* personFactory= PersonFactory::getInstance();

        Person* person= personFactory->create(1, "John");
        Vehicle* vehicle= vehicleFactory->create("CA1234AA","Descripiton");

        person->addVehicle(vehicle);

        //Assert
        REQUIRE_THROWS_WITH(vehicleFactory->remove("CA1234AA", false),"Are you sure you want to delete Vehicle with id: CA1234AA");
        REQUIRE(person->getNumberOfVehicles() == 1);

        //Clean
        vehicleFactory->destroy();
        personFactory->destroy();
    }
    SECTION("Removing vehicle who has relation, with user confirmation"){
        //Arrange
        VehicleFactory* vehicleFactory= VehicleFactory::getInstance();
        PersonFactory* personFactory= PersonFactory::getInstance();

        Person* person= personFactory->create(1, "John");
        Vehicle* vehicle= vehicleFactory->create("CA1234AA","Descripiton");

        person->addVehicle(vehicle);

        //Act
        vehicleFactory->remove("CA1234AA", true);

        //Assert
        REQUIRE(person->getNumberOfVehicles()==0);

        //Clean
        personFactory->destroy();
        vehicleFactory->destroy();
    }

    SECTION("Removing vehicle who does not have relation, without user confirmation"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();
        factory->create("CA1234AA", "Description");

        //Act
        factory->remove("CA1234AA", false);

        //Assert
        REQUIRE(factory->getNumberOfElements() == 0);

        //Clean
        factory->destroy();
    }

    SECTION("Removing vehicle who does not have relation, with user confirmation"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();
        factory->create("CA1234AA", "Description");

        //Act
        factory->remove("CA1234AA", true);

        //Assert
        REQUIRE(factory->getNumberOfElements() == 0);

        //Clean
        factory->destroy();
    }
}

TEST_CASE("Retrieving vehicle by ID"){
    SECTION("Retrieving by nullptr ID"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->getById(nullptr), "ID should not be null!");

        //Clean
        factory->destroy();
    }
    SECTION("Retrieving not existing vehicle"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->getById("CA1234AA"), "Vehicle does not exist!");

        //Clean
        factory->destroy();
    }
    SECTION("Retrieving existing vehicle"){
        //Arrange
        VehicleFactory* factory = VehicleFactory::getInstance();
        Vehicle* v = factory->create("CA1234AA", "Description");

        //Act
        const Vehicle* v1 = factory->getById("CA1234AA");

        //Assert
        REQUIRE(v==v1);
        REQUIRE(v1->getId() == "CA1234AA");

        //Clean
        factory->destroy();
    }
}

