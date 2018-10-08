#define CATCH_CONFIG_MAIN

#include "../include/IntegerAbstractInterval.hpp"
#include "../libs/catch2/catch.hpp"

TEST_CASE("Operations on IntegerInterval instances",
          "[IntegerAbstractInterval]") {

    domain::IntegerAbstractInterval i(domain::Bound(0), domain::Bound(1));
    domain::IntegerAbstractInterval ii(domain::Bound(domain::Infinity('-')), domain::Bound(domain::Infinity('+')));
    domain::IntegerAbstractInterval iii(domain::Bound(domain::Infinity('-')), domain::Bound(5));
    domain::IntegerAbstractInterval iv(domain::Bound(0), domain::Bound(domain::Infinity('+')));
    domain::IntegerAbstractInterval v(domain::Bound(-1), domain::Bound(1));
    domain::IntegerAbstractInterval vi(domain::Bound(1), domain::Bound(1));

    SECTION("Arithmetic operations", "[Interval operations]") {
        REQUIRE(i.getLowerBound().is_integer());
        REQUIRE(i.getUpperBound().is_integer());
        REQUIRE(ii.getLowerBound().is_infinity());

        auto res1 = i + v;
        REQUIRE(res1.getLowerBound() == domain::Bound(-1));
        REQUIRE(res1.getUpperBound() == domain::Bound(2));

        auto res2 = ii - v;
        REQUIRE(res2.getLowerBound() == domain::Bound(domain::Infinity('-')));
        REQUIRE(res2.getUpperBound() == domain::Bound(domain::Infinity('+')));

        auto res3 = iv * vi;
        REQUIRE(res3.getLowerBound() == domain::Bound(0));
        REQUIRE(res3.getUpperBound() == domain::Bound(domain::Infinity('+')));

        auto res4 = iii / v;
        REQUIRE(res4.getLowerBound() == domain::Bound(domain::Infinity('-')));
        REQUIRE(res4.getUpperBound() == domain::Bound(domain::Infinity('+')));
    }

    SECTION("Widenings", "[Interval operations]") {
        auto wid1 = iv.widening(i);
        REQUIRE(wid1.getLowerBound() == domain::Bound(0));
        REQUIRE(wid1.getUpperBound() == domain::Bound(domain::Infinity('+')));

        auto wid2 = iii.widening(v);
        REQUIRE(wid2.getLowerBound() == domain::Bound(domain::Infinity('-')));
        REQUIRE(wid2.getUpperBound() == domain::Bound(5));
    }

    SECTION("Narrowings", "[Interval operations]") {
        auto nar1 = ii.narrowing(iii);
        REQUIRE(nar1.getLowerBound() == domain::Bound(domain::Infinity('-')));
        REQUIRE(nar1.getUpperBound() == domain::Bound(5));
    }
}
