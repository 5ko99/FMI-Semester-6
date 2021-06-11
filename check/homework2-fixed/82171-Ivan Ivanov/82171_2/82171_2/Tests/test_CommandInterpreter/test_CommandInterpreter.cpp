// #define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "CommandInterpreterTester/CommandInterpreterTester.h"
#include "../../CommandInterpreter/CommandInterpreter.h"
#include "../../ObjectHolders/PersonHolder/PersonHolder.h"
#include "../../ObjectHolders/VehicleHolder/VehicleHolder.h"
#include <iostream>

SCENARIO("testing toLower", "[format]") {
    GIVEN("A string which includes capital letters") {
        std::string testString = "Asasa!122sDfGH";
        std::string testStringLowered = "asasa!122sdfgh";

        WHEN("toLower is called on the string") {
            CommandInterpreterTester::toLower(testString);

            THEN("The result string has no capital letters") {
                REQUIRE(testString == testStringLowered);
            }
        }
    }
}

SCENARIO("testing removing additional spaces", "[format]") {
    GIVEN("A string which includes only the needed spaces between the words") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = partA + " " + partB + " " + partC;

        WHEN("additional spaces are removed") {
            CommandInterpreterTester::removeAdditionalSpaces(testString);

            THEN("The result string has no additional spaces") {
                REQUIRE(testString == partA + " " + partB + " " + partC);
            }
        }
    }

    GIVEN("A string which includes more than the needed spaces between the words") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = partA + "   " + partB + "    " + partC;

        WHEN("additional spaces are removed") {
            CommandInterpreterTester::removeAdditionalSpaces(testString);

            THEN("The result string has no additional spaces") {
                REQUIRE(testString == partA + " " + partB + " " + partC);
            }
        }
    }

    GIVEN("A string which includes more than the needed spaces at the beginning") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = "   " + partA + " " + partB + " " + partC;

        WHEN("additional spaces are removed") {
            CommandInterpreterTester::removeAdditionalSpaces(testString);

            THEN("The result string has no additional spaces") {
                REQUIRE(testString == partA + " " + partB + " " + partC);
            }
        }
    }

    GIVEN("A string which includes more than the needed spaces at the end") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = partA + " " + partB + " " + partC + "   ";

        WHEN("additional spaces are removed") {
            CommandInterpreterTester::removeAdditionalSpaces(testString);

            THEN("The result string has no additional spaces") {
                REQUIRE(testString == partA + " " + partB + " " + partC);
            }
        }
    }
}

SCENARIO("testing splitting in array", "[format]") {
    GIVEN("A string which consists of three words with no quotations") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = partA + " " + partB + " " + partC;

        WHEN("The string is split") {
            std::string resultWords[3];
            CommandInterpreterTester::splitInArray(testString, resultWords);

            THEN("The words are correclty split") {
                REQUIRE(resultWords[0] == partA);
                REQUIRE(resultWords[1] == partB);
                REQUIRE(resultWords[2] == partC);
            }
        }
    }

    GIVEN("A string which consists of three words with quotations") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = partA + " \"" + partB + "\" \"" + partC + "\"";

        WHEN("The string is split") {
            std::string resultWords[3];
            CommandInterpreterTester::splitInArray(testString, resultWords);
            THEN("The words are correclty split") {
                REQUIRE(resultWords[0] == partA);
                REQUIRE(resultWords[1] == partB);
                REQUIRE(resultWords[2] == partC);
            }
        }
    }
}

SCENARIO("testing formatting", "[format]") {
    GIVEN("A formatted string") {
        std::string partA = "test";
        std::string partB = "string";
        std::string partC = "value";
        std::string testString = partA + " " + partB + " " + partC;

        WHEN("The string is formatted") {
            std::string resultWords[3];
            CommandInterpreterTester::formatCommand(testString, resultWords);

            THEN("The result string is formatted") {
                REQUIRE(resultWords[0] == partA);
                REQUIRE(resultWords[1] == partB);
                REQUIRE(resultWords[2] == partC);
            }
        }
    }

    GIVEN("A not formatted string without quotes") {
        std::string partA = "tEst";
        std::string partAFormated = "test";
        std::string partB = "stRing";
        std::string partC = "vAlue";
        std::string testString = "   " + partA + "   " + partB + "  " + partC + "   ";

        WHEN("The string is formatted") {
            std::string resultWords[3];
            CommandInterpreterTester::formatCommand(testString, resultWords);

            THEN("The result string is formatted") {
                REQUIRE(resultWords[0] == partAFormated);
                REQUIRE(resultWords[1] == partB);
                REQUIRE(resultWords[2] == partC);
            }
        }
    }

    GIVEN("A not formatted string with quotes") {
        std::string partA = "tEst";
        std::string partAFormated = "test";
        std::string partB = "stRing";
        std::string partC = "vAlue";
        std::string testString = "  " + partA + "   \"  " + partB + " \" \"  " + partC + "  \"  ";

        WHEN("The string is formatted") {
            std::string resultWords[3];
            CommandInterpreterTester::formatCommand(testString, resultWords);

            THEN("The result string is formatted") {
                REQUIRE(resultWords[0] == partAFormated);
                REQUIRE(resultWords[1] == partB);
                REQUIRE(resultWords[2] == partC);
            }
        }
    }
}

