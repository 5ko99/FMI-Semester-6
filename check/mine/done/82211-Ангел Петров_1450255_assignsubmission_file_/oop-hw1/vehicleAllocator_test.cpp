#define CATCH_CONFIG_MAIN
#include <cstring>
#include "catch2.hpp"
#include "myString.h"
#include "vehicle.h"
#include "vehicleAllocator.h"

TEST_CASE ("allocate") {

    VehicleAllocator container(1);
    
    Vehicle* ptr = container.allocate("A 0000 AA", "A vehicle.", 1);

    CHECK(!strcmp((*ptr).getDescription(), "A vehicle."));
    CHECK(!strcmp((*ptr).getRegistration(), "A 0000 AA"));

}