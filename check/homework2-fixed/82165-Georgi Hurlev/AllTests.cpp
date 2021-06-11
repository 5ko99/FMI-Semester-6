#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "Interface.h" //includes all headers
#include <iostream>
#include <cstdio>

using std::cout;

//tests of print functions are commented so it won't fill the console output every time

/*
РћР±РёРєРЅРѕРІРµРЅРѕ СЂР°Р·РґРµР»СЏРј С‚РµСЃС‚РѕРІРµС‚Рµ РІ РѕС‚РґРµР»РЅРё С„Р°Р№Р»РѕРІРµ Р·Р° РІСЃРµРєРё РєР»Р°СЃ,
РЅРѕ РІ СЃР»СѓС‡Р°СЏ СЂРµС€РёС… ,С‡Рµ Р·Р° РїРѕ-Р»РµСЃРЅРѕС‚Рѕ С‚РµСЃС‚РІР°РЅРµ РЅР° С†СЏР»РѕСЃС‚РЅР°С‚Р° РїСЂРѕРіСЂР°РјР°
С‰Рµ Рµ РїРѕ-РґРѕР±СЂРµ ,Р°РєРѕ СЃР° РІ РµРґРЅРё С„Р°Р№Р».
*/

TEST_CASE("Disclaimer") {
	//
	std::cout << "(Please just answer '1' to the next 3 questions. Otherwise a test might fail.)\n";
	std::cout << "(They come from caught throws in the interface)\n";
	//
}


TEST_CASE("Testing Registration class")
{
	WHEN("Creating registr with valid argument")
	{
		REQUIRE_NOTHROW(Registration("C1234AB"));
		REQUIRE_NOTHROW(Registration("XY1111YX"));
		REQUIRE_NOTHROW(Registration("A9999ZZ"));
		REQUIRE_NOTHROW(Registration("A0000ZZ"));
	}
	WHEN("Creating reg with invalid arguments")
	{
		REQUIRE_THROWS(Registration("ZZC1234AB"));
		REQUIRE_THROWS(Registration("11234AB"));
		REQUIRE_THROWS(Registration("ZZ234AB"));
		REQUIRE_THROWS(Registration("ZZ234AAB"));
		REQUIRE_THROWS(Registration("ZZ2345B"));
		REQUIRE_THROWS(Registration("Za1234AB"));
		REQUIRE_THROWS(Registration("ZZ2341aB"));
		REQUIRE_THROWS(Registration("ZZ234aB"));
		REQUIRE_THROWS(Registration("ZZ2341B"));
		REQUIRE_THROWS(Registration("aa1234aa"));
		REQUIRE_THROWS(Registration("01234567"));
		REQUIRE_THROWS(Registration("ABVGDEJZ"));
		REQUIRE_THROWS(Registration("12ABVH23"));
	}
	WHEN("Testing getAsString")
	{
		std::string str = "AB1234BA";
		Registration reg(str);
		THEN("Testing if string is the same as starting") {
			REQUIRE(reg.getAsString() == str);
		}
	}

	SECTION("Testing move assignment")
	{
		WHEN("Creating first reg")
		{
			Registration reg("AB1234BA");
			THEN("Creating second reg with std::move") {
				Registration reg2 = std::move(Registration("A5234BA"));
				REQUIRE(reg2.getAsString() == "A5234BA");
				THEN("Move operator test") {
					reg2 = std::move(reg);
					REQUIRE(reg2.getAsString() == "AB1234BA");
					REQUIRE(reg.getAsString().empty());
				}
			}
		}
	}
}


