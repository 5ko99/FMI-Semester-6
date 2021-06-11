#include "catch.h"
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"
#include "Commands.h"

#include <fstream>
#define CATCH_CONFIG_MAIN
TEST_CASE("AllCommands")
{
    Commands TestingListOfCommands;
    std::string addPerson = "person gosho 123";
    TestingListOfCommands.Command(addPerson);
    std::string addVehicle = "vehicle CA1234CA description";
    TestingListOfCommands.Command(addVehicle);
    std::string acquire = "acquire 123 CA1234CA";
    TestingListOfCommands.Command(acquire);
    std::string addVehicle2 = "vehicle CA1235CA description";
    TestingListOfCommands.Command(addVehicle2);
    std::string removeVehicle = "remove CA1235CA";
    TestingListOfCommands.Command(removeVehicle);
    std::string save = "save E:\\C++fmi\\test.txt";
    TestingListOfCommands.Command(save);
    std::ifstream newFile;
    newFile.open ("E:\\C++fmi\test.txt");
    std::string test;
    newFile >> test;
    bool result = (test == "person gosho 123\n"
                           "vehicle CA1234CA description\n"
                          "acquire 123 CA1234CA");
    REQUIRE(result == 1);
}
