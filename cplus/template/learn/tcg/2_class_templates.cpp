#include <catch.hpp>

#include <array>
#include <functional>
#include <iostream>
#include <type_traits>

namespace 
{

} // noname

TEST_CASE("2 class templates")
{
	SECTION("std::array")
	{
		std::array<int, 5> av;
	}
}
