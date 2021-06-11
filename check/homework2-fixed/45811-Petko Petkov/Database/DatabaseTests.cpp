#include "catch2.hpp"
#include<cassert>
#include "Database.h"

using db = Database;

/**
*	Since the Database class is singleton, testing it would mean that we have to
*	delete every record after using it in the current test case.
*	After every add in the end of the test there will be a delete call.
*/
TEST_CASE("Database deletePersonRecord", "[deletePersonRecord]") {
	SECTION("deletePersonRecord_OnValidId_RemovePersonRecordAccordingly") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Act
		db::getInstance().deletePersonRecord(10);

		//Assert
		REQUIRE(db::getInstance().findPersonById(10) == nullptr);
	}

	SECTION("deletePersonRecord_OnInvalidId_Throw") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE_THROWS(db::getInstance().deletePersonRecord(11));
		REQUIRE_THROWS_AS(db::getInstance().deletePersonRecord(11), std::invalid_argument);
		db::getInstance().deletePersonRecord(10);
	}
}

TEST_CASE("Database addPersonRecord", "[addPersonRecord]") {
	SECTION("addPersonRecord_NonExistingRecord_AddItAccordingly") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE(db::getInstance().findPersonById(10) != nullptr);
		db::getInstance().deletePersonRecord(10);
	}

	SECTION("addPersonRecord_ExistingRecord_Throw") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE_THROWS(db::getInstance().addPersonRecord("name", 10));
		REQUIRE_THROWS_AS(db::getInstance().addPersonRecord("name", 10), std::invalid_argument);
		db::getInstance().deletePersonRecord(10);
	}
}

TEST_CASE("Database findPersonById", "[findPersonById]") {
	SECTION("findPersonById_OnExistingRecord_ReturnPersonAccordingly") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE(db::getInstance().findPersonById(10) != nullptr);
		db::getInstance().deletePersonRecord(10);
	}

	SECTION("findPersonById_OnNonExistingRecord_ReturnNullptr") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE(db::getInstance().findPersonById(11) == nullptr);
		db::getInstance().deletePersonRecord(10);
	}

	SECTION("findPersonById_OnExistingRecord_HaveSamePropertiesAsInitialized") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Act
		Person* p = db::getInstance().findPersonById(10);

		//Assert
		REQUIRE(p->getID() == 10);
		REQUIRE(p->getRegistrationsCount() == 0);
		db::getInstance().deletePersonRecord(10);
	}
}

TEST_CASE("Database deleteVehicleRecord", "[deleteVehicleRecord]") {
	SECTION("deleteVehicleRecord_OnExistingVehicle_DeleteItAccordingly") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Act
		db::getInstance().deleteVehicleRecord("X1234BB");

		//Assert
		REQUIRE(db::getInstance().findVehicleByRegistration("X1234BB") == nullptr);
	}

	SECTION("deleteVehicleRecord_OnNonExistingVehicle_Throw") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE_THROWS(db::getInstance().deleteVehicleRecord("X4321AA"));
		REQUIRE_THROWS_AS(db::getInstance().deleteVehicleRecord("X4321AA"), std::invalid_argument);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}
}

TEST_CASE("Database addVehicleRecord", "[addVehicleRecord]") {
	SECTION("addVehicleRecord_NonExistingRecord_AddItAccordingly") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE(db::getInstance().findVehicleByRegistration("X1234BB") != nullptr);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("addVehicleRecord_NonExistingRecord_HaveSamePropertiesAsInitialized") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Act
		Vehicle* v = db::getInstance().findVehicleByRegistration("X1234BB");

		//Assert
		REQUIRE(v->getOwnerID() == 0);
		REQUIRE(v->getRegistration() == "X1234BB");
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("addVehicleRecord_ExistingRecord_Throw") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE_THROWS(db::getInstance().addVehicleRecord("X1234BB", "Audi"));
		REQUIRE_THROWS_AS(db::getInstance().addVehicleRecord("X1234BB", "Audi"), std::invalid_argument);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}
}

TEST_CASE("Database findVehicleByRegistration", "[findVehicleByRegistration]") {
	SECTION("findVehicleByRegistration_OnExistingRecord_ReturnVehicleAccordingly") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE(db::getInstance().findVehicleByRegistration("X1234BB") != nullptr);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("findVehicleByRegistration_OnNonExistingRecord_ReturnNullptr") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE(db::getInstance().findVehicleByRegistration("A1234AA") == nullptr);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("findPersonById_OnExistingRecord_HaveSamePropertiesAsInitialized") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Act
		Vehicle* v = db::getInstance().findVehicleByRegistration("X1234BB");

		//Assert
		REQUIRE(v->getOwnerID() == 0);
		REQUIRE(v->getRegistration() == "X1234BB");
		db::getInstance().deleteVehicleRecord("X1234BB");
	}
}

