#include <catch.hpp>
#include <algorithm>
#include <string_view>

namespace
{
template <class _Ty, class _Pr>
constexpr _Ty(max)(std::initializer_list<_Ty> _Ilist, _Pr _Pred) 
{
    // return leftmost/largest
    const _Ty* _Res = std::_Max_element_unchecked(_Ilist.begin(), _Ilist.end(), std::_Pass_fn(_Pred));
    return *_Res;
}

#pragma warning(push)
#pragma warning(disable : 28285) // (syntax error in SAL annotation, occurs when _Ty is not an integral type)
template <class _Ty>
_NODISCARD _Post_equal_to_(_Left < _Right ? _Right : _Left) constexpr const _Ty& (max)(
    const _Ty& _Left, const _Ty& _Right) noexcept(noexcept(_Left < _Right)) /* strengthened */ 
{
    // return larger of _Left and _Right
    return _Left < _Right ? _Right : _Left;
}
#pragma warning(pop)
} // noname

TEST_CASE("chap02_02")
{
	SECTION("stl max initializer list")
	{
        max({ 1, 2, 3 }, [](const int a1, const int a2) {
            return a1 < a2;
            });

        // initializer_list는 배열과 거의 동일하다. 원래 항목에서 복사생성된 배열로 봐도 된다. 
    }

    SECTION("max for numeric types")
    {
        REQUIRE(max(1, 3) == 3);

        // _Post_equal_to_는 SAL 구문이다. 
        // 
    }

    SECTION("noexcept")
    {
        REQUIRE(noexcept(1 < 3));
    }
}

