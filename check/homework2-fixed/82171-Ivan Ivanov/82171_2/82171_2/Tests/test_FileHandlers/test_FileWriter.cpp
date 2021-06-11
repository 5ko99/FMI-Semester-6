// #define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../../FileHandlers/FileWriter/FileWriter.h"
#include "../../FileHandlers/FileReader/FileReader.h"
#include "../../CommandInterpreter/CommandInterpreter.h"

SCENARIO("Testing writing to a file") {
    GIVEN("A vehicleHolder and a personHolder with data and a file path") {
        PersonHolder pH;
        VehicleHolder vH;
        std::string filePath = "../../testWriter.txt";

        std::string createPerson = "person \"A A\" 1";
        std::string createVehicle = "vehicle tt0000AA testDescription";
        std::string acquireVehicle = "acquire 1 tt0000AA";

        CommandInterpreter::execute(createPerson, *pH, *vH);
        CommandInterpreter::execute(createVehicle, *pH, *vH);
        CommandInterpreter::execute(acquireVehicle, *pH, *vH);

        WHEN("The commands are written on a file and executed using empty holders") {
            PersonHolder pHDest;
            VehicleHolder vHDest;

            FileWriter::writeToFile(filePath, *pH, *vH);
            FileReader::generateFromFile(filePath, *pHDest, *vHDest);
            
            THEN("The initially empty holders hold the right objects") {
                REQUIRE(pHDest.getByID(1)->getName() == "A A");
                REQUIRE(pHDest.getByID(1)->getVehiclesCount() == 1);
                REQUIRE(vHDest.getByRegistration(Registration("tt0000AA"))->getOwner()->getName() == "A A");
            }
        }
        remove(filePath.c_str());
    }
}
