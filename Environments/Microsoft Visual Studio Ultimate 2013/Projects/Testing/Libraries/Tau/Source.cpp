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
				TEST_METHOD(Number_Integer_Decimal)
				{
					Assert::IsTrue(Parse("0") == SUT::Object(0));
					Assert::IsTrue(Parse("1") == SUT::Object(1));
					Assert::IsTrue(Parse("5") == SUT::Object(5));
					Assert::IsTrue(Parse("10") == SUT::Object(10));
					Assert::IsTrue(Parse("12345") == SUT::Object(12345));
					Assert::IsTrue(Parse("10 000 000") == SUT::Object(10000000));
					Assert::IsTrue(Parse("+0") == SUT::Object(0));
					Assert::IsTrue(Parse("+1") == SUT::Object(1));
					Assert::IsTrue(Parse("+100") == SUT::Object(100));
					Assert::IsTrue(Parse("-0") == SUT::Object(0));
					Assert::IsTrue(Parse("-1") == SUT::Object(-1));
					Assert::IsTrue(Parse("-100") == SUT::Object(-100));
				}
				TEST_METHOD(Number_Floating_Decimal)
				{
					Assert::IsTrue(Parse("0.0") == SUT::Object(0.0));
					Assert::IsTrue(Parse("1.0") == SUT::Object(1.0));
					Assert::IsTrue(Parse("5.0") == SUT::Object(5.0));
					Assert::IsTrue(Parse("10.0") == SUT::Object(10.0));
					Assert::IsTrue(Parse("12345.0") == SUT::Object(12345.0));
					Assert::IsTrue(Parse("10 000 000.0") == SUT::Object(10000000.0));
					Assert::IsTrue(Parse("+0.0") == SUT::Object(0.0));
					Assert::IsTrue(Parse("+1.0") == SUT::Object(1.0));
					Assert::IsTrue(Parse("+100.0") == SUT::Object(100.0));
					Assert::IsTrue(Parse("-0.0") == SUT::Object(0.0));
					Assert::IsTrue(Parse("-1.0") == SUT::Object(-1.0));
					Assert::IsTrue(Parse("-100.0") == SUT::Object(-100.0));
					Assert::IsTrue(Parse("12 3 4 . 5 67") == SUT::Object(1234.567));
				}
				TEST_METHOD(String)
				{
					Assert::IsTrue(Parse("\"abc123\"") == SUT::Object("abc123"));
					Assert::IsTrue(Parse("\"\\\"\"") == SUT::Object("\""));
					Assert::IsTrue(Parse("\"\\n\"") == SUT::Object("\n"));
					Assert::IsTrue(Parse("\"\\r\"") == SUT::Object("\r"));
					Assert::IsTrue(Parse("\"\\v\"") == SUT::Object("\v"));
					Assert::IsTrue(Parse("\"\\t\"") == SUT::Object("\t"));
					Assert::IsTrue(Parse("\"x\"   \"y\"   \"z\"") == SUT::Object("xyz"));
				}
			};
		}
	}
}