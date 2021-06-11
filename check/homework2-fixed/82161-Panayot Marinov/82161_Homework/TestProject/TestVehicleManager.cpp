#include "catch2.hpp"
#include "../MainProject/Headers/Person.h"
#include "../MainProject/Headers/VehicleManager.h"

TEST_CASE("Tessting addVehicle function") {
    SECTION("Testing with one vehicle") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        REQUIRE((vm[0] == Vehicle("X5859KC", "BMW 530")) == true);
        REQUIRE(vm.getNumberOfVehicles() == 1);
    }

    SECTION("Testing with two vehicles with equal number plates") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        REQUIRE_THROWS_AS(vm.addVehicle("X5859KC", "Peugeot"), std::invalid_argument);
        CHECK_THROWS_AS(vm.addVehicle("X5859KC", "Peugeot"), std::invalid_argument);
        REQUIRE(vm.getNumberOfVehicles() == 1);
    }

    SECTION("Testing with two vehicles with non-equal number plates") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.addVehicle("X9941AH", "Peugeot");
        REQUIRE((vm[0] == Vehicle("X5859KC", "BMW 530")) == true);
        REQUIRE((vm[1] == Vehicle("X9941AH", "Peugeot")) == true);
        REQUIRE(vm.getNumberOfVehicles() == 2);
    }
}

TEST_CASE("Tessting removeVehicle function") {
    SECTION("Testing with one vehicle") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.removeVehicle("X5859KC");
        REQUIRE(vm.getNumberOfVehicles() == 0);
    }

        SECTION("Testing with non-existing person") {
            VehicleManager vm;
            REQUIRE_THROWS_AS(vm.removeVehicle("X9941AH"), std::invalid_argument);
            CHECK_THROWS_AS(vm.removeVehicle("X9941AH"), std::invalid_argument);
        }

    SECTION("Testing with 2 vehicles which have owners") {
        VehicleManager vm;
        Person person1("Ivan");
        Person person2("Dragan");
        vm.addVehicle("X5859KC", "BMW 530");
        vm.addVehicle("X9941AH", "Peugeot");
        vm.at(0).setOwner(&person1);
        vm.at(1).setOwner(&person2);
        vm.removeVehicle("X9941AH");
        REQUIRE(vm.getNumberOfVehicles() == 1);
    }
}

TEST_CASE("Tessting findVehicle function") {
    SECTION("Testing with one vehicle and string") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        Vehicle* vPointer = vm.findVehicle(string("X5859KC"));
        REQUIRE((*vPointer == Vehicle("X5859KC", "BMW 530")) == true);
    }

    SECTION("Testing with one vehicle and Registration") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        Vehicle* vPointer = vm.findVehicle(Registration("X5859KC"));
        REQUIRE((*vPointer == Vehicle("X5859KC", "BMW 530")) == true);
    }

    SECTION("Testing with non-existing vehicle") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.removeVehicle("X5859KC");
        REQUIRE_THROWS_AS(vm.findVehicle(Registration("X5859KC")), std::invalid_argument);
        CHECK_THROWS_AS(vm.findVehicle(Registration("X5859KC")), std::invalid_argument);
    }

    SECTION("Testing with another non-existing vehicle") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        REQUIRE_THROWS_AS(vm.findVehicle(Registration("X5959KC")), std::invalid_argument);
        CHECK_THROWS_AS(vm.findVehicle(Registration("X5959KC")), std::invalid_argument);
    }

    SECTION("Testing with 2 vehicles") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.addVehicle("X9941AH", "Peugeot");
        REQUIRE((*(vm.findVehicle(Registration("X9941AH"))) == Vehicle("X9941AH", "Peugeot")) == true);
        REQUIRE((*(vm.findVehicle(Registration("X5859KC"))) == Vehicle("X5859KC", "BMW 530")) == true);
    }
}

TEST_CASE("Tessting at function") {
    SECTION("Testing with no vehicles") {
        VehicleManager vm;
        REQUIRE_THROWS_AS(vm.at(0), std::out_of_range);
        CHECK_THROWS_AS(vm.at(0), std::out_of_range);
    }
    
    SECTION("Testing with all vehicles removed") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.addVehicle("X9941AH", "Peugeot");
        vm.removeVehicle("X9941AH");
        vm.removeVehicle("X5859KC");
        REQUIRE_THROWS_AS(vm.at(0), std::out_of_range);
        CHECK_THROWS_AS(vm.at(0), std::out_of_range);
        REQUIRE_THROWS_AS(vm.at(1), std::out_of_range);
        CHECK_THROWS_AS(vm.at(1), std::out_of_range);
    }

    SECTION("Testing with one vehicle left") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.addVehicle("X9941AH", "Peugeot");
        vm.removeVehicle("X9941AH");
        REQUIRE_THROWS_AS(vm.at(1), std::out_of_range);
        CHECK_THROWS_AS(vm.at(1), std::out_of_range);
    }

    SECTION("Testing with two vehicles") {
        VehicleManager vm;
        vm.addVehicle("X5859KC", "BMW 530");
        vm.addVehicle("X9941AH", "Peugeot");
        REQUIRE_THROWS_AS(vm.at(2), std::out_of_range);
        CHECK_THROWS_AS(vm.at(2), std::out_of_range);
    }
}
