#include "../catch2/catch2.hpp"
#include "../VPAllocator/VPAllocator.hpp"

VPAllocator vpa;
std::string num1 = "HY2904YH", num2 = "G2105IF" , num3 = "H54G", num4 = "TR5435NTSO";
std::string num5 = "5346BGYN", num6 = "BG4324GB", num7="Y4324UN", num8 = "OP5345GGG";
std::string desc1 = "plane", desc2 =  "tractor", desc3 = "boat";
std::string uuid1 = "5465", uuid2 = "4", uuid3 = "HY2904YH";

TEST_CASE("New vehicle") {
    bool added;
    SECTION("correct creating 1") {
        added = true;
        try {
            vpa.newVehicle(num1,desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(added);   
    }

    SECTION("vehicle with the same number") {
        added = true;
        try {
            vpa.newVehicle(num1,desc3);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(!added);        
    }

    SECTION("correct creating 2") {
        added = true;
        try {
            vpa.newVehicle(num2,desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(added);      
    }

    SECTION("number too short") {
        added = true;
        try {
            vpa.newVehicle(num3,desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(!added);        
    }

    SECTION("number too long") {
        added = true;
        try {
            vpa.newVehicle(num4,desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(!added);        
    }

    SECTION("invalid number") {
        added = true;
        try {
            vpa.newVehicle(num5,desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(!added);        
    }

    SECTION("correct creating 3") {
        added = true;
        try {
            vpa.newVehicle(num6,desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(added);      
    }

    SECTION("correct creating 4") {
        added = true;
        try {
            vpa.newVehicle(num7,desc3);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(added);      
    }
}

TEST_CASE("vehicle exists at index") {
    SECTION ("0") {
        Registration reg(num1);
        Vehicle veh(reg,desc1);
        REQUIRE(*vpa.getVListInd(0) == veh);
    }     
    SECTION ("1") {
        Registration reg(num2);
        Vehicle veh(reg,desc1);
        REQUIRE(*vpa.getVListInd(1) == veh);
    }  
    SECTION ("2") {
        Registration reg(num6);
        Vehicle veh(reg,desc1);
        REQUIRE(*vpa.getVListInd(2) == veh);
    }  
}

TEST_CASE("New person") {
    bool added;
    SECTION("Correct creating 1") {
        added = true;
        try {
            vpa.newPerson("Gosho", uuid1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(added);   
    }

    SECTION("Person with same uuid") {
        added = true;
        try {
            vpa.newPerson("Pesho", uuid1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(!added);   
    }

    SECTION("Correct creating 2") {
        added = true;
        try {
            vpa.newPerson("Grisho", uuid2);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(added);   
    }
    
    SECTION("Person with invalid uuid") {
        added = true;
        try {
            vpa.newPerson("Misho", desc1);
        } catch (std::exception& e) {
            added = false;
        }
        REQUIRE(!added);   
    }
}

TEST_CASE("Person exists at index") {
    SECTION ("0") {
        REQUIRE(vpa.getPListInd(0)->getUUID() == 5465);
    }  
    SECTION ("1") {
        REQUIRE((*vpa.getPListInd(1)).getUUID() == 4);
    }  
}

TEST_CASE("Assign vehicle") {
    bool assigned;
    SECTION ("correct assign (unowned) 0.3 1.1 2.0") {
        assigned = true;
        try {
            vpa.acquire(uuid1, num1);
        } catch (std::exception& e) {
            assigned = false;
        }
        REQUIRE(assigned);
    }

    SECTION ("vehicle doesn't exsist 0.3 1.1 2.0") {
        assigned = true;
        try {
            vpa.acquire(uuid2, num8);
        } catch (std::exception& e) {
            assigned = false;
        }
        REQUIRE(!assigned);
    }

    SECTION ("invalid number 0.3 1.1 2.0") {
        assigned = true;
        try {
            vpa.acquire(uuid2, num3);
        } catch (std::exception& e) {
            assigned = false;
        }
        REQUIRE(!assigned);
    }

    SECTION ("correct assign (unowned) 0.2 1.2 2.0") {
        assigned = true;
        try {
            vpa.acquire(uuid1, num6);
        } catch (std::exception& e) {
            assigned = false;
        }
        REQUIRE(assigned);
    }

    SECTION ("correct assign (owned) 0.2 1.1 2.1") {
        assigned = true;
        try {
            vpa.acquire(uuid2, num6);
        } catch (std::exception& e) {
            assigned = false;
        }
        REQUIRE(assigned);
    }

    SECTION ("correct assign (unowned) 0.1 1.1 2.2") {
        assigned = true;
        try {
            vpa.acquire(uuid2, num7);
        } catch (std::exception& e) {
            assigned = false;
        }
        REQUIRE(assigned);
    }
}

TEST_CASE("Release vehicle") {
    bool released;
    SECTION ("correct release 0.2 1.0 2.2") {
        released = true;
        try {
            vpa.release(uuid1, num1);
        } catch (std::exception& e) {
            released = false;
        }
        REQUIRE(released);
    }

    SECTION ("not owned 0.2 1.0 2.2") {
        released = true;
        try {
            vpa.release(uuid1, num1);
        } catch (std::exception& e) {
            released = false;
        }
        REQUIRE(!released);
    }

    SECTION ("doesn't exist 0.2 1.0 2.2") {
        released = true;
        try {
            vpa.release(uuid1, num3);
        } catch (std::exception& e) {
            released = false;
        }
        REQUIRE(!released);
    }
}

TEST_CASE("Remove") {
    bool removed;
    SECTION ("correct remove unowned vehicle 0.1 1.0 2.2") {
        removed = true;
        try {
            vpa.remove(num1);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(removed);
    }

    SECTION ("vehicle doesn't exist 0.1 1.0 2.2") {
        removed = true;
        try {
            vpa.remove(num1);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(!removed);
    }

    SECTION ("invalid number 0.1 1.0 2.2") {
        removed = true;
        try {
            vpa.remove(num3);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(!removed);
    }

    SECTION ("correct remove owned vehicle 0.1 1.0 2.1") {
        removed = true;
        try {
            vpa.remove(num6);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(removed);
    }

    SECTION ("correct remove person without vehicles 0.1 2.1") {
        removed = true;
        try {
            vpa.remove(uuid1);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(removed);
    }

    SECTION ("person doesn't exist 0.1 2.1") {
        removed = true;
        try {
            vpa.remove(uuid1);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(!removed);
    }

    SECTION ("correct remove person with vehicles 0.2") {
        removed = true;
        try {
            vpa.remove(uuid2);
        } catch (std::exception& e) {
            removed = false;
        }
        REQUIRE(removed);
    }
}
