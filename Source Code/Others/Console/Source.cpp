#include "../Tau/Tau.hpp"
#include <iostream>


void main()
{
	Tau::Object x;

	/*x = nullptr;
	x = true;		std::cout << "true: " << (bool) x << std::endl;
	x = false;		std::cout << "false: " << (bool) x << std::endl;
	x = 5;			std::cout << "int -> int: " << (int) x << std::endl << "int -> float: " << (float) x << std::endl << "int -> double: " << (double) x << std::endl;
	x = 5.0;		std::cout << "float -> int: " << (int) x << std::endl << "float -> float: " << (float) x << std::endl << "float -> double: " << (double) x << std::endl;
	x = 5.0f;		std::cout << "double -> int: " << (int) x << std::endl << "double -> float: " << (float) x << std::endl << "double -> double: " << (double) x << std::endl;
	x = "text";		std::cout << "string: " << (std::string) x << std::endl;

	std::cout << "is string: " << x.Is<Tau::String>() << std::endl;
	std::cout << "is number: " << x.Is<Tau::Number>() << std::endl;

	std::cout << "string.Length: " << x.Length() << std::endl;

	x = 5;

	std::cout << "is string: " << x.Is<Tau::String>() << std::endl;
	std::cout << "is number: " << x.Is<Tau::Number>() << std::endl;
	std::cout << "x == 5: " << (x == Tau::Object(5)) << std::endl;

	x = Tau::Array();

	std::cout << "is array: " << x.Is<Tau::Array>() << std::endl;
	std::cout << "array.Length: " << x.Length() << std::endl;

	x.Add(5);
	
	std::cout << "array.Length: " << x.Length() << std::endl;*/
	
	/*x = Tau::Array({
		1,
		2,
		Tau::Array({
			3,
			4,
			5,
		}),
		6,
		7,
		8,
		9,
		nullptr,
		true,
		false,
		"text",
	});

	auto a = Tau::Array({
		1,
		true,
		"ololo",
		Tau::Array({
			1,
			2,
			3,
		}),
	});
	auto b = Tau::Array({
		1,
		true,
		"ololo",
		Tau::Array({
			1,
			2,
			3,
		}),
	});

	std::cout << "x: " << Tau::Stringifier().Stringify(x) << std::endl;
	std::cout << "a == b: " << (a == b) << std::endl;*/

	/*auto a = Tau::Map({
		Tau::Pair(nullptr, "text"),
		Tau::Pair(true, 5),
		Tau::Pair(5, true),
		Tau::Pair("text", nullptr),
		Tau::Pair("ololo", Tau::Array({
			1,
			2,
			3,
		})),
		Tau::Pair(Tau::Array({
			1,
			2,
			3,
		}), "ololo"),
	});
	auto b = Tau::Map({
		Tau::Pair(nullptr, "text"),
		Tau::Pair(true, 5),
		Tau::Pair(5, true),
		Tau::Pair("text", nullptr),
	});

	std::cout << "a: " << Tau::Stringifier().Stringify(a) << std::endl;

	std::cout << "a == b: " << (a == b) << std::endl;*/

	auto a = Tau::Binary::Hex();

	for (size_t i = 0; i < 16; ++i)
	{
		a.Data().push_back(i);
	}

	std::cout << "a: " << Tau::Stringifier().Stringify(a) << std::endl;

	std::system("pause");
}
