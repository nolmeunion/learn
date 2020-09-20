#include <catch.hpp>
#include <functional>
#include <iostream>
#include <type_traits>

namespace 
{
template <typename T, typename U> 
auto max(const T a, const U b) // c++ 14, // c++ 11 -> decltype(a+b)
{
	return a > b ? a : b;
}

template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
{
	return b < a ? a : b;
}

template <typename T, typename U>
struct decay_equiv : std::is_same<typename std::decay<T>::type, U>::type
{
};

} // noname

TEST_CASE("1 function templates")
{
	SECTION("max")
	{
		CHECK(max(1, 3) == 3);
		CHECK(max(1.1, 3.3) == 3.3);
		CHECK(max(1, 3.1f) == 3.1f);

		std::string s1{ "mathematics" };
		std::string s2{ "math" };

		CHECK(max(s1, s2) == s1);

		CHECK(max(1.0, 3) == 3);
	}

	SECTION("decay")
	{
		std::cout << std::boolalpha
			<< decay_equiv<int, int>::value << '\n'
			<< decay_equiv<int&, int>::value << '\n'
			<< decay_equiv<int&&, int>::value << '\n'
			<< decay_equiv<const int&, int>::value << '\n'
			<< decay_equiv<int[2], int*>::value << '\n'
			<< decay_equiv<int(int), int(*)(int)>::value << '\n';
	}

	SECTION("ref, cref")
	{
	}
}