SCENARIO("testing executing a command", "[execute]") {
    GIVEN("A personHolder and a vehicleHolder") {
        PersonHolder pH;
        VehicleHolder vH;
        WHEN("A command to create a person is passed") {
            std::string createPerson = "person \"Ivan Ivanov\" 1";
            CommandInterpreter::execute(createPerson, *pH, *vH);
            THEN("The person is in the holder") {
                REQUIRE(pH.getByID(1)->getName() == "Ivan Ivanov");
            }

            AND_WHEN("A command to create a vehicle is passed") {
                std::string createVehicle = "vehicle tt0000AA testDescription";
                Registration testRegistration("tt0000AA"); // registration of the vehicle passed
                CommandInterpreter::execute(createVehicle, *pH, *vH);
                THEN("The vehicle is in the holder") {

                    REQUIRE(vH.getByRegistration(testRegistration)->getDescription() == "testDescription");
                }

                AND_WHEN("A command to acquire the vehicle is passed") {
                    std::string acquireVehicle = "acquire 1 tt0000AA";
                    CommandInterpreter::execute(acquireVehicle, *pH, *vH);
                    THEN("The vehicle is acquired") {
                        REQUIRE(vH.getByRegistration(testRegistration)->getOwner()->getName() == "Ivan Ivanov");
                        REQUIRE(pH.getByID(1)->getVehiclesCount() == 1);
                    }

                    AND_WHEN("A command to release the vehicle is passed") {
                        std::string releaseVehicle = "release 1 tt0000AA";
                        CommandInterpreter::execute(releaseVehicle, *pH, *vH);
                        THEN("The vehicle is released") {
                            REQUIRE(vH.getByRegistration(testRegistration)->getOwner() == nullptr);
                            REQUIRE(pH.getByID(1)->getVehiclesCount() == 0);
                        }
                    }

                    AND_WHEN("A command to remove the vehicle is passed") {
                        std::string removeVehicle = "remove tt0000AA";
                        CommandInterpreter::execute(removeVehicle, *pH, *vH);
                        THEN("The vehicle is removed") {
                            REQUIRE_THROWS_AS(vH.getByRegistration(testRegistration), VehicleException);
                        }
                        AND_THEN("The person owns no vehicles") {
                            REQUIRE(pH.getByID(1)->getVehiclesCount() == 0);
                        }
                    }

                    AND_WHEN("A command to remove the person is passed") {
                        std::string removePerson = "remove 1";
                        CommandInterpreter::execute(removePerson, *pH, *vH);
                        THEN("The person is removed") {
                            REQUIRE_THROWS_AS(pH.getByID(1), PersonException);
                        }
                        AND_THEN("The vehicle has no owner") {
                            REQUIRE(vH.getByRegistration(testRegistration)->getOwner() == nullptr);
                        }
                    }
                }

                AND_WHEN("A command to release the vehicle before it's acquired is passed") {
                    std::string releaseVehicle = "release 1 tt0000AA";
                    THEN("An exception is thrown") {
                        REQUIRE_THROWS_AS(CommandInterpreter::execute(releaseVehicle, *pH, *vH), PersonException);
                        REQUIRE(vH.getByRegistration(testRegistration)->getOwner() == nullptr);
                        REQUIRE(pH.getByID(1)->getVehiclesCount() == 0);
                    }
                }

                AND_WHEN("A command to remove the vehicle is passed") {
                    std::string removeVehicle = "remove tt0000AA";
                    CommandInterpreter::execute(removeVehicle, *pH, *vH);
                    THEN("The vehicle is removed") {
                        REQUIRE_THROWS_AS(vH.getByRegistration(testRegistration), VehicleException);
                    }
                    AND_THEN("The person still owns no vehicles") {
                        REQUIRE(pH.getByID(1)->getVehiclesCount() == 0);
                    }
                }

                AND_WHEN("A command to remove a vehicle not in the holder is passed") {
                    std::string removeVehicle = "remove tt0000BB";
                    THEN("An exception is thrown and the holder holds the right vehicles") {
                        REQUIRE_THROWS_AS(CommandInterpreter::execute(removeVehicle, *pH, *vH), VehicleException);
                        REQUIRE(vH.getByRegistration(testRegistration)->getDescription() == "testDescription");
                    }
                }
            }

            AND_WHEN("A command to remove the person is passed") {
                std::string removePerson = "remove 1";
                CommandInterpreter::execute(removePerson, *pH, *vH);
                THEN("The person is removed") {
                    REQUIRE_THROWS_AS(pH.getByID(1), PersonException);
                }
            }

            AND_WHEN("A command to remove a person not in the holder is passed") {
                std::string removePerson = "remove 2";
                THEN("An exception is thrown and the holder holds the right people") {
                    REQUIRE_THROWS_AS(CommandInterpreter::execute(removePerson, *pH, *vH), PersonException);
                    REQUIRE(pH.getByID(1)->getName() == "Ivan Ivanov");
                }
            }
        }
        AND_WHEN("A command to end the prgoramm is passed") {
            std::string removePerson = "end";
            THEN("An exception is thrown") {
                REQUIRE_THROWS_AS(CommandInterpreter::execute(removePerson, *pH, *vH), EndException);
            }
        }
    }
}
