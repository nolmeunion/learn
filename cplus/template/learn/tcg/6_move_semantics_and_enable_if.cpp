#include <catch.hpp>

#include <array>
#include <list>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

namespace 
{
class N {
public:
	N() {}
	N(N const&) = delete; // this class is neither copyable ...
	N(N&&) = delete; // ... nor movable
};

N make_N() {
	return N{}; // Always creates a conceptual temporary prior to C++17.
} // In C++17, no temporary is created at this point.

class X {
};

void g(X&) {
	std::cout << "g() for variable\n";
}
void g(X const&) {
	std::cout << "g() for constant\n";
}
void g(X&&) {
	std::cout << "g() for movable object\n";
}
// let f() perfect forward argument val to g():
template<typename T>
void f(T&& val) {
	g(std::forward<T>(val)); // call the right g() for any passed argument val
}

template <typename T>
using EnableT = std::enable_if_t<std::is_integral<T>::value>;

} // noname

TEST_CASE("6 move semantics and enable_if<>")
{
	SECTION("perfect forwarding")
	{
		X v;
		X const c; 

		f(v);
		f(c);
		f(X());
	}

	SECTION("prvalue in c++17")
	{
		auto n = make_N(); // 어떻게 동작하는가??

		// 이전에는 N{}을 만들고 n에 복사 생성해서 넣었다. 
		//  
	}

	SECTION("enable_if")
	{
		std::cout << typeid(EnableT<int>).name() << std::endl; // void 
	}
}
