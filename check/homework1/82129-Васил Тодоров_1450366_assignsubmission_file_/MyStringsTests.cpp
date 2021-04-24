#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{

	TEST_CLASS(MyStringsTests)
	{
	public:
		TEST_METHOD(CheckInitializationWithEqOperator)
		{
			MyString name1("Ivan");
			MyString name2("Georgi");
			name1 = name2;
			Assert::AreEqual("Georgi", name1.c_str());
			Assert::AreEqual("Georgi", name2.c_str());
			name2.clear();
			Assert::AreNotEqual("Georgi", name2.c_str());
		}
		TEST_METHOD(CheckInitializationAtPosition)
		{
			MyString name("Ivan");
			Assert::AreEqual('I', name.at(0));
			Assert::AreEqual('v', name.at(1));
			Assert::AreEqual('a', name.at(2));
			Assert::AreEqual('n', name.at(3));
		}
		TEST_METHOD(CheckInitializationAtThrowExceptionOverLimit)
		{
			MyString name("Ivan");
			bool isCorect = false;
			try
			{
				name.at(4);
			}
			catch (...)
			{
				isCorect = true;
			}
			Assert::AreEqual(true, isCorect);
		}
		TEST_METHOD(CheckInitializationConstAtPosition)
		{
			const MyString name("Ivan");
			Assert::AreEqual('I', name.at(0));
			Assert::AreEqual('v', name.at(1));
			Assert::AreEqual('a', name.at(2));
			Assert::AreEqual('n', name.at(3));
		}
		TEST_METHOD(CheckInitializationConstAtThrowExceptionOverLimit)
		{
			const MyString name("Ivan");
			bool isCorect = false;
			try
			{
				name.at(4);
			}
			catch (...)
			{
				isCorect = true;
			}
			Assert::AreEqual(true, isCorect);
		}
		TEST_METHOD(CheckAfterInitializationSubscriptOperatorPosition)
		{
			MyString name("Ivan");
			Assert::AreEqual('I', name[0]);
			Assert::AreEqual('v', name[1]);
			Assert::AreEqual('a', name[2]);
			Assert::AreEqual('n', name[3]);
		}
		TEST_METHOD(CheckAfterInitializationConstSubscriptOperatorPosition)
		{
			const MyString name("Ivan");
			Assert::AreEqual('I', name[0]);
			Assert::AreEqual('v', name[1]);
			Assert::AreEqual('a', name[2]);
			Assert::AreEqual('n', name[3]);
		}
		TEST_METHOD(CheckInitializationFront)
		{
			MyString name("Ivan");
			Assert::AreEqual('I', name.front());
		}
		TEST_METHOD(CheckInitializationConstFront)
		{
			const MyString name("Ivan");
			Assert::AreEqual('I', name.front());
		}
		TEST_METHOD(CheckInitializationBack)
		{
			MyString name("Ivan");
			Assert::AreEqual('n', name.back());
		}
		TEST_METHOD(CheckInitializationConstBack)
		{
			MyString name("Ivan");
			Assert::AreEqual('n', name.back());
		}
		TEST_METHOD(CheckAfterInitializationEmpty)
		{
			MyString name("");
			Assert::AreEqual(true, name.empty());
			name = "Ant";
			Assert::AreEqual(false, name.empty());
		}
		TEST_METHOD(CheckAfterInitializationClear)
		{
			MyString name("Petar");
			name.clear();
			Assert::AreEqual("", name.c_str());
		}
		TEST_METHOD(CheckAfterInitializationPushBack)
		{
			MyString name("Petar");
			name.push_back('c');
			Assert::AreEqual("Petarc", name.c_str());
			name.push_back('d');
			name.push_back('a');
			Assert::AreEqual("Petarcda", name.c_str());
		}
		TEST_METHOD(CheckAfterInitializationPopBack)
		{
			MyString name("Petar");
			name.pop_back();
			Assert::AreEqual("Peta", name.c_str());
			name.pop_back();
			name.pop_back();
			Assert::AreEqual("Pe", name.c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorAdditionAssignmenChar)
		{
			MyString name("Petar");
			name += 'c';
			Assert::AreEqual("Petarc", name.c_str());
			name += 'd';
			name += 'a';
			Assert::AreEqual("Petarcda", name.c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorAdditionAssignmenMyString)
		{
			MyString name1("Petar");
			MyString name2("Ivan");
			MyString name3("");
			name1 += name2 += name2;
			Assert::AreEqual("PetarIvanIvan", name1.c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorAdditionAssignmenEmptyMyString)
		{
			MyString name1("Petar");
			MyString name2("");
			name1 += name2 += name2;
			Assert::AreEqual("Petar", name1.c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorAdditionChar)
		{
			MyString name1("Petar");
			Assert::AreEqual("Petarc", (name1 + 'c').c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorAdditionMyString)
		{
			MyString name1("Petar");
			MyString name2("Ivan");
			Assert::AreEqual("IvanPetar", (name2 + name1).c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorAdditionEmptyMyString)
		{
			MyString name1("Petar");
			MyString name2("");
			Assert::AreEqual("Petar", (name2 + name1).c_str());
		}
		TEST_METHOD(CheckAfterInitializationC_str)
		{
			MyString name1("Petar");
		}
		TEST_METHOD(CheckInitializationStringC_str)
		{
			MyString name("Ivan");
			Assert::AreEqual("Ivan", name.c_str());
		}
		TEST_METHOD(CheckAfterInitializationOperatorEqualTo)
		{
			MyString name1("Ivan");
			MyString name2("Ivan");
			Assert::AreEqual(true, name1 == name2);
		}
		TEST_METHOD(CheckAfterInitializationOperatorLessThan)
		{
			MyString name1("Asena");
			MyString name2("Boris");
			Assert::AreEqual(true, name1 < name2);
			Assert::AreEqual(false, name2 < name1);
			Assert::AreEqual(false, name1 < name1);

		}
	};
}