TEST_CASE("Testing Person class") {

	/*WHEN("Creating Person with invalid ID")
	{

	}*/
	WHEN("Creating Person") {
		THEN("Testing normal person creation") {
			REQUIRE_NOTHROW(Person("Gosho", 123));
		}
		THEN("Testing person with 0 ID") {
			REQUIRE_NOTHROW(Person("Ivan", 000));
		}
		THEN("Testing creating person with very long name") { //its not said to be invalid so...
			REQUIRE_NOTHROW(Person("Roses are Red,\
								This string is long,\
								That name is Rick Astley's song:\
								We're no strangers to love\
								You know the rules and so do I\
								A full commitment's what I'm thinking of\
								You wouldn't get this from any other guy\
								I just wanna tell you how I'm feeling\
								Gotta make you understand\
								Never gonna give you up\
								Never gonna let you down\
								Never gonna run around and desert you\
								Never gonna make you cry\
								Never gonna say goodbye\
								Never gonna tell a lie and hurt you", 25102009));
		}

	}
	WHEN("Testing move constructor and move assignm operator")
	{
		THEN("Move constr")
		{
			Person first = std::move(Person("George", 1234512));
			REQUIRE(first.getId() == 1234512);
			REQUIRE(first.getName() == "George");
		}
		THEN("More operator=")
		{
			Person first("Albert", 12341);
			Person second("Nobody", 0);
			second = std::move(first);
			REQUIRE(second.getId() == 12341);
			REQUIRE(second.getName() == "Albert");
			REQUIRE(first.getId() == 0);
			REQUIRE(first.getName().empty());
		}
	}
	WHEN("Testing operator ==") {
		Person first("ABC", 123);
		Person second("ABC", 123);
		THEN("Comparing two strings") {
			REQUIRE(first == second);
			REQUIRE(first == first);
			second = std::move(Person("abc", 1234));
			REQUIRE_FALSE(first == second);
			second = std::move(Person("ABCD", 1123));
			REQUIRE_FALSE(first == second);
			second = std::move(Person("AB", 1239));
			REQUIRE_FALSE(first == second);
			second = std::move(Person("ABC", 1234567891));
			REQUIRE_FALSE(first == second);
		}
	}
	WHEN("Adding vehicles") {
		Person human("The collector", 2021);
		GIVEN("Creating vehicles") {
			Vehicle vehFirst(Registration("A1234BC"), "First");
			Vehicle vehSecond(Registration("AA1234BC"), "First");
			WHEN("Add new veh") {
				REQUIRE_NOTHROW(human.addVehicle(vehFirst));

				REQUIRE_NOTHROW(human.addVehicle(vehSecond));
				THEN("Try inserting a dublicate")
				{
					REQUIRE_THROWS_AS(human.addVehicle(vehFirst), int);
					REQUIRE_THROWS_AS(human.addVehicle(vehSecond), int);
					Vehicle vehTest(Registration("AA1234BC"), "Some");
					REQUIRE_THROWS_AS(human.addVehicle(vehTest), int);
				}

			}
		}//given
		GIVEN("Adding many different vehicles created dynamically")
		{
			std::vector<Vehicle*> vehs;
			std::string startingReg = "A0000AA";
			Vehicle* newVeh = new Vehicle(startingReg, "None");
			REQUIRE_NOTHROW(human.addVehicle(*newVeh));
			vehs.push_back(newVeh);
			for (unsigned i = 1; i < 1000; i++) //makes 999 different Registrations, 9,999 executes too slow
			{
				/*if (i % 1000 == 0) { //i=0 is valid here so I start from 1
					startingReg[0]++;
					startingReg[1] = '0';
					startingReg[2] = '0';
					startingReg[3] = '0';
				}*/
				if (i % 100 == 0) {
					startingReg[1]++;
					startingReg[2] = '0';
					startingReg[3] = '0';
				}
				else if (i % 10 == 0) {
					startingReg[2]++;
					startingReg[3] = '0';
				}
				else {
					startingReg[3]++;
				}

				try {
					Vehicle* newVeh = new Vehicle(startingReg, "None");
					REQUIRE_NOTHROW(human.addVehicle(*newVeh));
					vehs.push_back(newVeh);
				}
				catch (const std::exception& e) { //allocation error
					std::cerr << e.what() << std::endl;
					for (unsigned j = 0; j < vehs.size(); j++) {
						delete vehs[j];
					}
					break;
				}
				catch (int j) {
					if (j == 1) {
						std::cerr << "Veh already owned error line 183!\n";
					}
					else if (j == 0) {
						std::cerr << "std::bad_alloc trying to push_back vehicles in human line 186";
					}
					else if (j == -2) {
						std::cerr << "Unknown error line 189";
					}
					for (unsigned g = 0; g < vehs.size(); g++) {
						delete vehs[g];
					}
					break;
				}
			}//for
			THEN("Check if all added successfully") {
				REQUIRE(human.getOwnedVehNum() == 1000);
			}
			THEN("Testing removeAll") {
				human.removeAllVehicles();
				REQUIRE(human.getOwnedVehNum() == 0);
			}
			for (short g = 0; g < vehs.size(); g++) {
				delete vehs[g];
			}

		}//given
	}//when

	WHEN("Testing vehicle removing") {
		Person human("Random lucky man", 7777);

		GIVEN("Adding vehs") {
			Vehicle first(Registration("AB1234BA"), "First");
			Vehicle second(Registration("B1234BA"), "Second");
			human.addVehicle(first);
			human.addVehicle(second);
			REQUIRE(human.getOwnedVehNum() == 2);
			THEN("Remove added and test if can be readded") {
				human.removeVehicle(first.getRegistration());
				REQUIRE(human.getOwnedVehNum() == 1);
				REQUIRE_NOTHROW(human.addVehicle(first));
				REQUIRE(human.getOwnedVehNum() == 2);
				human.removeVehicle("AB1234BA");
				human.removeVehicle("B1234BA");
				REQUIRE(human.getOwnedVehNum() == 0);
			}
		}

	}
	/*WHEN("Test printing") {
		GIVEN("Creating person with vehicles") {
			Person human("Ivan Ivanov", 126798);
			Vehicle first(Registration("AB1234CD"), "Peugeot 406");
			Vehicle second(Registration("HD1280PX"), "Audi S 45");
			human.addVehicle(first);
			human.addVehicle(second);
			THEN("Printing full info") {
				std::cout << "(FUll info)\n";
				human.printFullInfo(std::cout);
			}
			THEN("Printing just person info") {
				std::cout << "\n(Just personal info)\n";
				human.printPersonalInfo(std::cout);
			}
			THEN("Printing as command")
			{
				std::cout << "\n(As a command)\n";
				human.outputAsCommand(std::cout);
			}
		}
	}*/

}


