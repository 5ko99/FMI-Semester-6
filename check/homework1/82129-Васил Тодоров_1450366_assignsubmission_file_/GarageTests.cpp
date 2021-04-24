#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	void  assertVehiclesAreEqual(const Vehicle& vehicle1, const Vehicle& vehicle2)
	{
		Assert::AreEqual(vehicle1.registration(), vehicle2.registration());
		Assert::AreEqual(vehicle1.description(), vehicle2.description());
		Assert::AreEqual(vehicle1.space(), vehicle2.space());
	}
	void  assertVehiclesAreNotEqual(const Vehicle& vehicle1, const Vehicle& vehicle2)
	{
		Assert::AreNotEqual(vehicle1.registration(), vehicle2.registration());
		Assert::AreNotEqual(vehicle1.description(), vehicle2.description());
		Assert::AreNotEqual(vehicle1.space(), vehicle2.space());
	}
	TEST_CLASS(GarageTests)
	{
	public:
		TEST_METHOD(CheckInitialization)
		{
			Garage prime(4);
			Assert::AreEqual((size_t)0, prime.size());
		}

		TEST_METHOD(CheckWhenInitializedEmpty)
		{
			Garage prime(3);
			Assert::AreEqual(true, prime.empty());
		}

		TEST_METHOD(CheckWhenInitializedAt5Fails)
		{
			Garage prime(3);
			bool isFail = false;
			try
			{
				Vehicle truck = prime.at(5);
			}
			catch (...)
			{
				isFail = true;
			}
			Assert::AreEqual(true, isFail);
		}

		TEST_METHOD(CheckAfterInsertedVehicleSize)
		{
			Garage prime(3);
			Vehicle truck("reg1", "fdd", 2);
			prime.insert(truck);
			Assert::AreEqual((size_t)1, prime.size());
		}

		TEST_METHOD(CheckAfterInsertedVehicleClear)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg2", "desc2", 1);
			prime.insert(truck1);
			prime.insert(truck2);
			prime.clear();
			Assert::AreEqual((size_t)0, prime.size());
		}

		TEST_METHOD(CheckAfterInsertedTwiseSameRegisterVehicleFails)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg1", "fdd", 2);
			prime.insert(truck1);

			bool isFail = false;
			try
			{
				prime.insert(truck2);
			}
			catch (...)
			{
				isFail = true;
			}
			Assert::AreEqual(true, isFail);
		}

		TEST_METHOD(CheckAfterInsertedVehicleAt)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg2", "desc2", 1);
			prime.insert(truck1);
			prime.insert(truck2);
			Vehicle truckAt1 = prime.at(1);
			assertVehiclesAreEqual(truck2, truckAt1);
		}

		TEST_METHOD(CheckAfterInsertedVehicleEmpty)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			prime.insert(truck1);
			Assert::AreEqual(false, prime.empty());
		}

		TEST_METHOD(CheckAfterInsertedVehicleErase)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			prime.insert(truck1);
			prime.erase("reg1");
			Assert::AreEqual((size_t)0, prime.size());
		}

		TEST_METHOD(CheckAfterInsertedVehicleEraseFails)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			prime.insert(truck1);
			prime.erase("dddf");
			Assert::AreEqual((size_t)1, prime.size());
		}

		TEST_METHOD(CheckAfterInsertedVehicleFindWhenExists)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg2", "desc2", 1);
			prime.insert(truck1);
			prime.insert(truck2);
			Assert::AreEqual(true, &truck1 == prime.find("reg1"));
		}

		TEST_METHOD(CheckAfterInsertedVehicleFindWhenNotExists)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg2", "desc2", 1);
			prime.insert(truck1);
			prime.insert(truck2);
			Assert::AreEqual(true, nullptr == prime.find("dddffhdh"));
		}

		TEST_METHOD(CheckInitializationWithEqOperator)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg2", "desc2", 1);
			prime.insert(truck1);
			prime.insert(truck2);
			Garage modern(1);
			modern = prime;
			Assert::AreEqual(modern.size(), prime.size());
			assertVehiclesAreEqual(modern.at(0), prime.at(0));
			assertVehiclesAreEqual(modern.at(1), prime.at(1));
			prime.erase("reg1");
			assertVehiclesAreNotEqual(modern.at(0), prime.at(0));
		}

		TEST_METHOD(CheckInsertOverLimitFails)
		{
			Garage prime(1);
			Vehicle truck1("reg1", "fdd", 10);
			bool isFail = false;
			try
			{
				prime.insert(truck1);
			}
			catch (...)
			{
				isFail = true;
			}
			Assert::AreEqual(true, isFail);
		}

		// TODO: add tests for [] , with assert,and negative
		TEST_METHOD(CheckSubscriptPosition)
		{
			Garage prime(4);
			Vehicle truck1("reg1", "fdd", 2);
			Vehicle truck2("reg2", "desc2", 1);
			prime.insert(truck1);
			prime.insert(truck2);
			assertVehiclesAreEqual(prime[1], truck2);
		}

	};

}
