#define CATCH_CONFIG_MAIN

#include "../include/FloatingPointAbstractInterval.hpp"
#include "../libs/catch2/catch.hpp"


TEST_CASE("Floating Point interval operations", "[FP operations]") {
    domain::FloatingPointAbstractInterval i(domain::Bound(3.5), domain::Bound(3.5));
    domain::FloatingPointAbstractInterval ii(domain::Bound(1.5), domain::Bound(4.2));
    domain::FloatingPointAbstractInterval iii(domain::Bound(domain::Infinity('-')),
                                              domain::Bound(domain::Infinity('+')));
    domain::FloatingPointAbstractInterval iv(domain::Bound(-1.3), domain::Bound(4.8));
    domain::FloatingPointAbstractInterval v(domain::Bound(0), domain::Bound(domain::Infinity('+')));

    SECTION("Arithmetic operations", "[Interval operations]") {
        auto res1 = i + ii;
        REQUIRE(res1.getLowerBound() == domain::Bound(5));
        REQUIRE(res1.getUpperBound() == domain::Bound(7.7));

        auto res2 = iii - iv;
        REQUIRE(res2.getUpperBound() == domain::Bound(domain::Infinity('+')));
        REQUIRE(res2.getLowerBound() == domain::Bound(domain::Infinity('-')));

        auto res3 = i * v;
        REQUIRE(res3.getLowerBound() == domain::Bound(0));
        REQUIRE(res3.getUpperBound() == domain::Bound(domain::Infinity('+')));

        auto res4 = v / i;
        REQUIRE(res4.getLowerBound() == domain::Bound(0));
        REQUIRE(res4.getUpperBound() == domain::Bound(domain::Infinity('+')));
    }

    SECTION("Widenings", "[Interval operations]") {
        auto wid1 = i.widening(v);
        REQUIRE(wid1.getLowerBound() == domain::Bound(domain::Infinity('-')));
        REQUIRE(wid1.getUpperBound() == domain::Bound(domain::Infinity('+')));

        auto wid2 = ii.widening(iii);
        REQUIRE(wid2.getUpperBound() == domain::Bound(domain::Infinity('+')));
        REQUIRE(wid2.getLowerBound() == domain::Bound(domain::Infinity('-')));
    }

    SECTION("Narrowings", "[Interval operations]") {
        auto nar1 = iii.narrowing(iv);
        REQUIRE(nar1.getLowerBound() == domain::Bound(-1.3));
        REQUIRE(nar1.getUpperBound() == domain::Bound(4.8));
    }
}