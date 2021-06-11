#include "../catch2/catch2.hpp"
#include "../Person/Person.hpp"

Registration num("HY2904YH"), num2("TG2105IF");
Vehicle veh(num, "pickup truck");
Vehicle veh1(num, "tractor");
Vehicle veh2(num2, "airplane");
unsigned uuid = 9, uuid2 = 44;
Person per("Nj", uuid);

TEST_CASE("No Vehicles") {
    SECTION("UUID") REQUIRE(per.getUUID() == uuid);
    SECTION("Vehicle count") REQUIRE(!per.vehicleCount());
}

TEST_CASE("Add vehicle") {
    bool isAdded;
    SECTION("Corrrect adding veh") {
        isAdded = true;
        try {
            per.addVehicle(veh);
        } catch (std::exception& e) {
            isAdded = false;
        }
        REQUIRE(isAdded);
    }

    SECTION("Vehicle already exists") {
        isAdded = true;
        try {
            per.addVehicle(veh);
        } catch (std::exception& e) {
            isAdded = false;
        }
        REQUIRE(!isAdded);
    }

    SECTION("Vehicle with the same number already exists") {
        isAdded = true;
        try {
            per.addVehicle(veh1);
        } catch (std::exception& e) {
            isAdded = false;
        }
        REQUIRE(!isAdded);
    }

    SECTION("Corrrect adding veh2") {
        isAdded = true;
        try {
            per.addVehicle(veh2);
        } catch (std::exception& e) {
            isAdded = false;
        }
        REQUIRE(isAdded);
    }
}

TEST_CASE("Vehicle count with 2") {
    REQUIRE(per.vehicleCount() == 2);
}

TEST_CASE("Index") {
    SECTION("Corrrect indexing with 0") {
        REQUIRE(*per.getVehicleAtInd(0) == veh);
    }
}

TEST_CASE("Remove vehicle") {
    bool isRemoved;
    SECTION("Corrrect removing veh") {
        isRemoved = true;
        try {
            per.removeVehicle(veh);
        } catch (std::exception& e) {
            isRemoved = false;
        }
        REQUIRE(isRemoved);
    }

    SECTION("Vehicle not found") {
        isRemoved = true;
        try {
            per.removeVehicle(veh);
        } catch (std::exception& e) {
            isRemoved = false;
        }
        REQUIRE(!isRemoved);
    }

    SECTION("Vehicle with the same number not found") {
        isRemoved = true;
        try {
            per.removeVehicle(veh1);
        } catch (std::exception& e) {
            isRemoved = false;
        }
        REQUIRE(!isRemoved);
    }

    SECTION("Corrrect removing veh2") {
        isRemoved = true;
        try {
            per.removeVehicle(veh2);
        } catch (std::exception& e) {
            isRemoved = false;
        }
        REQUIRE(isRemoved);
    }
}

TEST_CASE("Vehicle count with 0") {
    REQUIRE(per.vehicleCount() == 0);
}

TEST_CASE("Clear all") {
    per.addVehicle(veh);
    per.addVehicle(veh2);
    per.removeAllVehicles();
    REQUIRE(!per.vehicleCount());
}

TEST_CASE("Compare") {
    Person per1("Nj", uuid);
    Person per2("waldo", uuid2);
    SECTION("equal") REQUIRE(per == per1);
    SECTION("different") REQUIRE(!(per == per2));
}
