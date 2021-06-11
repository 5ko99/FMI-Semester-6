#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PersonUnitTests
{
	TEST_CLASS(PersonUnitTests)
	{
	public:

		TEST_METHOD(CheckLettersOnlyIsNotValid)
		{
			bool isCorect = false;
			try
			{
				Registration r("sadsad");
			}
			catch (...)
			{
				isCorect = true;
			}
			Assert::AreEqual(true, isCorect);

		}
	};
}
