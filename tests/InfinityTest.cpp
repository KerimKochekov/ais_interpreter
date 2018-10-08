#define CATCH_CONFIG_MAIN

#include "../include/Infinity.hpp"
#include "../include/UndefinedOperationException.hpp"
#include "../libs/catch2/catch.hpp"

TEST_CASE("Operations on Infinity instances", "[Infinity]") {
    domain::Infinity  i('+');
    domain::Infinity  ii('-');
    domain::Infinity* arr = new domain::Infinity[2]{ i, ii };

    REQUIRE(i.getSign() == 1);
    REQUIRE(ii.getSign() == 0);
    REQUIRE(i.isPositive());
    REQUIRE(!ii.isPositive());
    REQUIRE(!i.isNegative());
    REQUIRE(ii.isNegative());

    SECTION("Minimum and maximum between two infinities") {
        REQUIRE(domain::Infinity::min(arr).getSign() == 0);
        REQUIRE(domain::Infinity::max(arr).getSign() == 1);
    }

    delete[] arr;

    SECTION("Operations between two infinities") {
        REQUIRE((i + i).getSign() == 1);
        REQUIRE((ii + ii).getSign() == 0);
        REQUIRE_THROWS_AS(i + ii, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii + i, exceptions::UndefinedOperationException);

        REQUIRE_THROWS_AS(i - i, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii - ii, exceptions::UndefinedOperationException);
        REQUIRE((i - ii).getSign() == 1);
        REQUIRE((ii - i).getSign() == 0);

        REQUIRE((i * i).getSign() == 1);
        REQUIRE((ii * ii).getSign() == 1);
        REQUIRE((i * ii).getSign() == 0);
        REQUIRE((ii * i).getSign() == 0);

        REQUIRE_THROWS_AS(i / i, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii / ii, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(i / ii, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii / i, exceptions::UndefinedOperationException);
    }

    SECTION("Operations between infinity and int") {
        REQUIRE((i + 2).getSign() == 1);
        REQUIRE((ii + 2).getSign() == 0);
        REQUIRE((2 + i).getSign() == 1);
        REQUIRE((2 + ii).getSign() == 0);

        REQUIRE((i - 2).getSign() == 1);
        REQUIRE((ii - 2).getSign() == 0);
        REQUIRE((2 - i).getSign() == 0);
        REQUIRE((2 - ii).getSign() == 1);

        REQUIRE((i * 2).getSign() == 1);
        REQUIRE((ii * 2).getSign() == 0);
        REQUIRE((2 * i).getSign() == 1);
        REQUIRE((2 * ii).getSign() == 0);

        REQUIRE_THROWS_AS(i * 0, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii * 0, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(0 * ii, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(0 * i, exceptions::UndefinedOperationException);

        REQUIRE((i / 2).getSign() == 1);
        REQUIRE((ii / 2).getSign() == 0);
        REQUIRE((2 / i) == 0);
        REQUIRE((2 / ii) == 0);

        REQUIRE_THROWS_AS(i / 0, exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii / 0, exceptions::UndefinedOperationException);
    }

    SECTION("Operations between infinity and float") {
        REQUIRE((i + (float) 2.5).getSign() == 1);
        REQUIRE((ii + (float) 2.5).getSign() == 0);
        REQUIRE(((float) 2.5 + i).getSign() == 1);
        REQUIRE(((float) 2.5 + ii).getSign() == 0);

        REQUIRE((i - (float) 2.5).getSign() == 1);
        REQUIRE((ii - (float) 2.5).getSign() == 0);
        REQUIRE(((float) 2.5 - i).getSign() == 0);
        REQUIRE(((float) 2.5 - ii).getSign() == 1);

        REQUIRE((i * (float) 2.5).getSign() == 1);
        REQUIRE((ii * (float) 2.5).getSign() == 0);
        REQUIRE(((float) 2.5 * i).getSign() == 1);
        REQUIRE(((float) 2.5 * ii).getSign() == 0);

        REQUIRE_THROWS_AS(i * (float) 0,
                          exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii * (float) 0,
                          exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS((float) 0 * ii,
                          exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS((float) 0 * i,
                          exceptions::UndefinedOperationException);

        REQUIRE((i / (float) 2.5).getSign() == 1);
        REQUIRE((ii / (float) 2.5).getSign() == 0);
        REQUIRE(((float) 2.5 / i) == 0);
        REQUIRE(((float) 2.5 / ii) == 0);

        REQUIRE_THROWS_AS(i / (float) 0,
                          exceptions::UndefinedOperationException);
        REQUIRE_THROWS_AS(ii / (float) 0,
                          exceptions::UndefinedOperationException);
    }

    SECTION("comparison between two infinities") {
        REQUIRE((i == ii) == false);
        REQUIRE((ii == i) == false);
        REQUIRE((i == i) == true);
        REQUIRE((ii == ii) == true);

        REQUIRE((i != ii) == true);
        REQUIRE((ii != i) == true);
        REQUIRE((i != i) == false);
        REQUIRE((ii != ii) == false);

        REQUIRE((i < ii) == false);
        REQUIRE((ii < i) == true);
        REQUIRE((i < i) == false);
        REQUIRE((ii < ii) == false);

        REQUIRE((i <= ii) == false);
        REQUIRE((ii <= i) == true);
        REQUIRE((i <= i) == true);
        REQUIRE((ii <= ii) == true);

        REQUIRE((i > ii) == true);
        REQUIRE((ii > i) == false);
        REQUIRE((i > i) == false);
        REQUIRE((ii > ii) == false);

        REQUIRE((i >= ii) == true);
        REQUIRE((ii >= i) == false);
        REQUIRE((i >= i) == true);
        REQUIRE((ii >= ii) == true);
    }

    SECTION("comparison between infinity and int") {
        REQUIRE((i == 2) == false);
        REQUIRE((ii == -2) == false);
        REQUIRE((-2 == i) == false);
        REQUIRE((2 == ii) == false);

        REQUIRE((i != 2) == true);
        REQUIRE((ii != -2) == true);
        REQUIRE((-2 != i) == true);
        REQUIRE((2 != ii) == true);

        REQUIRE((i < 2) == false);
        REQUIRE((ii < -2) == true);
        REQUIRE((-2 < i) == true);
        REQUIRE((2 < ii) == false);

        REQUIRE((i <= -2) == false);
        REQUIRE((ii <= 2) == true);
        REQUIRE((2 <= i) == true);
        REQUIRE((-2 <= ii) == false);

        REQUIRE((i > 2) == true);
        REQUIRE((ii > -2) == false);
        REQUIRE((-2 > i) == false);
        REQUIRE((2 > ii) == true);

        REQUIRE((i >= 2) == true);
        REQUIRE((ii >= -2) == false);
        REQUIRE((-2 >= i) == false);
        REQUIRE((2 >= ii) == true);
    }

    SECTION("comparison between infinity and float") {
        REQUIRE((i == (float) 2.5) == false);
        REQUIRE((ii == (float) -2.5) == false);
        REQUIRE(((float) -2.5 == i) == false);
        REQUIRE(((float) 2.5 == ii) == false);

        REQUIRE((i != (float) 2.5) == true);
        REQUIRE((ii != (float) -2.5) == true);
        REQUIRE(((float) -2.5 != i) == true);
        REQUIRE(((float) 2.5 != ii) == true);

        REQUIRE((i < (float) 2.5) == false);
        REQUIRE((ii < (float) -2.5) == true);
        REQUIRE(((float) -2.5 < i) == true);
        REQUIRE(((float) 2.5 < ii) == false);

        REQUIRE((i <= (float) -2.5) == false);
        REQUIRE((ii <= (float) 2.5) == true);
        REQUIRE(((float) 2.5 <= i) == true);
        REQUIRE(((float) -2.5 <= ii) == false);

        REQUIRE((i > (float) 2.5) == true);
        REQUIRE((ii > (float) -2.5) == false);
        REQUIRE(((float) -2.5 > i) == false);
        REQUIRE(((float) 2.5 > ii) == true);

        REQUIRE((i >= (float) 2.5) == true);
        REQUIRE((ii >= (float) -2.5) == false);
        REQUIRE(((float) -2.5 >= i) == false);
        REQUIRE(((float) 2.5 >= ii) == true);
    }
}