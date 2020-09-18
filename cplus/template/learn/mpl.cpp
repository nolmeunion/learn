#include <catch.hpp>

#include <array>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>
#include <type_traits>

namespace
{

template <int i, int j> 
struct mult
{
	const static int value = i * j;
};

template <int v> 
struct factorial
{
	const static int value = v * factorial<v - 1>::value;
};

template<> 
struct factorial<0>
{
	const static int value = 1;
};

} // noname

TEST_CASE("modern cplus. mpl")
{
	SECTION("simple function")
	{
		REQUIRE(mult<3, 4>::value == 12);
	}

	SECTION("factorial")
	{
		REQUIRE(factorial<10>::value == 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1);
	}

	SECTION("type traits")
	{
		REQUIRE(std::is_integral<int>::value);
		REQUIRE(std::is_same<int, int>::value);
		REQUIRE(std::is_same<int, short>::value == false);
	}
}
