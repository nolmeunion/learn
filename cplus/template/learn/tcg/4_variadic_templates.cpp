#include <catch.hpp>

#include <array>
#include <functional>
#include <iostream>
#include <type_traits>

namespace 
{
void print()
{}

template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
	std::cout << firstArg << "\n";
	print(args...); // call print() for remaining arguments
}

} // noname

TEST_CASE("4 variadic templates")
{
	SECTION("simple examples")
	{
		print(1, "hello", 5.0f);
	}
}
