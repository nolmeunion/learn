#include <catch.hpp>

#include <array>
#include <list>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

namespace 
{

// print elements of an STL container
template<typename T>
void printcoll(T const& coll)
{
	typename T::const_iterator pos; // iterator to iterate over coll
	typename T::const_iterator end(coll.end()); // end position
	for (pos = coll.begin(); pos != end; ++pos) {
		std::cout << *pos << " ";
	}
	std::cout << "\n";
}

template<typename T>
class Base {
public:
	void bar();
};
template<typename T>
class Derived : Base<T> {
public:
	void foo() {
		this->bar(); // calls external bar() or error
	}
};

template <typename T>
constexpr T pi{ 3.1415926535897932385 };

} // noname

TEST_CASE("5 tricky basics")
{
	SECTION("keyword typename")
	{
		// typename has to be used whenever a name that depends 
		// on a template parameter is a type

		std::vector<int> v{ 1, 2, 3 };
		printcoll(v);

		std::list<int> lv{ 4, 5, 6 };
		printcoll(lv);
	}

	SECTION("zero initialization")
	{
		int v{};
		CHECK(v == 0);

		std::string sv{};
		CHECK(sv == "");

		void* p{};
		CHECK(p == nullptr);
	}

	SECTION("using this->")
	{
		Derived<int> dv;
	}

	SECTION("variable template")
	{
		auto f1 = pi<float>;
		auto d1 = pi<double>;

		CHECK(f1 > d1); // 반올림으로 float가 더 크다.
	}
}
