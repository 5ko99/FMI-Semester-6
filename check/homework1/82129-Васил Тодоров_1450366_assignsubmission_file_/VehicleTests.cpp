#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{

	TEST_CLASS(VehicleTests)
	{
	public:

		TEST_METHOD(CheckInitialization)
		{
			Vehicle car("reg2123c", "small", 1);
			Assert::AreEqual("reg2123c", car.registration());
			Assert::AreEqual("small", car.description());
			Assert::AreEqual((size_t)1, car.space());
		}
		TEST_METHOD(CheckWhenInitilizedRegistration)
		{
			Vehicle car("reg2123c", "small", 1);
			Assert::AreEqual("reg2123c", car.registration());
		}
		TEST_METHOD(CheckWhenInitilizedDescription)
		{
			Vehicle car("reg2123c", "large", 1);
			Assert::AreEqual("large", car.description());
		}
		TEST_METHOD(CheckWhenInitilizedSpace)
		{
			Vehicle car("reg2123c", "small", 5);
			Assert::AreEqual((size_t)5, car.space());
		}


	};
}
