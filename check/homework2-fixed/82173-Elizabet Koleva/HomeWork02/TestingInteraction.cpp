#include "Catch2/catch_amalgamated.hpp"
#include "Interaction.h"

TEST_CASE("Testing class Interaction", "[interaction]")
{
    SECTION("Testing functions without class Commands")
    {
        GIVEN("Interaction object & string")
        {
            Interaction userInteract;
            string test = "become will be capital";
            Interaction::capitalizeString(test);

            WHEN("Testing capitalize string")
            {
                using Catch::Matchers::Contains;
                
                test = "become will be capital";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE(test == "BECOME will be capital");
                    REQUIRE_THAT(test, Contains("BECOME will be capital"));
                }
                
            }

            WHEN("Testing operator =")
            {
                // Interaction newInteraction;
                // newInteraction.userPreference
            }
        }
        
    }

    SECTION("Testing functions with class Commands")
    {
        GIVEN("Interaction object & string")
        {
            Interaction userInteract;
            string test = "";
            const std::vector<Vehicle*>* cars = userInteract.getVehiclesVectorPointers();
            const std::vector<Person*>* people = userInteract.getPersonVectorPointers();

            WHEN("Testing with < 2 arguments")
            {
                test = "Person";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE_THROWS_AS(userInteract.userPreference(test), std::invalid_argument);
                }

                test = "vEhIcle e es";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE_THROWS_AS(userInteract.userPreference(test), std::invalid_argument);
                }

                test = "   vehicle    .";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE_THROWS_AS(userInteract.userPreference(test), std::invalid_argument);
                }

                test = "   release 123 AA1134BB";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE_THROWS_AS(userInteract.userPreference(test), std::invalid_argument);
                }
            }
        
            WHEN("Testing with unknown command")
            {
                test = "Abra Kadabra Simsalabim!";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE_THROWS_AS(userInteract.userPreference(test), std::invalid_argument);
                }

                test = "";
                Interaction::capitalizeString(test);
                THEN("Testing the functions")
                {
                    REQUIRE_THROWS_AS(userInteract.userPreference(test), std::invalid_argument);
                }
            }

            WHEN("Testing add vehicle command") 
            {
                test = "vEhiCle AR4532WB testing101!";
                Interaction::capitalizeString(test);
                userInteract.userPreference(test);

                REQUIRE(cars->size() == 1);
                REQUIRE((*cars).front()->getDescr() == "testing101!");
                REQUIRE((*cars).front()->getRegistrationNumb() == "AR4532WB");

                test = "  veHIclE      E0122BK   Now trying this car desc";
                Interaction::capitalizeString(test);
                userInteract.userPreference(test);
                REQUIRE(cars->size() == 2);
                REQUIRE((*cars)[1]->getRegistrationNumb() == "E0122BK");
                REQUIRE((*cars)[1]->getDescr() == "Now trying this car desc");
                
                THEN("Testing remove [what] - vehicle") 
                {
                    test =" remOvE  AR4532WB";
                    Interaction::capitalizeString(test);
                    userInteract.userPreference(test);
                    REQUIRE(cars->size() == 1);

                    REQUIRE((*cars).front()->getRegistrationNumb() == "E0122BK");
                    REQUIRE((*cars).front()->getDescr() == "Now trying this car desc");
                    
                    test =" REMOve  E0122BK";
                    Interaction::capitalizeString(test);
                    userInteract.userPreference(test);
                    REQUIRE(cars->size() == 0);
                }
            }

            WHEN("Testing person [smth] [smth] command") 
            {
                test = " PErSon \"Peyo Konov\" 110101";
                Interaction::capitalizeString(test);
                userInteract.userPreference(test);
                REQUIRE(people->size() == 1);

                REQUIRE((*people).front()->getID() == 110101);
                REQUIRE((*people).front()->getName() == "Peyo Konov");

                test = "  PERSOn \"Zhivko\"       05698";
                Interaction::capitalizeString(test);
                userInteract.userPreference(test);
                REQUIRE(people->size() == 2);

                REQUIRE((*people)[1]->getName() == "Zhivko");
                REQUIRE((*people)[1]->getID() == 5698);
                
                THEN("Testing remove [what] - person") 
                {
                    test = " remOVE  110101";
                    Interaction::capitalizeString(test);
                    userInteract.userPreference(test);
                    REQUIRE(people->size() == 1);

                    REQUIRE((*people)[0]->getName() == "Zhivko");
                    REQUIRE((*people)[0]->getID() == 5698);

                    test = " ReMOve  05698";
                    Interaction::capitalizeString(test);
                    userInteract.userPreference(test);
                    REQUIRE(people->size() == 0);
                }
            }


            test = "veHICLE ZY0000XO Test functions";
            Interaction::capitalizeString(test);
            userInteract.userPreference(test);

            test = " PERSON \"Ivaylo Bratoev\"  123321";
            Interaction::capitalizeString(test);
            userInteract.userPreference(test);

            WHEN("Testing acquire [id] [carPlate]") 
            {
                test = "AcquiRE 123321 ZY0000XO";
                Interaction::capitalizeString(test);
                userInteract.userPreference(test);

                THEN("Testing ownership") 
                {
                    REQUIRE((*cars)[0]->isOwned());
                    REQUIRE((*people)[0]->getOwnedVehNum() == 1);
                    // REQUIRE((*cars)[0]->getOwner() == &(*people)[0]);
                }

                THEN("Testing remove vehicle and see ownership") 
                {
                    test = " REmoVE ZY0000XO";
                    Interaction::capitalizeString(test);
                    userInteract.userPreference(test);
                    REQUIRE((*people)[0]->getOwnedVehNum() == 0);
                }
                
                THEN("Testing remove person and see ownership but car's side") 
                {
                    test = "   REMOVE 123321";
                    Interaction::capitalizeString(test);
                    userInteract.userPreference(test);
                    REQUIRE_FALSE((*cars)[0]->isOwned());
                }
            }

            // userInteract.userPreference("veHICLE ZY0000XO Test functions");
            // userInteract.userPreference(" PERSON \"Ivaylo Bratoev\"  123321");    99007");
            test = "AcquiRE 123321 ZY0000XO";
            Interaction::capitalizeString(test);
            userInteract.userPreference(test);

            WHEN("Testing release [id] [plate]") 
            {
                test = " relEAse  123321 ZY0000XO";
                Interaction::capitalizeString(test);
                userInteract.userPreference(test);
                
                THEN("Testing released done(ness)") {
                    REQUIRE((*people)[0]->getOwnedVehNum() == 0);
                    REQUIRE_FALSE((*cars)[0]->isOwned());
                }
            }

            WHEN("Testing SAVE command")
            {
                THEN("Testing the functions")
                {
                    
                }
            }

            // WHEN("Testing SHOW command")
            // {
            //     THEN("Testing the functions")
            //     {
            //         cout << endl << "~~~~~~PEOPLE~~~~~" << endl;
            //         userInteract.userPreference(" shoW  people");

            //         userInteract.userPreference(" shoW  ZY0000XO");

            //         userInteract.userPreference(" shoW  123321");

            //         cout << endl << "~~~~~~CARS~~~~~" << endl;
            //         userInteract.userPreference(" shoW  vehicles");
            //     } 
            // }

        }
    }
}
