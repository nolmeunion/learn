#include <catch.hpp>

#include <array>
#include <list>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

namespace 
{
template <typename T> 
void printR(T const arg)
{
	std::cout << typeid(decltype(arg)).name() << std::endl;
}

} // noname

TEST_CASE("7 by value or by reference")
{
	SECTION("reference type")
	{
		printR("hi"); // char const [3]. 책은 char const (&) [3]로 나온다. 
		const char* h = "hi";
		printR(h);

		int arr[4];
		printR(arr);
	}

	SECTION("ref and cref")
	{
		std::string s{ "hello" };

		printR(std::cref(s));
	}
}
