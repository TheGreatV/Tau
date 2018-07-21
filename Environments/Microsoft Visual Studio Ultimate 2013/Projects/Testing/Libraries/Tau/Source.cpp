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
					Assert::IsTrue(Parse("\"\"") == SUT::Object(""));
					Assert::IsTrue(Parse("\"abc123\"") == SUT::Object("abc123"));
					Assert::IsTrue(Parse("\"\\\"\"") == SUT::Object("\""));
					Assert::IsTrue(Parse("\"\\n\"") == SUT::Object("\n"));
					Assert::IsTrue(Parse("\"\\r\"") == SUT::Object("\r"));
					Assert::IsTrue(Parse("\"\\v\"") == SUT::Object("\v"));
					Assert::IsTrue(Parse("\"\\t\"") == SUT::Object("\t"));
					Assert::IsTrue(Parse("\"x\"   \"y\"   \"z\"") == SUT::Object("xyz"));
				}
				TEST_METHOD(Array)
				{
					Assert::IsTrue(Parse("array()") == SUT::Array());
					Assert::IsTrue(Parse("array(1,2,3)") == SUT::Array({ 1,2,3 }));
					Assert::IsTrue(Parse("array(1,2,3,)") == SUT::Array({ 1, 2, 3 }));
					Assert::IsTrue(Parse("array(array())") == SUT::Array(std::vector<SUT::Object>({ SUT::Array() })));
				}
				TEST_METHOD(Map)
				{
					Assert::IsTrue(Parse("map()") == SUT::Map());
					Assert::IsTrue(Parse("map(true:false)") == SUT::Map({ SUT::Pair(true, false) }));
					Assert::IsTrue(Parse("map(1:\"1\",2:\"2\")") == SUT::Map({ SUT::Pair(1, "1"), SUT::Pair(2, "2") }));
					Assert::IsTrue(Parse("map(\"x\":map())") == SUT::Map({ SUT::Pair("x", SUT::Map()) }));
				}
				TEST_METHOD(Binary_Hex)
				{
					Assert::IsTrue(Parse("hex()") == SUT::Binary::Hex(SUT::Binary::Value({})));
					Assert::IsTrue(Parse("hex( 0 1 0 2 )") == SUT::Binary::Hex(SUT::Binary::Value({1,2})));
					Assert::IsTrue(Parse("hex(00 01 02 03 04 05 06 07 08 09 0a 0A 0b 0B 0c 0C 0d 0D 0e 0E 0f 0F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0A, 0x0b, 0x0B, 0x0c, 0x0C, 0x0d, 0x0D, 0x0e, 0x0E, 0x0f, 0x0F })));
					Assert::IsTrue(Parse("hex(10 11 12 13 14 15 16 17 18 19 1a 1A 1b 1B 1c 1C 1d 1D 1e 1E 1f 1F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1A, 0x1b, 0x1B, 0x1c, 0x1C, 0x1d, 0x1D, 0x1e, 0x1E, 0x1f, 0x1F })));
					Assert::IsTrue(Parse("hex(20 21 22 23 24 25 26 27 28 29 2a 2A 2b 2B 2c 2C 2d 2D 2e 2E 2f 2F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2A, 0x2b, 0x2B, 0x2c, 0x2C, 0x2d, 0x2D, 0x2e, 0x2E, 0x2f, 0x2F })));
					Assert::IsTrue(Parse("hex(30 31 32 33 34 35 36 37 38 39 3a 3A 3b 3B 3c 3C 3d 3D 3e 3E 3f 3F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3A, 0x3b, 0x3B, 0x3c, 0x3C, 0x3d, 0x3D, 0x3e, 0x3E, 0x3f, 0x3F })));
					Assert::IsTrue(Parse("hex(40 41 42 43 44 45 46 47 48 49 4a 4A 4b 4B 4c 4C 4d 4D 4e 4E 4f 4F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4A, 0x4b, 0x4B, 0x4c, 0x4C, 0x4d, 0x4D, 0x4e, 0x4E, 0x4f, 0x4F })));
					Assert::IsTrue(Parse("hex(50 51 52 53 54 55 56 57 58 59 5a 5A 5b 5B 5c 5C 5d 5D 5e 5E 5f 5F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5A, 0x5b, 0x5B, 0x5c, 0x5C, 0x5d, 0x5D, 0x5e, 0x5E, 0x5f, 0x5F })));
					Assert::IsTrue(Parse("hex(60 61 62 63 64 65 66 67 68 69 6a 6A 6b 6B 6c 6C 6d 6D 6e 6E 6f 6F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6A, 0x6b, 0x6B, 0x6c, 0x6C, 0x6d, 0x6D, 0x6e, 0x6E, 0x6f, 0x6F })));
					Assert::IsTrue(Parse("hex(70 71 72 73 74 75 76 77 78 79 7a 7A 7b 7B 7c 7C 7d 7D 7e 7E 7f 7F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7A, 0x7b, 0x7B, 0x7c, 0x7C, 0x7d, 0x7D, 0x7e, 0x7E, 0x7f, 0x7F })));
					Assert::IsTrue(Parse("hex(80 81 82 83 84 85 86 87 88 89 8a 8A 8b 8B 8c 8C 8d 8D 8e 8E 8f 8F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8A, 0x8b, 0x8B, 0x8c, 0x8C, 0x8d, 0x8D, 0x8e, 0x8E, 0x8f, 0x8F })));
					Assert::IsTrue(Parse("hex(90 91 92 93 94 95 96 97 98 99 9a 9A 9b 9B 9c 9C 9d 9D 9e 9E 9f 9F)") == SUT::Binary::Hex(SUT::Binary::Value({ 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9A, 0x9b, 0x9B, 0x9c, 0x9C, 0x9d, 0x9D, 0x9e, 0x9E, 0x9f, 0x9F })));
					Assert::IsTrue(Parse("hex(a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa aA ab aB ac aC ad aD ae aE af aF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xaA, 0xab, 0xaB, 0xac, 0xaC, 0xad, 0xaD, 0xae, 0xaE, 0xaf, 0xaF })));
					Assert::IsTrue(Parse("hex(A0 A1 A2 A3 A4 A5 A6 A7 A8 A9 Aa AA Ab AB Ac AC Ad AD Ae AE Af AF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAa, 0xAA, 0xAb, 0xAB, 0xAc, 0xAC, 0xAd, 0xAD, 0xAe, 0xAE, 0xAf, 0xAF })));
					Assert::IsTrue(Parse("hex(b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bA bb bB bc bC bd bD be bE bf bF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbA, 0xbb, 0xbB, 0xbc, 0xbC, 0xbd, 0xbD, 0xbe, 0xbE, 0xbf, 0xbF })));
					Assert::IsTrue(Parse("hex(B0 B1 B2 B3 B4 B5 B6 B7 B8 B9 Ba BA Bb BB Bc BC Bd BD Be BE Bf BF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBa, 0xBA, 0xBb, 0xBB, 0xBc, 0xBC, 0xBd, 0xBD, 0xBe, 0xBE, 0xBf, 0xBF })));
					Assert::IsTrue(Parse("hex(c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cA cb cB cc cC cd cD ce cE cf cF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcA, 0xcb, 0xcB, 0xcc, 0xcC, 0xcd, 0xcD, 0xce, 0xcE, 0xcf, 0xcF })));
					Assert::IsTrue(Parse("hex(C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 Ca CA Cb CB Cc CC Cd CD Ce CE Cf CF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCa, 0xCA, 0xCb, 0xCB, 0xCc, 0xCC, 0xCd, 0xCD, 0xCe, 0xCE, 0xCf, 0xCF })));
					Assert::IsTrue(Parse("hex(d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 da dA db dB dc dC dd dD de dE df dF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdA, 0xdb, 0xdB, 0xdc, 0xdC, 0xdd, 0xdD, 0xde, 0xdE, 0xdf, 0xdF })));
					Assert::IsTrue(Parse("hex(D0 D1 D2 D3 D4 D5 D6 D7 D8 D9 Da DA Db DB Dc DC Dd DD De DE Df DF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDa, 0xDA, 0xDb, 0xDB, 0xDc, 0xDC, 0xDd, 0xDD, 0xDe, 0xDE, 0xDf, 0xDF })));
					Assert::IsTrue(Parse("hex(e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eA eb eB ec eC ed eD ee eE ef eF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeA, 0xeb, 0xeB, 0xec, 0xeC, 0xed, 0xeD, 0xee, 0xeE, 0xef, 0xeF })));
					Assert::IsTrue(Parse("hex(E0 E1 E2 E3 E4 E5 E6 E7 E8 E9 Ea EA Eb EB Ec EC Ed ED Ee EE Ef EF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEa, 0xEA, 0xEb, 0xEB, 0xEc, 0xEC, 0xEd, 0xED, 0xEe, 0xEE, 0xEf, 0xEF })));
					Assert::IsTrue(Parse("hex(f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fA fb fB fc fC fd fD fe fE ff fF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfA, 0xfb, 0xfB, 0xfc, 0xfC, 0xfd, 0xfD, 0xfe, 0xfE, 0xff, 0xfF })));
					Assert::IsTrue(Parse("hex(F0 F1 F2 F3 F4 F5 F6 F7 F8 F9 Fa FA Fb FB Fc FC Fd FD Fe FE Ff FF)") == SUT::Binary::Hex(SUT::Binary::Value({ 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFa, 0xFA, 0xFb, 0xFB, 0xFc, 0xFC, 0xFd, 0xFD, 0xFe, 0xFE, 0xFf, 0xFF })));
				}
			};
		}
	}
}