TEST_CASE("Database assignVehicleToOwner", "[assignVehicleToOwner]") {
	SECTION("assignVehicleToOwner_OnExistingVehiclesAndPerson_AcquireItProperly") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Act
		db::getInstance().assignVehicleToOwner(10, "X1234BB");

		//Assert
		REQUIRE(db::getInstance().findPersonById(10)->getRegistrationsCount() == 1);
		REQUIRE(db::getInstance().findPersonById(10)->getRegistrationAt(0) == "X1234BB");
		REQUIRE(db::getInstance().findVehicleByRegistration("X1234BB")->getOwnerID() == 10);
		REQUIRE(db::getInstance().findVehicleByRegistration("X1234BB")->getRegistration() == "X1234BB");
		db::getInstance().deletePersonRecord(10);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("assignVehicleToOwner_OnNonExistingVehicle_Throw") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE_THROWS(db::getInstance().assignVehicleToOwner(10, "A4321BB"));
		REQUIRE_THROWS_AS(db::getInstance().assignVehicleToOwner(10, "A4321BB"), std::invalid_argument);
		db::getInstance().deletePersonRecord(10);
	}

	SECTION("assignVehicleToOwner_OnNonExistingPerson_Throw") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE_THROWS(db::getInstance().assignVehicleToOwner(10, "X1234BB"));
		REQUIRE_THROWS_AS(db::getInstance().assignVehicleToOwner(10, "X1234BB"), std::invalid_argument);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("assignVehicleToOwner_OnNonExistingPerson_Throw") {
		//Arrange
		db::getInstance().addPersonRecord("James", 10);
		db::getInstance().addPersonRecord("Bond", 11);
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Act
		db::getInstance().assignVehicleToOwner(10, "X1234BB");
		db::getInstance().assignVehicleToOwner(11, "X1234BB");

		Person* p = db::getInstance().findPersonById(10);
		Person* b = db::getInstance().findPersonById(11);
		Vehicle* v = db::getInstance().findVehicleByRegistration("X1234BB");

		//Assert
		REQUIRE(p->getRegistrationsCount() == 0);
		REQUIRE(b->getRegistrationsCount() == 1);
		REQUIRE(v->getOwnerID() == 11);
		db::getInstance().deleteVehicleRecord("X1234BB");
		db::getInstance().deletePersonRecord(10);
		db::getInstance().deletePersonRecord(11);
	}
}

TEST_CASE("Database releaseVehicleOfOwner", "[releaseVehicleOfOwner]") {
	SECTION("releaseVehicleOfOwner_OnExistingPersonAndVehicle_ReleaseVehicleAccordingly") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Act
		db::getInstance().assignVehicleToOwner(10, "X1234BB");
		db::getInstance().releaseVehicleOfOwner(10, "X1234BB");
		Person* p = db::getInstance().findPersonById(10);
		Vehicle* v = db::getInstance().findVehicleByRegistration("X1234BB");

		//Assert
		REQUIRE(p->getRegistrationsCount() == 0);
		REQUIRE(v->getOwnerID() == 0);
		db::getInstance().deletePersonRecord(10);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}

	SECTION("releaseVehicleOfOwner_OnNonExistingVehicle_Throw") {
		//Arrange
		db::getInstance().addPersonRecord("name", 10);

		//Assert
		REQUIRE_THROWS(db::getInstance().releaseVehicleOfOwner(10, "A4321BB"));
		REQUIRE_THROWS_AS(db::getInstance().releaseVehicleOfOwner(10, "A4321BB"), std::invalid_argument);
		db::getInstance().deletePersonRecord(10);
	}

	SECTION("releaseVehicleOfOwner_OnNonExistingPerson_Throw") {
		//Arrange
		db::getInstance().addVehicleRecord("X1234BB", "Audi");

		//Assert
		REQUIRE_THROWS(db::getInstance().releaseVehicleOfOwner(10, "X1234BB"));
		REQUIRE_THROWS_AS(db::getInstance().releaseVehicleOfOwner(10, "X1234BB"), std::invalid_argument);
		db::getInstance().deleteVehicleRecord("X1234BB");
	}
}

TEST_CASE("Database isStringPersonID", "[isStringPersonID]") {
	SECTION("isStringPersonID_OnPersonID_True") {
		//Arrange
		db::getInstance().addPersonRecord("James", 12345);

		//Act
		bool isPersonId = db::getInstance().isStringPersonID("12345");

		//Assert
		REQUIRE(isPersonId == true);
		db::getInstance().deletePersonRecord(12345);
	}

	SECTION("isStringPersonID_OnNonPersonID_False") {
		//Arrange
		db::getInstance().addPersonRecord("James", 12345);

		//Act
		bool isPersonId = db::getInstance().isStringPersonID("X1234BB");

		//Assert
		REQUIRE(isPersonId == false);
		db::getInstance().deletePersonRecord(12345);
	}
}
