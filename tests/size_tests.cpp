#include "catch.hpp"

#include "../src/Size.h"

TEST_CASE("test size", "[Size]")
{
    io::Size2i s = { 100, 100 };
    REQUIRE(s.w == 100);
    REQUIRE(s.h == 100);
}