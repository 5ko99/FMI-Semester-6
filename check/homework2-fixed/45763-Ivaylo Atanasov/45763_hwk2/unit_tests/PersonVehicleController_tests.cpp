#include "../Homework_2_2/PersonVehicleController/PersonVehicleController.hpp"
#include "catch2.hpp"

TEST_CASE("general use tests"){
    
    SECTION("creating/removing a person"){
        PersonVehicleController pvc;
        pvc.createPerson("ivan", "123");
        
        REQUIRE(pvc.personExists(123));
        pvc.remove("123");
        REQUIRE(!pvc.personExists(123));
    }
    
    SECTION("creating/removing a vehicle"){
        PersonVehicleController pvc;
        pvc.createVehicle("AB1111CD", "veh1");
        
        Registration reg("AB1111CD");
        REQUIRE(pvc.vehicleExists(reg));
        pvc.remove("AB1111CD");
        REQUIRE(!pvc.vehicleExists(reg));
    }
    
    SECTION("acquiring/releasing vehicles"){
        PersonVehicleController pvc;
        pvc.createPerson("ivan", "123");
        pvc.createVehicle("AB1111CD", "veh1");
        Registration reg("AB1111CD");
        
        Person* p = pvc.getPersonById(123);
        Vehicle* v = pvc.getVehicleById(reg);
    
        pvc.acquire("123", "AB1111CD");
        REQUIRE(p->owns(reg));
        REQUIRE(v->getOwnerPtr() == p);
        
        pvc.release("123", "AB1111CD");
        REQUIRE(!p->owns(reg));
        REQUIRE(v->getOwnerPtr() == nullptr);
    }
    
    SECTION("removing people"){
        PersonVehicleController pvc;
        pvc.createPerson("ivan", "123");
        pvc.createVehicle("AB1111CD", "veh1");
        pvc.createVehicle("AB2222CD", "veh2");
        Registration reg1("AB1111CD");
        Registration reg2("AB2222CD");
        
        pvc.acquire("123", "AB1111CD");
        pvc.acquire("123", "AB2222CD");
    
        pvc.remove("123");
        REQUIRE(!pvc.personExists(123));
        
        Vehicle* v1 = pvc.getVehicleById(reg1);
        Vehicle* v2 = pvc.getVehicleById(reg2);
        REQUIRE(v1->getOwnerPtr() == nullptr);
        REQUIRE(v2->getOwnerPtr() == nullptr);
    }
    SECTION("removing vehicles"){
        PersonVehicleController pvc;
        pvc.createPerson("ivan", "123");
        pvc.createVehicle("AB1111CD", "veh1");
        pvc.createVehicle("AB2222CD", "veh2");
        Registration reg1("AB1111CD");
        Registration reg2("AB2222CD");
        
        pvc.acquire("123", "AB1111CD");
        pvc.acquire("123", "AB2222CD");
    
        pvc.remove("AB2222CD");
        REQUIRE(!pvc.vehicleExists(reg2));
        
        Person* p = pvc.getPersonById(123);
        REQUIRE(p->owns(reg1));
        REQUIRE(!p->owns(reg2));
    }
    SECTION("clearing everything"){
        PersonVehicleController pvc;
        pvc.createPerson("ivan", "123");
        pvc.createVehicle("AB1111CD", "veh1");
        pvc.createVehicle("AB2222CD", "veh2");
        Registration reg1("AB1111CD");
        Registration reg2("AB2222CD");
        
        pvc.acquire("123", "AB1111CD");
        pvc.acquire("123", "AB2222CD");
    
        pvc.clear();
        REQUIRE(!pvc.personExists(123));
        REQUIRE(!pvc.vehicleExists(reg1));
        REQUIRE(!pvc.vehicleExists(reg2));
    }
}
    
 
