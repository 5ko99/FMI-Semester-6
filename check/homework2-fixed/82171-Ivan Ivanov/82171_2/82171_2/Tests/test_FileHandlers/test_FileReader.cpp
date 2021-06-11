// #define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../../FileHandlers/FileReader/FileReader.h"
#include <stdio.h>

SCENARIO("Testing reading from a file") {
    GIVEN("A vehicleHolder, a personHolder and a file path") {
        PersonHolder pH;
        VehicleHolder vH;
        std::string filePath = "../../testReader.txt";
        WHEN("The file is created and read") {
            std::ofstream file(filePath);
            file << "person \"A A\" 1" << std::endl;
            file << "vehicle tt0000AA testDescription" << std::endl;
            file << "acquire 1 tt0000AA";
            file.close();

            FileReader::generateFromFile(filePath, *pH, *vH);

            THEN("The holders hold the right objects") {
                REQUIRE(pH.getByID(1)->getName() == "A A");
                REQUIRE(pH.getByID(1)->getVehiclesCount() == 1);
                REQUIRE(vH.getByRegistration(Registration("tt0000AA"))->getOwner()->getName() == "A A");
            }
        }

        remove(filePath.c_str());
    }
}
