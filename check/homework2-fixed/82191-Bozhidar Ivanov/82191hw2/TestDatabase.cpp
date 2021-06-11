#define CATCH_CONFIG_MAIN
#include "catch2.hpp"

#define private public // KEKW
#include "Database.h"
#include "Utils.h"

void CreateDb(Database& db)
{
    for (uint32_t i = 0; i < 10; i++)
        db.InsertPerson("test" + std::to_string(i), i);
    for (uint32_t i = 1000; i < 1010; i++)
        db.InsertVehicle("AB" + std::to_string(i) + "AB", "desc" + std::to_string(i));
    db.Acquire(0, "AB1000AB");
    db.Acquire(1, "AB1001AB");
    db.Acquire(2, "AB1002AB");
    db.Acquire(0, "AB1003AB");
    db.Acquire(0, "AB1004AB");
    db.Acquire(3, "AB1005AB");
}

TEST_CASE("Database empty create", "[empty]") {
    Database db;
    REQUIRE(db.m_OwnedVehicles.size() == 0);
    REQUIRE(db.m_People.size() == 0);
    REQUIRE(db.m_Vehicles.size() == 0);
    REQUIRE(db.m_VehicleOwners.size() == 0);
}

TEST_CASE("Database insert", "[insert]") {
    Database db;
    SECTION("Person") {
        db.InsertPerson("6969", 6969);
        REQUIRE_THROWS(db.InsertPerson("6969", 6969));
        REQUIRE(db.m_People.size() == 1);
        REQUIRE(db.m_People[6969].m_Id == 6969);
        REQUIRE(db.m_People[6969].m_Name == "6969");
    }
    SECTION("Vehicle") {
        db.InsertVehicle("AB6969AB", "696969");
        REQUIRE_THROWS(db.InsertVehicle("AB6969AB", "696969"));
        uint32_t id = Utils::Fnv1a("AB6969AB");
        REQUIRE_THROWS(db.InsertVehicle("111145", "111145"));
        REQUIRE_THROWS(db.InsertVehicle("ABC34DEF", "ABC34DEF"));
        REQUIRE_THROWS(db.InsertVehicle("ABCDEF", "ABCDEF"));
        REQUIRE_THROWS(db.InsertVehicle("C11D", "C11D"));
        REQUIRE(db.m_Vehicles.size() == 1);
        REQUIRE(db.m_Vehicles[id].m_Id == id);
        REQUIRE(db.m_Vehicles[id].m_Registration.m_RegistrationText == "AB6969AB");
        REQUIRE(db.m_Vehicles[id].m_Description == "696969");
        REQUIRE_NOTHROW(db.InsertVehicle("C1234BA", "C1234BA"));
    }
}

TEST_CASE("Database acquire", "[acquire]") {
    Database db;
    db.InsertPerson("6969", 6969);
    db.InsertVehicle("AB6969AB", "6969");
    db.Acquire(6969, "AB6969AB");
    REQUIRE_THROWS(db.Acquire(1234, "1234"));
    REQUIRE_THROWS(db.Acquire(6969, "1234"));
    uint32_t id = Utils::Fnv1a("AB6969AB");
    REQUIRE(db.m_OwnedVehicles.size() == 1);
    REQUIRE(db.m_OwnedVehicles[6969].size() == 1);
    REQUIRE(db.m_OwnedVehicles[6969].find(id) != db.m_OwnedVehicles[6969].end());
    REQUIRE(db.m_VehicleOwners.size() == 1);
    REQUIRE(db.m_VehicleOwners.find(id) != db.m_VehicleOwners.end());
}

TEST_CASE("Database reacquire", "[reacquire]") {
    Database db;
    db.InsertPerson("6969", 6969);
    db.InsertPerson("1337", 1337);
    db.InsertVehicle("AB6969AB", "6969");
    db.Acquire(6969, "AB6969AB");
    db.Acquire(1337, "AB6969AB");
    
    uint32_t id = Utils::Fnv1a("AB6969AB");
    REQUIRE(db.m_OwnedVehicles.size() == 2);
    REQUIRE(db.m_OwnedVehicles[1337].size() == 1);
    REQUIRE(db.m_OwnedVehicles[1337].find(id) != db.m_OwnedVehicles[1337].end());
    REQUIRE(db.m_VehicleOwners.size() == 1);
    REQUIRE(db.m_VehicleOwners.find(id) != db.m_VehicleOwners.end());
}