TEST_CASE("Testing Vehicle class") {
	WHEN("Creating a vehicle") {
		REQUIRE_NOTHROW(Vehicle(Registration("AA1111ZZ"), "Some vehicle made for tests"));
		REQUIRE_THROWS(Vehicle(Registration("A11111ZZ"), "Some other vehicle made for tests with invalid registartion"));
		REQUIRE_NOTHROW(Vehicle(Registration("VE7777RY"), "Roses are Red...\
														  writing good descriptions for vehicles\
														  for me are just miracles \
														  (So here's a funny poem)\
														  Tinkle, Tinkle little car\
														  How I wonder what you are.\
														  Leaking oil every day\
			                                              Having it your own way.\
			                                              Going up hills real slow\
			                                              I don't want you any mo'.\
		                                               	  Tinkle, Tinkle little car\
			                                              Boy, what a lemon you are."));
		Vehicle test1(Registration("AB1111ZZ"), "Test");
		REQUIRE(test1.getRegistration() == "AB1111ZZ");
		REQUIRE(test1.getDescrpt() == "Test");
	}
	WHEN("Testing move constr") {
		Vehicle test = std::move(Vehicle(Registration("AB1234BC"), "Move subject"));
		REQUIRE(test.getRegistration() == "AB1234BC");
		REQUIRE(test.getDescrpt() == "Move subject");
		THEN("Testing move assignm operator") {
			Vehicle second(Registration("AB1234BD"), "Some");
			second = std::move(test);
			REQUIRE(second.getDescrpt() == "Move subject");
			REQUIRE(second.getRegistration() == "AB1234BC");
			REQUIRE(test.getDescrpt().empty());
			REQUIRE(test.getRegistration().empty());
		}
	}
	WHEN("Testing operator ==") {
		Vehicle first(Registration("TE0000ST"), "First car");
		Vehicle second(Registration("DI0000FF"), "Second car");
		REQUIRE_FALSE(first == second);
		REQUIRE(first == first);
		second = std::move(Vehicle(Registration("TE0000ST"), "Moved car"));
		REQUIRE(first == second);
	}
	WHEN("Testing adding and removing owner") {
		Person theOwner("Random lucky man", 7777);
		Vehicle car(Registration("DI0000FF"), "Some car");
		WHEN("Adding owner to veh") {
			car.addOwner(theOwner);
			REQUIRE(car.hasOwner());
			THEN("Removing owner") {
				car.removeOwner();
				REQUIRE_FALSE(car.hasOwner());
				THEN("Try readding") {
					car.addOwner(theOwner);
					REQUIRE(car.hasOwner());
				}
			}
		}

	}//when
	/*WHEN("Test printing") {
		GIVEN("Creating a vehicle with owner") {
			Person human("Ivan Ivanov", 126798);
			Vehicle car(Registration("AB1234CD"), "Peugeot 406");
			car.addOwner(human);
			THEN("Printing full info") {
				std::cout << "(FUll info)\n";
				car.printFullInfo(std::cout);
			}
			THEN("Printing just person info") {
				std::cout << "\n(Just personal info)\n";
				car.printSpecifications(std::cout);
			}
			THEN("Printing as command")
			{
				std::cout << "\n(As a command)\n";
				car.outputAsCommand(std::cout);
			}
		}
	}*/

}//test_case


