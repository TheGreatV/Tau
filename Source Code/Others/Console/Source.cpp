#include "../Tau/Tau.hpp"
#include <iostream>


void main()
{
	Tau::Object x;

	x = nullptr;
	x = true;		std::cout << "true: " << (bool) x << std::endl;
	x = false;		std::cout << "false: " << (bool) x << std::endl;
	x = 5;			std::cout << "int -> int: " << (int) x << std::endl << "int -> float: " << (float) x << std::endl << "int -> double: " << (double) x << std::endl;
	x = 5.0;		std::cout << "float -> int: " << (int) x << std::endl << "float -> float: " << (float) x << std::endl << "float -> double: " << (double) x << std::endl;
	x = 5.0f;		std::cout << "double -> int: " << (int) x << std::endl << "double -> float: " << (float) x << std::endl << "double -> double: " << (double) x << std::endl;
	x = "text";		std::cout << "string: " << (std::string) x << std::endl;

	std::cout << "is string: " << x.Is<Tau::String>() << std::endl;
	std::cout << "is number: " << x.Is<Tau::Number>() << std::endl;

	x = 5;

	std::cout << "is string: " << x.Is<Tau::String>() << std::endl;
	std::cout << "is number: " << x.Is<Tau::Number>() << std::endl;

	std::system("pause");
}