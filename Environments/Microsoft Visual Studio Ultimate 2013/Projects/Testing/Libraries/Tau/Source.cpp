#include "stdafx.h"
#include "CppUnitTest.h"

#include <../Tau/Tau.hpp>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	namespace Tau
	{
		namespace SUT = ::Tau; // System Under Test

		namespace ObjectRepresentation
		{
			TEST_CLASS(Smoke)
			{
			public:
				TEST_METHOD(None)
				{
					Assert::IsTrue(SUT::Object(nullptr) == SUT::Object(nullptr));
				}
				TEST_METHOD(Boolean)
				{
					Assert::IsTrue(SUT::Object(true) == SUT::Object(true));
					Assert::IsTrue(SUT::Object(false) == SUT::Object(false));
					Assert::IsTrue(SUT::Object(true) != SUT::Object(false));
					Assert::IsTrue(SUT::Object(false) != SUT::Object(true));
				}
				TEST_METHOD(Number)
				{
					Assert::IsTrue(SUT::Object(5) == SUT::Object(5));
					Assert::IsTrue(SUT::Object(5) != SUT::Object(10));
				}
				TEST_METHOD(String)
				{
					Assert::IsTrue(SUT::Object("text") == SUT::Object("text"));
					Assert::IsTrue(SUT::Object("text") != SUT::Object("text "));
				}
				TEST_METHOD(Array)
				{
					Assert::IsTrue(SUT::Array({ nullptr, true, 5, "text" }) == SUT::Array({ nullptr, true, 5, "text" }));
					Assert::IsTrue(SUT::Array({ nullptr, true, 5, "text" }) != SUT::Array({ nullptr, true, 10, "text" }));
					Assert::IsTrue(SUT::Array({ nullptr, true, 5, "text" }) != SUT::Array({ nullptr, true, 5, "text", 10 }));
				}
			};
		}
		namespace Parser
		{
			TEST_CLASS(Smoke)
			{
			protected:
				SUT::Object Parse(const std::string& input_)
				{
					return SUT::Parser().Parse(input_);
				}
			public:
				TEST_METHOD(None)
				{
					auto object = Parse("none");

					Assert::IsTrue(object == SUT::Object(nullptr));
				}
				TEST_METHOD(Boolean_True)
				{
					auto object = Parse("true");

					Assert::IsTrue(object == SUT::Object(true));
				}
				TEST_METHOD(Boolean_False)
				{
					auto object = Parse("false");

					Assert::IsTrue(object == SUT::Object(false));
				}
			};
		}
	}
}