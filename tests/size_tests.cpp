#include "catch.hpp"

#include "../src/Size.h"

using namespace io;

TEST_CASE("basics", "[Size]")
{
    Size2i s0;
    Size2i s1 = { 100, 100 };
    Size2i s2(50, 50);
    Size2i s3 = s1;
    Size2i s4(s2);
    Size2f sf1 = { 100.0f, 100.0f };
    Size2f sf2 = sf1;
    Size2f sf3 = { 50.0f, 50.0f };
    
    REQUIRE(s0.w == 0);
    REQUIRE(s0.h == 0);
    REQUIRE(s1.w == 100);
    REQUIRE(s1.h == 100);
    REQUIRE(s2.w == 50);
    REQUIRE(s2.h == 50);
    REQUIRE(s3.w == 100);
    REQUIRE(s3.h == 100);
    REQUIRE(s4.w == 50);
    REQUIRE(s4.h == 50);
    REQUIRE(s1 == s3);
    REQUIRE(s1 != s2);
    REQUIRE(sf1.is_equal(sf2));
    REQUIRE(!sf1.is_equal(sf3));
}

TEST_CASE("maths", "[Size]")
{
    Size2i s = { 100, 100 };
    Size2i s2 = { 50, 50 };
    s += { 100, 100 };
    REQUIRE(s == Size2i(200, 200));
    s = s2 + s2;
    REQUIRE(s == Size2i(100, 100));
    s -= s2;
    REQUIRE(s == Size2i(50, 50));
    s = s - s * 2;
    REQUIRE(s == Size2i(-50, -50));
    s = -s;
    REQUIRE(s == Size2i(50, 50));
    s = s / 2;
    REQUIRE(s == Size2i(25, 25));
    s *= 5;
    REQUIRE(s == Size2i(125, 125));
    s /= 5;
    REQUIRE(s == Size2i(25, 25));
}