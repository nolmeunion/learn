#include <catch.hpp>

#include <array>
#include <string>
#include <functional>
#include <cmath>
#include <tuple>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
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

template <typename ...Args>
auto addup(Args... args)
{
	return (... + args);
}

template <typename Range, typename Function> 
void forEachRange(const Range& range, Function func)
{
	for (const auto& x : range) func(x);
}

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

	SECTION("variadic template")
	{
		SECTION("parameter pack")
		{
			// parameter pack expansion ... 

			REQUIRE(addup(2, 3, 4) == 9);
		}
	}

	SECTION("templates with ranges")
	{
		auto xs = std::vector<int>{ 1, 2, 3, 4, 5, 6, 7 };

		forEachRange(xs, [](int x) { std::cout << " x = " << x << std::endl; });
	}
}

namespace
{

// Check whether type is float point 
template<class T>
auto isFPNumber() -> bool {
	return false;
}
// Template specialization of isFPNumber for type float
template<> auto isFPNumber<float>() -> bool {
	return true;
}
// Template specialization of isFPNumber for type double 
template<> auto isFPNumber<double>() -> bool {
	return true;
}

template <class T> 
auto isFPNumber(T v) -> bool
{
	return isFPNumber<T>();
}


// Return name of a given type 
template<class Type>
auto TypeName() -> const std::string { return "unknown"; }

#define REGISTER_TYPE(type)  template<> \
        auto TypeName<type>() -> const std::string { return #type; } 

// Specialization for int type 
template<>
auto TypeName<int>() -> const std::string { return "int"; }

// Automate boilerplate code using macros.
REGISTER_TYPE(bool);
REGISTER_TYPE(std::string);
REGISTER_TYPE(const char*);
REGISTER_TYPE(float);
REGISTER_TYPE(double);
REGISTER_TYPE(long);
REGISTER_TYPE(unsigned);
REGISTER_TYPE(char);
REGISTER_TYPE(long long);


template<class A, class B>
struct type_equal {
	static bool get() { return false; }
	enum { value = 0 };
};

// Partial specialisation
template<class A>
struct type_equal<A, A> {
	static bool get() { return true; }
	enum { value = 1 };
};

} // noname

TEST_CASE("template specialization")
{
	SECTION("is float point number")
	{
		CHECK(isFPNumber<int>() == false);
		CHECK(isFPNumber<double>() == true);
		CHECK(isFPNumber(3.0));
	}

	SECTION("RTTI")
	{
		CHECK(TypeName<bool>() == "bool");
		CHECK(TypeName<double>() == "double");
	}

	SECTION("type equality")
	{
		CHECK(type_equal<int, int>::get() == true);
		CHECK(type_equal<int, float>::get() == false);
	}
}

namespace
{

template <class T>
using Action = std::function<T(int)>;

template<class T>
void doTimes(int n, Action<T> action) {
	for (int i = 0; i < n; i++)
		std::cout << " i = 0; x = " << action(i) << "\n";
}

} // noname


TEST_CASE("template type alias")
{
	SECTION("basic example")
	{
		doTimes<double>(3, [](int i) { return 3.0 * i + 4.5; });
	}
}

namespace
{

template<typename T>
void printTypes(const T& x) {
	std::cout << std::left << std::setw(15) << x
		<< std::setw(10) << std::right << " size = "
		<< std::setw(2) << sizeof(x) << "\n";
	std::clog << " [TRACE] Base case => x = " << x << "\n";
}

// Variadic template arguments 
template<typename T, typename ... Types>
void printTypes(const T& x, const Types ... args) {
	std::cout << std::left << std::setw(15) << x
		<< std::setw(10) << std::right << " size = "
		<< std::setw(2) << sizeof(x) << "\n";
	printTypes(args ...);
}

struct TypeInfo
{
	TypeInfo(const std::string& name, size_t hash_code, size_t size)
		: name(name),
		hash_code(hash_code),
		size(size)
	{
	}
	std::string		name;
	size_t			hash_code;
	size_t			size;
};

template<typename ... Types>
auto printTypesInfoFromRTTI() -> void
{
	auto tlist = std::vector<TypeInfo>{
			TypeInfo{
			   typeid(Types).name(),
			   typeid(Types).hash_code(),
			   sizeof(Types)
					} ... };

	std::cout << std::setw(5) << "Name"
		<< std::setw(5) << "Size"
		<< std::setw(15) << "Hash"
		<< "\n";
	std::stringstream ss;
	for (const auto& x : tlist) {
		ss.str("");
		ss.clear();
		ss << "0x" << std::hex << x.hash_code;
		std::cout << std::right
			<< std::setw(5) << x.name
			<< std::setw(5) << x.size
			<< std::setw(15) << ss.str()
			<< "\n";
	}
}

template<class T>
typename std::enable_if<std::is_integral<T>::value, void>::type
classifyType(T value) {
	std::cout << " Type = integral ; " << " 3 * value = " << 3 * value << std::endl;
}

// Second Overload of classifyType
template<class T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
classifyType(T value) {
	std::cout << " Type = floating point ; " << " 25% x value = " << 0.25 * value << std::endl;
}

} // noname

TEST_CASE("type traits")
{
	SECTION("is_integral")
	{
		CHECK(std::is_integral<int>::value);
	}

	SECTION("variadic template")
	{
		printTypes("hello world", 10, 'x', 20.23f, true, NAN);
	}

	SECTION("typeinfo")
	{
		printTypesInfoFromRTTI<int, float, std::vector<int>>();
	}

	SECTION("enable_if")
	{
		classifyType(20);
		classifyType(100L);
		classifyType('x');

		double z = 9.34;
		classifyType(z);
		float x = 3.1415f;
		classifyType(x);
	}
}