TEST_CASE("Database release", "[release]") {
    Database db;
    db.InsertPerson("6969", 6969);
    db.InsertVehicle("AB6969AB", "6969");
    db.Acquire(6969, "AB6969AB");
    uint32_t id = Utils::Fnv1a("AB6969AB");
    db.Release(6969, "AB6969AB");
    REQUIRE_THROWS(db.Release(6969, "AB6969AB"));
    
    REQUIRE(db.m_OwnedVehicles[6969].size() == 0);
    REQUIRE(db.m_VehicleOwners.size() == 0);
}

TEST_CASE("Database remove person", "[remove_person]") {
    Database db;
    db.InsertPerson("6969", 6969);
    db.InsertPerson("1337", 1337);
    db.InsertVehicle("AB6969AB", "6969");
    db.Acquire(6969, "AB6969AB");
    db.RemovePerson(6969);
    REQUIRE_THROWS(db.RemovePerson(6969));
    
    REQUIRE(db.m_People.size() == 1);
    REQUIRE(db.m_OwnedVehicles[6969].size() == 0);
    uint32_t id = Utils::Fnv1a("AB6969AB");
    REQUIRE(db.m_VehicleOwners.find(id) == db.m_VehicleOwners.end());
}

TEST_CASE("Database remove vehicle", "[remove_vehicle]") {
    Database db;
    db.InsertPerson("6969", 6969);
    db.InsertVehicle("AB6969AB", "6969");
    db.InsertVehicle("AB1337AB", "1337");
    db.Acquire(6969, "AB6969AB");
    uint32_t id = Utils::Fnv1a("AB6969AB");
    db.RemoveVehicle("AB6969AB");
    REQUIRE_THROWS(db.RemoveVehicle("AB6969AB"));
    
    REQUIRE(db.m_Vehicles.size() == 1);
    REQUIRE(db.m_OwnedVehicles[6969].size() == 0);
    REQUIRE(db.m_VehicleOwners.find(id) == db.m_VehicleOwners.end());
}

// tests both save and load
TEST_CASE("Database load", "[load]") {
    Database db;
    CreateDb(db);
    db.Save("test.bin");
    Database loaded("test.bin");
    REQUIRE(loaded.m_People.size() == db.m_People.size());
    for (auto& kv : loaded.m_People)
        REQUIRE((kv.second.m_Id == db.m_People[kv.first].m_Id && kv.second.m_Name == db.m_People[kv.first].m_Name));
    
    REQUIRE(loaded.m_Vehicles.size() == db.m_Vehicles.size());
    for (auto& kv : loaded.m_Vehicles)
    {
        REQUIRE(kv.second.m_Registration.GetRegistrationText() == db.m_Vehicles[kv.first].m_Registration.GetRegistrationText());
        REQUIRE(kv.second.m_Description == db.m_Vehicles[kv.first].m_Description);
        REQUIRE(kv.second.m_Id == db.m_Vehicles[kv.first].m_Id);
    }

    REQUIRE(loaded.m_VehicleOwners.size() == db.m_VehicleOwners.size());
    for (auto& kv : loaded.m_VehicleOwners)
        REQUIRE(kv.second == db.m_VehicleOwners[kv.first]);
    
    REQUIRE(loaded.m_OwnedVehicles.size() == db.m_OwnedVehicles.size());
    for (auto& kv : loaded.m_OwnedVehicles)
    {
        REQUIRE(kv.second.size() == db.m_OwnedVehicles[kv.first].size());
        for (uint32_t id : kv.second)
            REQUIRE(db.m_OwnedVehicles[kv.first].find(id) != db.m_OwnedVehicles[kv.first].end());
    }
}