TEST_CASE("Testing Commands class") {
	WHEN("Testing different command extraction") {
		Command command;
		THEN("Inserting save path") {
			command.processCommand("SaVe C:/Temp/My Program/Info.txt");

			REQUIRE(command.getCommand() == CommandOption::save);
			REQUIRE(command.getSavePath() == "C:/Temp/My Program/Info.txt");

			command.processCommand("   SaVe                C:/Temp/My Program/Info.txt");

			REQUIRE(command.getCommand() == CommandOption::save);
			REQUIRE(command.getSavePath() == "C:/Temp/My Program/Info.txt");
		}
		THEN("Testing VEHICLE parameters") {
			command.processCommand("VEhiCLE AB1234BA Super cool vehicle!");
			REQUIRE(command.getCommand() == CommandOption::vehicle);
			Vehicle expectedVeh(Registration("AB1234BA"), "Super cool vehicle!"); //= std::move(command.getVehicleParameters());
			Vehicle commandVeh = std::move(command.getVehicleParameters());
			REQUIRE(expectedVeh == commandVeh);
			REQUIRE(expectedVeh.getDescrpt() == commandVeh.getDescrpt());
			THEN("Testing for blank spaces") {
				command.processCommand("VEhiCLE    ZZ1234ZZ                 Super cool vehicle!");
				REQUIRE(command.getCommand() == CommandOption::vehicle);
				Vehicle expectedVeh(Registration("ZZ1234ZZ"), "Super cool vehicle!"); //= std::move(command.getVehicleParameters());
				Vehicle commandVeh = std::move(command.getVehicleParameters());
				REQUIRE(expectedVeh == commandVeh);
				REQUIRE(expectedVeh.getDescrpt() == commandVeh.getDescrpt());
			}
		}
		THEN("Testing Person parameters") {
			command.processCommand("perSon \"Dimitar Dimchov\" 99007");
			REQUIRE(command.getCommand() == CommandOption::person);
			Person expectedPerson("Dimitar Dimchov", 99007); //= std::move(command.getVehicleParameters());
			Person commandPerson = std::move(command.getPersonParameters());
			REQUIRE(expectedPerson == commandPerson);
			REQUIRE(expectedPerson.getName() == commandPerson.getName());
			THEN("Testing for blank spaces") {
				command.processCommand("perSon        \"Dimitar Dimchov\"                99007");
				REQUIRE(command.getCommand() == CommandOption::person);
				Person expectedPerson("Dimitar Dimchov", 99007); //= std::move(command.getVehicleParameters());
				Person commandPerson = std::move(command.getPersonParameters());
				REQUIRE(expectedPerson == commandPerson);
				REQUIRE(expectedPerson.getName() == commandPerson.getName());

			}
		}
		THEN("Testing Release/Acquire parameters") {  //acquire calls release so it's the same
			GIVEN("Creating Person pointer and owns a Vehicle pointer") {
				Person* human = new Person("Ivan Ivanov", 1997);
				Vehicle* car = new Vehicle(Registration("IV1997AN"), "Ivan's car");
				human->addVehicle(*car);
				REQUIRE((*car).hasOwner());
				REQUIRE((*human).getOwnedVehNum() == 1);
				WHEN("Executing command and getting parameters") {
					command.processCommand("  ReLease   1997  IV1997AN");
					REQUIRE(command.getCommand() == CommandOption::release);
					std::tuple< unsigned int, std::string> param = command.getReleaseParameters();
					THEN("Checking if parameters are right") {
						REQUIRE((*human).getId() == std::get<0>(param));
						REQUIRE((*car).getRegistration() == std::get<1>(param));
						THEN("Check if releasing goes right") {
							human->removeVehicle(std::get<1>(param));
							car->removeOwner();
							REQUIRE_FALSE((*car).hasOwner());
							REQUIRE((*human).getOwnedVehNum() == 0);
						}
					}
				}
				WHEN("Testing ACQUIRE ") {
					command.processCommand("  AcQUiRE    1997  IV1997AN");
					REQUIRE(command.getCommand() == CommandOption::acquire);
				}
				delete car;
				delete human;
			}//given
		}//then
		THEN("Testing Remove parameters") {
			command.processCommand("  REmove       1999989");
			REQUIRE(command.getCommand() == CommandOption::removed);
			REQUIRE(command.getRemoveParameter() == "1999989");
			command.processCommand("   REmovE          SOMEONE");
			REQUIRE(command.getCommand() == CommandOption::removed);
			REQUIRE(command.getRemoveParameter() == "SOMEONE");
			command.processCommand("remove     ABABABABA123,");
			REQUIRE(command.getCommand() == CommandOption::removed);
			REQUIRE(command.getRemoveParameter() == "ABABABABA123,");
		}
		THEN("Testing Show parameters") {
			//SHOW [PEOPLE|VEHICLES|<id>]
			command.processCommand("  shOW     [PEOPLE]");
			REQUIRE(command.getCommand() == CommandOption::show);
			REQUIRE(command.getShowParameter() == "PEOPLE");
			command.processCommand("  sHow   [VEHICLES]");
			REQUIRE(command.getCommand() == CommandOption::show);
			REQUIRE(command.getShowParameter() == "VEHICLES");
			command.processCommand("SHOW    [AB1234BI]");
			REQUIRE(command.getCommand() == CommandOption::show);
			REQUIRE(command.getShowParameter() == "AB1234BI");
			command.processCommand("show  [999111]");
			REQUIRE(command.getCommand() == CommandOption::show);
			REQUIRE(command.getShowParameter() == "999111");
			command.processCommand("show  [999111");
			REQUIRE_THROWS(command.getShowParameter());
			command.processCommand("show  999111");
			REQUIRE_THROWS(command.getShowParameter());
			command.processCommand("show  999111]");
			REQUIRE_THROWS(command.getShowParameter());
			command.processCommand("show  ");
			REQUIRE_THROWS(command.getShowParameter());
		}
	}//when
}//command


