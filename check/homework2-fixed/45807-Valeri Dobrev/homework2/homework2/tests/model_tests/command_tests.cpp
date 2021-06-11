#define CATCH_CONFIG_MAIN
#include "../catch2.hpp"
#include "../../models/commands/acquire/acquire_command.hpp"
#include "../../models/commands/release/release_command.hpp"

#include "../../models/commands/person/person_command.hpp"
#include "../../models/commands/vehicle/vehicle_command.hpp"
#include "../../models/commands/remove/remove_command.hpp"


TEST_CASE("Create person"){
    SECTION("Invalid number of arguments"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("1");

        PersonCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid number of arguments passed to PERSON! - expected 2, 1 provided!");
    }
    SECTION("Invalid first argument - person's ID - not a number passed"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("aa");
        args.push_back("John Snow");


        PersonCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid argument passed to PERSON for person's ID!");
    }
    SECTION("Regular call"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("John");
        args.push_back("1");
        PersonFactory *factory = PersonFactory::getInstance();
        PersonCommand command(args);
        
        //Act
        command.execute();

        //Assert
        REQUIRE(factory->getNumberOfElements() == 1);
        
        //Clean
        factory->destroy();
    }
}
TEST_CASE("Create vehicle"){
    SECTION("Invalid number of arguments"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("CA1234AA");

        VehicleCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid number of arguments passed to VEHICLE! - expected 2, 1 provided!");
    }
    SECTION("Regular call"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("CA1234AA");
        args.push_back("John Snow's car");
        VehicleFactory *factory = VehicleFactory::getInstance();
        VehicleCommand command(args);
        
        //Act
        command.execute();

        //Assert
        REQUIRE(factory->getNumberOfElements() == 1);
        
        //Clean
        factory->destroy();
    }
}


TEST_CASE("Acquire command"){

    SECTION("Invalid number of arguments"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("1");

        AcquireCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid number of arguments passed to ACQUIRE! - expected 2, 1 provided!");
    }

    SECTION("Invalid first argument - person's ID - not a number passed"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("aa");
        args.push_back("CA1234AA");


        AcquireCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid argument passed to ACQUIRE for person's ID!");
    }
    SECTION("Regular acquire"){
        //Arrange
        PersonFactory* personFactory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

        personFactory->create(1,"John");
        Vehicle* v = vehicleFactory->create("CA1234AA", "Desc");

        std::vector<std::string> args;
        args.push_back("1");
        args.push_back("CA1234AA");

        AcquireCommand command(args);

        //Act
        command.execute();

        //Assert
        REQUIRE(v->getOwner()->getId() == 1);

        //Clean
         vehicleFactory->destroy();
         personFactory->destroy();
    }
}

TEST_CASE("Remove command"){
    SECTION("Invalid number of arguments"){
        //Arrange
        std::vector<std::string> args;

        RemoveCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid number of arguments passed to REMOVE! - expected 2, 0 provided!");
    }
    SECTION("Withouth user premision to delete"){
        //Arrange
        
        PersonFactory* factory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

        Vehicle* vehicle = vehicleFactory->create("CA1234AA", "Desc");
        Person *p = factory->create(1, "John");

        p->addVehicle(vehicle);

        std::vector<std::string> args;
        args.push_back("1");
        args.push_back("false");

        RemoveCommand command(args);

        //Assert
        REQUIRE_THROWS_WITH(command.execute(), "Are you sure you want to delete Person with id: 1");

        factory->destroy();
        vehicleFactory->destroy();
    }
    SECTION("Withouth user premision to delete"){
        //Arrange
        
        PersonFactory* factory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

        Vehicle* vehicle = vehicleFactory->create("CA1234AA", "Desc");
        Person *p = factory->create(1, "John");

        p->addVehicle(vehicle);

        std::vector<std::string> args;
        args.push_back("CA1234AA");
        args.push_back("false");

        RemoveCommand command(args);

        //Assert
        REQUIRE_THROWS_WITH(command.execute(), "Are you sure you want to delete Vehicle with id: CA1234AA");

        factory->destroy();
        vehicleFactory->destroy();
    }
    SECTION("Regular person remove"){
        //Arrange
        
        PersonFactory* factory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

        Vehicle* vehicle = vehicleFactory->create("CA1234AA", "Desc");
        Person *p = factory->create(1, "John");

        p->addVehicle(vehicle);

        std::vector<std::string> args;
        args.push_back("1");
        args.push_back("true");

        RemoveCommand command(args);

        //Act
        command.execute();

        //Assert
        REQUIRE(factory->getNumberOfElements()==0);

        factory->destroy();
        vehicleFactory->destroy();
    }
    SECTION("Regular vehicle remove"){
        //Arrange
        
        PersonFactory* factory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

        Vehicle* vehicle = vehicleFactory->create("CA1234AA", "Desc");
        Person *p = factory->create(1, "John");

        p->addVehicle(vehicle);

        std::vector<std::string> args;
        args.push_back("CA1234AA");
        args.push_back("true");

        RemoveCommand command(args);

        //Act
        command.execute();

        //Assert
        REQUIRE(vehicleFactory->getNumberOfElements()==0);

        factory->destroy();
        vehicleFactory->destroy();
    }
}


TEST_CASE("Release command"){
    SECTION("Invalid number of arguments"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("1");

        ReleaseCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid number of arguments passed to RELEASE! - expected 2, 1 provided!");
    }

    SECTION("Invalid first argument - person's ID - not a number passed"){
        //Arrange
        std::vector<std::string> args;
        args.push_back("aa");
        args.push_back("CA1234AA");


        ReleaseCommand command(args);
        //Assert
        REQUIRE_THROWS_WITH(command.execute(),"Invalid argument passed to RELEASE for person's ID!");
    }
    SECTION("Regular release"){
        //Arrange
        PersonFactory* personFactory = PersonFactory::getInstance();
        VehicleFactory* vehicleFactory = VehicleFactory::getInstance();

        Person* p = personFactory->create(1,"John");
        Vehicle* v = vehicleFactory->create("CA1234AA", "Desc");
        v->setOwner(p);

        std::vector<std::string> args;
        args.push_back("1");
        args.push_back("CA1234AA");

        ReleaseCommand command(args);

        //Act
        command.execute();

        //Assert
        REQUIRE(v->getOwner() == nullptr);

        //Clean
         vehicleFactory->destroy();
         personFactory->destroy();
    }
}
