#define CATCH_CONFIG_MAIN
#include"../../catch2.hpp"
#include "../../../services/factories/factory.hpp"

TEST_CASE("Single instance of the factory"){
    //Arrange
    PersonFactory* factory = PersonFactory::getInstance();
    //Act
    PersonFactory* factory2 = PersonFactory::getInstance();

    //Assert
    REQUIRE(factory2==factory);

    //Clean
    factory->destroy();
}


TEST_CASE("Adding person"){
    SECTION("Creating person with null ID"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->create(NULL, std::string("Description")),"ID should not be null!");

        //Clean
        factory->destroy();
    } 
    SECTION("Creating person with duplicated ID"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        
        //Act
        factory->create(1, std::string("John"));
        
        //Assert
        REQUIRE_THROWS_WITH(factory->create(1, std::string("Josh")), "Person with id: 1 already exists!");

        //Clean
        factory->destroy();
    }  
    SECTION("Creating unique valid person"){
         //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        
        //Act
        Person* p = factory->create(1, std::string("John"));

        //Assert
        REQUIRE(factory->getById(1) == p);
        REQUIRE(factory->getNumberOfElements() == 1);

         //Clean
        factory->destroy();
    }
}

TEST_CASE("Remove person"){
    
    SECTION("Removing person, when null ID is provided"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->remove(NULL), "ID should not be null!");

        //Clean
        factory->destroy();
    }

    SECTION("Removing person, when invalid ID is provided"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->remove(2), "Person not found!");

        //Clean
        factory->destroy();
    }
    
    SECTION("Removing person who has relation, without user confirmation"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();
        Person* p = factory->create(1,"John");
        Vehicle* v = vehicleFactory->create("CA1234AA", "Description");

        p->addVehicle(v);

        //Assert
        REQUIRE_THROWS_WITH(factory->remove(1,false), "Are you sure you want to delete Person with id: 1");
        REQUIRE(v->getOwner() == p);
        REQUIRE(p->getNumberOfVehicles()==1);
         
        //Clean
        factory->destroy();
        vehicleFactory->destroy();

    }
    SECTION("Removing person who has relation, with user confirmation"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();
        Person* p = factory->create(1,"John");
        Vehicle* v = vehicleFactory->create("CA1234AA", "Description");

        p->addVehicle(v);

        //Act
        factory->remove(1, true);

        //Assert
        REQUIRE(v->getOwner() == nullptr);

        //Clean
        factory->destroy();
        vehicleFactory->destroy();

    }
    SECTION("Removing person with who don't have relation without user confirmation"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        factory->create(1, std::string("John"));

        //Act
        factory->remove(1, false);

        //Assert
        REQUIRE(factory->getNumberOfElements() == 0);

        //Clean
        factory->destroy();
    }
    SECTION("Removing person who don't have relation, with user confirmation"){
         //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        factory->create(1, std::string("John"));

        //Act
        factory->remove(1, true);

        //Assert
        REQUIRE(factory->getNumberOfElements() == 0);

        //Clean
        factory->destroy();
    }
}

TEST_CASE("Retrieving person by ID"){
    SECTION("Retrieving by NULL ID"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->getById(NULL), "ID should not be null!");

        //Clean
        factory->destroy();
    }
    SECTION("Retrieving not existing person"){
         //Arrange
        PersonFactory* factory = PersonFactory::getInstance();

        //Assert
        REQUIRE_THROWS_WITH(factory->getById(1), "Person does not exist!");

        //Clean
        factory->destroy();
    }
    SECTION("Retrieving existing person"){
        //Arrange
        PersonFactory* factory = PersonFactory::getInstance();
        Person* p = factory->create(1, std::string("John"));

        //Act
        const Person* p1 = factory->getById(1);

        //Assert
        REQUIRE(p==p1);
        REQUIRE(p1->getId() == 1);

        //Clean
        factory->destroy();
    }
}