TEST_CASE("Testing Interface class") {
	GIVEN("Creating interface") {
		Interface interface;
		const std::vector<Person*>* people = interface.getPeoplePointer();
		const std::vector<Vehicle*>* vehs = interface.getVehiclesPointer();

		WHEN("Testing add Vehicle") {
			interface.executeCommand(" VEhiCLE AB1234BA Car for tests!");
			REQUIRE(vehs->size() == 1);
			REQUIRE((*vehs).front()->getRegistration() == "AB1234BA");
			REQUIRE((*vehs).front()->getDescrpt() == "Car for tests!");
			//REQUIRE_THROWS(interface.executeCommand(" VEhiClE ABABABA Car for throws!"));
			interface.executeCommand("  VEhiCLE      AZ1234OB       Car for other test!");
			REQUIRE(vehs->size() == 2);
			REQUIRE((*vehs)[1]->getRegistration() == "AZ1234OB");
			REQUIRE((*vehs)[1]->getDescrpt() == "Car for other test!");
			THEN("Testing car removing") {
				interface.executeCommand(" REMOve  AB1234BA");
				REQUIRE(vehs->size() == 1);
				REQUIRE((*vehs).front()->getRegistration() == "AZ1234OB");
				REQUIRE((*vehs).front()->getDescrpt() == "Car for other test!");
				interface.executeCommand(" REMOve  AZ1234OB");
				REQUIRE(vehs->size() == 0);

			}
		}
		WHEN("Testing add Person") {
			interface.executeCommand(" perSon \"Dimitar Dimchov\" 99007");
			REQUIRE(people->size() == 1);
			REQUIRE((*people).front()->getId() == 99007);
			REQUIRE((*people).front()->getName() == "Dimitar Dimchov");
			interface.executeCommand("  person \"Ivancho Ivanchov\"       0007");
			REQUIRE(people->size() == 2);
			REQUIRE((*people)[1]->getId() == 7);
			REQUIRE((*people)[1]->getName() == "Ivancho Ivanchov");
			THEN("Testing person removing") {
				interface.executeCommand(" REMOve  99007");
				REQUIRE(people->size() == 1);
				REQUIRE((*people)[0]->getId() == 7);
				REQUIRE((*people)[0]->getName() == "Ivancho Ivanchov");
				interface.executeCommand(" REMOve  0007");
				REQUIRE(people->size() == 0);

			}
		}
		WHEN("Testing Acquiring vehicle") {
			GIVEN("Adding vehicle and person with commands") {
				interface.executeCommand("   VEhiCLE AB1234BA Car for adding!");
				interface.executeCommand(" perSon \"Dimitar Dimchovvvvvvvv\"     99007");
				WHEN("Executing acquire") {
					interface.executeCommand("Acquire 99007   AB1234BA");
					THEN("Check if owned") {
						REQUIRE((*people)[0]->getOwnedVehNum() == 1);
						REQUIRE((*vehs)[0]->hasOwner());
					}
					THEN("Check if removing vehicle affect ownership") {
						interface.executeCommand("   REMOVE AB1234BA");
						REQUIRE((*people)[0]->getOwnedVehNum() == 0);
					}
					THEN("Check if removing person affect veh ownership") {
						interface.executeCommand("   REMOVE 99007");
						REQUIRE_FALSE((*vehs)[0]->hasOwner());
					}
				}
			}
		}
		WHEN("Testing release") {
			GIVEN("Creating person and vehicle , and acquire it") {
				interface.executeCommand("   VEhiCLE AB1234BA Car for adding!");
				interface.executeCommand(" perSon \"Dimitar Dimchovvvvvvvv\"     99007");
				interface.executeCommand("Acquire 99007   AB1234BA");
				WHEN("Executing release") {
					interface.executeCommand("  reLease 99007   AB1234BA");
					THEN("Check if released") {
						REQUIRE_FALSE((*vehs)[0]->hasOwner());
						REQUIRE((*people)[0]->getOwnedVehNum() == 0);
					}
				}
			}//given
		}//release
		/*
		WHEN("Testing show objects") {
			interface.executeCommand("   VEhiCLE AB1234BA Car for adding!");
			interface.executeCommand(" perSon \"Dimitar Ivanov\"     99007");
			interface.executeCommand("   VEhiCLE AZ1909BZ Best car so far!");
			interface.executeCommand(" perSon \"Gerogi Harlev\"     130221");
			interface.executeCommand("Acquire 99007   AB1234BA");
			interface.executeCommand("Acquire 130221  AZ1909BZ");
			THEN("Testing show PEOPLE") {
				std::cout << "\n------------(all PEOPLE)----------\n";
				interface.executeCommand(" Show [PEOPLE]");
			}
			THEN("Testing show VEHICLES") {
				std::cout << "\n------------(all VEHICLES)----------\n";
				interface.executeCommand(" Show [VEHICLES]");
			}
			THEN("Testing show with ID") {
				std::cout << "\n------------(id 99007)----------\n";
				interface.executeCommand(" Show [99007]");
				std::cout << "\n------------(id 130221)----------\n";
				interface.executeCommand(" Show [130221]");
				std::cout << "\n------------(reg AZ1909BZ)----------\n";
				interface.executeCommand(" Show [AZ1909BZ]");
			}
		}*/

		WHEN("Testing file save") {
			GIVEN("Creating a temporary file for the test") {
				std::fstream file;
				std::string fileName = "TestFile";
				do {
					if (file.is_open()) {
						//std::cout << "closed";
						file.close();
					}
					fileName += "1";
					file.open(fileName + ".txt");
				} while (file.good()); //find a filename that doesn't exist

				if (file.is_open()) {
					file.close();
				}
				fileName += ".txt";
				file.open(fileName, std::ios::out);//create
				file.close();
				file.open(fileName, std::ios::out | std::ios::in); //open for write and read

				if (!file.is_open()) {
					//std::cout << fileName << std::endl;
					throw std::exception("cant open");
				}
				WHEN("Create vehicle and people") {
					Interface interface;
					interface.executeCommand("   VEhiCLE AB1234BA Car for adding!");
					interface.executeCommand(" perSon \"Dimitar\"     99007");
					interface.executeCommand("Acquire 99007   AB1234BA");
					interface.executeCommand("save " + fileName);
					THEN("Check if saved properly in file") {
						std::string str;
						short i = 0;
						while (std::getline(file, str)) {
							if (i == 0) {
								REQUIRE(str == "PERSON \"Dimitar\" 99007");
							}
							else if (i == 1) {
								REQUIRE(str == "VEHICLE AB1234BA Car for adding!");
							}
							else {
								REQUIRE(str == "ACQUIRE 99007 \"Dimitar\"");
							}
							i++;
						}
					}
				}//when
				file.close();
				if (std::remove(fileName.c_str()) != 0) {
					std::cout << "(File " << fileName << " was created but could not be removed)\n";
				}
			}

			THEN("Test without parameter") {
				//	REQUIRE_THROWS_AS(interface.executeCommand("save "), int);
				REQUIRE_THROWS_AS(interface.executeCommand("save "), std::logic_error);

				REQUIRE_THROWS_AS(interface.executeCommand("   SAve "), std::logic_error);
				REQUIRE_THROWS_AS(interface.executeCommand("   SAve"), std::logic_error);
			}
		}



	}//given


}

