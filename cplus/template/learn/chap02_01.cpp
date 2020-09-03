#include <catch.hpp>

namespace {
template <typename T>
T const& max(T const& a, T const& b)
{
	return a < b ? b : a;
}

int const& max(int const& a, int const& b)
{
	return a < b ? b : a;
}

} // noname

TEST_CASE("chap_02")
{
	SECTION("max_test")
	{
		REQUIRE(max(3, 5) == 5);
		auto rd = max(3.0, 5.1);

		REQUIRE(rd == 5.1);
	}

	SECTION("overloading_1") // �Ϲ� �Լ��� ���� ���
	{
		max(7, 42); // max �Ϲ� �Լ� ȣ��
		// max('a', 42.7); // ������ ���� 
	}

	SECTION("overloading_2")
	{
		max(7, 42); // max �Ϲ� �Լ� ȣ��
		max('a', 42.7); // max �Ϲ� �Լ� ȣ��
	}
}

