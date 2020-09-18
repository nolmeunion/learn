#include <catch.hpp>

#include <array>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

namespace
{

class X
{
public:
	X(int v)
	{
		m_v = v;
	}

private: 
	int m_v{ 0 };
};

} // noname

TEST_CASE("modern cplus")
{
	SECTION("uniform initialization")
	{
		SECTION("int")
		{
			int a{ 3 };
			REQUIRE(a == 3);
		}

		SECTION("tuple")
		{
			std::tuple<int, int, float> v_tuple{ 1, 3, 5.0f };

			auto v1 = std::get<0>(v_tuple);
			REQUIRE(v1 == 1);

			auto v2 = std::get<1>(v_tuple);
			REQUIRE(v2 == 3);

			auto v3 = std::get<2>(v_tuple);
			REQUIRE(v3 == 5.0f);
		}

		SECTION("vector")
		{
			std::vector<int> v_vec{ 1, 3, 5, 7, 9, 11, 13 };
			REQUIRE(v_vec[1] == 3);
		}
	}

	SECTION("auto and decltype")
	{
		int i = 3;
		decltype(3.0f) iv = 5;
		REQUIRE(iv == 5);

		REQUIRE(typeid(iv) == typeid(decltype(3.0f)));

		// std::cout << typeid(iv).name() << std::endl; // float
		//
		// learn auto, decltype and type inference 
	}

	SECTION("variable scope")
	{
		SECTION("if")
		{
			if (auto fl = 3; 1 < 3) // who will use this?
			{
				REQUIRE(fl == 3);
			}
		}

		SECTION("not")
		{
			REQUIRE(((not false and 1 == 1) or 3 == 1));
		}
	}

	SECTION("bits in int")
	{
		int v = 7;

		int bit_count = 0;

		for (int i = 0; i < 32; ++i)
		{
			auto cb = v & 0x0000001;
			bit_count += cb;
			v = v >> 1;
		}

		REQUIRE(bit_count == 3);
	}

	SECTION("string")
	{
		auto s{ R"(Hello String)" };
		REQUIRE(s == "Hello String");

		auto si = std::to_string(3);
		REQUIRE(si == "3");

		auto ds = std::stod(si);
		REQUIRE(ds == 3);

		// exception:
		// - std::_Xout_of_range("test message");
		// - std::stod 내부에서 사용
	}

	SECTION("array")
	{
		std::array<double, 3> a_vs{ 1.1, 1.3, 1.5 };
		REQUIRE(a_vs[0] == 1.1);

	}

	SECTION("range based for")
	{
		std::vector<std::string> names{ "Arnold", "Howard", "Johnson", "Jack" };

		REQUIRE(names[0] == "Arnold");
		REQUIRE(names.size() == 4);

		int j = 1;

		for (auto i : { 1, 2, 3, 4 })
		{
			REQUIRE(i == j++);
		}
	}

	SECTION("constexpr")
	{
		// something that can be evaluated (expression) at compile time
	}

	SECTION("make_shared")
	{
		std::shared_ptr<X> p1{ new X{1} };


	}
}