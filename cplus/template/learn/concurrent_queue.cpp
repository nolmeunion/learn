#include <catch.hpp>

#include <array>
#include <concurrent_queue.h>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

TEST_CASE("concurernt queue")
{
	SECTION("basic interface")
	{
		Concurrency::concurrent_queue<int> cq;

		cq.push(3);

		int v = 0;

		cq.try_pop(v);
	}
}