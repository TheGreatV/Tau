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
				TEST_METHOD(TestMethod1)
				{
					SUT::Object x;
				}
			};
		}
	}
}