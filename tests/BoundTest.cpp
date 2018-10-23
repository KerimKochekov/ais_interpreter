#define CATCH_CONFIG_MAIN

#include "Bound.hpp"
#include "UndefinedOperationException.hpp"
#include "catch.hpp"

TEST_CASE("Checks on Bound instances", "[Bound]") {
    domain::Bound i(domain::Infinity('+'));
    domain::Bound ii(10);
    domain::Bound iii((double) 10.3);
    domain::Bound iv(domain::Infinity('-'));
    domain::Bound v(0);

    REQUIRE((i.is_infinity()) == true);
    REQUIRE((ii.is_infinity()) == false);
    REQUIRE((iii.is_infinity()) == false);
    REQUIRE((iv.is_infinity()) == true);

    REQUIRE((i.is_integer()) == false);
    REQUIRE((ii.is_integer()) == true);
    REQUIRE((iii.is_integer()) == false);
    REQUIRE((iv.is_integer()) == false);

    REQUIRE((i.is_float()) == false);
    REQUIRE((ii.is_float()) == false);
    REQUIRE((iii.is_float()) == true);
    REQUIRE((iv.is_float()) == false);

    REQUIRE(i.getInfinityValue() == domain::Infinity('+'));
    REQUIRE(ii.getIntValue() == 10);
    REQUIRE(iii.getFloatValue() == (double) 10.3);
    REQUIRE(iv.getInfinityValue() == domain::Infinity('-'));

    REQUIRE((i.revertSign() == domain::Bound(domain::Infinity('-'))) == true);
    REQUIRE((ii.revertSign() == domain::Bound(-10)) == true);
    REQUIRE((iii.revertSign() == domain::Bound((double) -10.3)) == true);
    REQUIRE((i.revertSign() == domain::Bound(domain::Infinity('-'))) == true);

    SECTION("Addition between two bounds") {
        REQUIRE((i + i == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE((i + ii == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE((i + iii == domain::Bound(domain::Infinity('+'))) == true);

        REQUIRE((iv + iv == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iv + ii == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iv + iii == domain::Bound(domain::Infinity('-'))) == true);

        REQUIRE((ii + ii == domain::Bound(20)) == true);
        REQUIRE((ii + iii == domain::Bound((double) 20.3)) == true);
        REQUIRE((iii + iii == domain::Bound((double) 20.6)) == true);
    }

    SECTION("Subtraction between two bounds") {
        REQUIRE((i - ii == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE((i - iii == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE(ii - iv == domain::Bound(domain::Infinity('+')));
        REQUIRE((iii - iv == domain::Bound(domain::Infinity('+'))) == true);

        REQUIRE((iv - ii == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iv - iii == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((ii - i == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iii - i == domain::Bound(domain::Infinity('-'))) == true);

        REQUIRE((ii - ii == domain::Bound(0)) == true);
        REQUIRE((iii - ii == domain::Bound((double) 0.3)) == true);
        REQUIRE((iii - iii == domain::Bound((double) 0.0)) == true);
    }

    SECTION("Multiplication between two bounds") {
        REQUIRE((i * i == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE((i * ii == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE((i * iii == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE(
            (iv * iv).getInfinityValue().getSign() ==
            domain::Bound(domain::Infinity('+')).getInfinityValue().getSign());

        REQUIRE((iv * i == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iv * ii == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iv * iii == domain::Bound(domain::Infinity('-'))) == true);
    }

    SECTION("Division between two bounds") {
        REQUIRE((i / ii == domain::Bound(domain::Infinity('+'))) == true);
        REQUIRE((i / iii == domain::Bound(domain::Infinity('+'))) == true);

        REQUIRE((iv / ii == domain::Bound(domain::Infinity('-'))) == true);
        REQUIRE((iv / iii == domain::Bound(domain::Infinity('-'))) == true);

        REQUIRE((ii / ii == domain::Bound(1)) == true);
        REQUIRE((iii / iii == domain::Bound((double) 1.0)) == true);
    }

    SECTION("Bound comparation") {
        REQUIRE((ii < i) == true);
        REQUIRE((ii < iii) == true);
        REQUIRE((iii < i) == true);
        REQUIRE((iv < i) == true);
        REQUIRE((iv < ii) == true);
        REQUIRE((iv < iii) == true);
        REQUIRE((ii <= i) == true);
        REQUIRE((ii <= iii) == true);
        REQUIRE((iii <= i) == true);
        REQUIRE((iv <= i) == true);
        REQUIRE((iv <= ii) == true);
        REQUIRE((iv <= iii) == true);

        REQUIRE((i == i) == true);
        REQUIRE((ii == ii) == true);
        REQUIRE((iii == iii) == true);
        REQUIRE((iv == iv) == true);
        REQUIRE((i <= i) == true);
        REQUIRE((ii <= ii) == true);
        REQUIRE((iii <= iii) == true);
        REQUIRE((iv <= iv) == true);
        REQUIRE((i >= i) == true);
        REQUIRE((ii >= ii) == true);
        REQUIRE((iii >= iii) == true);
        REQUIRE((iv >= iv) == true);

        REQUIRE((i > ii) == true);
        REQUIRE((i > iii) == true);
        REQUIRE((i > iv) == true);
        REQUIRE((ii > iii) == false);
        REQUIRE((ii > iv) == true);
        REQUIRE((iii > iv) == true);
    }

    SECTION("Throws in Bound's operators") {
        REQUIRE_THROWS_AS(i + iv, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(iv + i, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(i - i, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(iv - iv, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(i / i, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(i / iv, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(iv / i, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(iv / iv, exceptions::UndefinedOperationException);

        REQUIRE_THROWS_AS(i / v, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii / v, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(iii / v, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(iv / v, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(v / v, exceptions::UndefinedOperationException);
    }
}
