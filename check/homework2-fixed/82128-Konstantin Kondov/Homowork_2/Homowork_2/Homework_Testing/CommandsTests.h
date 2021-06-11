#ifndef COMMANDSTESTS_H
#define COMMANDSTESTS_H
#include "../Homework/Commands.h"
#include "DatabaseTests.h"
#include "VehicleTests.h"
#include "PersonTests.h"



TEST_CASE("Inputting commands", "[Commands]") {

	SECTION("Inputting unrecognizable commands throws exception", "[Commands]") {

		Database database;

		std::string com1 = "  'asd";
		std::string com2 = "MovE";
		std::string com3 = "ExEcUTe Person";

		std::string argument = "argument";

		RT(Command(com1, argument, database));
		RT(Command(com2, argument, database));
		RT(Command(com3, argument, database));

	}

	SECTION("Inputting recognizable command Person with valid arguments but adding the same person twice throws exception", "[Commands]") {

		std::string com1 = "Person";
		std::string argument1 = "\"Ivan Ivanov\" 9128";

		std::string com2 = "PeRson";
		std::string argument2 = "\"Ivan Ivanov\" 9128";


		Database database;

		RNT(Command(com1, argument1, database));
		RT(Command(com2, argument2, database));


	}

	SECTION(("Inputting recognizable command PERSON doenst throw exception", "[Commands]")) {

		std::string com1 = "Person";
		std::string argument1 = "\"Ivan Ivanov\" 9128";

		std::string com2 = "PeRson";
		std::string argument2 = "\" Dimitur Rusenov\"      9    ";

		std::string com3 = "person";
		std::string argument3 = "             \"Malkiq vanio\"     899 ";

		Database database;

		RNT(Command(com1, argument1, database));
		RNT(Command(com2, argument2, database));
		RNT(Command(com3, argument3, database));
		

		SECTION("Verifying giving arguments and comamnds for Person", "[Commands]") {

			std::string com1 = "Person";
			std::string argument1 = "\"Ivan Ivanov\" 9128";

			std::string com2 = "PeRson";
			std::string argument2 = "\" Dimitur Rusenov\"      9    ";

			std::string com3 = "person";
			std::string argument3 = "             \"Malkiq vanio\"     899 ";

			Database database;


			Command exe1(com1, argument1, database);
			Command exe2(com2, argument2, database);
			Command exe3(com3, argument3, database);

			R(exe1.GetCommand() == "PERSON");
			R(exe1.GetFirstArg() == "Ivan Ivanov");
			R(exe1.GetSecondArg() == "9128");

			R(exe2.GetCommand() == "PERSON");
			R(exe2.GetFirstArg() == " Dimitur Rusenov");
			R(exe2.GetSecondArg() == "9");

			R(exe3.GetCommand() == "PERSON");
			R(exe3.GetFirstArg() == "Malkiq vanio");
			R(exe3.GetSecondArg() == "899");

		}
		
	}


	SECTION("Inputting recognizable command VEHICLE with invalid argumetn throws exception", "[Commands]") {


		std::string com1 = "VEHICLE";
		std::string argument1 = "  ASS11SF 9128    ";

		std::string com2 = "vehicle";
		std::string argument2 = "A56a89XX 6889     ";

		Database database;

		RT(Command(com1, argument1, database));
		RT(Command(com2, argument2, database));


	}

	SECTION("Inputting recognizable command VEHICLE with valid arguments but the same vehicle inputting twice throws exception", "[Commands]") {

		std::string com1 = "VEHICLE";
		std::string argument1 = "AS1234AS 9999";

		std::string com2 = "vehicle";
		std::string argument2 = "AS1234AS 9999";

		Database database;

		RNT(Command(com1, argument1, database));
		RT(Command(com2, argument2, database));


	}

	SECTION("Inputting recognizable command VEHICLE with valid arguments doenst throw exception", "[Commands]") {

		std::string com1 = "VEHICLE";
		std::string argument1 = "  AS1231SF 9128    ";

		std::string com2 = "vehicle";
		std::string argument2 = "A5689XX 6889     ";

		std::string com3 = "VeHiClE";
		std::string argument3 = "   PS3723LL    899 ";

		Database database;

		RNT(Command(com1, argument1, database));
		RNT(Command(com2, argument2, database));
		RNT(Command(com3, argument3, database));

		SECTION("Verifying giving arguments and comamnds for Person", "[Commands]") {

			std::string com1 = "VEHICLE";
			std::string argument1 = "  AS1231SF 9128    ";

			std::string com2 = "vehicle";
			std::string argument2 = "A5689XX 6889     ";

			std::string com3 = "VeHiClE";
			std::string argument3 = "   PS3723LL    899 ";

			Database database;

			Command exe1(com1, argument1, database);
			Command exe2(com2, argument2, database);
			Command exe3(com3, argument3, database);

			R(exe1.GetCommand() == "VEHICLE");
			R(exe1.GetFirstArg() == "AS1231SF");
			R(exe1.GetSecondArg() == "9128");

			R(exe2.GetCommand() == "VEHICLE");
			R(exe2.GetFirstArg() == "A5689XX");
			R(exe2.GetSecondArg() == "6889");

			R(exe3.GetCommand() == "VEHICLE");
			R(exe3.GetFirstArg() == "PS3723LL");
			R(exe3.GetSecondArg() == "899");

		}

	}

	SECTION("Inputting recognisable command ACQUIRE when there are no cars and people in the data base throws exception") {


		std::string com1 = "Acquire";
		std::string arg1 = "23123   AS1234AS";

		std::string com2 = "AcqUIre";
		std::string arg2 = "   23123   AS12 34AS         ";

		
		Database database;

		RT(Command(com1, arg1, database));
		RT(Command(com2, arg2, database));



	}

	SECTION("Inputting recognisable command ACQUIRE with Person's id not met in the database throws exception") {


		std::string com1 = "VEHICLE";
		std::string arg1 = "AS1234AS 12341";

		std::string com2 = "ACQUIRE";
		std::string arg2 = "68423 AS1234AS";

		Database database;
		
		Command exe1(com1, arg1, database);
		RT(Command(com2, arg2, database));




	}

	SECTION("Inputting recognisable command ACQUIRE with Vehicle's Registration number not met in the database throws exception") {

		std::string com1 = "PERSON";
		std::string arg1 = "\"Vanio\"   681";

		std::string com2 = "ACQUIRE";
		std::string arg2 = "681 AS12341234";
		

		Database database;

		Command exe1(com1, arg1, database);

		RT(Command(com2,arg2,database));


	}

	SECTION("Inputting recognisable command ACQUIRE with valid arguments and no dublication of objects doesnt throw exception", "[Commands]") {


		std::string com1 = "PERSON";
		std::string arg1 = "\"Vanio\"   681";


		std::string com2 = "PERSON";
		std::string arg2 = "\"Gancho Gancho Ganchev\"  182912";

		std::string com3 = "VEHICLE";
		std::string arg3 = "  AS1234AS   93812";

		std::string com4 = "VEHICLE";
		std::string arg4 = "KL9283KL 351";


		std::string com5 = "ACQUIRE";
		std::string arg5 = "681  AS1234AS  ";

		std::string com6 = "ACQUIRE";
		std::string arg6 = "182912  KL9283KL";

		Database database;

		//adding objects to database
		RNT(Command(com1, arg1, database));
		RNT(Command(com2, arg2, database));
		RNT(Command(com3, arg3, database));
		RNT(Command(com4, arg4, database));



		RNT(Command(com5, arg5, database));
		RNT(Command(com6, arg6, database));


		SECTION("Verifying giving arguments and comamnds for ACQUIRE", "[Commands]") {


			std::string com1 = "PERSON";
			std::string arg1 = "\"Vanio\"   681";


			std::string com2 = "PERSON";
			std::string arg2 = "\"Gancho Gancho Ganchev\"  182912";

			std::string com3 = "VEHICLE";
			std::string arg3 = "  AS1234AS   93812";

			std::string com4 = "VEHICLE";
			std::string arg4 = "KL9283KL 351";


			std::string com5 = "ACQUIRE";
			std::string arg5 = "681  AS1234AS  ";

			std::string com6 = "ACQUIRE";
			std::string arg6 = "182912  KL9283KL";

			Database database;

			//adding objects to database
			RNT(Command(com1, arg1, database));
			RNT(Command(com2, arg2, database));
			RNT(Command(com3, arg3, database));
			RNT(Command(com4, arg4, database));



			R(Command(com5, arg5, database).GetCommand() == "ACQUIRE");
			R(Command(com5, arg5, database).GetFirstArg() == "681");
			R(Command(com5, arg5, database).GetSecondArg() == "AS1234AS");


			R(Command(com6, arg6, database).GetCommand() == "ACQUIRE");
			R(Command(com6, arg6, database).GetFirstArg() == "182912");
			R(Command(com6, arg6, database).GetSecondArg() == "KL9283KL");




		}






	}

	SECTION("Inputting recognisable command RELEASE when there are no cars and person in the data base throws exception") {


		std::string com1 = "RELEASE";
		std::string arg1 = "23123   AS1234AS";

		std::string com2 = "RElEaSe";
		std::string arg2 = "   23123   AS1212SS         ";


		Database database;

		RT(Command(com1, arg1, database));
		RT(Command(com2, arg2, database));




	}

	SECTION("Inputting recognisable command RELEASE with Person's id not met in the database throws exception") {


		std::string com1 = "VEHICLE";
		std::string arg1 = "AS1234AS 12341";

		std::string com2 = "ACQUIRE";
		std::string arg2 = "68423 AS1234AS";

		Database database;

		Command exe1(com1, arg1, database);
		RT(Command(com2, arg2, database));




	}

	SECTION("Inputting recognisable command RELEASE with Vehicle's Registration number not met in the database throws exception") {

		std::string com1 = "PERSON";
		std::string arg1 = "\"Vanio\"   681";

		std::string com2 = "ACQUIRE";
		std::string arg2 = "681 AS12341234";


		Database database;

		Command exe1(com1, arg1, database);

		RT(Command(com2, arg2, database));


	}
	
	SECTION("Inputting recognisable command RELEASE with valid arguments and no dublication of objects doesnt throw exception", "[Commands]") {


		std::string com1 = "PERSON";
		std::string arg1 = "\"Vanio\"   681";


		std::string com2 = "PERSON";
		std::string arg2 = "\"Gancho Gancho Ganchev\"  182912";

		std::string com3 = "VEHICLE";
		std::string arg3 = "  AS1234AS   93812";

		std::string com4 = "VEHICLE";
		std::string arg4 = "KL9283KL 351";


		std::string com5 = "RELEASE";
		std::string arg5 = "681  AS1234AS  ";

		std::string com6 = "RELEASE";
		std::string arg6 = "182912  KL9283KL";

		Database database;

		//adding objects to database
		RNT(Command(com1, arg1, database));
		RNT(Command(com2, arg2, database));
		RNT(Command(com3, arg3, database));
		RNT(Command(com4, arg4, database));



		RNT(Command(com5, arg5, database));
		RNT(Command(com6, arg6, database));


		SECTION("Verifying giving arguments and comamnds for ACQUIRE", "[Commands]") {


			std::string com1 = "PERSON";
			std::string arg1 = "\"Vanio\"   681";


			std::string com2 = "PERSON";
			std::string arg2 = "\"Gancho Gancho Ganchev\"  182912";

			std::string com3 = "VEHICLE";
			std::string arg3 = "  AS1234AS   93812";

			std::string com4 = "VEHICLE";
			std::string arg4 = "KL9283KL 351";


			std::string com5 = "RELEASE";
			std::string arg5 = "681  AS1234AS  ";

			std::string com6 = "RELEASE";
			std::string arg6 = "182912  KL9283KL";

			Database database;

			//adding objects to database
			RNT(Command(com1, arg1, database));
			RNT(Command(com2, arg2, database));
			RNT(Command(com3, arg3, database));
			RNT(Command(com4, arg4, database));




			R(Command(com5, arg5, database).GetCommand() == "RELEASE");
			R(Command(com5, arg5, database).GetFirstArg() == "681");
			R(Command(com5, arg5, database).GetSecondArg() == "AS1234AS");


			R(Command(com6, arg6, database).GetCommand() == "RELEASE");
			R(Command(com6, arg6, database).GetFirstArg() == "182912");
			R(Command(com6, arg6, database).GetSecondArg() == "KL9283KL");




		}



	}

	SECTION("Inputting recognisable command REMOVE with valid arguments but no objects in the database throws exception", "[Commands]") {



		std::string com = "REMOVE";
		std::string arg1 = "123121";
		std::string arg2 = "AX5681AP";

		Database database;

		RT(Command(com, arg1, database));
		RT(Command(com, arg1, database));
	



	}


	SECTION("Inputting recognisable command REMOVE with valid arguments but argument doenst appeear in Database throws exception", "[Commands]") {


		std::string com1 = "Person";
		std::string arg1 = "\"Bai Ganu \"    1223";

		std::string com2 = "Vehicle";
		std::string arg2 = "AX1920OL 6547";


		std::string com3 = "RELEASE";
		std::string arg3 = "777";

		std::string com4 = "RElease";
		std::string arg4 = "JN8274PP";

		Database database;

		RNT(Command(com1,arg1,database));
		RNT(Command(com2, arg2, database));

		RT(Command(com3, arg3, database));
		RT(Command(com4, arg4, database));


	}
}







#endif
